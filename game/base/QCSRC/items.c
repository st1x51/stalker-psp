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