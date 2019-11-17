#define AUTOAIM_2DEGREES  0.0348994967025
#define AUTOAIM_5DEGREES  0.08715574274766
#define AUTOAIM_8DEGREES  0.1391731009601
#define AUTOAIM_10DEGREES 0.1736481776669
vector(float flDelta) GetAutoaimVector =
{
		makevectors( self.v_angle + self.punchangle );
		return v_forward;
}
vector() GetGunPosition =
{
	local vector org;
	org = self.origin + self.view_ofs;
	return org;
}
float(entity targ, entity inflictor) CanDamage =
{
// bmodels need special checking because their origin is 0,0,0
	if (targ.movetype == MOVETYPE_PUSH)
	{
		traceline(inflictor.origin, 0.5 * (targ.absmin + targ.absmax), TRUE, self);
		if (trace_fraction == 1)
			return TRUE;
		if (trace_ent == targ)
			return TRUE;
		return FALSE;
	}
	
	traceline(inflictor.origin, targ.origin, TRUE, self);
	if (trace_fraction == 1)
		return TRUE;
	traceline(inflictor.origin, targ.origin + '15 15 0', TRUE, self);
	if (trace_fraction == 1)
		return TRUE;
	traceline(inflictor.origin, targ.origin + '-15 -15 0', TRUE, self);
	if (trace_fraction == 1)
		return TRUE;
	traceline(inflictor.origin, targ.origin + '-15 15 0', TRUE, self);
	if (trace_fraction == 1)
		return TRUE;
	traceline(inflictor.origin, targ.origin + '15 -15 0', TRUE, self);
	if (trace_fraction == 1)
		return TRUE;

	return FALSE;
};
/*
=-=-=-=-=
 Killed
=-=-=-=-=
*/
void(entity targ, entity attacker) Killed =
{
	local entity oself;

	if (targ.health < -99)
		targ.health = -99;		// don't let sbar look bad if a player

	targ.takedamage = DAMAGE_NO;
	targ.touch = SUB_Null;

	oself = self;
	self = targ; // self must be targ for th_die
	self.th_die ();
	self = oself;
};
/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
T_Damage

The damage is coming from inflictor, but get mad at attacker
This should be the only function that ever reduces health.
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

void(entity targ, entity inflictor, entity attacker, float damage) T_Damage=
{
    local	vector	dir;
    local	entity	oldself;


    if (!targ.takedamage)
        return;

// used by buttons and triggers to set activator for target firing
    damage_attacker = attacker;

// figure momentum add
    if ( (inflictor != world) && (targ.movetype == MOVETYPE_WALK) )
    {
        dir = targ.origin - (inflictor.absmin + inflictor.absmax) * 0.5;
        dir = normalize(dir);
        targ.velocity = targ.velocity + dir*damage*8;
    }

// check for godmode
    if (targ.flags & FL_GODMODE)
        return;

// add to the damage total for clients, which will be sent as a single
// message at the end of the frame
    if (targ.flags & FL_CLIENT)
    {
        targ.dmg_take = targ.dmg_take + damage;
        targ.dmg_save = targ.dmg_save + damage;
        targ.dmg_inflictor = inflictor;
    }

// team play damage avoidance
    if ( (teamplay == 1) && (targ.team > 0)&&(targ.team == attacker.team) )
        return;

// do the damage
    targ.health = targ.health - damage;

    if (targ.health <= 0)
    {
        Killed (targ, attacker);
        return;
    }

// react to the damage
    oldself = self;
    self = targ;

	if ( (self.flags & FL_MONSTER) && attacker != world)
	{
	// get mad unless of the same class (except for soldiers)
		if (self != attacker && attacker != self.enemy)
		{
			if ( (self.classname != attacker.classname) )
			{
				if (self.enemy.classname == "player")
					self.oldenemy = self.enemy;
				self.enemy = attacker;
				FoundTarget ();
			}
		}
	}
    if (self.th_pain)
        self.th_pain (attacker, damage);

    self = oldself;

};
/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
WaterMove

Can be used for clients or monsters
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

void() WaterMove =
{
    if (self.movetype == MOVETYPE_NOCLIP)
        return;

    if (self.health < 0)
        return;

    if (self.waterlevel != 3)
    {
        self.air_finished = time + 12;
        self.dmg = 2;
    }
    else if (self.air_finished < time && self.pain_finished < time)
    {   // drown!
        self.dmg = self.dmg + 2;

        if (self.dmg > 15)
            self.dmg = 10;

        T_Damage (self, world, world, self.dmg);
        self.pain_finished = time + 1;
    }

    if (self.watertype == CONTENT_LAVA && self.dmgtime < time)
    {   // do damage
        self.dmgtime = time + 0.2;
        T_Damage (self, world, world, 6*self.waterlevel);
    }
    else if (self.watertype == CONTENT_SLIME && self.dmgtime < time)
    {   // do damage
        self.dmgtime = time + 1;
        T_Damage (self, world, world, 4*self.waterlevel);
    }
};

float() crandom =
{
	return 2*(random() - 0.5);
};

void(vector org, vector vel, float damage) SpawnBlood =
{
	particle (org, vel*0.1, 73, damage*4);
};

entity	multi_ent;
float	multi_damage;
void() ClearMultiDamage =
{
	multi_ent = world;
	multi_damage = 0;
};

void() ApplyMultiDamage =
{
	if (!multi_ent)
		return;
	T_Damage (multi_ent, self, self, multi_damage);
};

