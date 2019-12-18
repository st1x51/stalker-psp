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
void(string text)format_text=
{
	float stringsteps = 16;
	string teststring;
	lengh = strlen(text);
	currentlengh = 0;
	for(float i = 0;currentlengh <= lengh;i++)
	{
		teststring = substring(text,currentlengh,40);
		currentlengh += 40;
		answer[i] = strzone(teststring);
		stringsteps += 16;
		ShowString(s[i],answer[i],90,stringsteps,8);
	}
}

void() dialog_choice_tolyan=
{
	string dialog;
	string vopros;
	string otvet;
	string textotvet;
	if(	cvar("saved3") == 0)
		self.impulse = 23;
	if(question == 1) //medkit
	{
		string dialog1,dialog2;
		string action;
		clear_text();
		//getting text from person
		action = xmlparsedialog("base/dialogs_escape.xml","tutorial_wounded_give_medkit",ftos(cvar("saved3")),"action");
		if(action == "dialogs.transfer_medkit")
		{
			entity oldent;
			entity object;
			object = find(world,classname,"tolyan");
			RemoveItem("medkit");
			oldent = self;
			self = object;
			tolyan_use();
			self = oldent;
		}
		nextnode = xmlparsedialog("base/dialogs_escape.xml","tutorial_wounded_give_medkit",ftos(cvar("saved3")),"next");
		cvar_set("saved3",nextnode);

		dialog1 = xmlparsedialog("base/dialogs_escape.xml","tutorial_wounded_give_medkit",ftos(cvar("saved3")),"text");
		answer3 = strzone(xmlparsetext("base/stable_dialogs_escape.xml",dialog1,"text"));
	// 	ShowString("s3",answer3,100,30,8);
		format_text(answer3);
		nextnode = xmlparsedialog("base/dialogs_escape.xml","tutorial_wounded_give_medkit",ftos(cvar("saved3")),"next");
		cvar_set("saved3",nextnode);
		dialog2 = xmlparsedialog("base/dialogs_escape.xml","tutorial_wounded_give_medkit",ftos(cvar("saved3")),"text");
		question1 =  strzone(xmlparsetext("base/stable_dialogs_escape.xml",dialog2,"text"));
	}
	if(question == 2)
	{
		string dialog1,dialog2;
		clear_text();
		//getting text from person
		nextnode = xmlparsedialog("base/dialogs_escape.xml","tutorial_wounded_give_medkit",ftos(cvar("saved3")),"next");
		cvar_set("saved3",nextnode);

		dialog1 = xmlparsedialog("base/dialogs_escape.xml","tutorial_wounded_give_medkit",ftos(cvar("saved3")),"text");
		answer3 = strzone(xmlparsetext("base/stable_dialogs_escape.xml",dialog1,"text"));
	// 	ShowString("s3",answer3,100,30,8);
		format_text(answer3);
		nextnode = xmlparsedialog("base/dialogs_escape.xml","tutorial_wounded_give_medkit",ftos(cvar("saved3")),"next");
		if(cvar("saved3")== 1)
			nextnode = "3";
		cvar_set("saved3",nextnode);
		dialog2 = xmlparsedialog("base/dialogs_escape.xml","tutorial_wounded_give_medkit",ftos(cvar("saved3")),"text");
		question1 =  strzone(xmlparsetext("base/stable_dialogs_escape.xml",dialog2,"text"));
	}
	if(question == 3)
	{
		string dialog1,dialog2;
		clear_text();
		//getting text from person
		nextnode = xmlparsedialog("base/dialogs_escape.xml","tutorial_wounded_give_medkit",ftos(cvar("saved3")),"next");
		cvar_set("saved3",nextnode);
		if(	cvar("saved3") == 0) // be sure
				self.impulse = 23;
		dialog1 = xmlparsedialog("base/dialogs_escape.xml","tutorial_wounded_give_medkit",ftos(cvar("saved3")),"text");
		answer3 = strzone(xmlparsetext("base/stable_dialogs_escape.xml",dialog1,"text"));
		format_text(answer3);
		nextnode = xmlparsedialog("base/dialogs_escape.xml","tutorial_wounded_give_medkit",ftos(cvar("saved3")),"next");
		if(cvar("saved3")== 1)
			nextnode = "3";
		cvar_set("saved3",nextnode);
		dialog2 = xmlparsedialog("base/dialogs_escape.xml","tutorial_wounded_give_medkit",ftos(cvar("saved3")),"text");
		question1 =  strzone(xmlparsetext("base/stable_dialogs_escape.xml",dialog2,"text"));
	}

	ShowString("ch1",	substring(question1,0,40),90,160,8);
	ShowString("ch2",	substring(question1,40,40),90,176,8);
		if(	cvar("saved3") == 0)
			ShowString("ch1","...",90,160,8);
}

