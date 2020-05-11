void() func_illusionary =
{
	self.angles = '0 0 0';
	self.movetype = MOVETYPE_NONE;
	self.solid = SOLID_NOT;
	setmodel (self, self.model);
	makestatic (self);
};
void() func_wall_use =
{	
	self.frame = 1 - self.frame;
};
.vector m_vecTestPos;
void()lod_think=
{
	vector len;
	entity pl;
	pl = find(world,classname,"player");
	//len = pl.origin - ((self.mins+self.maxs)*0.5);
	len = pl.origin - self.m_vecTestPos;
	len += self.origin_z;
	if(rint(vlen(len)) < (cvar("r_loddist")))
	{
		self.effects = 0;
	}
	else
	{
		self.effects = EF_NODRAW;
	}
	self.think = lod_think;
	self.nextthink = time + 0.1;
}
void() func_wall =
{
	self.angles = '0 0 0';
	self.movetype = MOVETYPE_PUSH;
	self.solid = SOLID_BSP;
	self.use = func_wall_use;
	setmodel (self, self.model);
	self.m_vecTestPos[0] = self.absmin[0] + (0.5 * (self.absmax[0] - self.absmin[0]));
	self.m_vecTestPos[1] = self.absmin[1] + (0.5 * (self.absmax[1] - self.absmin[1]));
	self.m_vecTestPos[2] = self.absmin[2] + (0.5 * (self.absmax[2] - self.absmin[2]));
	lod_think();
};
float MISC_MODEL_ANIMATION = 1;
float MISC_MODEL_NOCOLLISION = 2;
.float startframe,endframe;
void()misc_model_animation=
{
	if(self.frame == self.endframe)
		self.frame = self.startframe;
	self.frame += 1;
	self.think = misc_model_animation;
	self.nextthink = time + 0.05;
}
void() misc_model =
{
	precache_model (self.model);
	setmodel (self, self.model);
	self.movetype = MOVETYPE_STEP;
	self.solid = SOLID_BBOX;
	if(self.spawnflags & MISC_MODEL_ANIMATION)
	{
		self.frame = self.startframe;
		self.think = misc_model_animation;
		self.nextthink = time +0.1;
	}
	setsize(self,'-16 -16 0','16 16 32');
	if(self.spawnflags & MISC_MODEL_NOCOLLISION)
	{
		self.movetype = MOVETYPE_NONE;
		self.solid = SOLID_NOT;
	}
}; 
.string texture;
.float decalsize;
void() infodecal =
{
	WriteByte  (MSG_ALL, SVC_BSPDECAL);
	WriteString(MSG_ALL, self.texture);
	if(!self.decalsize)
		WriteShort (MSG_ALL, 10);
	else
		WriteShort (MSG_ALL, self.decalsize);
	WriteCoord (MSG_ALL, self.origin_x);
	WriteCoord (MSG_ALL, self.origin_y);
	WriteCoord (MSG_ALL, self.origin_z);

	setsize (self, '-16 -16 0', '16 16 56');
};
void (float dur, float ht, float f, float r, float g, float b, float a) ScreeFade =
{
		WriteByte (MSG_ALL, SVC_SCREENFADE);

		WriteShort(MSG_ALL, dur );
		WriteShort(MSG_ALL, ht  );
		WriteShort(MSG_ALL, f   );

		WriteByte(MSG_ALL,  r);
		WriteByte(MSG_ALL,  g);
		WriteByte(MSG_ALL,  b);
		WriteByte(MSG_ALL,  a);
		
};
void()niva_use=
{
	setmodel(other,self.model);
	setmodel(self,"");
	setorigin(other,self.origin);
	other.angles = self.angles;
	other.fixangle = 1;
	cvar_set("chase_active","1");
	cvar_set("chase_up","40");
	cvar_set("chase_back","150");
	cvar_set("in_analog_disable","1");
	cvar_set("cl_bob","0");
	setsize(other,'-64 -32 0','64 32 32');
	localcmd("exec car.cfg");
	other.incar = 1;
	remove(self);
}
void()car_niva=
{
	setmodel (self, "models/niva.mdl");
	self.solid = SOLID_BBOX;
	self.movetype = MOVETYPE_STEP;	
	self.use = niva_use;
	self.useflags = self.useflags | PL_LONGUSE;
	setsize(self,'-64 -32 0','64 32 32');

}