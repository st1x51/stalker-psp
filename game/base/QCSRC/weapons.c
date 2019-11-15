void() BoltTouch =
{
	//sound (self, CHAN_WEAPON, "weapons/bounce.wav", 1, ATTN_NORM);	// bounce sound
	if (self.velocity == '0 0 0')
		self.avelocity = '0 0 0';
	remove(self);
};

void() ThrowBolt =
{
	local	entity bolt;
	bolt = spawn ();
	bolt.owner = self;
	bolt.movetype = MOVETYPE_BOUNCE;
	bolt.solid = SOLID_BBOX;
	bolt.classname = "bolt";
		
// set bolt speed	

	makevectors (self.v_angle);

	if (self.v_angle_x)
		bolt.velocity = v_forward*600 + v_up * 200;
	else
	{
		bolt.velocity = aim(self, 10000);
		bolt.velocity = bolt.velocity * random(200,400);
		bolt.velocity_z = 200;
	}

	bolt.avelocity = '100 100 100';

	bolt.angles = vectoangles(bolt.velocity);
	bolt.angles_x = random(0,360);
	bolt.angles_y = random(0,360);
	//bolt.touch = GrenadeTouch;
	
// set bolt duration
	bolt.nextthink = time + 3;
	bolt.think = BoltTouch;

	setmodel (bolt, "models/w_bolt.mdl");
	setsize (bolt, '0 0 0', '0 0 0');		
	setorigin (bolt, self.origin + v_forward*48);

};
void() KnifeAttack =
{
	local	vector	source;
	local	vector	org;
	local 	entity	targ;

	targ = self.enemy;
	
	makevectors (self.v_angle);
	source = self.origin + '0 0 28';
	traceline (source, source + v_forward*64, FALSE, self);
	
	org = trace_endpos - v_forward*4;

	float r = random();
	/*
	if (trace_ent == targ)
	{
		if (r < 0.5)
			sound (self, CHAN_WEAPON, "weapons/Wrench/Wrench_hit1.wav", 1, ATTN_NORM);
		else
			sound (self, CHAN_WEAPON, "weapons/Wrench/Wrench_hit2.wav", 1, ATTN_NORM);
	}
	else
	{
		if (r < 0.35)
			sound (self, CHAN_WEAPON, "weapons/Wrench/Wrench_hitbod1.wav", 1, ATTN_NORM);
		if (r < 0.65)
			sound (self, CHAN_WEAPON, "weapons/Wrench/Wrench_hitbod1.wav", 1, ATTN_NORM);
		else
			sound (self, CHAN_WEAPON, "weapons/Wrench/Wrench_hitbod1.wav", 1, ATTN_NORM);
	}
	*/
	if (trace_ent.takedamage)
	{			
		T_Damage (trace_ent, self, self, 25);
	}
	else
	{	// hit wall
		/*
		WriteByte (MSG_BROADCAST, SVC_TEMPENTITY);
		WriteByte (MSG_BROADCAST, TE_GUNSHOT);
		WriteCoord (MSG_BROADCAST, org_x);
		WriteCoord (MSG_BROADCAST, org_y);
		WriteCoord (MSG_BROADCAST, org_z);
		WriteShort (MSG_BROADCAST, etoi(trace_ent));
		*/
	}
};
void()UpdateWeapon=
{
	if(self.weapon == WEP_KNIFE)
	{
		self.weaponmodel = "models/v_knife.mdl";
		if(self.state == IDLE)
		{
			self.sequence = 0; //idle anim
			self.weaponframe = 0;
		}
		if(self.state == RUNNING)
		{
			self.sequence = 1; //running anim
			self.weaponframe = 0;	
		}
		self.currentammo = 0;
		self.ammo_shells = 0;
	}
	if(self.weapon == WEP_BOLT)
	{
		self.weaponmodel = "models/v_bolt.mdl";
		if(self.state == IDLE)
		{
			self.sequence = 0; //idle anim
			self.weaponframe = 0;
		}
		if(self.state == RUNNING)
		{
			self.sequence = 1; //running anim
			self.weaponframe = 0;	
		}
		self.currentammo = 0;
		self.ammo_shells = 0;
	}
	if(self.weapon == WEP_PM)
	{
		self.weaponmodel = "models/v_pm.mdl";
		if(self.state == IDLE)
		{
			self.sequence = 0; //idle anim
			self.weaponframe = 0;
		}
		if(self.state == RUNNING)
		{
			self.sequence = 3; //running anim
			self.weaponframe = 0;	
		}
		MaxSpreadX = 5;
		MaxSpreadY = 5;
		SpreadX = 2;
		SpreadY = 2;
		self.currentammo = self.pm_clip;
		self.ammo_shells = self.ammo_pm;
	}
	if(self.weapon == WEP_TOZBM)
	{
		self.weaponmodel = "models/v_toz_bm.mdl";
		if(self.state == IDLE)
		{
			self.sequence = 0; //idle anim
			self.weaponframe = 0;
		}
		if(self.state == RUNNING)
		{
			self.sequence = 2; //running anim
			self.weaponframe = 0;	
		}
		MaxSpreadX = 7;
		MaxSpreadY = 7;
		SpreadX = 5;
		SpreadY = 3;
		self.currentammo = self.tozbm_clip;
		self.ammo_shells = self.ammo_tozbm;
	}
	if(self.weapon == WEP_AKSU)
	{
		self.weaponmodel = "models/v_aksu.mdl";
		if(self.state == IDLE)
		{
			self.sequence = 0; //idle anim
			self.weaponframe = 0;
		}
		if(self.state == RUNNING)
		{
			self.sequence = 4; //running anim
			self.weaponframe = 0;	
		}
		MaxSpreadX = 7;
		MaxSpreadY = 7;
		SpreadX = 4;
		SpreadY = 2;
		self.currentammo = self.aksu_clip;
		self.ammo_shells = self.ammo_aksu;
	}

}
void()knife_attack=
{
	if(self.weaponframe == 58)
	{
		self.sequence = 0;
		self.weaponframe = 0;
		self.state = IDLE;
		return;
	}
	if(self.weaponframe == 20)
		KnifeAttack();
	self.weaponframe +=1;
	self.think = knife_attack;
	self.nextthink = time + 0.02;	
}
void()bolt_attack_end=
{
	if(self.weaponframe == 14)
	{
		self.sequence = 0;
		self.weaponframe = 0;
		self.state = IDLE;
		return;
	}
	self.weaponframe +=1;
	self.think = bolt_attack_end;
	self.nextthink = time + 0.02;		
}
void()bolt_attack=
{
	if(self.weaponframe == 19)
	{
		ThrowBolt();
		self.sequence = 5;
		self.weaponframe = 0;
		bolt_attack_end();
		return;
	}
	self.weaponframe +=1;
	self.think = bolt_attack;
	self.nextthink = time + 0.02;	
}
void()pm_attack_anim=
{
	if(self.weaponframe == 10)
	{
		self.sequence = 0;
		self.weaponframe = 0;
		self.state = IDLE;
		return;
	}
	self.weaponframe +=1;
	self.think = pm_attack_anim;
	self.nextthink = time + 0.02;	
}
void()aksu_attack_anim=
{
	if(self.weaponframe == 5)
	{
		self.sequence = 0;
		self.weaponframe = 0;
		self.state = IDLE;
		return;
	}
	self.weaponframe +=1;
	self.think = aksu_attack_anim;
	self.nextthink = time + 0.02;	
}
void()tozbm_attack_anim=
{
	if(self.weaponframe == 15)
	{
		self.sequence = 0;
		self.weaponframe = 0;
		self.state = IDLE;
		return;
	}
	self.weaponframe +=1;
	self.think = tozbm_attack_anim;
	self.nextthink = time + 0.02;	
}

