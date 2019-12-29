/*
+------+
|Client|
+------+-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-+
| Scratch                                      Http://www.admdev.com/scratch |
+=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-+
| Handle's "clients" (eg, Players) connecting, disconnecting, etc.           |
+=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-+
*/
void()CheckImpulses;
void()WeaponFrame;
void() GetSinglePlayerParameters =
{
 
	local float readparms;
	local string readtext;
	if(cvar("saved1") == 1)
		readparms = fopen ("data/sp_params.bin", FILE_READ);	
	if(cvar("saved1") == 0)
		readparms = fopen ("data/sp_newparams.bin", FILE_READ);

	if (readparms < 0)//if file not found
	{
		objerror("Error: sp_parms.bin not found!\n");//error
		localcmd("disconnect");
		return;
	}
	//задействовать strzone?
	//health
	readtext = fgets(readparms);
	self.health  = stof(readtext);
	//stamina
 	readtext = fgets(readparms);
	self.stamina  = stof(readtext);
	//player items
	readtext = fgets(readparms);
	self.maxitems  = stof(readtext);
	//weather start
	readtext = fgets(readparms);
	weather  = stof(readtext);
	
	readtext = fgets(readparms);
	nightdaychanger.daynightlightlevel  = stof(readtext);
	
	readtext = fgets(readparms);
	nightdaychanger.lightchange  = stof(readtext);
	//weapons stuff
	readtext = fgets(readparms);
	self.slotwep  = stof(readtext);
	
	readtext = fgets(readparms);
	self.weapon  = stof(readtext);
	
	readtext = fgets(readparms);
	self.primaryweapon  = stof(readtext);
	
	readtext = fgets(readparms);
	self.secondaryweapon  = stof(readtext);
	//pm
	readtext = fgets(readparms);
	self.pm_clip  = stof(readtext);
	
	readtext = fgets(readparms);
	self.ammo_pm  = stof(readtext);
	
	readtext = fgets(readparms);
	self.pm_fired  = stof(readtext);	
	//toz
	readtext = fgets(readparms);
	self.tozbm_clip  = stof(readtext);
	
	readtext = fgets(readparms);
	self.ammo_tozbm  = stof(readtext);
	
	readtext = fgets(readparms);
	self.tozbm_fired  = stof(readtext);	
	//ak
	readtext = fgets(readparms);
	self.aksu_clip  = stof(readtext);	
	
	readtext = fgets(readparms);
	self.ammo_aksu  = stof(readtext);	
	
	readtext = fgets(readparms);
	self.aksu_fired  = stof(readtext);	
	fclose (readparms);
};
 
