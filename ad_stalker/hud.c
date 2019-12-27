/*
Copyright (C) 1996-1997 Id Software, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/
#include "quakedef.h"
#include <pspgu.h>

int      	hudpic,crosshairpic,hudpic,inventorypic,menupic;	
int			sb_updates;
cvar_t scope = {"scope", "0"};
char		str_count[3];
int count_actors;
//scope here
qpic_t      *scope_sniper;	
void Hud_LoadPics(void)
{
	crosshairpic = loadtextureimage_hud("gfx/crosshair");
	hudpic =  loadtextureimage_hud("gfx/ui_hud");
	//inventorypic =  loadtextureimage_hud("gfx/ui_inventory2");
	//menupic = loadtextureimage_hud("gfx/mainmenu"); 
	//mappic  =  loadtextureimage_hud("gfx/agro_map");
}
void Hud_Init (void)
{
	Hud_LoadPics(); //we are loading our precached pictures
	Cvar_RegisterVariable (&scope);
}
/*
void Hud_DrawPicAlpha (int x, int y, qpic_t *pic, float alpha)
{
	Draw_AlphaPic (x + ((vid.width - 320)>>1), y + (vid.height - 24), pic, alpha);
}

void Hud_DrawPic (int x, int y, qpic_t *pic)
{
	Draw_AlphaPic (x + ((vid.width - 320)>>1), y + (vid.height - 24), pic,1.0f);
}
*/
void Hud_Changed (void)
{
	sb_updates = 0;	
}
/*
void DrawNumber(int x, int y, int number)
{
	int a,b,c,d,e;
	int numpoints[] ={0,25,45,70,95,120,145,170,190,215,0}; 
	a = number / 10000;
	b = (number/1000)%10;
	c = (number/100)%10;
	d = (number/10)%10;
	e = number%10;
	if(number >= 100)
		showimgpart (x, y, numpoints[c], 0, 25, 25, hudpic, 1,GU_RGBA(180, 124, 41, 255));
	if(number >= 10)
		showimgpart (x+20, y, numpoints[d], 0, 25, 25, hudpic, 1,GU_RGBA(180, 124, 41, 255));
	showimgpart (x+40, y, numpoints[e], 0, 25, 25, hudpic, 1,GU_RGBA(180, 124, 41, 255));
}
*/
/*
===============
DrawRadar
===============
*/
//3920x3263
void DrawRadar (void)
{
	entity_t	*ent, *player;
	player = &cl_entities[cl.viewentity];
	int i;
	int px, py, dx, dy;
	model_t *clmodel;	
	edict_t	*e;
	//showimgpart (7, 9,0,0, 40, 40, mappic, 2,GU_RGBA(200, 0, 0, 255));
	count_actors = 0;
	for (i=0 ; i<sv.num_edicts ; i++)
	{
		e = EDICT_NUM(i);
		if ( !strcmp (pr_strings + e->v.classname, "actor_green") ||  !strcmp (pr_strings + e->v.classname, "actor_sidor"))
		{
			px = (player->origin[0]-e->v.origin[0])*0.06;
			py = (e->v.origin[1]-player->origin[1])*0.06;
			if (abs(px) < 39 && abs(py) < 39)
			{
				//Red blip
				dx = cos((cl.viewangles[YAW]+90)/57) * px - sin((cl.viewangles[YAW]+90)/57) * py;
				dy = sin((cl.viewangles[YAW]+90)/57) * px + cos((cl.viewangles[YAW]+90)/57) * py;
				showimgpart (45 + dx, 45 + dy, 305, 41, 2, 2, hudpic, 0,GU_RGBA(200, 0, 0, 255));
				count_actors+=1;
			}
			
		}
	}

	showimgpart (45 , 45 , 305, 41, 2, 2, hudpic, 0,GU_RGBA(200, 0, 0, 255));
	/*
	for (i=0,ent=cl_entities ; i<cl.num_entities ; i++,ent++)
	{
		clmodel = ent->model;
		if (!strcmp (clmodel->name, "models/medkit.mdl"))
		{
			//I dunno, do shit? I don't have graphics yet..
			//Hooray for placeholder graphics!
			px = (player->origin[0]-ent->origin[0])*0.06;
			py = (ent->origin[1]-player->origin[1])*0.06;
			if (abs(px) < 39 && abs(py) < 39)
			{
				//Red blip
				dx = cos((cl.viewangles[YAW]+90)/57) * px - sin((cl.viewangles[YAW]+90)/57) * py;
				dy = sin((cl.viewangles[YAW]+90)/57) * px + cos((cl.viewangles[YAW]+90)/57) * py;
				showimgpart (45 + dx, 45 + dy, 305, 41, 2, 2, hudpic, 0,GU_RGBA(200, 0, 0, 255));
			}
		}
	}
	*/
	/*
	for (i=0,ent=cl_entities ; i<cl.num_entities ; i++,ent++)
	{
		if (ent->health > 0)
		{
			//I dunno, do shit? I don't have graphics yet..
			//Hooray for placeholder graphics!
			px = (player->origin[0]-ent->origin[0])*0.06;
			py = (ent->origin[1]-player->origin[1])*0.06;
			if (abs(px) < 39 && abs(py) < 39)
			{
				//Red blip
				dx = cos((cl.viewangles[YAW]+90)/57) * px - sin((cl.viewangles[YAW]+90)/57) * py;
				dy = sin((cl.viewangles[YAW]+90)/57) * px + cos((cl.viewangles[YAW]+90)/57) * py;
				showimgpart (45 + dx, 45 + dy, 305, 41, 2, 2, hudpic, 0,GU_RGBA(200, 200, 200, 255));
			}
		}
	}
	*/
	//cl.stats[STAT_AMMO] = player->health;	
}
int		hud_text,hud_text_x,hud_text_y;
void DrawText ()
{
		Draw_String (hud_text_x, hud_text_y, hud_text);
}

