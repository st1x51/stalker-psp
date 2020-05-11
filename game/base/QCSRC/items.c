void() SUB_regen =
{
	self.model = self.mdl;		// restore original model
	self.solid = SOLID_TRIGGER;	// allow it to be touched again
	setorigin (self, self.origin);
};
/*
============
PlaceItem

plants the object on the floor
============
*/

void() PlaceItem =
{
	self.mdl = self.model;
	self.flags = FL_ITEM;		// make extra wide
	self.solid = SOLID_TRIGGER;
	self.movetype = MOVETYPE_TOSS;	
	self.velocity = '0 0 0';
	self.origin_z = self.origin_z + 10;
	if (!droptofloor())
	{
		bprint ("Item fell out of level at ");
		bprint (vtos(self.origin));
		bprint ("\n");
		remove(self);
		return;
	}
};

/*
============
StartItem

Sets the clipping size and plants the object on the floor
============
*/
void() StartItem =
{
	self.nextthink = time + 0.2;	// items start after other solids
	self.think = PlaceItem;
};
void()item_touch=
{
	if(other.classname != "player")
		return;
	if(other.maxitems == MAX_ITEMS)
	{
		bprint("other.maxitems == MAX_ITEM\n");
		return;
	}
	local float k;
	for(k=1;k<MAX_ITEMS;k++) //потому что так надо
	{
		if(!other.slot[k].isfull)
		{
			other.slot[k].netname = self.netname;
			other.slot[k].isfull = 1;
			break;		
		}		
	}
	other.maxitems += 1;
	self.model = string_null;
	self.solid = SOLID_NOT;	
	if(self.netname == "pm")
	{
		if(self.dropped == 1)
		{
			other.pm_clip = self.pm_clip;
			other.ammo_pm = self.ammo_pm;	
			other.pm_fired = self.pm_fired;
		}
		else
		{
			other.pm_clip = 12;
			other.ammo_pm += 12;
		}
	}
	if(self.netname == "tozbm")
	{
		other.tozbm_clip = 2;
		other.ammo_tozbm += 8;
	}
	if(self.netname == "aksu")
	{
		if(self.dropped == 1)
		{
			other.aksu_clip = self.aksu_clip;
			other.ammo_aksu = self.ammo_aksu;	
			other.aksu_fired = self.aksu_fired;
		}
		else
		{
			other.aksu_clip = 30;
			other.ammo_aksu += 90;
		}
	}
	remove(self);
}
void() item_pm =
{
	setmodel (self, "models/w_pm.mdl");
	self.netname = "pm";
	self.use = item_touch;
	self.useflags = self.useflags | PL_SHORTUSE;
	setsize (self, '-4 -4 -4', '4 4 4');
	StartItem ();
};
void() item_aksu =
{
	setmodel (self, "models/w_aksu.mdl");
	self.netname = "aksu";
	self.use = item_touch;
	self.useflags = self.useflags | PL_SHORTUSE;
	setsize (self, '-4 -4 -4', '4 4 4');
	StartItem ();
};
void() item_tozbm =
{
	setmodel (self, "models/w_toz_bm.mdl");
	self.netname = "tozbm";
	self.use = item_touch;
	self.useflags = self.useflags | PL_SHORTUSE;
	setsize (self, '-4 -4 -4', '4 4 4');
	StartItem ();
};

void() item_medkit =
{
	setmodel (self, "models/medkit.mdl");
	self.netname = "medkit";
	self.use = item_touch;
	self.useflags = self.useflags | PL_SHORTUSE;
	setsize (self, '-4 -4 -4', '4 4 4');
	StartItem ();
};
void() item_antirad =
{
	setmodel (self, "models/antirad.mdl");
	self.netname = "antirad";
	self.use = item_touch;
	self.useflags = self.useflags | PL_SHORTUSE;
	setsize (self, '-4 -4 -4', '4 4 4');
	StartItem ();
};

