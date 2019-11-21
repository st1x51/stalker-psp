.float maxitems;
.float in_gasmask;
.float dropped;
float inventory;
.float cursor_x;
.float cursor_y;
float currentslot; //текущий слот
.entity slot[MAX_ITEMS]; //объекты слота
string item[MAX_ITEMS]=
{"",
"item1",
"item2",
"item3",
"item4",
"item5",
"item6",
"item7",
"item8",
"item9",
"item10",
"item11",
"item12"
}; //вещи в слоте
float slot_x[MAX_ITEMS]= {0,20,52,84,116,20,52,84,116,20,52,84,116}; //кординаты x
float slot_y[MAX_ITEMS] = {0,50,50,50,50,82,82,82,82,114,114,114,114}; //координаты y
.float isfull; //есть ли что-то в слоте
float(string itemname)RemoveItem=
{
	local float k;
	for(k=1;k<MAX_ITEMS;k++) 
	{
		if(self.slot[k].netname == itemname && self.slot[k].isfull)
		{
			self.maxitems -=1;
			self.slot[k].isfull = 0;
			self.slot[k].netname = string_null;
			HideLmp(item[k]);
			return 1;
		}
	}
	return 0;
}
//test,todo
float(string itemname)GiveItem=
{
	if(other.maxitems == MAX_ITEMS)
	{
		bprint("other.maxitems == MAX_ITEM\n");
		return;
	}
	local float k;
	for(k=1;k<MAX_ITEMS;k++)
	{
		if(!other.slot[k].isfull)
		{
			other.slot[k].netname = itemname;
			other.slot[k].isfull = 1;
			break;		
		}		
	}
}
float(string itemname)CheckItem=
{
	local float k;
	for(k=1;k<MAX_ITEMS;k++)
	{
		if(other.slot[k].netname == itemname && other.slot[k].isfull == 1)
			return 1;		
	}
	return 0;
}
string(float index)GetPicName=
{
	return strcat("gfx/icon_",self.slot[index].netname);
}
void(float index)ShowPicInSlot=
{
	local string picture;
	if(self.slot[index].isfull)
	{
		picture = GetPicName(index);
		ShowLmp(item[index],picture,slot_x[index],slot_y[index]);  
	}
}
void()Item_Descripton_OFF=
{
	HideString("itemdesc");
	HideString("itemdesc2");
}

void()Item_Descripton_ON=
{
	string description,description2;
	if(self.slot[currentslot].netname == "pm")
		description = "макарыч";
	if(self.slot[currentslot].netname == "medkit")
		description = "тарена нету";
	if(self.slot[currentslot].netname == "aksu")
	{
		description = "калаш мне";
		description2 = "в зад";
	}
	if(self.slot[currentslot].netname == "gasmask")
		description = "если напердели";
	if(self.slot[currentslot].netname == "antirad")
	{
		description = "бесполезные";	
		description2 = "пилюли";
	}
	if(self.slot[currentslot].netname == "battery")
	{
		description = "единственный";
		description2 = "в зоне";
	}	
	if(self.slot[currentslot].netname == "tozbm")
		description = "два ствола пара";		
	if(self.slot[currentslot].netname == "drink")
		description = "пшшшшш";	
	
	ShowString("itemdesc",description,190,60,8);
	ShowString("itemdesc2",description2,190,76,8);
}
void()ShowInventory=
{
	localcmd("exec inventory.cfg\n");
	cvar_set("scr_nohud","1");
	cvar_set("r_drawviewmodel","0"); 
	self.cursor_x = 36;
	self.cursor_y = 66;
	//CheckSlot();
	local float i;
	for(i =1;i < MAX_ITEMS;i++)
	{
		ShowPicInSlot(i);
	}

	ShowLmp("loa1","gfx/icon_inv.png",20,50);
	ShowLmp("loa2","gfx/icon_inv.png",52,50);
	ShowLmp("loa3","gfx/icon_inv.png",84,50);
	ShowLmp("loa4","gfx/icon_inv.png",116,50);
	
	ShowLmp("loa5","gfx/icon_inv.png",20,82);
	ShowLmp("loa6","gfx/icon_inv.png",52,82);
	ShowLmp("loa7","gfx/icon_inv.png",84,82);
	ShowLmp("loa8","gfx/icon_inv.png",116,82);
	
	ShowLmp("loa9","gfx/icon_inv.png",20,114);
	ShowLmp("loa10","gfx/icon_inv.png",52,114);
	ShowLmp("loa11","gfx/icon_inv.png",84,114);
	ShowLmp("loa12","gfx/icon_inv.png",116,114);

	ShowLmp("invert","gfx/stalker_inv.png",0,0);
	ShowLmp("iconnpc","gfx/ui_icons_npc_4.png",380,55);
	//player
	ShowLmp("cursor","gfx/cursor",self.cursor_x,self.cursor_y);
	inventory = 1;
	currentslot = 1;	
	ShowString("s1","Описание",190,42,8);
	ShowString("s2","Костюм",365,42,8);
	sound (self, CHAN_BODY, "player/inv_open.wav", 1, ATTN_STATIC);
	ShowString("s3",questlog,20,255);
	Item_Descripton_ON();
}