void Predrawtext (int hudtxt,int x,int y)
{
	hud_text_x = x;
	hud_text_y = y;
	hud_text = hudtxt;
}
void Hud_Draw (void)
{
	if (scr_con_current == vid.height)
		return;		
    if (scr_nohud.value)
        return;
	sb_updates++;
	DrawRadar();
	//map
	showimgpart (0, 0, 0, 0, 92, 96, hudpic, 2,GU_RGBA(200, 200, 200, 255));
	//running
	showimgpart (0, 210, 175, 37, 61, 56, hudpic, 2,GU_RGBA(200, 200, 200, 255));
	
	showimgpart (390, 200, 92, 0, 82, 36, hudpic, 2,GU_RGBA(200, 200, 200, 255));
	//hp
	showimgpart (410, 222, 255, 26, cl.stats[STAT_HEALTH] * 0.55, 5, hudpic, 2,GU_RGBA(200, 200, 200, 255));
	//stamina
	showimgpart (16, 253, 174, 95, cl.stats[STAT_STAMINA] * 2.8,4, hudpic, 2,GU_RGBA(200, 200, 200, 255));
	//counter
	showimgpart (75 , 80 , 0, 95, 18, 16, hudpic, 0,GU_RGBA(200, 0, 0, 255));
	sprintf (str_count," %2i", count_actors);
	M_Print (65,85,  str_count);
	
	//states
	if(cl.stats[STAT_STATE] == 0) //sit
		showimgpart (15, 230, 0, 190, 30,21, hudpic, 2,GU_RGBA(200, 200, 200, 255));
	if(cl.stats[STAT_STATE] == 1) //move
		showimgpart (15, 220, 0, 330, 28,33, hudpic, 2,GU_RGBA(200, 200, 200, 255));
	if(cl.stats[STAT_STATE] == 2) //stay
		showimgpart (15, 220, 0, 215, 28,33, hudpic, 2,GU_RGBA(200, 200, 200, 255));
	if(cl.stats[STAT_STATE] == 3) //run
		showimgpart (15, 220, 0, 252, 28,33, hudpic, 2,GU_RGBA(200, 200, 200, 255));
	if(cl.stats[STAT_STATE] == 4) //ladder
		showimgpart (15, 220, 0, 290, 28,33, hudpic, 2,GU_RGBA(200, 200, 200, 255));
	//showimgpart (0, 240, 50, 25, 20, 22, hudpic, 1,GU_RGBA(180, 124, 41, 255));
	//if(cl.stats[STAT_HEALTH] <= 0)
	//	DrawNumber(30,240,0);
	//else
	//	DrawNumber(30,240,cl.stats[STAT_HEALTH]);

	//DrawNumber(390,240,cl.stats[STAT_SHELLS]); //ammo
	//DrawNumber(300,240,cl.stats[STAT_AMMO]); //clip
		// ammo
	
	char		str_ammo[3];
	showimgpart (390, 235, 92, 36, 80,32, hudpic, 2,GU_RGBA(200, 200, 200, 255));
	Draw_Character (vid.width - 45, vid.height - 25,  175);
	sprintf (str_ammo," %3i", cl.stats[STAT_SHELLS]);
	M_Print (vid.width - 50, vid.height - 25,  str_ammo);
	sprintf (str_ammo," %3i", cl.stats[STAT_AMMO]);
	M_Print (vid.width - 80, vid.height - 25,  str_ammo);

	//if (((int)scope.value == 1) &&  (cl.stats[STAT_ACTIVEWEAPON] == IT_AWP))
	//	Draw_Pic (0,0, scope_sniper);
}
