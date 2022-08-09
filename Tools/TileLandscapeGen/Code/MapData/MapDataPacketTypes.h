#ifndef MAP_DATA_PACKET_TYPES_H
#define MAP_DATA_PACKET_TYPES_H


#define		NUM_TERRAIN_LINES_IN_PACKET		4
#define		NUM_WALLS_IN_PACKET				4
#define		NUM_TERRAIN_IN_PACKET			8

enum
{ 
	MAP_INVALID = 0,
	MAP_FOREST,					// 1
	MAP_LINE_OF_TREES,			// 2
	MAP_LEGACY1,				// 3
	MAP_LEGACY2,				// 4
	MAP_LINE_OF_TERRAIN,		// 5
	MAP_TERRAIN,				// 6
	MAP_WALL,					// 7
	MAP_ITEM_DELETED,			// 8
	MAP_RACE_CHECKPOINT_LINE,	// 9
	MAP_RACE_SPAWN_POINT,		// 10
	MAP_LAKE,					// 11
	MAP_RIVER_SOURCE,			// 12
	MAP_BOX_OF_TERRAIN,			// 13
	MAP_SPAWN_POINT,			// 14
	MAP_CRATER,					// 15
	MAP_TILE_ROTATION,			// 16
	MAP_CROW_FLAG,				// 17
	MAP_SAFE_ZONE,				// 18
	MAP_TEXTURE_MAP,			// 19
	MAP_LINE_OF_MODEL,			// 20
	MAP_HORNBALL_PITCH,			// 21
	MAP_HORNBALL_GOAL,			// 22
	MAP_VEHICLE,				// 23
	MAP_SURFACE_PAINT,			// 24
	MAP_WICKET,					// 25
	MAP_BOWLER,					// 26
	MAP_BATSMAN,				// 27
	MAP_BONGOSQUARES_PITCH,		// 28
	MAP_WILDLIFE_REGION,		// 29
	MAP_BUILD_ZONE,				// 30
	MAP_NO_BUILD_ZONE,			// 31
	MAP_BUILDING,				// 32
	MAP_FOREST_OF_BGMODELS,		// 33
	MAP_SOUNDZONE,				// 34
	MAP_AUTOROAD,				// 35
	MAP_CUSTOMRACE_CHECKPOINT,	// 36
	MAP_BUILDING_CONNECTOR,		// 37
	MAP_LOCALISED_EFFECT,		// 38

	MAX_NUM_VALID_MAP_PACKET_TYPES,		// EOL
};



typedef struct
{
	ulong	aulTexIndex[NUM_TERRAIN_IN_PACKET];

} MAP_PACKET_TERRAIN;

typedef struct
{
	ulong	ulTexIndex1;
	ulong	ulTexIndex2;

} ONE_LINE_OF_TERRAIN;

typedef struct
{
	ONE_LINE_OF_TERRAIN		axPackets[NUM_TERRAIN_LINES_IN_PACKET];

} MAP_PACKET_LINE_OF_TERRAIN;


typedef struct
{
	ONE_LINE_OF_TERRAIN		axPackets[NUM_TERRAIN_LINES_IN_PACKET];

} MAP_PACKET_BOX_OF_TERRAIN;		// line_of_terrain and box_of_terrain should be the same for now..

typedef struct
{
	float	fCheckpointX;
	float	fCheckpointY;
	float	fCheckpointZ;

	float	fRotationX;
	float	fRotationZ;

	BYTE	bCheckpointType;
	BYTE	bCheckpointPad1;
	short	wCheckpointPad2;

	ulong	ulCheckpointPad3;

} MAP_PACKET_CUSTOMRACE_CHECKPOINT;

typedef struct
{
	ulong	ulCourseIndex1;
	ulong	ulModeIndex2;

} MAP_PACKET_RACE_CHECKPOINT_LINE;

typedef struct
{
	ulong	ulBuildingRecordNum1;
	ulong	ulBuildingRecordNum2;
	float	fHeight;
	BYTE	bMode;
	BYTE	bPad1;
	ushort	uwPad1;

	ulong	ulPad1;

} MAP_PACKET_BUILDING_CONNECTOR;


typedef struct
{
	ulong	ulTypeIndex1;
	ulong	ulIndex2;

} ONE_WALL;

typedef struct
{
	ONE_WALL		axPackets[NUM_WALLS_IN_PACKET];

} MAP_PACKET_WALL;

typedef struct
{
	float	fX;
	float	fY;
	float	fSpread;
	short	wNumTrees;
	short	wTreeType;

} MAP_PACKET_FOREST;

typedef struct
{
	short	wCraterType;
	short	wCraterParam;
	short	wMapX;
	short	wMapY;
	int		nSize;
	int		nDepth;
	
	ulong	ulPad1;

} MAP_PACKET_CRATER;

typedef struct
{
	int		nIndex;
	BYTE	bSurfaceNum;
	BYTE	bTolerance;
	BYTE	bPad1;
	BYTE	bPad2;

} MAP_PACKET_PAINT_FILL;


typedef struct
{
	float	fX1;
	float	fY1;
	float	fX2;
	float	fY2;
	short	wNumTrees;
	short	wTreeType;

} MAP_PACKET_LINE_OF_TREES;


typedef struct
{
	int		nIndex;
	short	wBuildingCode;
	ushort	uwDamage;

	short	wBuildingRecordNum;
	BYTE	bConstructionFlags;
	BYTE	bPad1;
	ushort	uwRentedBy;
	ushort	uwFamily;

	float	fBuildingPositionX;
	float	fBuildingPositionY;
	ulong	ulPadForZ;
	
	ulong	ulPad1;
	ulong	ulPad2;

} MAP_PACKET_BUILDING;





#endif