/*
Copyright (C) 1996-1997 Id Software, Inc.
Copyright (C) 2007 Peter Mackay and Chris Swindle.

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
// r_misc.c

#include <pspgu.h>
#include <pspgum.h>

extern "C"
{
#include "../quakedef.h"
}

void GL_InitTextureUsage ();


int decal_blood1, decal_blood2, decal_blood3, decal_q3blood, decal_burn, decal_mark, decal_glow;

/*
==================
R_InitOtherTextures
==================
*/
void	R_InitOtherTextures (void)
{
	//static decals
	decal_blood1  = loadtextureimage ("textures/decals/blood_splat01", 0, 0, qfalse, GU_LINEAR);
	decal_blood2  = loadtextureimage ("textures/decals/blood_splat02", 0, 0, qfalse, GU_LINEAR);
	decal_blood3  = loadtextureimage ("textures/decals/blood_splat03", 0, 0, qfalse, GU_LINEAR);
    decal_q3blood = loadtextureimage ("textures/decals/blood_stain", 0, 0, qfalse, GU_LINEAR);
	decal_burn	  = loadtextureimage ("textures/decals/explo_burn01", 0, 0, qfalse, GU_LINEAR);
	decal_mark	  = loadtextureimage ("textures/decals/particle_burn01", 0, 0, qfalse, GU_LINEAR);
	decal_glow	  = loadtextureimage ("textures/decals/glow2", 0, 0, qfalse, GU_LINEAR);
}

/*
==================
R_InitTextures
==================
*/
void	R_InitTextures (void)
{
	int		x,y, m;
	byte	*dest;

	GL_InitTextureUsage ();

// create a simple checkerboard texture for the default
	r_notexture_mip = static_cast<texture_t*>(Hunk_AllocName (sizeof(texture_t) + 16*16+8*8+4*4+2*2, "notexture"));
	
	r_notexture_mip->width = r_notexture_mip->height = 16;
	r_notexture_mip->offsets[0] = sizeof(texture_t);
	r_notexture_mip->offsets[1] = r_notexture_mip->offsets[0] + 16*16;
	r_notexture_mip->offsets[2] = r_notexture_mip->offsets[1] + 8*8;
	r_notexture_mip->offsets[3] = r_notexture_mip->offsets[2] + 4*4;
	
	for (m=0 ; m<4 ; m++)
	{
		dest = (byte *)r_notexture_mip + r_notexture_mip->offsets[m];
		for (y=0 ; y< (16>>m) ; y++)
			for (x=0 ; x< (16>>m) ; x++)
			{
				if (  (y< (8>>m) ) ^ (x< (8>>m) ) )
					*dest++ = 0;
				else
					*dest++ = 0xff;
			}
	}	
}

byte	dottexture[8][8] =
{
	{0,1,1,0,0,0,0,0},
	{1,1,1,1,0,0,0,0},
	{1,1,1,1,0,0,0,0},
	{0,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0},
};