void() item_gasmask =
{
	setmodel (self, "models/gasmask.mdl");
	self.netname = "gasmask";
	self.use = item_touch;
	self.useflags = self.useflags | PL_SHORTUSE;
	setsize (self, '-4 -4 -4', '4 4 4');
	StartItem ();
};
void() item_drink =
{
	setmodel (self, "models/drink.mdl");
	self.netname = "drink";
	self.use = item_touch;
	self.useflags = self.useflags | PL_SHORTUSE;
	setsize (self, '-4 -4 -4', '4 4 4');
	StartItem ();
};
.float radioused;
void()radio_reuse=
{
	self.radioused = 0;
}
void()radio_use=
{
	if(!self.radioused)
	{
		sound (self, CHAN_WEAPON, "1976.wav", 1, ATTN_NORM);
		self.think = radio_reuse;
		self.nextthink = time + getsoundlen("1976.wav");
	}
	self.radioused = 1;
}
void() item_radio =
{
	precache_model("models/radio.mdl");
	setmodel (self, "models/radio.mdl");
	precache_sound("1976.wav");
	self.netname = "radio";
	self.use = radio_use;
	self.useflags = self.useflags | PL_SHORTUSE;
	setsize (self, '-4 -4 -4', '4 4 4');
	StartItem ();
	self.think = radio_use;
	self.nextthink = time + 1;
};

void()battery_stop=
{
	addparticle(29,self.origin + [random(-4,4),random(-4,4),random(0,4)],2,random(5,10),0.5,0,self.origin +  [0,0,random(-2,8)]);
	self.velocity_z = -2;
	self.think = battery_think;
	self.nextthink = time + 1;
}

void()battery_think=
{
	addparticle(29,self.origin + [random(-4,4),random(-4,4),random(0,4)],2,random(5,10),0.5,0,self.origin +  [0,0,random(-2,8)]);
	self.velocity_z += 6;
	self.nextthink = time + 0.5;
	self.think = battery_stop;
}
void()battery_touch=
{
	if(other.classname != "bolt")
		return;
	addparticle(3,self.origin,1,2,1,0,self.origin + [0,0,5]);
	bprint("touched\n");
}
void()item_battery=
{
	precache_model("models/batareika.mdl");
	setmodel(self,"models/batareika.mdl");
	self.solid = SOLID_TRIGGER;
	self.movetype = MOVETYPE_FLY;	
	self.velocity = '0 0 0';
	self.origin_z = self.origin_z + 10;
	self.netname = "battery";
	self.use = item_touch;
	self.useflags = self.useflags | PL_SHORTUSE;
	setsize (self, '-8 -8 -8', '8 8 8');
	//self.touch = battery_touch;
	self.think = battery_think;
	self.nextthink = time + 1;
}

void() hurt_on=
{
	self.solid = SOLID_TRIGGER;
	self.effects = 0;
	self.think = gaz_think;
	self.nextthink = time + 0.5;
};

