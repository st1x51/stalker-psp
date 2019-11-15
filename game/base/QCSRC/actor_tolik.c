void()HelpSound=
{
	local entity e;
	e =  findradius(self.origin, 400);
	while (e)
	{
		if(e.classname == "player")
		{	
			local float r;
			r=floor(random()*4);
			if(r == 0)
				sound (self, CHAN_WEAPON, "tolik/tolik_help_1.wav", 1, ATTN_NORM);
			if(r == 1)
				sound (self, CHAN_WEAPON, "tolik/tolik_help_2.wav", 1, ATTN_NORM);
			if(r == 2)
				sound (self, CHAN_WEAPON, "tolik/tolik_help_3.wav", 1, ATTN_NORM);
			if(r == 3)
				sound (self, CHAN_WEAPON, "tolik/tolik_help_4.wav", 1, ATTN_NORM);
		}
		e = e.chain;
	}
}
void()tolyan_dead =
{
	if(self.frame == 59)
	{
		self.frame = 0;
		HelpSound();
	}
	self.frame +=1;
	self.think = tolyan_dead;
	self.nextthink = time + 0.1;
}

void()tolyan_use=
{
	if(self.health <= 10)
	{
		if(RemoveItem("medkit"))
		{
			self.health = 100;
			self.sequence = 0;
			self.frame = 0;
			self.th_stand = actor_stand;
			self.th_walk = actor_walk;
			self.nextthink = time + 0.1 + random();
			self.think = self.th_stand;
			self.ai_state = 0;
			local entity player;
			player = find(world,classname,"player");
			self.enemy = player;
			bot_face();
			sound (self, CHAN_WEAPON, "tolik/tolik_thanks.wav", 1, ATTN_NORM);
			self.pausetime = time + getsoundlen("tolik/tolik_thanks.wav");
		}
	}
}
void()actor_tolik=
{
	local entity bot;
	precache_model("models/tolyan.mdl");
	precache_sound("tolik/tolik_help_1.wav");
	precache_sound("tolik/tolik_help_2.wav");
	precache_sound("tolik/tolik_help_3.wav");
	precache_sound("tolik/tolik_help_4.wav");
	precache_sound("tolik/tolik_thanks.wav");
// initializing the entity
	bot = spawn();
	bot.origin = self.origin + '0 0 10';
	bot.angles = self.angles;
	bot.fixangle = TRUE;	
	bot.solid = SOLID_BBOX;
	bot.movetype = MOVETYPE_STEP;
	setmodel(bot, "models/tolyan.mdl");
	bot.sequence = 3;
	bot.frame = 0;
	bot.think = tolyan_dead;
	bot.nextthink = time + 1;
	bot.health = 10;
	//bot.classname = "actor_green";
	bot.use = tolyan_use;
	bot.useflags = bot.useflags | PL_SHORTUSE;
// polishing him up
	setsize (bot, '-16 -16 0 ', '16 16 32');
	bot.ideal_yaw = bot.angles * '0 1 0';
	bot.yaw_speed = 120;
	bot.speed = 1;
	bot.view_ofs = '0 0 22';
	bot.takedamage = DAMAGE_NO;
	//bot.attack_state = 0;
	bot.button1 = 90;
	bot.ai_state = 0;
}