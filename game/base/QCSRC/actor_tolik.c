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
void()tolyan_use=
{
	if(self.health <= 10)
	{
		//if(RemoveItem("medkit"))
		//{
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
	//	}
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

void()dialog_choice_tolyan=
{
	entity oldent;
	entity object;
	object = find(world,classname,"tolyan");

	if(choice == 1 && choice_complite[1] != 1)
	{
		if(question == 1)
		{
			clear_text();
			RemoveItem("medkit");
			oldent = self;
			self = object;
			tolyan_use();
			self = oldent;
			answer3 = "Спасибо";
			question1 = "Да не за что";
			question2 = "";
		    ShowString("s3",answer3,120,nextchoice_y,8);
			nextchoice_y += 16;
			number_choices = 1;
			self.impulse = 23;
		}
		if(question == 2)
		{
			answer5 = "Поищи у трупа";
			question1 = "Хорошо";
			question2 = "";
			ShowString("s5",answer5,120,nextchoice_y,8);
			nextchoice_y += 16;
			number_choices = 1;
		}
		if(question == 3)
		{
			self.impulse = 23;
			number_choices = 1;
		}
		question += 1;
	}
	
	
	ShowString("ch1",question1,120,160);
	ShowString("ch2",question2,120,168);
}
void()tolyan_touch=
{
	other.talkperson = 2;
	localcmd("exec dialogue.cfg\n");
	d_cursor_x = 112;
	d_cursor_y = 160;
	choice = 1;
	number_choices = 1;
	nextchoice_y = 46;
	ShowLmp("dialog","gfx/dialog_window.tga",0,0);

	local float i;
	float stringsteps = 16;
	string teststring;
	string 	text = "";
	if(self.health <= 10)
		text = "Мужик, помоги, дай аптечку";
	else
		text = "Спасибо, Меченый";
	lengh = strlen(text);
	currentlengh = 0;


	for(i = 0;currentlengh <= lengh;i++)
	{
		teststring = substring(text,currentlengh,40);
		currentlengh += 40;
		answer[i] = strzone(teststring);
		stringsteps += 16;
		ShowString(s[i],answer[i],120,stringsteps,8);
	}
	if(CheckItem("medkit"))
	{
		question = 1;
		question1 = "Держи";
	}
	else
	{
		question = 2;
		question1 = "Извини, нету";
	}
	if(self.health >= 100)
	{
		question = 3;
		question1 = "Пока";
		self.enemy = other;
		bot_face();
		self.sequence = 0;
		self.frame = 0;
		self.nextthink = time + 0.1 + random();
		self.think = self.th_stand;
		self.ai_state = 0;
		self.pausetime = time + 15;
	}
		
	ShowString("ch1",question1,120,160,8);
	ShowString("ch2",question2,120,176,8);
	ShowString("cursor",">",d_cursor_x,d_cursor_y,8);
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
	bot.use = tolyan_touch;
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
	bot.classname = "tolyan";
}