void()HideInventory=
{
	localcmd("exec gameplay.cfg\n");
	cvar_set("scr_nohud","0");
	cvar_set("r_drawviewmodel","1"); 
	HideLmp("loa1");
	HideLmp("loa2");
	HideLmp("loa3");
	HideLmp("loa4");
	HideLmp("loa5");
	HideLmp("loa6");
	HideLmp("loa7");
	HideLmp("loa8");
	HideLmp("loa9");
	HideLmp("loa10");
	HideLmp("loa11");
	HideLmp("loa12");
	HideLmp("cursor");
	HideLmp("invert");
	HideLmp("iconnpc");
	for(float k=1;k<MAX_ITEMS;k++) 
	{
		HideLmp(item[k]);
	}
	inventory = 0;
	HideString("s1");
	HideString("s2");
	HideString("s3");
	Item_Descripton_OFF();
	sound (self, CHAN_BODY, "player/inv_close.wav", 1, ATTN_STATIC);
}

void()MoveInventoryRight=
{
	if(inventory)
	{
   		if(currentslot==12)
		{
			self.cursor_x = 36;
			self.cursor_y = 66;
			currentslot = 1;
			goto show;
			return;
		}
		
		if(currentslot==4)
		{
			self.cursor_y +=32; //так надо
			self.cursor_x = 4;
		}
		if(currentslot==8)
		{
			self.cursor_y +=32; //так надо
			self.cursor_x = 4;
		}
		self.cursor_x += 32; //так надо
		currentslot += 1;
		show:
		ShowLmp("cursor","gfx/cursor",self.cursor_x,self.cursor_y);
		Item_Descripton_ON();
	}		
}

void()MoveInventoryLeft=
{
	if(inventory)
	{			
   		if(currentslot==1)
		{
			self.cursor_x = 130;
			self.cursor_y = 130;
			currentslot = 12;
			goto show;
			return;
		}
		
		if(currentslot==5)
		{
			self.cursor_y -=32; //так надо
			self.cursor_x = 164;
		}
		if(currentslot==9)
		{
			self.cursor_y -=32; //так надо
			self.cursor_x = 164;
		}
		
		self.cursor_x -= 32; //так надо
		currentslot -= 1;
		show:
		ShowLmp("cursor","gfx/cursor",self.cursor_x,self.cursor_y);
		Item_Descripton_ON();
	}		
}

void()UseInventoryItems=
{
	if(inventory)
	{
		if(self.slot[currentslot].isfull)
		{
			if(self.slot[currentslot].isfull)
			{
				if(self.slot[currentslot].netname == "medkit")
				{
					if(self.health >= 100)
					{
						self.impulse = 0;
						return;
					}
					if(self.health >= 75)
						self.health = 100;
					else
						self.health += 25;
					self.maxitems -= 1;
				}
				if(self.slot[currentslot].netname == "drink")
				{
					if(self.stamina == 10)
					{
						self.impulse = 0;
						return;
					}	
					self.stamina += 8;	
					if(self.stamina >= 10)
						self.stamina = 10;
					self.maxitems -= 1;
				}
				if(self.slot[currentslot].netname == "antirad")
				{
					self.health -= 25;	
					self.maxitems -= 1;
				}
				if(self.slot[currentslot].netname == "gasmask")
				{
					if(!self.in_gasmask)
					{
						ShowLmp("gasmask","gfx/gasmask.png",0,0);
						self.impulse = 0;
						localcmd("room_type 8\n");
						self.in_gasmask = 1;
						sound (self, CHAN_BODY, "player/inv_slot.wav", 1, ATTN_STATIC);
						return;
					}
					else
					{
						HideLmp("gasmask");
						self.impulse = 0;
						localcmd("room_type 0\n");
						self.in_gasmask = 0;
						sound (self, CHAN_BODY, "player/inv_slot.wav", 1, ATTN_STATIC);
						return;	
					}
				}
				if(self.slot[currentslot].netname == "aksu")
				{
					if(self.secondaryweapon == 0 || self.secondaryweapon)
					{
						self.secondaryweapon = WEP_AKSU;
						self.slotwep = SECONDARY;
						self.weapon = self.secondaryweapon;
						UpdateWeapon();
					}
					else
					{
						self.secondaryweapon = 0;
						if(self.weapon == WEP_AKSU)
							ChangeWeapon();
					}
					sound (self, CHAN_BODY, "player/inv_slot.wav", 1, ATTN_STATIC);
					return;	
				}
				if(self.slot[currentslot].netname == "pm")
				{
					if(self.primaryweapon == 0 || self.secondaryweapon)
					{
						self.primaryweapon = WEP_PM;
						self.slotwep = PRIMARY;
						self.weapon = self.primaryweapon;
						UpdateWeapon();
					}
					else
					{
						self.primaryweapon = 0;
						if(self.weapon == WEP_PM)
							ChangeWeapon();
					}
					sound (self, CHAN_BODY, "player/inv_slot.wav", 1, ATTN_STATIC);
					return;	
				}
				if(self.slot[currentslot].netname == "tozbm")
				{
					
					if(self.secondaryweapon == 0 || self.secondaryweapon)
					{
						self.secondaryweapon = WEP_TOZBM;
						self.slotwep = SECONDARY;
						self.weapon = self.secondaryweapon;
						UpdateWeapon();
					}
					else
					{
						self.secondaryweapon = 0;
						if(self.weapon == WEP_TOZBM)
							ChangeWeapon();
					}
					sound (self, CHAN_BODY, "player/inv_slot.wav", 1, ATTN_STATIC);
					return;	
				}
				if(currentslot)
					HideLmp(item[currentslot]);
				self.slot[currentslot].isfull = 0;
				self.slot[currentslot].netname = string_null;//но это не точно 
			}
		}	
	}
}

