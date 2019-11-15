/*
+--------+
|Impulses|
+--------+-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-+
| Scratch                                      Http://www.admdev.com/scratch |
+=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-+
| Handle and execute "Impulse" commands - as entered from console.           |
+=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-+
*/      
void()ChangeWeapon;
void() CheckImpulses =
{
	if(self.impulse == 10)
		ChangeWeapon();
	if (self.impulse == 13)
    {	
		if(self.velocity == '0 0 0' || self.state == FIRING || self.state == RELOADING)
		{
			self.impulse = 0;  
			return;
		}
		if(self.sprinting)
		{
			self.sprint_time = time;
			self.sprinting = FALSE;    
			self.state = IDLE;	
			self.pl_state = 2;			
			UpdateWeapon();
		}
		if (!(self.sprinting))
		{
			 if ((time - self.sprint_time) > 1)//wait until we can sprint again...
			 {
				self.sprint_time = time + self.stamina; //4
				self.sprinting = TRUE;
				self.state = RUNNING;
				self.pl_state = 3;
				UpdateWeapon();
			 }
		}
    }
   
   if(self.impulse == 14)
   {
	if(!inventory)
	{
		//stuffcmd(self,"menu_inventory \n");
		ShowInventory();
	}
	else
	{	
		//stuffcmd(self,"menu_inventory \n");
		HideInventory();
	}
   }
   if(self.impulse == 15) //двигаемся ток в одну сторону пока что
   {
		MoveInventoryRight();
   }
   if(self.impulse == 16) //use items here
   {
		MoveInventoryLeft();
   }
   if(self.impulse == 17) //use items here
   {
		UseInventoryItems();
		//DropItem();
   }
   if(self.impulse == 18) //use items here
   {
		DropItem();
   }
   if(self.impulse == 20)
   {
		dialog_down();
   }
   if(self.impulse == 21)
   {
		dialog_up();
   }
   if(self.impulse == 22)
   {
		dialog_choice();
   }
   
   if(self.impulse == 23)
   {
		localcmd("exec gameplay.cfg\n");
		HideLmp("dialog");
		HideString("s1");
		HideString("s2");
		HideString("s3");
		HideString("s4");
		HideString("s5");
		HideString("ch1");
		HideString("ch2");
		HideString("cursor");
   }
  if(self.impulse == 24)
  {
  	if(self.incar)
	{
		local entity car,oldself;
		local vector car_origin;
		car_origin = self.origin;
		oldself = self;
		car = spawn();
		car.origin = car_origin;
		car.angles = self.angles;
		self = car;
		car_niva();
		//setsize(self,'-64 -32 0','64 32 32');
		
		self = oldself;
		setorigin(self,car_origin + '0 0 80');
		setmodel (self, "progs/player.mdl"); // Set my player to the player model
		setsize (self, VEC_HULLHL_MIN, VEC_HULLHL_MAX);
		self.hull = 2;
		self.view_ofs = '0 0 28';
		self.incar = 0;
		localcmd("exec gameplay.cfg \n");
		cvar_set("chase_active","0");
		cvar_set("in_analog_disable","0");
		cvar_set("cl_bob","0.02");
		cvar_set("cl_yawspeed","140");
	}
  }
	self.impulse = 0;                              // Clear impulse list.
};