void() hurt_touch=
{
	if(other.classname == "bolt")
	{
		self.effects = 32;
		sound (self, CHAN_WEAPON, "anomaly/buzz_hit.wav", 1, ATTN_STATIC);
	}
	if (other.takedamage)
	{
		self.solid = SOLID_NOT;
		T_Damage (other, self, self, 20);
		sound (self, CHAN_WEAPON, "anomaly/buzz_hit.wav", 1, ATTN_STATIC);
		self.think = hurt_on;
		self.nextthink = time + 0.5;
	}

	return;
};
vector oldorg;
void()gaz_think=
{
	if(self.frame >=7)
	{
		self.frame = 0;
		addparticle(p_smoke_green,self.origin + [random(-64,64),random (-64,64),0],1,10,2,0,self.origin + [0,0,10]);
		setorigin(self,oldorg + [random(-64,64),random(-64,64),0]);
	}
	self.nextthink = time + 0.1;
	self.frame +=1;
	self.think = gaz_think;
}
void()item_gaz=
{
	entity gaz[4];
	gaz[0] = spawn();
	gaz[1] = spawn();
	gaz[2] = spawn();
	gaz[3] = spawn();
	precache_model("sprites/gaz.spr32");
	precache_sound("anomaly/buzz_idle.wav");
	precache_sound("anomaly/buzz_hit.wav");
	setmodel(self,"sprites/gaz.spr32");
	setmodel(gaz[0],"sprites/gaz.spr32");
	setmodel(gaz[1],"sprites/gaz.spr32");
	setmodel(gaz[2],"sprites/gaz.spr32");
	setmodel(gaz[3],"sprites/gaz.spr32");
	self.solid = SOLID_TRIGGER;
	gaz[0].solid = SOLID_TRIGGER;
	gaz[1].solid = SOLID_TRIGGER;
	gaz[2].solid = SOLID_TRIGGER;
	gaz[3].solid = SOLID_TRIGGER;
	self.movetype = MOVETYPE_NONE;	
	self.velocity = '0 0 0';
	gaz[0].angles = '90 0 0';
	gaz[1].angles = '90 0 0';
	gaz[2].angles = '90 0 0';
	gaz[3].angles = '90 0 0';
	self.netname = "gaz";
	self.angles = '90 0 0';
	setsize (self, '-16 -16 -8', '16 16 8');
	setsize (gaz[0], '-16 -16 -8', '16 16 8');
	setsize (gaz[1], '-16 -16 -8', '16 16 8');
	setsize (gaz[2], '-16 -16 -8', '16 16 8');
	setsize (gaz[3], '-16 -16 -8', '16 16 8');
	self.rendermode = 1;
	self.rendercolor = '150 240 0';
	gaz[0].rendermode = 1;
	gaz[0].rendercolor = '150 240 0';
	gaz[1].rendermode = 1;
	gaz[1].rendercolor = '150 240 0';
	gaz[2].rendermode = 1;
	gaz[2].rendercolor = '150 240 0';
	gaz[3].rendermode = 1;
	gaz[3].rendercolor = '150 240 0';
	gaz[0].touch = hurt_touch;
	gaz[1].touch = hurt_touch;
	gaz[2].touch = hurt_touch;
	gaz[3].touch = hurt_touch;
	setorigin(gaz[0],self.origin + [random(-64,64),random(-64,64),0]);
	setorigin(gaz[1],self.origin + [random(-64,64),random(-64,64),0]);
	setorigin(gaz[2],self.origin + [random(-64,64),random(-64,64),0]);
	setorigin(gaz[3],self.origin + [random(-64,64),random(-64,64),0]);
	gaz[0].think = gaz_think;
	gaz[1].think = gaz_think;
	gaz[2].think = gaz_think;
	gaz[3].think = gaz_think;
	gaz[0].nextthink = time + random(0.5,1);
	gaz[1].nextthink = time + random(0.5,1);
	gaz[2].nextthink = time + random(0.5,1);
	gaz[3].nextthink = time + random(0.5,1);
	self.effects = 32;
	oldorg = self.origin;
	ambientsound (self.origin, "anomaly/buzz_idle.wav", 1, ATTN_STATIC);
}
void()AnimFire=
{
	if(self.frame == 13)
		self.frame = 1;
	self.frame +=1;
	self.think = AnimFire;
	self.nextthink = time + 0.1;
}
void()FireAnimation=
{
	local entity fire;
	fire = spawn();
	setorigin(fire,self.origin + '0 0 35');
	fire.movetype = MOVETYPE_NONE;
	setsize (fire, '0 0 0', '0 0 0');
	setmodel (fire, "sprites/fire.spr32");
	fire.frame = 1;
	fire.effects = 16;
	ambientsound (fire.origin, "ambience/fire2.wav", 1, ATTN_STATIC);
	self = fire;
	AnimFire();
}
void()object_barrel=
{
	precache_model("models/barrel_burning.mdl");
	setmodel(self,"models/barrel_burning.mdl");
	self.movetype = MOVETYPE_STEP;
	self.solid = SOLID_BBOX;
	self.classname = "object_barrel";
	setsize (self, '-8 -8 0', '8 8 24');
	FireAnimation();
}