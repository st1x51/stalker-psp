float()	CheckDogMelee =
{
	if (enemy_range == RANGE_MELEE)
	{	// FIXME: check canreach
		self.attack_state = AS_MELEE;
		return TRUE;
	}
	return FALSE;
};

float()	DogCheckAttack =
{
	local	vector	vec;
	
	if (CheckDogMelee ())
	{
		self.attack_state = AS_MELEE;
		return TRUE;
	}
	
	return FALSE;
};
/*
================
dog_bite

================
*/
void() dog_bite =
{
	local vector	delta;
	local float 	ldmg;

	if (!self.enemy)
		return;

	ai_charge(10);

	if (!CanDamage (self.enemy, self))
		return;

	delta = self.enemy.origin - self.origin;
	if (vlen(delta) > 120)
	{
		self.think = dog_run_anim;
		return;
	}
	if (self.enemy.health <= 0)
	{
		self.think = SUB_Null;
		return;
	}	
	ldmg = (random() + random() + random()) * 8;
	T_Damage (self.enemy, self, self, 8);
};

void()dog_stand_anim=
{
	//AdvanceFrame(0,59);
	if(self.frame == 59)
	{
		self.frame = 0;
		sound (self, CHAN_AUTO, "monsters/dog/idle_0.wav", 1, ATTN_NORM);
	}
	self.frame += 1;
	self.sequence = 0;
	ai_stand();
	self.nextthink = time + 0.005;
}
void()dog_stand=
{
	self.sequence = 0;
	self.frame = 0;
	dog_stand_anim();
}
void()dog_run_anim=
{
	AdvanceFrame(0,19);
	if(self.frame == 19)
		self.frame = 0;
	ai_run(5);
	self.sequence = 1;
	self.nextthink = time + 0.05;
}

void()dog_walk_anim=
{
	AdvanceFrame(0,29);
	if(self.frame == 29)
	{
		local float r;
		r = floor(random() * 5);
		if(r ==0)
			sound (self, CHAN_VOICE, "monsters/dog/bdog_distant_0.wav", 1, ATTN_NORM);
		else if (r == 1)
			sound (self, CHAN_VOICE, "monsters/dog/bdog_distant_1.wav", 1, ATTN_NORM);
		else if (r == 2)
			sound (self, CHAN_VOICE, "monsters/dog/bdog_distant_2.wav", 1, ATTN_NORM);
		else if (r == 3)
			sound (self, CHAN_VOICE, "monsters/dog/bdog_distant_3.wav", 1, ATTN_NORM);
		else if (r == 4)
			sound (self, CHAN_VOICE, "monsters/dog/bdog_distant_4.wav", 1, ATTN_NORM);
		else if (r == 5)	
			sound (self, CHAN_VOICE, "monsters/dog/bdog_distant_5.wav", 1, ATTN_NORM);
		self.frame = 0;
	}
	ai_walk(2);
	self.sequence = 4;
	self.nextthink = time + 0.05;
}

void()dog_attack_anim=
{
	//AdvanceFrame(0,24);
	if(self.frame == 24)
		self.frame = 0;
	if(self.frame == 5)
	{
		local float r;
		r = floor(random() * 3);
		if(r ==0)
			sound (self, CHAN_VOICE, "monsters/dog/bdog_attack_0.wav", 1, ATTN_NORM);
		else if (r == 1)
			sound (self, CHAN_VOICE, "monsters/dog/bdog_attack_1.wav", 1, ATTN_NORM);
		else 
			sound (self, CHAN_VOICE, "monsters/dog/bdog_attack_2.wav", 1, ATTN_NORM);
		dog_bite();
	}
	self.sequence = 3;
	ai_face();
	self.frame += 1;
	self.nextthink = time + 0.05;
}
void()dog_attack=
{
	self.sequence = 2;
	self.frame = 0;
	dog_attack_anim();
}

void() dog_pain =
{
	sound (self, CHAN_VOICE, "monsters/dog/hit_0.wav", 1, ATTN_NORM);
	ai_pain(0);	
};


void() dog_die =
{
// regular death
	local float r;
	r = floor(random() * 3);
	if(r ==0)
		sound (self, CHAN_VOICE, "monsters/dog/bdog_die_0.wav", 1, ATTN_NORM);
	else if (r == 1)
		sound (self, CHAN_VOICE, "monsters/dog/bdog_die_1.wav", 1, ATTN_NORM);
	else 
		sound (self, CHAN_VOICE, "monsters/dog/bdog_die_2.wav", 1, ATTN_NORM);
	
	self.solid = SOLID_NOT;
	self.angles_z -= 90;
	self.sequence = 0;
	self.frame = 0;
	self.think = SUB_Null;
};

void() monster_dog =
{
	precache_model ("models/dog.mdl");

	precache_sound ("monsters/dog/idle_0.wav");
	precache_sound ("monsters/dog/threaten_0.wav");
	precache_sound ("monsters/dog/threaten_1.wav");
	precache_sound ("monsters/dog/bdog_attack_0.wav");
	precache_sound ("monsters/dog/bdog_attack_1.wav");
	precache_sound ("monsters/dog/bdog_attack_2.wav");
	precache_sound ("monsters/dog/hit_0.wav");
	precache_sound ("monsters/dog/bdog_die_0.wav");
	precache_sound ("monsters/dog/bdog_die_1.wav");
	precache_sound ("monsters/dog/bdog_die_2.wav");
	
	precache_sound ("monsters/dog/bdog_distant_0.wav");
	precache_sound ("monsters/dog/bdog_distant_1.wav");
	precache_sound ("monsters/dog/bdog_distant_2.wav");
	precache_sound ("monsters/dog/bdog_distant_3.wav");
	precache_sound ("monsters/dog/bdog_distant_4.wav");
	precache_sound ("monsters/dog/bdog_distant_5.wav");
	
	
	self.solid = SOLID_SLIDEBOX;
	self.movetype = MOVETYPE_STEP;
	self.takedamage = DAMAGE_AIM;
	setmodel (self, "models/dog.mdl");

	setsize (self, '-16 -16 0', '16 16 32');
	self.health = 50;
	
	self.th_stand = dog_stand_anim;
	self.th_walk = dog_walk_anim;
	self.th_run = dog_run_anim;
	self.th_pain = dog_pain;
	self.th_die = dog_die;
	self.th_melee = dog_attack_anim;
	walkmonster_start();	
};
