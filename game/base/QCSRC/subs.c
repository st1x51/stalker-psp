void() DelayThink =
{
	activator = self.enemy;
	SUB_UseTargets ();
	remove(self);
};

/*
==============================
SUB_UseTargets

the global "activator" should be set to the entity that initiated the firing.

If self.delay is set, a DelayedUse entity will be created that will actually
do the SUB_UseTargets after that many seconds have passed.

Centerprints any self.message to the activator.

Removes all entities with a targetname that match self.killtarget,
and removes them, so some events can remove other triggers.

Search for (string)targetname in all entities that
match (string)self.target and call their .use function

==============================
*/
void() SUB_UseTargets =
{
	local entity t, stemp, otemp, act;

//
// check for a delay
//
	if (self.delay)
	{
	// create a temp object to fire at a later time
		t = spawn();
		t.classname = "DelayedUse";
		t.nextthink = time + self.delay;
		t.think = DelayThink;
		t.enemy = activator;
		t.message = self.message;
		t.killtarget = self.killtarget;
		t.target = self.target;
		return;
	}
	
	
//
// print the message
//
	if (activator.classname == "player" && self.message != "")
	{
		centerprint (activator, self.message);
	}

//
// kill the killtagets
//
	if (self.killtarget)
	{
		t = world;
		do
		{
			t = find (t, targetname, self.killtarget);
			if (!t)
				return;
			remove (t);
		} while ( 1 );
	}
	
//
// fire targets
//
	if (self.target)
	{
		act = activator;
		t = world;
		do
		{
			t = find (t, targetname, self.target);
			if (!t)
			{
				return;
			}
			stemp = self;
			otemp = other;
			self = t;
			other = stemp;
			if (self.use != SUB_Null)
			{
				if (self.use)
					self.use ();
			}
			self = stemp;
			other = otemp;
			activator = act;
		} while ( 1 );
	}
};
void (entity tg)SUB_FireTargetsEnt =
{
    local entity  stemp, otemp, act;

	if (tg != world)
	{
		act = activator;
		activator = self;
		stemp = self;
		otemp = other;
		self = tg;
		other = stemp;
		if (self.use != SUB_Null)
		{
			if (self.use)
				self.use ();
		}
		self = stemp;
		other = otemp;
		activator = act;
	}
};

void(float normal) SUB_AttackFinished =
{
	self.attack_finished = time + normal;
};
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
void(float seq,float fr,void() func,optional float t)SUB_Anim=
{
	self.sequence = seq;
	self.frame = fr;
	self.think = func;
	if(!t)
		self.nextthink = time + 0.01;
	else
		self.nextthink = time + t;
}