void()PmReload=
{
	if(self.weaponframe == 80) 
	{
		self.sequence = 0;
		self.weaponframe = 0;
		UpdateWeapon();
		self.state = 0;
		return;
	}

	if(self.weaponframe  == 1)
		sound (self, CHAN_AUTO, "weapons/pm/pm_reload.wav", 1, ATTN_NORM);		
	
	self.weaponframe += 1;
	self.think = PmReload;
	self.nextthink = time + 0.04;
}


void()AksuReload=
{
	if(self.weaponframe == 90) 
	{
		self.sequence = 0;
		self.weaponframe = 0;
		UpdateWeapon();
		self.state = 0;
		return;
	}

	if(self.weaponframe  == 36)
		sound (self, CHAN_AUTO, "weapons/aksu/ak74u_reload.wav", 1, ATTN_NORM);		
	
	self.weaponframe += 1;
	self.think = AksuReload;
	self.nextthink = time + 0.03;
}
void()TozBMReload=
{
	if(self.weaponframe == 148) 
	{
		self.sequence = 0;
		self.weaponframe = 0;
		UpdateWeapon();
		self.state = 0;
		return;
	}

	//if(self.weaponframe  == 1)
	//	sound (self, CHAN_AUTO, "weapons/pm/pm_reload.wav", 1, ATTN_NORM);		
	
	self.weaponframe += 1;
	self.think = TozBMReload;
	self.nextthink = time + 0.04;
}

