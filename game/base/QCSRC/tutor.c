// declaring the routines before they are called
.float search_time,pausetime,walk_time;
.float ai_state;
// ------------------------------------------------
void() bot_search_for_items =
// ------------------------------------------------
{
	local entity item;
	local float r;
// he gives up on that item and marks it to avoid it for a while

	if (time > self.search_time && self.goalentity != world)
	{
		self.goalentity.search_time = time + 30;
		self.goalentity = world;
	}
	if(vlen(self.origin - self.goalentity.origin) < 40)
	{
		//bprint("found\n");
		self.ai_state = 0;
		self.sequence = 0;
		self.frame = 0;
		self.th_stand();
		self.think = actor_stand;
		self.nextthink = time + 0.1 + random();
		self.goalentity = world;
		return;
	}
	if (self.goalentity != world)
		return;
	
// checks a radius around him for items
	item = findradius(self.origin, 1500);
	//bprint("finding\n");
	while(item)
	{
		r = random();
		if(r < 0.3)
		{
			if (item.classname == "object_barrel")
			{
				self.search_time = time + 10;
				self.goalentity = item;
				self.ai_state = 1;
			}
		}
		if(r == 0.4 && r == 0.5)
		{
			if (item.classname == "item_radio")
			{
				self.search_time = time + 10;
				self.goalentity = item;
				self.ai_state = 1;
			}
		}
		if(r > 0.5)
		{
			self.search_time = time + 10;
			self.goalentity = world;
			self.ai_state = 4;
		}
		
		item = item.chain;
	}

};
/*

// -----------------------------------------
void() jump_forward =
// -----------------------------------------
{
// propels him into the air

	if (!(self.flags & FL_ONGROUND))
		return;

	self.flags = self.flags - (self.flags & FL_ONGROUND);
	makevectors(self.angles);
	self.velocity = self.velocity + (v_forward * 250);
	self.velocity_z = self.velocity_z + 250;

};

*/

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void() check_for_ledge =
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
{
local vector spot;

// movetogoal() will never move over a legde, so we have to 
// check for a break in front of him and force him to jump

	if (random() < 0.80)
		return;

	if (!(self.flags & FL_ONGROUND))
		return;

	makevectors (self.angles);
	spot = self.origin + (v_forward * 60);
	spot = spot - '0 0 35';
	//if (pointcontents(spot) == CONTENT_EMPTY)
	//	bot_jump1();
};



/*

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
float() bot_look_for_players =
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
{
	local entity	client;
	local float		r;

// this is just like id's FindTarget(), he's looking for clients

	client = checkclient ();
	if (!client)
		return FALSE;

	if (teamplay)
		if (self.team == client.team)
			return FALSE;

	if (client.netname == "observer")
		return FALSE;

	if (client == self.enemy)
		return FALSE;

	if (client.flags & FL_NOTARGET)
		return FALSE;

	r = range (client);
	if (r == RANGE_FAR)
		return FALSE;
		
	if (!visible (client))
		return FALSE;

	if (r == RANGE_NEAR)
	{
		if (client.show_hostile < time && !infront (client))
			return FALSE;
	}
	else if (r == RANGE_MID)
	{
		if (!infront (client))
			return FALSE;
	}
	
	self.enemy = client;
	
	FoundTarget ();

	return TRUE;
};
*/

// ----------------------
void() bot_face =
// ----------------------
{
// this turns him directly toward his enemy

	self.angles_y = vectoyaw(self.enemy.origin - self.origin);
};


// ----------------------
void() bot_stand =
// ----------------------
{

// his standing thoughts, pretty simple
	//check_for_water();
	if (time > self.pausetime)
	{
		self.pausetime = time + 5;
		self.ai_state = 1;
		self.sequence = 1;
		self.frame = 0;
		//bprint("go\n");
		self.th_walk();
		self.think = actor_walk;
		self.nextthink = time + 0.1 + random();
		return;

	}

// do a cute little turn
/*
	if (random() < 0.1)
		self.angles_y = self.angles_y - 15;
	else if (random() > 0.9)
		self.angles_y = self.angles_y + 15;
*/
	
};




// ******************************
void() coffee_move =
// ******************************
{

// this is the best subroutine i've ever written, and probably the
// most powerful bot roaming function. i hope you credit me if you use
// it. basically he strafes along a wall, then turns at a 45 or -45
// degree angle at the wall's corner. i have seen my bots do laps
// around entire levels with these three lines of code

	if (walkmove (self.angles_y, 2) == FALSE)
		if (walkmove (self.angles_y + self.button1, 2) == FALSE)
			self.angles_y = self.angles_y + (self.button1 / 2);

// every so often, he'll change his wall-hugging direction

	if (random() <= 0.02)
		if (self.button1 == 90)
			self.button1 = -90;
			else self.button1 = 90;

};
.vector last_org;

// ~~~~~~~~~~~~~~~~~~~~~~~~~
void() bot_roam =
// ~~~~~~~~~~~~~~~~~~~~~~~~~
{
	if (walkmove(self.angles_y, 2) == FALSE)
		self.angles_y = self.angles_y - 15;

	self.last_org = self.origin;
};
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void() bot_walk =
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
{

// this is his main AI routine, where he will look for items and enemies

	if (!(self.flags & FL_ONGROUND))
		return;
	//bot_look_for_players();
bot_search_for_items();
	//check_for_ledge();

	if (self.ai_state == 1)
		movetogoal(2);
	if (self.ai_state == 4)
		bot_roam();
};