void() writefirst =
{
	local float    writeparms;
	local string    writethis;
	   
	writeparms = fopen ("data/sp_params.bin", FILE_WRITE);
	if (writeparms < 0)
	{
		objerror("Error: sp_params.bin missing!\n");
		localcmd("disconnect\n");
		return;
	}

	writethis = ftos(other.health);
	fputs (writeparms, writethis,"\n");
	
	writethis = ftos(other.stamina);
	fputs (writeparms, writethis,"\n");
	
	writethis = ftos(other.maxitems);
	fputs (writeparms, writethis,"\n");
	
	writethis = ftos(weather);
	fputs (writeparms, writethis,"\n");
	
	writethis = ftos(nightdaychanger.daynightlightlevel);
	fputs (writeparms, writethis,"\n");
	
	writethis = ftos(nightdaychanger.lightchange);
	fputs (writeparms, writethis,"\n");
	
	//weapons stuff
	writethis = ftos(other.slotwep);
	fputs (writeparms, writethis,"\n");
	
	writethis = ftos(other.weapon);
	fputs (writeparms, writethis,"\n");
	
	writethis = ftos(other.primaryweapon);
	fputs (writeparms, writethis,"\n");
	
	writethis = ftos(other.secondaryweapon);
	fputs (writeparms, writethis,"\n");
	//pm
	writethis = ftos(other.pm_clip);
	fputs (writeparms, writethis,"\n");
	
	writethis = ftos(other.ammo_pm);
	fputs (writeparms, writethis,"\n");
	
	writethis = ftos(other.pm_fired);
	fputs (writeparms, writethis,"\n");
	//tozbm
	writethis = ftos(other.tozbm_clip);
	fputs (writeparms, writethis,"\n");
	
	writethis = ftos(other.ammo_tozbm);
	fputs (writeparms, writethis,"\n");
	
	writethis = ftos(other.tozbm_fired);
	fputs (writeparms, writethis,"\n");
	
	writethis = ftos(other.aksu_clip);
	fputs (writeparms, writethis,"\n");
	
	writethis = ftos(other.ammo_aksu);
	fputs (writeparms, writethis,"\n");
	
	writethis = ftos(other.aksu_fired);
	fputs (writeparms, writethis,"\n");
	fclose (writeparms);
	bprint("Saving Parameters \n");
};
void() writeinventory =
{
	local float    writeparms;
	local string    writethis;
	   
	writeparms = fopen ("data/inventory.bin", FILE_WRITE);
	if (writeparms < 0)
	{
		objerror("Error: inventory.bin missing!\n");
		localcmd("disconnect\n");
		return;
	}
	
	local float k;
	for(k=1;k<MAX_ITEMS;k++)
	{		
		writethis = ftos(other.slot[k].isfull);
		fputs (writeparms, writethis,"\n");
		
		writethis = other.slot[k].netname;
		fputs (writeparms, writethis,"\n");
	}

	bprint("Saving Inventory \n");
	fclose (writeparms);
};
void() readinventory =
{
	local float readparms;
	local string readtext;
	if(cvar("saved1") == 1)
		readparms = fopen ("data/inventory.bin", FILE_READ);
	if(cvar("saved1") == 0)
	{
		readparms = fopen ("data/inventory_start.bin", FILE_READ);
		cvar_set("saved1","1");
	}
	
	if (readparms < 0)//if file not found
	{
		objerror("Error: inventory file not found!\n");//error
		localcmd("disconnect");
		return;
	}
	
 	local float k;
	for(k=1;k<MAX_ITEMS;k++)
	{	
		readtext = strzone (fgets(readparms));
		self.slot[k].isfull = stof(readtext);
		readtext = strzone (fgets(readparms));
		self.slot[k].netname  = readtext;
	}
	

	fclose (readparms);
	bprint("Inventory Loaded \n");
};
.float nextfootstep;

void() playerfootstep =
{
	local float r;

	if (self.deadflag) // not walking dead...
		return;
	if (!(self.flags & FL_ONGROUND))
		return;

	if (vlen(self.velocity) < 50)
		return;

	if (time < self.nextfootstep)
		return;
	if(self.sprinting)
		self.nextfootstep = time + 0.3;
	else
		self.nextfootstep = time + 0.4;
	if(self.incar)
	{
		sound(self, CHAN_AUTO, "car/apc_run.wav", 1, ATTN_IDLE);
		return;
	}
		
	r = randomlong(0,3);
	// ATTN_IDLE to make them short range
	if (r == 0)
	{
		if(sound_step1)
	    	sound(self, CHAN_AUTO, sound_step1, 1, ATTN_IDLE);
    }
	else if (r == 1)
	{
		if(sound_step2)
	    	sound(self, CHAN_AUTO, sound_step2, 1, ATTN_IDLE);
    }
	else if (r == 2)
	{
		if(sound_step3)
	    	sound(self, CHAN_AUTO, sound_step3, 1, ATTN_IDLE);
    }
	else if (r == 3)
	{
		if(sound_step4)
	    	sound(self, CHAN_AUTO, sound_step4, 1, ATTN_IDLE);
    }
};
void() PlayerUse =
{
	local entity pre_use,to_use;
	vector source,org;
	makevectors(self.v_angle);
	if ( !(self.flags & FL_USERELEASED) )
		return;		// don't pogo stick

    self.flags = self.flags - (self.flags & FL_USERELEASED);
	source = self.origin + '0 0 28';
	traceline(source, source + v_forward * 96, 0, self);
	if (trace_fraction == 1)
		return;
	org = trace_endpos - v_forward * 4;
	pre_use = spawn();
	pre_use.origin = org;
	to_use = findradius (pre_use.origin, 32);
	if(to_use != world)
	{
	   if((to_use.useflags & PL_SHORTUSE) || (to_use.useflags & PL_LONGUSE))
          SUB_FireTargetsEnt(to_use);
	}
	remove(pre_use);
	self.button1 = 0;
};