void(entity hit, float damage) AddMultiDamage =
{
	if (!hit)
		return;
	
	if (hit != multi_ent)
	{
		ApplyMultiDamage ();
		multi_damage = damage;
		multi_ent = hit;
	}
	else
		multi_damage = multi_damage + damage;
};
void(float damage, vector dir) TraceAttack=
{
	local	vector	vel, org;
	
	vel = normalize(dir + v_up*crandom() + v_right*crandom());
	vel = vel + 2*trace_plane_normal;
	vel = vel * 200;

	org = trace_endpos - dir*4;

	if (trace_ent.takedamage)
	{
		//SpawnBlood (org, vel*0.2, damage);
		addparticle(p_blood1,org,1,10,5,0,vel*0.2);
		AddMultiDamage (trace_ent, damage);
	}
	else
	{
		WriteByte (MSG_BROADCAST, SVC_TEMPENTITY);
		WriteByte (MSG_BROADCAST, TE_GUNSHOT);
		WriteCoord (MSG_BROADCAST, org_x);
		WriteCoord (MSG_BROADCAST, org_y);
		WriteCoord (MSG_BROADCAST, org_z);
		WriteShort (MSG_BROADCAST, etoi(trace_ent));
		addparticle(p_smoke,org,1,2,0.8,0,self.origin);
	}
};
void(float cShots,vector vecSrc,vector vecDirShooting,vector vecSpread,float flDistance,float iDamage)FireBullets=
{
	local vector vecRight = v_right;
	local vector vecUp = v_up;
	local float x,y,z;
	local float newDamage = iDamage;
	
	ClearMultiDamage ();
	for(float iShot = 1; iShot <= cShots; iShot++)
	{
		
		do{
			x = RANDOM_LONG(-0.5,0.5) + RANDOM_LONG(-0.5,0.5);
			y = RANDOM_LONG(-0.5,0.5) + RANDOM_LONG(-0.5,0.5);
			z = x*x+y*y;
		} while(z>1);
	local vector vecDir = vecDirShooting + x * vecSpread_x * vecRight + y * vecSpread_y * vecUp;
	local vector vecEnd;
	vecEnd = vecSrc + vecDir * flDistance;
	traceline(vecSrc,vecEnd,0,self);
	if (trace_fraction != 1.0)
	{
		if(iDamage)
		{
			TraceAttack(iDamage,vecDir);
		}
		if(cShots == 1)
		{
			local float unit = iDamage;
			while(newDamage > 0)
			{
				if(pointcontents(trace_endpos + vecDir * iDamage) == CONTENT_SOLID)
					break;
				traceline(trace_endpos + vecDir * iDamage,vecSrc,0,self);
				if(trace_allsolid)
					break;
				WriteByte (MSG_BROADCAST, SVC_TEMPENTITY);
				WriteByte (MSG_BROADCAST, TE_GUNSHOT);
				WriteCoord (MSG_BROADCAST, trace_endpos_x);
				WriteCoord (MSG_BROADCAST, trace_endpos_y);
				WriteCoord (MSG_BROADCAST, trace_endpos_z);
				WriteShort (MSG_BROADCAST, etoi(trace_ent));
				newDamage /= 2;
				unit /= 2;
				vecSrc = trace_endpos;
				traceline(trace_endpos,vecEnd,0,self);
				newDamage -= vlen(trace_endpos - vecSrc) * 0.01;
				TraceAttack(newDamage,vecDir);
			}
		}
	}	
	}
	ApplyMultiDamage ();
}

void(float cShots,float damage,string soundpath)DefaultFire=
{
	local float m_iClip = self.currentammo;
	local float speed = vlen(self.velocity);
	if (m_iClip <= 0)
		return;
	if(soundpath)
		sound (self, CHAN_WEAPON, soundpath, 1, ATTN_NORM);
	cShots = mathlib_min(m_iClip,cShots);
	self.currentammo -= cShots;
	m_iClip -= cShots;
	local vector vecSrc;
	local vector vecAim;
	local vector vecAcc;
	vecSrc = GetGunPosition();
	vecAcc = '0 0 0';
	vecAim = GetAutoaimVector(AUTOAIM_2DEGREES);
	if(cShots != 1)
		vecAcc = [SpreadX / 100,SpreadY / 100,0];
	if(speed)
		vecAcc += [SpreadY / 5000,SpreadY / 5000,0] * speed;
	if(cShots == 1)
		vecAcc = vecAcc / 10;
	if ( !( self.flags & FL_ONGROUND ) )
		vecAcc += [SpreadY / 5000,SpreadY / 5000,0] * 250;

	FireBullets(cShots,vecSrc,vecAim,vecAcc,8192,damage);
	if(!LeftSpread)
		LeftSpread = 1;
	self.punchangle_x -= RANDOM_LONG(SpreadY / 2,SpreadY);
	self.punchangle_y += SpreadX * RANDOM_LONG(-1,1) / 2;
	if(self.punchangle_x < -MaxSpreadY)
	{
		self.punchangle_x = -MaxSpreadY + RANDOM_LONG(-2,2);
		self.punchangle_y += SpreadX * LeftSpread; 
	}
	
	if(self.punchangle_y <= -MaxSpreadX)
		LeftSpread = 1;
	else if(self.punchangle_y > MaxSpreadX)
		LeftSpread = -1;
}