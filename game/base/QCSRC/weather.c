// Night and Day Cycle Fields
//have some bugs with time on level changing
entity		nightdaychanger;
.float		daynightlightlevel;
.string		nightdaylightstring;
.float		lightchange;
float		min_lightlevel;
float		max_lightlevel;

//Autocvar for time between day and night changes (Can be set in autoexec.cfg or default.cfg)
float autocvar_nightdayinterval = 1;
//rain code
void() rain_touch = 
{		
	// remove rain when it hits ground or any other object
	//particle (self.origin, '0 0 0', 7.5, 5);
        remove(self);
};
float nosnd;
void()rain_sound
{
	if(weather)
		sound (self, CHAN_VOICE , "rain.wav", 1, ATTN_NONE);
	else
		sound (self, CHAN_VOICE , "null.wav", 1, ATTN_NONE);
	self.think = rain_sound;
	self.nextthink = time + 4;
}
void() rain_think =
{
	if(weather == 1)
	{
		local float temp1,temp2;
		local vector rain_org, rain_vel;
		local entity drop,pl,snd;
		if(!nosnd)
		{
		snd = spawn();
		snd.think = rain_sound;
		snd.nextthink = time + 0.1;
		nosnd = 1;
		}
		pl = find(world,classname,"player");
		rain_org = pl.origin;
		temp1 = random();
		temp2 = random();

		// random direction from func_rain origin
		if (temp1 < 0.5)
						rain_org_x = rain_org_x - 256*random();
		else
						rain_org_x = rain_org_x + 256*random();
		if (temp2 < 0.5)
						rain_org_y = rain_org_y - 256*random();
		else
						rain_org_y = rain_org_y + 256*random();
		rain_org_z = rain_org_z + 300;

		drop = spawn();
		setorigin (drop, rain_org);
		//setmodel (drop, "sprites/rain.spr");
		
		drop.classname = "raindrop";
		drop.movetype = MOVETYPE_TOSS;
		drop.solid = SOLID_BBOX;
		setsize (drop, '0 0 0', '0 0 0');
		rain_vel = '0 0 0';
		rain_vel_z = -30*random();
		addparticle(p_rain,drop.origin,1,2,5,0,rain_vel);
		drop.touch = rain_touch;
	}	
		self.nextthink = time + 0.01;
		self.think = rain_think;
};

void() rain=
{

	entity rain;
	rain = spawn();
	rain.owner = self;
	setorigin(rain, self.origin);
	rain.nextthink = time + 0.01;
	rain.think = rain_think;
}
// This function will change the time of day, basically every 20 seconds it will lower the lightlevel by 1 until it reaches the minimum light level and will start over again in reverse. 

void() NightDayLightThink =
{ 
	if(self.daynightlightlevel == 2 || self.daynightlightlevel == 14)
		autocvar_nightdayinterval = 120;
	else
		autocvar_nightdayinterval = 1;
        // If its time to be daylight again start increasing light
	if(self.lightchange)
	{ 
		self.daynightlightlevel += 0.1;
                // If the light level gets too high its full daytime start getting darker soon
		if(self.daynightlightlevel > max_lightlevel)
		{
			local float r;
			r = random();
			if(r > 0.5)
			{
				if(!weather)
					weather = 1;
				else
					weather = 0;
			}

			self.daynightlightlevel = max_lightlevel - 1;
			self.lightchange = FALSE;
		}
	}
        // Is it me or is it getting dark around here? 
	else
	{
		self.daynightlightlevel = self.daynightlightlevel - 0.1;
		
		if(self.daynightlightlevel < min_lightlevel)
		{ 
            //Make sure light level stays at min_lightlevel and restart
			local float r;
			r = random();
			if(r > 0.5)
			{
				if(!weather)
					weather = 1;
				else
					weather = 0;
			}

			self.daynightlightlevel = min_lightlevel;
			self.lightchange = TRUE;
		}
	}
        // This changes all lights in the level except torches, etc or any lights that use on and off flags lightstyles 32+
	lightstyle(0, substring(self.nightdaylightstring, self.daynightlightlevel, 1) );
	
	self.nextthink = time + autocvar_nightdayinterval; // Repeat in 20 seconds
};

// This will create our entity and start the cycle
void() NightDayLightChanger =
{ 
	if(autocvar_nightdayinterval > 0)
	{
                // Set up our light value min and max
		max_lightlevel = 25;
		min_lightlevel = 1.5;
                //If we don't have a sun make one!
		if(!nightdaychanger)
		{
			nightdaychanger = spawn();
                        // No need to send this to the client
			nightdaychanger.effects = EF_NODRAW;
			nightdaychanger.flags = nightdaychanger.flags | FL_ARCHIVE_OVERRIDE;
			//nightdaychanger.think = NightDayLightThink; //disabled
                        // Start it daylight because nighttime is scary
			nightdaychanger.daynightlightlevel = max_lightlevel;
			
                       // We want the light to change gradually			
                        nightdaychanger.nightdaylightstring = "abcdefghijklmnopqrstuvwxyz";
                        // Lets get started
			//nightdaychanger.nextthink = time + 0.01;
		}
	}
};