// --------------------------------
void() bot_run_slide =
// --------------------------------
{
	local float	ofs;
	
// this is a cool strafing routine
/*
	if (self.lefty)
		ofs = 90;
	else
		ofs = -90;
*/
	if (walkmove (self.angles_y + ofs, 20))
		return;
		
	//self.lefty = 1 - self.lefty;
	
	walkmove (self.angles_y - ofs, 20);

};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void() bot_run =
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
{

// his fighting thoughts. after a short while, he'll give up 
// on his enemy, but if he can see him, he'll always attack

	if (!(self.flags & FL_ONGROUND))
		return;

	//if (visible(self.enemy))
	//	self.search_time = time + 6;
/*
	if (time > self.search_time || self.enemy.health <= 0)
		{
		self.goalentity = world;
		self.enemy = world;
		self.pausetime = time + 4;
		self.th_stand();
		return;
		}
*/
	//bot_strafe();

	//if (visible(self.enemy) && time > self.attack_finished)
	//	self.th_missile();

};


// -------------------------------------
vector() bot_aim_at_enemy =
// -------------------------------------
{

	return normalize(self.enemy.origin - self.origin);

};
void()actor_stand=
{
	AdvanceFrame(0,199);
	if(self.frame == 199)
		self.frame = 0;
	//self.frame += 1;
	bot_stand();
	//self.think = actor_stand;
	self.nextthink = time + 0.02;
}
void()actor_walk=
{
//	local float result;
	//result = AdvanceFrame(0,39);
	AdvanceFrame(0,39);
	//bprint(ftos(result),"\n");
	if(self.frame == 39)
		self.frame = 0;
	//self.frame += 1;
	bot_walk();
	//self.think = actor_walk;
	self.nextthink = time + 0.05;
}
void()actor_hello=
{
	local float result;
	//result = AdvanceFrame(0,39);
	// AdvanceFrame(0,99);
	//result = AdvanceFrame(0,99);
	//bprint(ftos(self.frame),"\n");
	
	if(self.frame == 99)
	{
		self.pausetime = time + 5;
		self.ai_state = 0;
		self.sequence = 0;
		self.frame = 0;
		self.th_stand();
		self.think = actor_stand;
		self.nextthink = time + 0.1 + random();
		return;
	}
	self.frame += 1;
	//bot_stand();
	self.think = actor_hello;
	self.nextthink = time + 0.02;
}
void()bot_use=
{
	local entity player;
	player = find(world,classname,"player");
	self.ai_state = 3;
	self.sequence = 2;
	self.frame = 0;
	self.enemy = player;
	bot_face();
	actor_hello();
}
.float givenweapon;
void()GiveWeapon=
{
	if(self.givenweapon == WEP_PM)
	{
		local float k;
		for(k=1;k<7;k++) 
		{
			if(!other.slot[k].isfull)
			{
				other.slot[k].netname = "pm";
				other.slot[k].isfull = 1;
				break;		
			}		
		}
		other.maxitems += 1;
		other.pm_clip = 12;
		other.ammo_pm += 36;
	}
}
void()volk_use=
{
	if(quest == 1)
	{
		self.givenweapon = WEP_PM;
		GiveWeapon();
		quest = 2;
	}
}
.float actor;
// ------------------------------------------------
void() actor_green_neutral =
// ------------------------------------------------
{
	local entity bot;
	precache_model("models/volk.mdl");
// initializing the entity
	bot = spawn();
	bot.origin = self.origin + '0 0 10';
	bot.angles = self.angles;
	bot.fixangle = TRUE;	
	bot.solid = SOLID_BBOX;
	bot.movetype = MOVETYPE_STEP;

// defining his animation
	if(!self.actor)
		setmodel(bot, "models/green_neutral.mdl");
	if(self.actor == 1)
		setmodel(bot, "models/volk.mdl");
	bot.sequence = 0;
	bot.frame = 0;
	bot.th_stand = actor_stand;
	bot.th_walk = actor_walk;
	//bot.th_run = bot_run1;
	//bot.th_pain = bot_pain;
	//bot.th_die = bot_die;
//	bot.th_missile = bot_attack;
	bot.health = 100;
	bot.classname = "actor_green";
	if(!self.actor)
		bot.use = bot_use;
	if(self.actor == 1)
		bot.use = volk_use;
	bot.useflags = bot.useflags | PL_SHORTUSE;
// polishing him up
	setsize (bot, '-16 -16 0 ', '16 16 32');
	bot.ideal_yaw = bot.angles * '0 1 0';
	bot.yaw_speed = 120;
	bot.speed = 1;
	bot.view_ofs = '0 0 22';
	bot.takedamage = DAMAGE_AIM;
	//bot.attack_state = 0;
	bot.button1 = 90;
	bot.nextthink = time + 0.1 + random();
	bot.think = bot.th_stand;
	if(!self.actor)
		bot.pausetime = time + 5;
	if(self.actor == 1)	
		bot.pausetime = time + 9999;
	bot.ai_state = 0;
};