//player jump code
void() PlayerJump =
{
	local vector start, end;
	
	if (self.flags & FL_WATERJUMP)
		return;
	
	if (self.waterlevel >= 2)
	{
		if (self.watertype == CONTENT_WATER)
			self.velocity_z = 100;
		else if (self.watertype == CONTENT_SLIME)
			self.velocity_z = 80;
		else
			self.velocity_z = 50;
		return;
	}

	if (!(self.flags & FL_ONGROUND))
		return;

	if ( !(self.flags & FL_JUMPRELEASED) )
		return;		// don't pogo stick

	self.flags = self.flags - (self.flags & FL_JUMPRELEASED);
	self.flags = self.flags - FL_ONGROUND;	// don't stairwalk
	
	self.button2 = 0;
// player jumping sound
	sound (self, CHAN_BODY, "player/jump.wav", 1, ATTN_NORM);
	self.velocity_z = self.velocity_z + 270;
};
//Called when a client issues the 'kill' command
 void() ClientKill = {};
 //Called when a client connected to the server
 void() ClientConnect = {};
 //Called when a client disconnects from the server
 void() ClientDisconnect = {};
 //Called every frame, before physics.
.float anim_run_time;
.float anim_idle_time;
 void() WeaponIdle =
{
	if(time < self.anim_idle_time)
		return;
	if(self.state == IDLE)	
	{
		if(self.weapon == WEP_KNIFE)
		{
			self.sequence = 0;
			if(self.weaponframe == 179)	
				self.weaponframe = 0;
			self.anim_idle_time = time + 0.025;	
			self.weaponframe += 1;
			return;
		}
		if(self.weapon == WEP_BOLT)
		{
			self.sequence = 0;
			if(self.weaponframe == 45)	
				self.weaponframe = 0;
			self.anim_idle_time = time + 0.025;	
			self.weaponframe += 1;
			return;
		}
		if(self.weapon == WEP_PM)
		{
			self.sequence = 0;
			if(self.weaponframe == 55)	
				self.weaponframe = 0;
			self.anim_idle_time = time + 0.025;	
			self.weaponframe += 1;
			return;
		}
		if(self.weapon == WEP_TOZBM)
		{
			self.sequence = 0;
			if(self.weaponframe == 55)	
				self.weaponframe = 0;
			self.anim_idle_time = time + 0.025;	
			self.weaponframe += 1;
			return;
		}
		if(self.weapon == WEP_AKSU)
		{
			self.sequence = 0;
			if(self.weaponframe == 54)	
				self.weaponframe = 0;
			self.anim_idle_time = time + 0.025;	
			self.weaponframe += 1;
			return;
		}	
	}
}
 void() WeaponRun =
{
	if(time < self.anim_run_time)
		return;
	if(self.state == RUNNING)	
	{
		if(self.weapon == WEP_KNIFE)
		{
			self.sequence = 1;
			if(self.weaponframe == 19)	
				self.weaponframe = 0;
			self.anim_run_time = time + 0.025;	
			self.weaponframe += 1;
			return;
		}
		if(self.weapon == WEP_BOLT)
		{
			self.sequence = 1;
			if(self.weaponframe == 19)	
				self.weaponframe = 0;
			self.anim_run_time = time + 0.025;	
			self.weaponframe += 1;
			return;
		}
		if(self.weapon == WEP_PM)
		{
			self.sequence = 3;
			if(self.weaponframe == 19)	
				self.weaponframe = 0;
			self.anim_run_time = time + 0.025;	
			self.weaponframe += 1;
			return;
		}
		if(self.weapon == WEP_TOZBM)
		{
			self.sequence = 2;
			if(self.weaponframe == 19)	
				self.weaponframe = 0;
			self.anim_run_time = time + 0.025;	
			self.weaponframe += 1;
			return;
		}
		if(self.weapon == WEP_AKSU)
		{
			self.sequence = 4;
			if(self.weaponframe == 19)	
				self.weaponframe = 0;
			self.anim_run_time = time + 0.025;	
			self.weaponframe += 1;
			return;
		}
	}
	WeaponIdle();
}
void()TraceTexure=
{
    local vector start;
    local vector end;
    local vector end_player;
    
	end_player = self.origin;

	// Straight down
	end_player_z = end_player_z - 64;
	
	traceline (self.origin, end_player, TRUE, self);
	if (trace_fraction == 1.0)
		return;

	start = trace_endpos + trace_plane_normal * (-8);
	end = trace_endpos + trace_plane_normal * 8;

    local string trace_texture;
	trace_texture = tracematerial( trace_ent, start, end );

	if(trace_texture == "D")
	{
    	sound_step1 = "player/foot/dirt1.wav";
    	sound_step2 = "player/foot/dirt2.wav";
    	sound_step3 = "player/foot/dirt3.wav";
    	sound_step4 = "player/foot/dirt4.wav";
    }
	else if(trace_texture == "L")
	{
    	sound_step1 = "player/foot/ladder1.wav";
    	sound_step2 = "player/foot/ladder2.wav";
    	sound_step3 = "player/foot/ladder3.wav";
    	sound_step4 = "player/foot/ladder4.wav";
    }
	else if(trace_texture == "M")
	{
    	sound_step1 = "player/foot/metal1.wav";
    	sound_step2 = "player/foot/metal2.wav";
    	sound_step3 = "player/foot/metal3.wav";
    	sound_step4 = "player/foot/metal4.wav";
    }
	else if(trace_texture == "S")
	{
    	sound_step1 = "player/foot/slosh1.wav";
    	sound_step2 = "player/foot/slosh2.wav";
    	sound_step3 = "player/foot/slosh3.wav";
    	sound_step4 = "player/foot/slosh4.wav";
    }
	else if(trace_texture == "T")
	{
    	sound_step1 = "player/foot/tile1.wav";
    	sound_step2 = "player/foot/tile2.wav";
    	sound_step3 = "player/foot/tile3.wav";
    	sound_step4 = "player/foot/tile4.wav";
    }
	else if(trace_texture == "W")
	{
    	sound_step1 = "player/foot/wood1.wav";
    	sound_step2 = "player/foot/wood2.wav";
    	sound_step3 = "player/foot/wood3.wav";
    	sound_step4 = "player/foot/wood4.wav";
    }
	else 
	{
    	sound_step1 = "player/foot/default1.wav";
    	sound_step2 = "player/foot/default2.wav";
    	sound_step3 = "player/foot/default3.wav";
    	sound_step4 = "player/foot/default4.wav";
	}
}
.float push_fast_time,rotate_time;
.float carspeed;
.float value;
void() AngleForSurface =
{
	local vector x1;
	local vector x2;
	local vector z1;
	local vector z2;
	local vector v;

	if (!(self.flags & FL_ONGROUND))
	{
		return;
	}
	makevectors(self.angles);
	traceline((self.origin + (v_forward * 8)), ((self.origin + (v_forward * 8)) - '0 0 64'), TRUE, self);
	if ((trace_fraction == 1))
	{
		return;
	}
	x1 = trace_endpos;
	traceline((self.origin - (v_forward * 8)), ((self.origin - (v_forward * 8)) - '0 0 64'), TRUE, self);
	if ((trace_fraction == 1))
	{
		return;
	}
	x2 = trace_endpos;
	traceline((self.origin - (v_right * 8)), ((self.origin - (v_right * 8)) - '0 0 64'), TRUE, self);
	if ((trace_fraction == 1))
	{
		return;
	}
	z1 = trace_endpos;
	traceline((self.origin + (v_right * 8)), ((self.origin + (v_right * 8)) - '0 0 64'), TRUE, self);
	if ((trace_fraction == 1))
	{
		return;
	}
	z2 = trace_endpos;
	v = normalize((x1 - x2));
	v = vectoangles(v);
	self.angles_x = v_x;
	v = normalize((z1 - z2));
	v = vectoangles(v);
	self.angles_z = v_x;
};
//-------------------------
void() car_drive =
//-------------------------
{
local vector 	new_vel;

	if (self.flags & FL_ONGROUND)			//don't drive in air
	{	
		makevectors(self.angles);
		new_vel_x = self.velocity_x;				//use new_vel to seperate x and y...
 		new_vel_y = self.velocity_y;				//...from z
		new_vel = self.carspeed * v_forward;		//only forward
		if(self.rotate_time > time)
			self.carspeed +=1;
		else
			self.carspeed -=5;
		if(self.carspeed <=0)
			self.carspeed = 0;	//stop
		if (self.push_fast_time - 0.5 > time)			//if player pressed
		{								//fire key. pause for 1 seconds
			new_vel = self.carspeed * v_forward;			//faster forward
		}

		self.velocity_x = new_vel_x ;				//don't change up or down movement
		self.velocity_y = new_vel_y;				//
		if(self.carspeed >= 250)
		{
			self.carspeed = 250;
		}	
		AngleForSurface();
	}			
	bprint(ftos(self.ideal_yaw)),"\n";
};

