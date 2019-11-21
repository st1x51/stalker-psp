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
	if(quest != 1)
	{
	if(choice == 1 && choice_complite[1] != 1)
	{
		if(question == 1)
		{
			clear_text();
			answer3 = "есть дело одно";
			question1 = "продолжай";
			question2 = "";
		    ShowString("s3",answer3,120,nextchoice_y);
			nextchoice_y += 8;
		}
		if(question == 2)
		{
			answer5 = "надо артефакт найти";
			question1 = "уже иду";
			question2 = "";
			ShowString("s5",answer5,120,nextchoice_y);
			nextchoice_y += 8;
			number_choices = 1;
		}
		if(question == 3)
		{
			answer4 = "он на агропроме";
			question1 = "ок";
			question2 = "";
			ShowString("s4",answer4,120,nextchoice_y);
			nextchoice_y += 8;
			quest = 1;
			questlog = "найти артефакт";
		}
		question += 1;
		//choice_complite[1] = 1;
	}
	if(choice == 2 && choice_complite[2] != 1)
	{
		if(question == 1)
		{
			clear_text();
			answer4 = "поговори с волком";
			question1 = "ок";
			question2 = "";
			ShowString("s4",answer4,120,nextchoice_y);
			number_choices = 1;
			dialog_up();
			quest = 1;
			questlog = "поговорить с волком";
		}

		//choice_complite[2] = 1;
		question += 1;
	}
	
	
	ShowString("ch1",question1,120,160);
	ShowString("ch2",question2,120,168);
	}
}
string answer[20];
string s[20] = {"s1","s2","s3","s4","s5","s6","s7","s8","s9","s10","s11","s12","s13","s14","s15"};
void()sidor_touch=
{
	self.sequence = 0;
	self.frame = 0;
	read();
	other.talkperson = SIDOR;
	//отрисовать меню
	//загрузить конфиг для импульсов
	//сделать выбор и ответы
	//сделать кнопку выхода
	localcmd("exec dialogue.cfg\n");
	d_cursor_x = 112;
	d_cursor_y = 160;
	choice = 1;
	number_choices = 2;
	nextchoice_y = 46;
	question = 1;
	ShowLmp("dialog","gfx/dialog_window.tga",0,0);

	local float i;
	if(quest != 1)
	{
		float stringsteps = 30;
		string teststring;
		string 	text = "";

		text = "????? ??????";
		lengh = strlen(text);
		currentlengh = 0;
	

		for(i = 0;currentlengh <= lengh;i++)
		{
			teststring = substring(text,currentlengh,40);
			currentlengh += 40;
			answer[i] = strzone(teststring);
			stringsteps += 8;
			ShowString(s[i],answer[i],80,stringsteps);
		}
		question1 = "давай как с новичком ничего не помню";
		question2 = "давай как с опытным";
		ShowString("ch1",question1,120,160);
		ShowString("ch2",question2,120,168);
		ShowString("cursor",">",d_cursor_x,d_cursor_y);
	}
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
	setsize (self, '-16 -16 -16', '16 16 16');
	self.sequence = 1;
	self.frame = 0;
	 quest = 0;
	self.think = first_talk;
	self.nextthink = time + 2;
}