byte	dottexture2[16][16] =
{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
	{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
	{0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
	{0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
	{0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0},
	{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
	{0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
int decaltexture;
void R_InitParticleTexture (void)
{
	int		x,y;
	byte	data[16][16][2];

	//
	// particle texture
	//
	
	for (x=0 ; x<16 ; x++)
	{
		for (y=0 ; y<16 ; y++)
		{
			data[y][x][0] = (dottexture2[x][y])*0xF0 | (dottexture2[x][y])*0x0F;
			data[y][x][1] = (dottexture2[x][y])*0xF0 | (dottexture2[x][y])*0x0F;
		}
	}
//	particletexture = GL_LoadTextureLM ("_particle_", 16, 16, &data[0][0][0], 2, GU_LINEAR, qtrue);
//	decaltexture = loadtextureimage("textures/{shot1.tga", 0, 0, qfalse, GU_LINEAR);
	
}

/*
===============
R_Envmap_f

Grab six views for environment mapping tests
===============
*/
void R_Envmap_f (void)
{
	byte	buffer[256*256*4];
	char	name[1024];

	/*glDrawBuffer  (GL_FRONT);
	glReadBuffer  (GL_FRONT);*/
	envmap = qtrue;

	r_refdef.vrect.x = 0;
	r_refdef.vrect.y = 0;
	r_refdef.vrect.width = 256;
	r_refdef.vrect.height = 256;

	r_refdef.viewangles[0] = 0;
	r_refdef.viewangles[1] = 0;
	r_refdef.viewangles[2] = 0;
	GL_BeginRendering (&glx, &gly, &glwidth, &glheight);
	R_RenderView ();
	/*glReadPixels (0, 0, 256, 256, GL_RGBA, GL_UNSIGNED_BYTE, buffer);*/
	COM_WriteFile ("env0.rgb", buffer, sizeof(buffer));		

	r_refdef.viewangles[1] = 90;
	GL_BeginRendering (&glx, &gly, &glwidth, &glheight);
	R_RenderView ();
	/*glReadPixels (0, 0, 256, 256, GL_RGBA, GL_UNSIGNED_BYTE, buffer);*/
	COM_WriteFile ("env1.rgb", buffer, sizeof(buffer));		

	r_refdef.viewangles[1] = 180;
	GL_BeginRendering (&glx, &gly, &glwidth, &glheight);
	R_RenderView ();
	/*glReadPixels (0, 0, 256, 256, GL_RGBA, GL_UNSIGNED_BYTE, buffer);*/
	COM_WriteFile ("env2.rgb", buffer, sizeof(buffer));		

	r_refdef.viewangles[1] = 270;
	GL_BeginRendering (&glx, &gly, &glwidth, &glheight);
	R_RenderView ();
	/*glReadPixels (0, 0, 256, 256, GL_RGBA, GL_UNSIGNED_BYTE, buffer);*/
	COM_WriteFile ("env3.rgb", buffer, sizeof(buffer));		

	r_refdef.viewangles[0] = -90;
	r_refdef.viewangles[1] = 0;
	GL_BeginRendering (&glx, &gly, &glwidth, &glheight);
	R_RenderView ();
	/*glReadPixels (0, 0, 256, 256, GL_RGBA, GL_UNSIGNED_BYTE, buffer);*/
	COM_WriteFile ("env4.rgb", buffer, sizeof(buffer));		

	r_refdef.viewangles[0] = 90;
	r_refdef.viewangles[1] = 0;
	GL_BeginRendering (&glx, &gly, &glwidth, &glheight);
	R_RenderView ();
	/*glReadPixels (0, 0, 256, 256, GL_RGBA, GL_UNSIGNED_BYTE, buffer);*/
	COM_WriteFile ("env5.rgb", buffer, sizeof(buffer));		

	envmap = qfalse;
	/*glDrawBuffer  (GL_BACK);
	glReadBuffer  (GL_BACK);*/
	GL_EndRendering ();
}

/*
===============
R_Init
===============
*/
void R_InitDecals (void);
void R_ToggleDecals_f (void);
void R_ToggleParticles_f (void);
void R_Init (void)
{	
	extern byte *hunk_base;
	/*extern cvar_t gl_finish;*/

	Cmd_AddCommand ("timerefresh", R_TimeRefresh_f);	
	Cmd_AddCommand ("envmap", R_Envmap_f);	
	Cmd_AddCommand ("pointfile", R_ReadPointFile_f);	
    Cmd_AddCommand ("toggleparticles", R_ToggleParticles_f);
	Cmd_AddCommand ("toggledecals",    R_ToggleDecals_f);

	Cvar_RegisterVariable (&r_norefresh);
	Cvar_RegisterVariable (&r_lightmap);
	Cvar_RegisterVariable (&r_fullbright);
	Cvar_RegisterVariable (&r_drawentities);
	Cvar_RegisterVariable (&r_drawviewmodel);
	Cvar_RegisterVariable (&r_shadows);
	Cvar_RegisterVariable (&r_skyfog);
	Cvar_RegisterVariable (&r_mirroralpha);
	Cvar_RegisterVariable (&r_skyclip);
	Cvar_RegisterVariable (&r_wateralpha);
	Cvar_RegisterVariable (&r_dynamic);
	Cvar_RegisterVariable (&r_novis);
	Cvar_RegisterVariable (&r_speeds);
	Cvar_RegisterVariable (&r_tex_scale_down);
	Cvar_RegisterVariable (&r_tex_format);
	Cvar_RegisterVariable (&r_tex_res);
	Cvar_RegisterVariable (&r_particles_simple);
	Cvar_RegisterVariable (&r_vsync);
	Cvar_RegisterVariable (&r_decals);
	Cvar_RegisterVariable (&r_mipmaps);
	Cvar_RegisterVariable (&r_mipmaps_func);
	Cvar_RegisterVariable (&r_mipmaps_bias);
	
	Cvar_RegisterVariable (&r_i_model_animation);
    Cvar_RegisterVariable (&r_i_model_transform);
	Cvar_RegisterVariable (&r_ipolations);
	Cvar_RegisterVariable (&r_asynch);
	Cvar_RegisterVariable (&r_skycolor);
	Cvar_RegisterVariable (&r_farclip);
	Cvar_RegisterVariable (&r_showtris);
	Cvar_RegisterVariable (&r_loddist);
	Cvar_RegisterVariable (&gl_keeptjunctions);
	Cvar_RegisterVariable (&r_hl_render_dist);
/*
	Cvar_RegisterVariable (&gl_finish);
	Cvar_RegisterVariable (&gl_clear);
	Cvar_RegisterVariable (&gl_texsort);

 	if (gl_mtexable)
		Cvar_SetValue ("gl_texsort", 0.0);

	Cvar_RegisterVariable (&gl_cull);
	Cvar_RegisterVariable (&gl_smoothmodels);
	Cvar_RegisterVariable (&gl_affinemodels);
	Cvar_RegisterVariable (&gl_polyblend);
	Cvar_RegisterVariable (&gl_flashblend);
	Cvar_RegisterVariable (&gl_playermip);
	Cvar_RegisterVariable (&gl_nocolors);

	Cvar_RegisterVariable (&gl_reporttjunctions);

	Cvar_RegisterVariable (&gl_doubleeyes);
*/

	Cvar_RegisterVariable (&r_maxrange);

    Cvar_RegisterVariable (&r_laserpoint);
	Cvar_RegisterVariable (&r_part_explosions);
	Cvar_RegisterVariable (&r_part_trails);
	Cvar_RegisterVariable (&r_part_sparks);
    Cvar_RegisterVariable (&r_part_spikes);
	Cvar_RegisterVariable (&r_part_gunshots);
	Cvar_RegisterVariable (&r_part_blood);
	Cvar_RegisterVariable (&r_part_telesplash);
	Cvar_RegisterVariable (&r_part_blobs);
	Cvar_RegisterVariable (&r_part_lavasplash);
	Cvar_RegisterVariable (&r_part_flames);
	Cvar_RegisterVariable (&r_part_lightning);
	Cvar_RegisterVariable (&r_part_flies);
    Cvar_RegisterVariable (&r_explosiontype);
    Cvar_RegisterVariable (&r_part_muzzleflash);

	Cvar_RegisterVariable (&r_showbboxes);
    Cvar_RegisterVariable (&r_showbboxes_full);
	
	R_InitParticles ();
	R_InitParticleTexture ();
	R_InitOtherTextures ();
	R_InitDecals ();

	Sky_Init (); //johnfitz
	Fog_Init (); //johnfitz

#ifdef GLTEST
	Test_Init ();
#endif

	/*
	playertextures = texture_extension_number;
	texture_extension_number += 16;
	*/
}

/*
===============
R_TranslatePlayerSkin

Translates a skin texture by the per-player color lookup
===============
*/
void R_TranslatePlayerSkin (int playernum)
{
	int		top, bottom;
	byte	translate[256];
	unsigned	translate32[256];
	int		i, j, s;
	model_t	*model;
	aliashdr_t *paliashdr;
	byte	*original;
	unsigned	pixels[512*256], *out;
	unsigned	scaled_width, scaled_height;
	int			inwidth, inheight;
	byte		*inrow;
	unsigned	frac, fracstep;
	extern	byte		**player_8bit_texels_tbl;

	/*GL_DisableMultitexture();*/

	top = cl.scores[playernum].colors & 0xf0;
	bottom = (cl.scores[playernum].colors &15)<<4;

	for (i=0 ; i<256 ; i++)
		translate[i] = i;

	for (i=0 ; i<16 ; i++)
	{
		if (top < 128)	// the artists made some backwards ranges.  sigh.
			translate[TOP_RANGE+i] = top+i;
		else
			translate[TOP_RANGE+i] = top+15-i;
				
		if (bottom < 128)
			translate[BOTTOM_RANGE+i] = bottom+i;
		else
			translate[BOTTOM_RANGE+i] = bottom+15-i;
	}

	//
	// locate the original skin pixels
	//
	currententity = &cl_entities[1+playernum];
	model = currententity->model;
	if (!model)
		return;		// player doesn't have a model yet
	if (model->type != mod_alias)
		return; // only translate skins on alias models

	paliashdr = (aliashdr_t *)Mod_Extradata (model);
	s = paliashdr->skinwidth * paliashdr->skinheight;
	if (currententity->skinnum < 0 || currententity->skinnum >= paliashdr->numskins) {
		Con_Printf("(%d): Invalid player skin #%d\n", playernum, currententity->skinnum);
		original = (byte *)paliashdr + paliashdr->texels[0];
	} else
		original = (byte *)paliashdr + paliashdr->texels[currententity->skinnum];
	if (s & 3)
		Sys_Error ("R_TranslateSkin: s&3");

	inwidth = paliashdr->skinwidth;
	inheight = paliashdr->skinheight;

	// because this happens during gameplay, do it fast
	// instead of sending it through gl_upload 8
    /*GL_Bind(playertextures + playernum);*/

#if 0
	byte	translated[320*200];

	for (i=0 ; i<s ; i+=4)
	{
		translated[i] = translate[original[i]];
		translated[i+1] = translate[original[i+1]];
		translated[i+2] = translate[original[i+2]];
		translated[i+3] = translate[original[i+3]];
	}


	// don't mipmap these, because it takes too long
	GL_Upload8 (translated, paliashdr->skinwidth, paliashdr->skinheight, qfalse, qfalse, qtrue);
#else
	scaled_width = 512;
	scaled_height = 256;

	/*if (VID_Is8bit())*/
	{ // 8bit texture upload
		byte *out2;

		out2 = (byte *)pixels;
		memset(pixels, 0, sizeof(pixels));
		fracstep = inwidth*0x10000/scaled_width;
		for (i=0 ; i<scaled_height ; i++, out2 += scaled_width)
		{
			inrow = original + inwidth*(i*inheight/scaled_height);
			frac = fracstep >> 1;
			for (j=0 ; j<scaled_width ; j+=4)
			{
				out2[j] = translate[inrow[frac>>16]];
				frac += fracstep;
				out2[j+1] = translate[inrow[frac>>16]];
				frac += fracstep;
				out2[j+2] = translate[inrow[frac>>16]];
				frac += fracstep;
				out2[j+3] = translate[inrow[frac>>16]];
				frac += fracstep;
			}
		}

		/*GL_Upload8((byte *)pixels, scaled_width, scaled_height, qfalse, qfalse);*/
		return;
	}


	for (i=0 ; i<256 ; i++)
		translate32[i] = d_8to24table[translate[i]];
/*
	out = pixels;
	fracstep = inwidth*0x10000/scaled_width;
	for (i=0 ; i<scaled_height ; i++, out += scaled_width)
	{
		inrow = original + inwidth*(i*inheight/scaled_height);
		frac = fracstep >> 1;
		for (j=0 ; j<scaled_width ; j+=4)
		{
			out[j] = translate32[inrow[frac>>16]];
			frac += fracstep;
			out[j+1] = translate32[inrow[frac>>16]];
			frac += fracstep;
			out[j+2] = translate32[inrow[frac>>16]];
			frac += fracstep;
			out[j+3] = translate32[inrow[frac>>16]];
			frac += fracstep;
		}
	}
	glTexImage2D (GL_TEXTURE_2D, 0, gl_solid_format, scaled_width, scaled_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	*/
#endif

}

void R_ClearDecals(void);
/*
===============
R_NewMap
===============
*/
void R_NewMap (void)
{
	int		i;
	
	for (i=0 ; i<256 ; i++)
		d_lightstylevalue[i] = 264;		// normal light value

	memset (&r_worldentity, 0, sizeof(r_worldentity));
	r_worldentity.model = cl.worldmodel;

// clear out efrags in case the level hasn't been reloaded
// FIXME: is this one short?
	for (i=0 ; i<cl.worldmodel->numleafs ; i++)
		cl.worldmodel->leafs[i].efrags = NULL;
		 	
	r_viewleaf = NULL;
	R_ClearParticles ();
//Crow_bar Decals
	R_ClearDecals();

	GL_BuildLightmaps ();

	Sky_NewMap (); //johnfitz -- skybox in worldspawn
	Fog_NewMap (); //johnfitz -- global fog in worldspawn

	// identify sky texture
	skytexturenum = -1;
	mirrortexturenum = -1;
	for (i=0 ; i<cl.worldmodel->numtextures ; i++)
	{
		if (!cl.worldmodel->textures[i])
			continue;
		if (!Q_strncmp(cl.worldmodel->textures[i]->name,"sky",3) )
			skytexturenum = i;
		if (!Q_strncmp(cl.worldmodel->textures[i]->name,"window02_1",10) )
			mirrortexturenum = i;
 		cl.worldmodel->textures[i]->texturechain = NULL;
	}
#ifdef QUAKE2
	R_LoadSkys ();
#endif
}


/*
====================
R_TimeRefresh_f

For program optimization
====================
*/
void R_TimeRefresh_f (void)
{
	int			i;
	double		start, stop, time;
	int			startangle;
	vrect_t		vr;


	start = Sys_FloatTime ();
	for (i=0 ; i<128 ; i++)
	{
		r_refdef.viewangles[1] = i/128.0*360.0;
		R_RenderView ();
	}

	stop = Sys_FloatTime ();
	time = stop-start;
	if (time > 0) 
		Con_Printf ("%f seconds (%f fps)\n", time, 128/time);

	GL_EndRendering ();
}

void D_FlushCaches (void)
{
}


