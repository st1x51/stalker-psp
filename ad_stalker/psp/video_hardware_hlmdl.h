/*
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Half-Life Model Renderer (Experimental) Copyright (C) 2001 James 'Ender' Brown [ender@quakesrc.org] This program is
    free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.
    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
    details. You should have received a copy of the GNU General Public License along with this program; if not, write
    to the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA. fromquake.h -
    
	model_hl.h - halflife model structure
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */

#include <cstring>      // memcpy

#define HLPOLYHEADER	(('T' << 24) + ('S' << 16) + ('D' << 8) + 'I')	/* little-endian "IDST" */
#define HLMDLHEADER		"IDST"

#define MAXSTUDIOTRIANGLES	32768	// TODO: tune this
#define MAXSTUDIOVERTS		4096	// TODO: tune this
#define MAXSTUDIOSEQUENCES	256		// total animation sequences
#define MAXSTUDIOSKINS		100		// total textures
#define MAXSTUDIOSRCBONES	512		// bones allowed at source movement
#define MAXSTUDIOBONES		128		// total bones actually used
#define MAXSTUDIOMODELS		32		// sub-models per model
#define MAXSTUDIOBODYPARTS	32
#define MAXSTUDIOGROUPS		4
#define MAXSTUDIOANIMATIONS	512		// per sequence
#define MAXSTUDIOMESHES		256
#define MAXSTUDIOEVENTS		1024
#define MAXSTUDIOPIVOTS		256
#define MAXSTUDIOCONTROLLERS 8

