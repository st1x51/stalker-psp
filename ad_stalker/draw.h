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

// draw.h -- these are the only functions outside the refresh allowed
// to touch the vid buffer

//extern	qpic_t		*draw_disc;	// also used on sbar

void Draw_Init (void);
void Draw_Character (int x, int y, int num);
void Draw_Character_Rus (int x, int y, int num);
void Draw_DebugChar (char num);
void Draw_Pic (int x, int y, qpic_t *pic);
void Draw_ColoredString (int x, int y, char *text, int red);
void Draw_TransPic (int x, int y, qpic_t *pic);
void Draw_TransPicTranslate (int x, int y, qpic_t *pic, byte *translation);
void Draw_ConsoleBackground (int lines);
void Draw_BeginDisc (void);
void Draw_EndDisc (void);
void Draw_TileClear (int x, int y, int w, int h);
void Draw_Fill (int x, int y, int w, int h, int c);
void Draw_LoadingFill(void);
void Draw_FadeScreen (void);
void Draw_FadeScreenColor (int r, int g, int b, int a);
void Draw_String (int x, int y, char *str);
void Draw_String_Rus (int x, int y, char *str);
qpic_t *Draw_PicFromWad (char *name);
qpic_t *Draw_CachePic (char *path);
byte *StringToRGB (char *s);
void showimgpart (int x, int y, int px, int py, int w, int h, int texnum, int mode,unsigned int c);
void Draw_FrontText(char* text, int x, int y, unsigned int color, int fw);
void Draw_StretchPic(int x, int y, int w, int h, qpic_t *pic);
extern float loading_cur_step;
extern char loading_name[32];
extern float loading_num_step;
void Clear_LoadingFill (void);