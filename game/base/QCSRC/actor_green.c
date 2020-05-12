.float alifestate;
enum
{
	JOKE,
	SMOKE,
	GUITAR,
	SITTING
};

void()play_guitar=
{
	if(self.frame == 149)
	{
		self.frame = 0;
	}
	self.frame +=1;
	self.think = play_guitar;
	self.nextthink = time + 0.025;
}
void()take_guitar=
{
	if(self.frame == 69)
	{
		self.sequence = 0;
		self.frame = 0;
		play_guitar();
		sound (self, CHAN_WEAPON, stringmusic, 1, ATTN_NORM);
		return;
	}
	self.frame +=1;
	self.think = take_guitar;
	self.nextthink = time + 0.025;
}
void()takeout_guitar=
{
	if(self.frame == 59)
	{
		self.bodygroup = 0;
		self.sequence = 4;
		self.frame = 0;
		self.alifestate = SMOKE;
		green_kurit();
		return;
	}
	self.frame +=1;
	self.think = takeout_guitar;
	self.nextthink = time + 0.025;
}
void()green_kurit=
{
	if(self.frame == 199)
	{
		self.frame = 0;
	}
	self.frame +=1;
	self.think = green_kurit;
	self.nextthink = time + 0.025;
}

string stringjoke,stringreaction,musicreaction,stringmusic;
float(entity e) getsound=
{
	if(e.alifestate == GUITAR)
		return getsoundlen(stringmusic);
	if(e.alifestate == JOKE)
		return getsoundlen(stringjoke);
	if(e.alifestate == SMOKE)
		return 20;
}
void()CheckReaction=
{
	local entity head;
	local float r,rs;
	r = random();

	//теперь думаем над тем,как реагировать если кто-то что-то делает
	// добавить реакции на шутки и на гитару
	// на рандоме отвечать очень редко
	if(self.alifestate == GUITAR || self.alifestate == JOKE )
		return;
	head = findradius(self.origin, 100);
	while (head)
	{
		if(head.classname == "actor_green")
		{
			if(head.alifestate == GUITAR)
			{
				rs = floor(random()*3);
				switch(rs)
				{
					case 0:
						musicreaction = "reaction/music/reaction_music_1.wav";
					break;
					case 1:
						musicreaction = "reaction/music/reaction_music_2.wav";
					break;
					case 2:
						musicreaction = "reaction/music/reaction_music_3.wav";
					break;
					default:
						musicreaction = "reaction/music/reaction_music_3.wav"; // add another
					break;
				}
				self.alifestate = SITTING;
				if(r < 0.3)
					sound (self, CHAN_WEAPON, musicreaction, 1, ATTN_NORM);
			}
			if( head.alifestate == JOKE )
			{
				rs = floor(random()*3);
				switch(rs)
				{
					case 0:
						stringreaction = "reaction/joke/reaction_joke_1.wav";
					break;
					case 1:
						stringreaction = "reaction/joke/reaction_joke_2.wav";
					break;
					case 2:
						stringreaction = "reaction/joke/reaction_joke_3.wav";
					break;
					default:
						stringreaction = "reaction/joke/reaction_joke_3.wav"; // add another
					break;
				}
				self.alifestate = SITTING;
				if(r < 0.3)
					sound (self, CHAN_WEAPON, stringreaction, 1, ATTN_NORM);
			}
		}
		
		head = head.chain;
	}
}
void()random_actions=
{
	local float r;
	CheckReaction();
	if(self.alifestate == GUITAR)
	{
		self.sequence = 2;
		self.frame = 0;
		takeout_guitar();
		return;
	}
	if(self.alifestate == SITTING)
	{
		self.sequence = 4;
		self.frame = 0;
		self.alifestate = SMOKE;
		green_kurit();
		return;
	}
	r=floor(random()*5);
	if(r == 0 || r == 1 || r == 2)
	{
		self.sequence = 4;
		self.frame = 0;
		self.alifestate = SMOKE;
		green_kurit();
	}
	if(r == 3)
	{
		//self.sequence = 0;
		//self.frame = 0;
		r=floor(random()*3);
		switch(r)
		{
			case 0:
				stringmusic = "guitar_9.wav";
			break;
			case 1:
				stringmusic = "guitar_10.wav";
			break;
			case 2:
				stringmusic = "guitar_11.wav";
			break;
			default:
				stringmusic = "guitar_11.wav"; // add another
			break;
		}
		self.alifestate = GUITAR;
		self.sequence = 5;
		self.frame = 0;
		self.bodygroup = 1;
		take_guitar();
		//play_guitar();	
	}
	if(r == 4)
	{
		self.sequence = 3;
		self.frame = 0;
		r=floor(random()*3);
		switch(r)
		{
			case 0:
				stringjoke = "joke_1.wav";
			break;
			case 1:
				stringjoke = "joke_2.wav";
			break;
			case 2:
				stringjoke = "joke_3.wav";
			break;
			default:
				stringjoke = "joke_3.wav";// add another
			break;
		}
		sound (self, CHAN_WEAPON, stringjoke, 1, ATTN_NORM);
		self.alifestate = JOKE;
		green_kurit();
	}
}
void()alife_think=
{
	local entity actor,oldent,oldactor;
	local float snd;
	
	oldent = self;
	self = self.owner;

	random_actions();
	snd = getsound(self);
	snd += 2; //stupid bug
	self = oldent;
	self.nextthink = time + snd;
	self.think = alife_think;
}
void()actor_green=
{
	precache_sound("guitar_9.wav");
	precache_sound("guitar_10.wav");
	precache_sound("guitar_11.wav");
	precache_sound("joke_1.wav");
	precache_sound("joke_2.wav");
	precache_sound("joke_3.wav");
	
	precache_model("models/green.mdl");
	setmodel (self, "models/green.mdl");
	setorigin(self,self.origin);
	self.movetype = MOVETYPE_STEP;
	self.solid = SOLID_BBOX;
	self.useflags = self.useflags | PL_SHORTUSE;
	self.classname = "actor_green";
	setsize (self, '-16 -16 0', '16 16 32');
	
	self.sequence = 4;
	self.frame = 0;
	self.alifestate = SMOKE;
	green_kurit();
	
	local entity alife;
	alife = spawn();
	alife.owner = self;
	alife.nextthink = time + random(2,4);
	alife.think = alife_think;

	//self.think = random_actions;
	//self.nextthink = time + 2;
}
