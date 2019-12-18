.float sidorstate;
void()CheckForPlayerLen=
{
	local entity pl;
	local float dist;
	pl = find(world,classname,"player");
	dist = vlen(self.origin - pl.origin);
	if(dist > 150)
	{
			local float r;
			r=floor(random()*6);
			if(r == 0)
				sound (self, CHAN_WEAPON, "trader/trader_script1b_1.wav", 1, ATTN_NORM);
			if(r == 1)
				sound (self, CHAN_WEAPON, "trader/trader_script1b_2.wav", 1, ATTN_NORM);
			if(r == 2)
				sound (self, CHAN_WEAPON, "trader/trader_script1b_3.wav", 1, ATTN_NORM);
			if(r == 3)
				sound (self, CHAN_WEAPON, "trader/trader_script1b_4.wav", 1, ATTN_NORM);
			if(r == 4)
				sound (self, CHAN_WEAPON, "trader/trader_script1b_5.wav", 1, ATTN_NORM);
			if(r == 5)
				sound (self, CHAN_WEAPON, "trader/trader_script1b_6.wav", 1, ATTN_NORM);	
	}
	if(dist > 150)
		self.sidorstate = 0;
}
void()CheckForPlayer=
{
	local entity e;
	e =  findradius(self.origin, 100);
	while (e)
	{
		if(e.classname == "player")
		{	
			local float r;
			r=floor(random()*6);
			if(r == 0)
				sound (self, CHAN_WEAPON, "trader/trader_script1a_1.wav", 1, ATTN_NORM);
			if(r == 1)
				sound (self, CHAN_WEAPON, "trader/trader_script1a_2.wav", 1, ATTN_NORM);
			if(r == 2)
				sound (self, CHAN_WEAPON, "trader/trader_script1a_3.wav", 1, ATTN_NORM);
			if(r == 3)
				sound (self, CHAN_WEAPON, "trader/trader_script1a_4.wav", 1, ATTN_NORM);
			if(r == 4)
				sound (self, CHAN_WEAPON, "trader/trader_script1a_5.wav", 1, ATTN_NORM);
			if(r == 5)
				sound (self, CHAN_WEAPON, "trader/trader_script1a_6.wav", 1, ATTN_NORM);	
			self.sidorstate = 1;
		}
		e = e.chain;
	}
}
void()idle=
{
	if(self.frame == 99)
	{
		self.frame = 0;
		if(!self.sidorstate)
			CheckForPlayer();
		if(self.sidorstate == 1)
			CheckForPlayerLen();
	}
	self.frame +=1;
	self.think = idle;
	self.nextthink = time + 0.025;
}
void()read=
{
	if(self.frame == 99)
	{
		self.sequence = 1;
		self.frame = 0;
		idle();
		return;
	}	
	self.frame +=1;
	self.think = read;
	self.nextthink = time + 0.025;
}

void()dialog_choice_sidor=
{
	string dialog;
	string vopros;
	string otvet;
	string textotvet;
	if(	cvar("saved3") == 0)
		self.impulse = 23;
	if(question == 1)
	{
		string dialog1,dialog2;
		clear_text();
		//getting text from person
		nextnode = xmlparsedialog("base/dialogs_escape.xml","escape_trader_start_dialog",ftos(cvar("saved3")),"next");
		cvar_set("saved3",nextnode);
		if(	cvar("saved3") == 0) // be sure
				self.impulse = 23;
		dialog1 = xmlparsedialog("base/dialogs_escape.xml","escape_trader_start_dialog",ftos(cvar("saved3")),"text");
		answer3 = strzone(xmlparsetext("base/stable_dialogs_escape.xml",dialog1,"text"));
		format_text(answer3);
		nextnode = xmlparsedialog("base/dialogs_escape.xml","escape_trader_start_dialog",ftos(cvar("saved3")),"next");
		if(cvar("saved3")== 1)
			nextnode = "3";
		cvar_set("saved3",nextnode);
		dialog2 = xmlparsedialog("base/dialogs_escape.xml","escape_trader_start_dialog",ftos(cvar("saved3")),"text");
		question1 =  strzone(xmlparsetext("base/stable_dialogs_escape.xml",dialog2,"text"));
	}

	ShowString("ch1",	substring(question1,0,40),90,160,8);
	ShowString("ch2",	substring(question1,40,40),90,176,8);
		if(	cvar("saved3") == 0)
			ShowString("ch1","...",90,160,8);
}
string answer[20];
string s[20] = {"s1","s2","s3","s4","s5","s6","s7","s8","s9","s10","s11","s12","s13","s14","s15"};
void()sidor_touch=
{
	self.sequence = 0;
	self.frame = 0;
	read();
	other.talkperson = 1;
	string xmltest,test2;
	local float i;
	float stringsteps = 16;
	string teststring;
	string 	text = "";
	string dialog,dialog2;
	dialog = xmlparsedialog("base/dialogs_escape.xml","escape_trader_start_dialog","3","text");
	text = strzone(xmlparsetext("base/stable_dialogs_escape.xml",dialog,"text"));

	localcmd("exec dialogue.cfg\n");
	d_cursor_x = 82;
	d_cursor_y = 160;
	choice = 1;
	number_choices = 2;
	nextchoice_y = 46;
	ShowLmp("dialog","gfx/dialog_window.png",0,0);

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
	question = 1;
	cvar_set("saved3","32");
	dialog =  xmlparsedialog("base/dialogs_escape.xml","escape_trader_start_dialog","32","text");
	question1 = strzone(xmlparsetext("base/stable_dialogs_escape.xml",dialog,"text"));
	ShowString("ch1",question1,90,160,8);
	ShowString("ch2",question2,90,176,8);
	ShowString("cursor",">",d_cursor_x,d_cursor_y,8);	
}
void()first_talk=
{
	sound (self, CHAN_WEAPON, "trader_monolog1.wav", 1, ATTN_NORM);
	self.sidorstate = 1;
	idle();
}
void()actor_sidor=
{
	precache_model("models/sidor.mdl");
	precache_sound("trader_monolog1.wav");
	precache_sound("trader/trader_script1a_1.wav");
	precache_sound("trader/trader_script1a_2.wav");
	precache_sound("trader/trader_script1a_3.wav");
	precache_sound("trader/trader_script1a_4.wav");
	precache_sound("trader/trader_script1a_5.wav");
	precache_sound("trader/trader_script1a_6.wav");
	
	precache_sound("trader/trader_script1b_1.wav");
	precache_sound("trader/trader_script1b_2.wav");
	precache_sound("trader/trader_script1b_3.wav");
	precache_sound("trader/trader_script1b_4.wav");
	precache_sound("trader/trader_script1b_5.wav");
	precache_sound("trader/trader_script1b_6.wav");
	setmodel (self, "models/sidor.mdl");
	self.movetype = MOVETYPE_STEP;
	self.solid = SOLID_BBOX;
	self.use = sidor_touch;
	self.useflags = self.useflags | PL_LONGUSE;
	setsize (self, '-16 -16 0', '16 16 32');
	self.sequence = 1;
	self.frame = 0;
	self.think = first_talk;
	self.nextthink = time + 2;
}