void()tolyan_touch=
{
	string xmltest,test2;
	local float i;
	float stringsteps = 16;
	string teststring;
	string 	text = "";
	string dialog;
	dialog = xmlparsedialog("base/dialogs_escape.xml","tutorial_wounded_give_medkit","6","text");
	text = strzone(xmlparsetext("base/stable_dialogs_escape.xml",dialog,"text"));

	other.talkperson = 2;
	localcmd("exec dialogue.cfg\n");
	d_cursor_x = 82;
	d_cursor_y = 160;
	choice = 1;
	number_choices = 1;
	nextchoice_y = 46;
	ShowLmp("dialog","gfx/dialog_window.png",0,0);

	if(self.health > 10)
	{
		dialog = xmlparsedialog("base/dialogs_escape.xml","tutorial_wounded_give_medkit","21","text");
		text = strzone(xmlparsetext("base/stable_dialogs_escape.xml",dialog,"text"));
	}
	lengh = strlen(text);
	currentlengh = 0;

	for(i = 0;currentlengh <= lengh;i++)
	{
		teststring = substring(text,currentlengh,40);
		currentlengh += 40;
		answer[i] = strzone(teststring);
		stringsteps += 16;
		ShowString(s[i],answer[i],90,stringsteps,8);
	}
	if(CheckItem("medkit"))
	{
		question = 1;
		nextnode = xmlparsedialog("base/dialogs_escape.xml","tutorial_wounded_give_medkit","6","next");
		cvar_set("saved3",nextnode);
		dialog =  xmlparsedialog("base/dialogs_escape.xml","tutorial_wounded_give_medkit","61","text");
		question1 = xmlparsetext("base/stable_dialogs_escape.xml",dialog,"text");
	}
	else
	{
		question = 2;
		nextnode = xmlparsedialog("base/dialogs_escape.xml","tutorial_wounded_give_medkit","6","next");
		cvar_set("saved3",nextnode);
		dialog =  xmlparsedialog("base/dialogs_escape.xml","tutorial_wounded_give_medkit","61","text"); 
		question1 = xmlparsetext("base/stable_dialogs_escape.xml",dialog,"text");
	}
	if(self.health >= 100)
	{
		nextnode = xmlparsedialog("base/dialogs_escape.xml","tutorial_wounded_give_medkit","21","next");
		cvar_set("saved3",nextnode);
		question = 3;
		dialog =  xmlparsedialog("base/dialogs_escape.xml","tutorial_wounded_give_medkit","211","text");
		question1 = xmlparsetext("base/stable_dialogs_escape.xml",dialog,"text");
		self.enemy = other;
		bot_face();
		self.sequence = 0;
		self.frame = 0;
		self.nextthink = time + 0.1 + random();
		self.think = self.th_stand;
		self.ai_state = 0;
		self.pausetime = time + 15;
	}

	ShowString("ch1",question1,90,160,8);
	ShowString("ch2",question2,90,176,8);
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
	setsize (bot, '-16 -16 0 ', '16 16 72');
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