void() PlayerPreThink = 
{
	if(self.incar)
	{	
		if(self.carspeed)
			cvar_set("cl_yawspeed","30");
		if(self.carspeed >=150)
			cvar_set("cl_yawspeed","50");
		if(!self.carspeed)
			cvar_set("cl_yawspeed","0");
		if(self.button0)
		{
			self.push_fast_time = time + 1;	
			if(self.value < 50)
				self.rotate_time = time + 0.25;
			else
				self.rotate_time = time + 0.5;
		}

		car_drive();
	}
	if ((self.stamina_time < time) &&  self.sprinting == FALSE)
    {
	   self.stamina_time = time + 2; //даем игроку отдышаться и восстановить стамину
	   if(self.stamina < 10 && self.deadflag == DEAD_NO)
	   {
		   self.stamina += 1;
	   }
	   else if(self.stamina > 10)
	   {
		   self.stamina = 10;
	   }
    }
    if ((self.stamina_time < time) &&  self.sprinting == TRUE)
    {
	   self.stamina_time = time + 1;//каждую секунду бега уменьшаем стамину
	   self.stamina -= 1;
    }
	WeaponRun();
	WeaponIdle();
	SetClientFrame ();
	WaterMove ();
	CheckImpulses();
	TraceTexure();
		
};
.float detector_time;
float counttime;
entity anomaly;
void()detector=
{
	vector anomaly_len;
	anomaly = findradius(self.origin,400);
	while (anomaly)
	{

		if(anomaly.classname == "item_battery" )
		{	
			anomaly_len = self.origin - anomaly.origin;
			counttime = vlen(anomaly_len) / 400;
			if (self.detector_time < time)
			{
				sound (self, CHAN_BODY, "detectors/da-2_beep1.wav", 1, ATTN_STATIC);
				self.detector_time = time + counttime;
			}
		}
		anomaly = anomaly.chain;
	}
}
 //Called every frame, AFTER physics.
 void() PlayerPostThink = 
 {
	if (self.deadflag)
		return;
	 if(self.velocity == '0 0 0' && self.state == RUNNING)
	 {
		self.sprint_time = time;
		self.sprinting = FALSE;   
		self.state = IDLE;
	 }
	if(self.velocity)
		self.pl_state = MOVE;
	else
		self.pl_state = STAY;
	if(self.velocity && self.state == RUNNING)
		self.pl_state = RUN;
	WeaponFrame ();
   if (self.sprint_time > time)
   {
      if ((self.flags) & FL_ONGROUND)
      {   
         if ((self.sprint_time - time) <= 0.1) // 0.1 fixes sound bug:)
		 {
			sound (self, CHAN_BODY, "player/breath.wav", 1, ATTN_STATIC);
			self.state = IDLE;
		 }
      }
   }
   else
   {
      if ((self.flags) & FL_ONGROUND)
      {
         self.velocity_x = (1 - (10 * frametime)) * (self.velocity_x);
         self.velocity_y = (1 - (10 * frametime)) * (self.velocity_y);
         self.sprinting = FALSE;
      }
   }
   	if (self.button1)
    {
        PlayerUse();
	}
	else
		self.flags = self.flags | FL_USERELEASED;
        
	if (self.button2 && !self.incar)
	{
		PlayerJump ();
	}
	else
		self.flags = self.flags | FL_JUMPRELEASED;
	
	playerfootstep();
	detector();
};
string nextmap;
string nextstartspot;
void()GotoNextMap =
{
	if (cvar("samelevel"))	// if samelevel is set, stay on same level
	{
		changelevel (mapname, startspot);
	}
	else
	{
		changelevel (nextmap, nextstartspot);
	}
}

