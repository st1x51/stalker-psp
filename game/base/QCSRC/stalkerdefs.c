#define RANDOM_LONG(x,y) (x + (y - x)*random())
#define RANDOM_FLOAT(x) floor(random() * x)
#define RENDER_NORMAL   0
#define RENDER_COLOR    1
#define RENDER_TEXTURE  2
#define RENDER_GLOW     3
#define RENDER_SOLID    4
#define RENDER_ADDITIVE 5
/*
-----------------------------------------
min
Returns the lesser of two (or more) numbers
part of mathlib by FrikaC
-----------------------------------------
*/
float (float a, float b) mathlib_min =
{
	if (a<b)
		return a;
	else
		return b;
};

//group defenitions
.float group;
enum
{
	LONER = 0,
	MONOLIT,
	DOLG,
	SVOBODA,
	BANDITS
};
//group etc

//player radiation?
.float radiation;
string nextnode;
//sprint
.float sprint_time,sprinting;
.float stamina_time;;
//weather
float weather;
//show / hide LMP
float psp_width = 480;
float psp_height = 272;
void(string indexname,string picname,float x,float y) ShowLmp=
{
	WriteByte (MSG_ALL, SVC_SHOWLMP);
	WriteString(MSG_ALL,indexname);
	WriteString(MSG_ALL,picname);
	WriteShort(MSG_ALL,x);
	WriteByte(MSG_ALL,y);
}

void(string indexname)HideLmp=
{
	WriteByte (MSG_ALL, SVC_HIDELMP);
	WriteString(MSG_ALL,indexname);
}
void(string indexname,string stringname,float x,float y,float width) ShowString=
{
	WriteByte (MSG_ALL, SVC_SHOWSTRING);
	WriteString(MSG_ALL,indexname);
	WriteString(MSG_ALL,stringname);
	WriteShort(MSG_ALL,x);
	WriteByte(MSG_ALL,y);
	WriteByte(MSG_ALL,width);
}
void(string indexname)HideString=
{
	WriteByte (MSG_ALL, SVC_HIDESTRING);
	WriteString(MSG_ALL,indexname);
}
.float state;
string questlog;
enum
{
	NONE,
	IDLE,
	FIRING,
	RUNNING,
	RELOADING
};
float WEP_KNIFE = 1;
float WEP_BOLT = 2;
float WEP_PM = 3;
float WEP_TOZBM = 4;
float WEP_AKSU = 5;
enum
{
	SIT = 0,
	MOVE,
	STAY,
	RUN,
	LADDER
};
//weapons
float MaxSpreadY,MaxSpreadX,SpreadX,SpreadY;
float LeftSpread;
.float pm_clip,ammo_pm,pm_fired;
.float slotwep,primaryweapon,secondaryweapon;
.float tozbm_clip,ammo_tozbm,tozbm_fired;
.float aksu_clip,ammo_aksu,aksu_fired;
enum
{
	BOLT = 0,
	KNIFE,
	PRIMARY,
	SECONDARY
};
.float incar;
#define MAX_ITEMS 13
.entity slot[MAX_ITEMS]; //объекты слота
enum
{
	p_spark, //0
	p_smoke,
	p_fire,
	p_fire2,
	p_bubble,
	p_lavasplash,
	p_gunblast,
	p_chunk,
	p_shockwave,
	p_inferno_flame,
	p_inferno_trail,
	p_sparkray,
	p_staticbubble,
	p_trailpart,
	p_dpsmoke,
	p_dpfire,
	p_teleflare,
	p_blood1,
	p_blood2,
	p_blood3,
	p_bloodcloud,
    p_q3blood,
	p_flame,
	p_lavatrail,
	p_bubble2,
	p_rain,
	p_streak,
	p_streaktrail,
	p_streakwave,
	p_lightningbeam,
	p_glow,
	p_alphatrail,//R00k
	p_torch_flame,
	p_flare,
	p_dot,
	p_muzzleflash,
	p_muzzleflash8,
	p_fly,
    p_q3blood_trail,
	p_q3blood_decal,
	p_q3rocketsmoke,
	p_q3grenadesmoke,
	p_q3explosion,
	p_q3flame,
	p_q3gunshot,
	p_q3teleport,
	p_smoke_green,
	num_particletypes
};