void(float r_frame)ReloadWeaponPm= 
{ 
	if(self.ammo_pm == 0)
	{
		self.state = IDLE;
		return;
	}
	if(self.pm_clip == 12)
		return;
	self.state = RELOADING;
	if(self.pm_fired >= self.ammo_pm) 
	{ 
		self.pm_clip += self.ammo_pm;
		self.ammo_pm = 0;
		UpdateWeapon(); 
		self.pm_fired = 0;
		self.sequence = 4;
		self.weaponframe = r_frame;
		PmReload();
		return; 
	} 
	self.ammo_pm -= self.pm_fired;
	self.pm_clip += self.pm_fired;
	UpdateWeapon(); 
	self.pm_fired = 0; 
	self.sequence = 4;
	self.weaponframe = r_frame;
	PmReload();
} 
	 
void(float r_frame)ReloadWeaponAksu= 
{ 
	if(self.ammo_aksu == 0)
	{
		self.state = IDLE;
		return;
	}
	if(self.aksu_clip == 30)
		return;
	self.state = RELOADING;
	if(self.aksu_fired >= self.ammo_aksu) 
	{ 
		self.aksu_clip += self.ammo_aksu;
		self.ammo_aksu = 0;
		UpdateWeapon(); 
		self.aksu_fired = 0;
		self.sequence = 1;
		self.weaponframe = r_frame;
		AksuReload();
		return; 
	} 
	self.ammo_aksu -= self.aksu_fired;
	self.aksu_clip += self.aksu_fired;
	UpdateWeapon(); 
	self.aksu_fired = 0; 
	self.sequence = 1;
	self.weaponframe = r_frame;
	AksuReload();
}
void(float r_frame)ReloadWeaponTozBM= 
{ 
	if(self.ammo_tozbm == 0)
	{
		self.state = IDLE;
		return;
	}
	if(self.tozbm_clip == 2)
		return;
	self.state = RELOADING;
	sound (self, CHAN_AUTO, "weapons/toz/toz34_reload.wav", 1, ATTN_NORM);
	if(self.tozbm_fired >= self.ammo_tozbm) 
	{ 
		self.tozbm_clip += self.ammo_tozbm;
		self.ammo_tozbm = 0;
		UpdateWeapon(); 
		self.tozbm_fired = 0;
		self.sequence = 4;
		self.weaponframe = r_frame;
		TozBMReload();
		return; 
	} 
	self.ammo_tozbm -= self.tozbm_fired;
	self.tozbm_clip += self.tozbm_fired;
	UpdateWeapon(); 
	self.tozbm_fired = 0; 
	self.sequence = 4;
	self.weaponframe = r_frame;
	TozBMReload();
}
void()pm_attack =
{
	if(self.pm_clip == 0)
	{
		ReloadWeaponPm(0); 
		return;
	}

	DefaultFire(1,12, "weapons/pm/pm_shoot.wav" );
	self.sequence = 5;
	self.weaponframe = 0;
	pm_attack_anim();
	self.effects = EF_MUZZLEFLASH;
	self.pm_clip -=1;
	self.pm_fired +=1;
	addparticle(p_muzzleflash,self.origin + self.view_ofs + v_forward*8 + (v_up*-0.5)+ (v_right*2),1,2,0.5,0,self.origin);
}
void()aksu_attack =
{
	if(self.aksu_clip == 0)
	{
		ReloadWeaponAksu(0); 
		return;
	}

	DefaultFire(1,12, "weapons/aksu/ak74u_shot_0.wav" );
	self.sequence = 7;
	self.weaponframe = 0;
	aksu_attack_anim();
	self.effects = EF_MUZZLEFLASH;
	self.aksu_clip -=1;
	self.aksu_fired +=1;
	addparticle(p_muzzleflash,self.origin + self.view_ofs + v_forward*8 + (v_up*-0.5)+ (v_right*0.5),1,2,0.5,0,self.origin);
	//addparticle(p_smoke,self.origin + self.view_ofs + v_forward*48 + (v_right*2),1,2,2,0,self.origin + self.view_ofs + v_forward*48); //smoke test
}
void()tozbm_attack =
{
	if(self.tozbm_clip == 0)
	{
		ReloadWeaponTozBM(0); 
		return;
	}
	local vector vecSrc,vecAcc,vecAim;
	sound (self, CHAN_AUTO, "weapons/toz/tm_toz34_shot.wav", 1, ATTN_NORM);
	vecSrc = self.origin + self.view_ofs;
	vecAcc = '0.08716 0.04362 0.00';
	vecAim = GetAutoaimVector(AUTOAIM_2DEGREES);
	FireBullets(9,vecSrc,vecAim,vecAcc,8192,6);
	self.sequence = 5;
	self.weaponframe = 0;
	tozbm_attack_anim();
	self.tozbm_clip -= 1;
	self.tozbm_fired += 1;
	self.currentammo -= 1;
	self.effects = EF_MUZZLEFLASH;
	addparticle(p_muzzleflash,self.origin + self.view_ofs + v_forward*8 + (v_up*-0.5)+ (v_right*1),1,2,0.5,0,self.origin);
}
void()WeaponAttack=
{
	self.show_hostile = time + 1;		// wake up other monsters
	if(self.weapon == WEP_KNIFE)
	{
		self.sequence = 6;
		self.weaponframe = 0;
		self.state = FIRING;
		sound (self, CHAN_WEAPON, "weapons/knife/knife_1.wav", 1, ATTN_NORM);
		knife_attack();
	}
	if(self.weapon == WEP_BOLT)
	{
		self.sequence = 4;
		self.weaponframe = 0;
		self.state = FIRING;
		bolt_attack();
	}
	if(self.weapon == WEP_PM)
	{
		self.state = FIRING;
		pm_attack();
	}
	if(self.weapon == WEP_TOZBM)
	{
		self.state = FIRING;
		tozbm_attack();
	}
	if(self.weapon == WEP_AKSU)
	{
		self.state = FIRING;
		aksu_attack();
	}
}
void()ChangeWeapon=
{
	if(self.state >= FIRING)
		return;
	while(1)
	{
		if(self.slotwep == BOLT)
		{
			self.slotwep = KNIFE;
			self.weapon = WEP_KNIFE;
			//goto update;
		}
		else if(self.slotwep == KNIFE)
		{
			self.slotwep = PRIMARY;
			self.weapon = self.primaryweapon;
			//goto update;
		}
		else if(self.slotwep == PRIMARY)
		{
			self.slotwep = SECONDARY;
			self.weapon = self.secondaryweapon;
			//goto update;
		}
		else if(self.slotwep == SECONDARY)
		{
			self.slotwep = BOLT;
			self.weapon = WEP_BOLT;
			//goto update;
		}
		if(self.weapon)
		{
			UpdateWeapon();
			return;
		}
	}
	/*
	if(self.weapon == WEP_KNIFE)
	{
		self.weapon = WEP_BOLT;
		goto update;
	}
	if(self.weapon == WEP_BOLT)
	{
		self.weapon = WEP_PM;
		goto update;
	}
		if(self.weapon == WEP_PM)
	{
		self.weapon = WEP_KNIFE;
		goto update;
	}
	*/
	//update:
	//UpdateWeapon();
}
void()WeaponFrame=
{
	if(self.state >= FIRING)
		return;
	if (self.button0)
		WeaponAttack ();	
}