entity it;
void()DropItem =
{
	if(inventory)
	{
		if(self.slot[currentslot].isfull)
		{
			it = spawn();
			makevectors(self.v_angle);
			traceline(self.origin,self.origin + '0 0 16' + v_forward * 32,FALSE,self);
			it.origin = trace_endpos;
			it.velocity = v_forward * random(150,200) + v_up * 150 + v_right*random(-50,50) + random()*v_up*10;
			it.solid = SOLID_TRIGGER;
			it.movetype = MOVETYPE_TOSS; 
			it.flags = it.flags |FL_ITEM;
			it.netname = self.slot[currentslot].netname;
			it.useflags = it.useflags | PL_SHORTUSE;
			it.dropped = 1;
			it.use = item_touch;
			self.maxitems -= 1; // выкидываем вещь
			sound (self, CHAN_BODY, "player/inv_drop.wav", 1, ATTN_STATIC);
			if(self.slot[currentslot].netname == "drink")
			{
				setmodel (it, "models/drink.mdl");
				setsize(it,'-4 -4 -4','4 4 4');
			}
			if(self.slot[currentslot].netname == "medkit")
			{
				setmodel (it, "models/medkit.mdl");
				setsize(it,'-4 -4 -4','4 4 4');
			}
			if(self.slot[currentslot].netname == "antirad")
			{
				setmodel (it, "models/antirad.mdl");
				setsize(it,'-4 -4 -4','4 4 4');
			}
			if(self.slot[currentslot].netname == "gasmask")
			{
				HideLmp("gasmask");
				localcmd("room_type 0\n");
				self.in_gasmask = 0;
				setmodel (it, "models/gasmask.mdl");
				setsize(it,'-4 -4 -4','4 4 4');
			}
			if(self.slot[currentslot].netname == "pm")
			{
				setmodel (it, "models/w_pm.mdl");
				setsize(it,'-4 -4 -4','4 4 4');
				self.primaryweapon = 0;
				it.ammo_pm = self.ammo_pm;
				it.pm_clip = self.pm_clip;
				it.pm_fired = self.pm_fired;
				if(self.weapon == WEP_PM)	
					ChangeWeapon();
			}
			if(self.slot[currentslot].netname == "tozbm")
			{
				setmodel (it, "models/w_toz_bm.mdl");
				setsize(it,'-4 -4 -4','4 4 4');
				self.secondaryweapon = 0;
				if(self.weapon == WEP_TOZBM)
					ChangeWeapon();
			}
			if(self.slot[currentslot].netname == "aksu")
			{
				setmodel (it, "models/w_aksu.mdl");
				setsize(it,'-4 -4 -4','4 4 4');
				self.secondaryweapon = 0;
				it.ammo_aksu = self.ammo_aksu;
				it.aksu_clip = self.aksu_clip;
				it.aksu_fired = self.aksu_fired;
				if(self.weapon == WEP_AKSU)	
					ChangeWeapon();
			}
			if(self.slot[currentslot].netname == "battery")
			{
				setmodel (it, "models/batareika.mdl");
				setsize(it,'-4 -4 -4','4 4 4');
				it.touch = battery_think;
			}
			
			if(currentslot)
				HideLmp(item[currentslot]);
			self.slot[currentslot].isfull = 0;
			self.slot[currentslot].netname = string_null;//но это не точно 
		}	
	}
}