void() changelevel_touch =
{
	local entity	pos;

	if (other.classname != "player")
		return;
	
	writefirst();
	writeinventory();
	nextmap = self.map;
	nextstartspot = self.target;

	SUB_UseTargets ();

	if ( (deathmatch == 0) )
	{	// NO_INTERMISSION
		GotoNextMap();
		return;
	}
	
	self.touch = SUB_Null;
};

/*QUAKED trigger_changelevel (0.5 0.5 0.5) ? NO_INTERMISSION
When the player touches this, he gets sent to the map listed in the "map" variable.  Unless the NO_INTERMISSION flag is set, the view will go to the info_intermission spot and display stats.
*/
void() trigger_changelevel =
{
	if (!self.map)
		objerror ("changelevel trigger doesn't have map");
	
	InitTrigger ();
	self.touch = changelevel_touch;
};
/*
============
SelectSpawnPoint

Returns the entity to spawn at
============
*/
entity() SelectSpawnPoint =
{
	local	entity spot;
	local	float  pcount;
	if (startspot)
	{
		spot = world;
		pcount = 1;
		while(pcount)
		{
			spot = find (spot, classname, "info_player_start");
			if (!spot)
				pcount = 0;
			else if (spot.targetname == startspot)
				pcount = 0;
		}
	}
			
	if (!spot)
	{
		spot = find (world, classname, "info_player_start");
		if (!spot)
			error ("PutClientInServer: no info_player_start on level");
	}
	return spot;
};