struct vertex
{
    float u, v;
    unsigned int color;
    float x, y, z;
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    main model header
 -----------------------------------------------------------------------------------------------------------------------
 */
typedef struct
{
    int		filetypeid;	//IDSP
	int		version;	//10
    char	name[64];
    int		filesize;
    vec3_t	unknown3[5];

    int		flags;
	int		numbones;
    int		boneindex;
    int		numcontrollers;
    int		controllerindex;
    int		unknown5[2];
    int		numseq;
    int		seqindex;

    int		numseqgroups;	// demand loaded sequences
    int		seqgroups;

	int		numtextures;
    int		textures;
	int		texturedataindex;
	int		numskinref;		// replaceable textures
	int		numskinfamilies;


	int		skins;
    int     numbodyparts;
    int		bodypartindex;

	int		unknown9[8];
} hlmdl_header_t;

typedef struct studiohdr_s
{
	int		id;                 // Model format ID, such as "IDST" (0x49 0x44 0x53 0x54)
	int		version;            // Format version number, such as 48 (0x30,0x00,0x00,0x00)
	int		checksum;           // This has to be the same in the phy and vtx files to load!
	char	name[64];		// The internal name of the model, padding with null bytes.
					// Typically "my_model.mdl" will have an internal name of "my_model"
	int		dataLength;	// Data size of MDL file in bytes.
 
	// A vector is 12 bytes, three 4-byte float-values in a row.
	vec3_t		eyeposition;	// Position of player viewpoint relative to model origin
	vec3_t		illumposition;	// ?? Presumably the point used for lighting when per-vertex lighting is not enabled.
	vec3_t		hull_min;	// Corner of model hull box with the least X/Y/Z values
	vec3_t		hull_max;	// Opposite corner of model hull box
	vec3_t	  	view_bbmin;
	vec3_t	 	view_bbmax;
 
	int		flags;		// Binary flags in little-endian order. 
					// ex (00000001,00000000,00000000,11000000) means flags for position 0, 30, and 31 are set. 
					// Set model flags section for more information
 
	/*
	 * After this point, the header contains many references to offsets
	 * within the MDL file and the number of items at those offsets.
	 *
	 * Offsets are from the very beginning of the file.
	 * 
	 * Note that indexes/counts are not always paired and ordered consistently.
	 */	
 
	// mstudiobone_t
	int		bone_count;	// Number of data sections (of type mstudiobone_t)
	int		bone_offset;	// Offset of first data section
 
	// mstudiobonecontroller_t
	int		bonecontroller_count;
	int		bonecontroller_offset;
 
	// mstudiohitboxset_t
	int		hitbox_count;
	int		hitbox_offset;
 
	// mstudioanimdesc_t
	int		localanim_count;
	int		localanim_offset;
 
	// mstudioseqdesc_t
	int		localseq_count;
	int		localseq_offset;
 
	int		activitylistversion; // ??
	int		eventsindexed;	// ??
 
	// VMT texture filenames
	// mstudiotexture_t
	int		texture_count;
	int		texture_offset;
 
	// This offset points to a series of ints.
        // Each int value, in turn, is an offset relative to the start of this header/the-file,
        // At which there is a null-terminated string.
	int		texturedir_count;
	int		texturedir_offset;
 
	// Each skin-family assigns a texture-id to a skin location
	int		skinreference_count;
	int		skinrfamily_count;
	int             skinreference_index;
 
	// mstudiobodyparts_t
	int		bodypart_count;
	int		bodypart_offset;
 
        // Local attachment points		
	// mstudioattachment_t
	int		attachment_count;
	int		attachment_offset;
 
	// Node values appear to be single bytes, while their names are null-terminated strings.
	int		localnode_count;
	int		localnode_index;
	int		localnode_name_index;
 
	// mstudioflexdesc_t
	int		flexdesc_count;
	int		flexdesc_index;
 
	// mstudioflexcontroller_t
	int		flexcontroller_count;
	int		flexcontroller_index;
 
	// mstudioflexrule_t
	int		flexrules_count;
	int		flexrules_index;
 
	// IK probably referse to inverse kinematics
	// mstudioikchain_t
	int		ikchain_count;
	int		ikchain_index;
 
	// Information about any "mouth" on the model for speech animation
	// More than one sounds pretty creepy.
	// mstudiomouth_t
	int		mouths_count; 
	int		mouths_index;
 
	// mstudioposeparamdesc_t
	int		localposeparam_count;
	int		localposeparam_index;
 
	/*
	 * For anyone trying to follow along, as of this writing,
	 * the next "surfaceprop_index" value is at position 0x0134 (308)
	 * from the start of the file.
	 */
 
	// Surface property value (single null-terminated string)
	int		surfaceprop_index;
 
	// Unusual: In this one index comes first, then count.
	// Key-value data is a series of strings. If you can't find
	// what you're interested in, check the associated PHY file as well.
	int		keyvalue_index;
	int		keyvalue_count;	
 
	// More inverse-kinematics
	// mstudioiklock_t
	int		iklock_count;
	int		iklock_index;
 
 
	float		mass; 		// Mass of object (4-bytes)
	int		contents;	// ??
 
	// Other models can be referenced for re-used sequences and animations
	// (See also: The $includemodel QC option.)
	// mstudiomodelgroup_t
	int		includemodel_count;
	int		includemodel_index;
	
	int		virtualModel;	// Placeholder for mutable-void*
 
	// mstudioanimblock_t
	int		animblocks_name_index;
	int		animblocks_count;
	int		animblocks_index;
	
	int		animblockModel; // Placeholder for mutable-void*

	// Points to a series of bytes?
	int		bonetablename_index;
	
	int		vertex_base;	// Placeholder for void*
	int		offset_base;	// Placeholder for void*
	
	// Used with $constantdirectionallight from the QC 
	// Model should have flag #13 set if enabled
	byte		directionaldotproduct;
	
	byte		rootLod;	// Preferred rather than clamped
	
	// 0 means any allowed, N means Lod 0 -> (N-1)
	byte		numAllowedRootLods;	
	
	byte		unused_0; // ??
	int		unused_1; // ??
	
	// mstudioflexcontrollerui_t
	int		flexcontrollerui_count;
	int		flexcontrollerui_index;
	
	/**
	 * Offset for additional header information.
	 * May be zero if not present, or also 408 if it immediately 
	 * follows this studiohdr_t
	 */
	// studiohdr2_t
	int		studiohdr2index;
	
	int		unused_3; // ??
	
	/**
	 * As of this writing, the header is 408 bytes long in total
	 */
} studiohdr_t;

/*
 -----------------------------------------------------------------------------------------------------------------------
    skin info
 -----------------------------------------------------------------------------------------------------------------------
*/

// lighting options
#define STUDIO_NF_FLATSHADE		0x0001
#define STUDIO_NF_CHROME		0x0002
#define STUDIO_NF_FULLBRIGHT	0x0004

typedef struct
{
    char	name[64];
    int		flags;
    int		w;	/* width */
    int		h;	/* height */
    int		i;	/* index */
} hlmdl_tex_t;


/*
 -----------------------------------------------------------------------------------------------------------------------
    body part index
 -----------------------------------------------------------------------------------------------------------------------
 */
typedef struct
{
    char	name[64];
    int		nummodels;
    int		base;
    int		modelindex;
} hlmdl_bodypart_t;

/*
 -----------------------------------------------------------------------------------------------------------------------
    meshes
 -----------------------------------------------------------------------------------------------------------------------
 */
typedef struct
{
    int numtris;
    int index;
    int skinindex;
    int numnorms;		// per mesh normals
	int normindex;		// normal vec3_t
} hlmdl_mesh_t;

/*
 -----------------------------------------------------------------------------------------------------------------------
    bones
 -----------------------------------------------------------------------------------------------------------------------
 */
typedef struct
{
    char	name[32];
    int		parent;
    int		unknown1;
    int		bonecontroller[6];
    float	value[6];
    float	scale[6];
} hlmdl_bone_t;

/*
 -----------------------------------------------------------------------------------------------------------------------
    bone controllers
 -----------------------------------------------------------------------------------------------------------------------
 */
typedef struct
{
    int		name;
    int		type;
    float	start;
    float	end;
    int		unknown1;
    int		index;
} hlmdl_bonecontroller_t;

/*
 -----------------------------------------------------------------------------------------------------------------------
    halflife model descriptor
 -----------------------------------------------------------------------------------------------------------------------
 */
typedef struct
{
    char	name[64];

    int		type;

    float	boundingradius;

    int		nummesh;
    int		meshindex;

    int		numverts;
    int		vertinfoindex;
    int		vertindex;

	int		numnorms;
	int		norminfoindex;	
	int		normindex;

    int		numgroups;
	int		groupindex;
} hlmdl_model_t;

/*
 -----------------------------------------------------------------------------------------------------------------------
    animation
 -----------------------------------------------------------------------------------------------------------------------
 */
typedef struct
{
    unsigned short	offset[6];
} hlmdl_anim_t;

/*
 -----------------------------------------------------------------------------------------------------------------------
    animation frames
 -----------------------------------------------------------------------------------------------------------------------
 */
typedef union
{
    struct
	{
        byte	valid;
        byte	total;
	} num;
    short	value;
} hlmdl_animvalue_t;

/*
 -----------------------------------------------------------------------------------------------------------------------
    sequence descriptions
 -----------------------------------------------------------------------------------------------------------------------
 */
typedef struct
{
    char	name[32];
    float	timing;
    int		unknown1[5];
    int		numframes;
    int		unknown2[2];
    int		motiontype;
    int		motionbone;
    vec3_t	unknown3;
    int		unknown4[2];
    vec3_t	unknown5[2];
    int		unknown6;
    int		index;
    int		unknown7[2];
    float	unknown[4];
    int		unknown8;
    int		seqindex;
    int		unknown9[4];
} hlmdl_sequencelist_t;

/*
 -----------------------------------------------------------------------------------------------------------------------
    sequence groups
 -----------------------------------------------------------------------------------------------------------------------
 */
typedef struct
{
    char			name[96];	/* should be split label[32] and name[64] */
    void *		cache;
    int				data;
} hlmdl_sequencedata_t;

/*
 -----------------------------------------------------------------------------------------------------------------------
    halflife model internal structure
 -----------------------------------------------------------------------------------------------------------------------
 */
typedef struct
{
    int		sequence;
    int		frame;					/* Current animation sequence and frame */
    float	frametime;				/* Time of last frame drawn */
    float	controller[4];			/* Position of bone controllers */
    float	adjust[4];

    /* Static pointers */
    hlmdl_header_t              *header;
    hlmdl_tex_t                 *textures;
    hlmdl_bone_t                *bones;
    hlmdl_bonecontroller_t		*bonectls;
} hlmodel_t;

typedef struct	//this is stored as the cache. an hlmodel_t is generated when drawing
{
    int header;
    int textures;
    int bones;
    int bonectls;
} hlmodelcache_t;

// lighting options
#define STUDIO_NF_FLATSHADE		0x0001
#define STUDIO_NF_CHROME		0x0002
#define STUDIO_NF_FULLBRIGHT	0x0004

// motion flags
#define STUDIO_X		0x0001
#define STUDIO_Y		0x0002
#define STUDIO_Z		0x0004
#define STUDIO_XR		0x0008
#define STUDIO_YR		0x0010
#define STUDIO_ZR		0x0020
#define STUDIO_LX		0x0040
#define STUDIO_LY		0x0080
#define STUDIO_LZ		0x0100
#define STUDIO_AX		0x0200
#define STUDIO_AY		0x0400
#define STUDIO_AZ		0x0800
#define STUDIO_AXR		0x1000
#define STUDIO_AYR		0x2000
#define STUDIO_AZR		0x4000
#define STUDIO_TYPES	0x7FFF
#define STUDIO_RLOOP	0x8000	// controller that wraps shortest distance

// sequence flags
#define STUDIO_LOOPING	0x0001

// bone flags
#define STUDIO_HAS_NORMALS	0x0001
#define STUDIO_HAS_VERTICES 0x0002
#define STUDIO_HAS_BBOX		0x0004
#define STUDIO_HAS_CHROME	0x0008	// if any of the textures have chrome on them

#define RAD_TO_STUDIO		(32768.0/M_PI)
#define STUDIO_TO_RAD		(M_PI/32768.0)

/* HL mathlib prototypes: */
void	QuaternionGLAngle(const vec3_t angles, vec4_t quaternion);
void	QuaternionGLMatrix(float x, float y, float z, float w, vec4_t *GLM);
//void	UploadTexture(hlmdl_tex_t *ptexture, qbyte *data, qbyte *pal);

/* HL drawing */
qboolean    Mod_LoadHLModel (model_t *mod, void *buffer);
int	        HL_CurSequence(hlmodel_t model);
int	        HL_NewSequence(hlmodel_t * model, int _inew);
void        HL_SetController(hlmodel_t *model, int num, float value);
void        R_DrawHLModel(entity_t	*curent);
