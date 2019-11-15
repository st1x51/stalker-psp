/*
+----+
|Main|
+----+-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-+
| Scratch                                      Http://www.admdev.com/scratch |
+=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-+
| Contains some 'base' subroutines. As a general rule nothing in this file   |
| does much, except to setup basic variables and entities.                   |
+=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-+
*/
void() precaches;
void() LightStyles_setup;

 void() main = {};
 void() worldspawn = 
 {
	 precaches();
	 LightStyles_setup();   
 };

 void() StartFrame = {};
 
void() precaches =
{
	//models
	precache_model ("progs/player.mdl");
	precache_model("sprites/rain.spr");
	precache_model("sprites/fire.spr32");
	precache_model ("models/medkit.mdl");
	precache_model ("models/antirad.mdl");
	precache_model ("models/gasmask.mdl");
	precache_model("models/v_bolt.mdl");
	precache_model("models/v_knife.mdl");
	precache_model("models/v_pm.mdl");
	precache_model("models/v_aksu.mdl");
	precache_model("models/v_toz_bm.mdl");
	precache_model("models/green_neutral.mdl");
	//world models
	precache_model("models/w_bolt.mdl");
	precache_model("models/drink.mdl");
	precache_model("models/w_pm.mdl");
	precache_model("models/w_toz_bm.mdl");
	precache_model("models/w_aksu.mdl");
	
	//car
	precache_model ("models/niva.mdl");
	precache_sound ("car/apc_run.wav");
	//sounds
	precache_sound("player/jump.wav");
	precache_sound("player/breath.wav");
	precache_sound("rain.wav");
	precache_sound("null.wav");
	precache_sound("ambience/fire2.wav");
	precache_sound("player/inv_open.wav");
	precache_sound("player/inv_close.wav");
	precache_sound("player/inv_slot.wav");
	precache_sound("player/inv_drop.wav");
	//foot
	precache_sound ("player/foot/dirt1.wav");
	precache_sound ("player/foot/dirt2.wav");
	precache_sound ("player/foot/dirt3.wav");
	precache_sound ("player/foot/dirt4.wav");
	
	precache_sound ("player/foot/ladder1.wav");
	precache_sound ("player/foot/ladder2.wav");
	precache_sound ("player/foot/ladder3.wav");
	precache_sound ("player/foot/ladder4.wav");
	
	precache_sound ("player/foot/metal1.wav");
	precache_sound ("player/foot/metal2.wav");
	precache_sound ("player/foot/metal3.wav");
	precache_sound ("player/foot/metal4.wav");
	
	precache_sound ("player/foot/slosh1.wav");
	precache_sound ("player/foot/slosh2.wav");
	precache_sound ("player/foot/slosh3.wav");
	precache_sound ("player/foot/slosh4.wav");
	
	precache_sound ("player/foot/tile1.wav");
	precache_sound ("player/foot/tile2.wav");
	precache_sound ("player/foot/tile3.wav");
	precache_sound ("player/foot/tile4.wav");
	
	precache_sound ("player/foot/default1.wav");
	precache_sound ("player/foot/default2.wav");
	precache_sound ("player/foot/default3.wav");
	precache_sound ("player/foot/default4.wav");
	
	precache_sound ("player/foot/wood1.wav");
	precache_sound ("player/foot/wood2.wav");
	precache_sound ("player/foot/wood3.wav");
	precache_sound ("player/foot/wood4.wav");
	//weapons
	precache_sound("weapons/knife/knife_1.wav");
	precache_sound("weapons/pm/pm_shoot.wav");
	precache_sound("weapons/pm/pm_reload.wav");
	precache_sound("weapons/pm/pm_draw.wav");
	precache_sound("weapons/toz/tm_toz34_shot.wav");
	precache_sound("weapons/toz/toz34_reload.wav");
	precache_sound("weapons/aksu/ak74u_reload.wav");
	precache_sound("weapons/aksu/ak74u_shot_0.wav");

	
	precache_sound("reaction/joke/reaction_joke_1.wav");
	precache_sound("reaction/joke/reaction_joke_2.wav");
	precache_sound("reaction/joke/reaction_joke_3.wav");
	
	precache_sound("reaction/music/reaction_music_1.wav");
	precache_sound("reaction/music/reaction_music_2.wav");
	precache_sound("reaction/music/reaction_music_3.wav");
	precache_sound("detectors/da-2_beep1.wav");
};