void() SetNewParms = {};
void() SetChangeParms = {};
void()DecodeLevelParms= {};
//Called to spawn the clients player entity
entity manager;
void()TaskManagerOFF=
{
	HideLmp("task");
	HideString("taskstring");
	remove(manager);
}
void(string icon,string msg)TaskManager=
{
	float len;
	manager = spawn();
	len = strlen(msg);
	len = len * 8;
	ShowLmp("task",icon,395,0);
	ShowString("taskstring",msg,395 - len,20,8);
	localcmd("play device/pda/pda_objective.wav \n");
	manager.think = TaskManagerOFF;
	manager.nextthink = time + 5;
}
void() PutClientInServer =
{
	local	entity spot;
	spot = SelectSpawnPoint ();
	self.classname = "player";           
	self.health = 100; 
	self.takedamage = DAMAGE_AIM;        // I can be fired at
	self.solid = SOLID_SLIDEBOX;         // Things sort of 'slide' past me
	self.movetype = MOVETYPE_WALK;       // Yep, I want to walk.
	self.flags = FL_CLIENT;              // Yes, I'm a client.
	self.group = LONER; // группа одиночка
	self.origin = spot.origin + '0 0 1'; // Move to the spawnspot location
	self.angles = spot.angles;     // Face the angle the spawnspot indicates
	self.fixangle = TRUE;                // Turn this way immediately
	setmodel (self, "progs/player.mdl"); // Set my player to the player model
	setsize (self, VEC_HULLHL_MIN, VEC_HULLHL_MAX);
	self.hull = 2;
	self.view_ofs = '0 0 28';
	self.velocity = VEC_ORIGIN;             // Stop any old movement,VEC_ORIGIN = '0 0 0'
	self.th_die = PlayerDie;
	self.slotwep = BOLT;
	self.weapon = WEP_BOLT;
	self.state = IDLE;
	self.stamina = 10;
	self.maxitems = 0;
	rain();
	self.cursor_x = 116; // задефайнить как-то глобально?
	self.cursor_y = 66;
	localcmd("exec gameplay.cfg\n");
	cvar_set("in_analog_disable","0");
	cvar_set("chase_active","0");
	cvar_set("scr_nohud","0");
	cvar_set("r_drawviewmodel","1"); 
	
	local float k;
	for(k=1;k<MAX_ITEMS;k++)
	{
		self.slot[k] = spawn();
	}
	 NightDayLightChanger();
	GetSinglePlayerParameters();
	self.think = readinventory;
	self.nextthink = time + 1;
	UpdateWeapon();
	//playing track after menu
	WriteByte(MSG_ALL,SVC_CDTRACK);
	WriteByte(MSG_ALL,2);
	WriteByte(MSG_ALL,0);
};
void() info_player_start={};