
#ifndef PARTY_EDITOR_MAIN_H
#define PARTY_EDITOR_MAIN_H

#define BOARD_ID_CUSTOM1 9
#define BOARD_ID_CUSTOM2 10
#define BOARD_ID_CUSTOM3 12
#define BOARD_ID_CUSTOM4 13

// Patch to expand board data
#define EXPAND_BOARD_PATCH NON_MATCHING && 1
// Patch boot directly into the game
#define AUTO_BOOT_MODE NON_MATCHING && 1
// The board ID to boot into
#define AUTO_BOOT_BOARD_ID 0
// We use stream music for any custom boards rather than sound sequences
#define USE_STREAM_MUSIC GWBoardGet() >= 9

#if EXPAND_BOARD_PATCH
    // Total board count. Must match the amount of new slots being added
    #define MAX_BOARD_COUNT 10
    // Board count when original is 6
    #define MAX_BOARD6_COUNT 10 
#else
    // Counter for total board count
    #define MAX_BOARD_COUNT 9
    // Counter for when 6 board max is used
    #define MAX_BOARD6_COUNT 6 
#endif

#define GET_BOARD_ID                   \
if (omcurovl == OVL_W30)                \
    GWSystem.board = BOARD_ID_CUSTOM1; \


#if EXPAND_BOARD_PATCH
    // Add multiple overlays for new slots, ie OVL_W30, OVL_W31
    #define CUSTOM_OVERLAYS OVL_W30
    // Add multiple dirs for new slots, ie DATADIR_W30, DATADIR_W31
    #define CUSTOM_BOARD_DIRS DATADIR_W30
#else
    #define CUSTOM_OVERLAYS
    #define CUSTOM_BOARD_DIRS
#endif

 
// Audio sound data for board
#define CUSTOM_AUDIO_SND { OVL_W30, 10, 0,  1, -1, -1 }

// game/board/audio.c. This MUST be part of CUSTOM_AUDIO_SND group ie OVL_W30, 9
#define CUSTOM_MUSIC_ID 23, 24, 25, 26, 27, 28, 29, 30

// item.c ExecItemWhistle()
#define FORCE_MOVE_SFX 0x38

// callAttackMotTbl[] from item.c
#define CUSTOM_CALL_ATTACK_MOT1 DATA_MAKE_NUM(DATADIR_W01, 31)
#define CUSTOM_CALL_ATTACK_MOT2 DATA_MAKE_NUM(DATADIR_W01, 32)

// messBaseTbl[] from last5.c
#define CUSTOM_LAST5_MESS_TBL MAKE_MESSID(14, 0)
#define CUSTOM_LAST5_MOT_TBL                                \
{                                                             \
    DATA_MAKE_NUM(DATADIR_BLAST5, 63),                       \
    DATA_MAKE_NUM(DATADIR_BLAST5, 64),                       \
    DATA_MAKE_NUM(DATADIR_BLAST5, 65),                       \
    DATA_MAKE_NUM(DATADIR_BLAST5, 66),                       \
    DATA_MAKE_NUM(DATADIR_BLAST5, 67),                       \
    DATA_MAKE_NUM(DATADIR_BLAST5, 68),                        \
    DATA_MAKE_NUM(DATADIR_BLAST5, 69),                        \
    DATA_MAKE_NUM(DATADIR_BLAST5, 70),                        \
}

// view.c Controls the camera top view size
#define CUSTOM_CAMERA_VIEW_MIN_Z -1800.0
#define CUSTOM_CAMERA_VIEW_MAX_Z 2000.0
#define CUSTOM_CAMERA_VIEW_MIN_X -2000.0
#define CUSTOM_CAMERA_VIEW_MAX_X 8000.0
#define CUSTOM_CAMERA_OVERHEAD_ZOOM 10000.0
#define CUSTOM_CAMERA_OVERHEAD_POSZ 0.0

#define CUSTOM_CAMERA_FOCUS        \
    camStartFocusPos.y = 100.0f;    \
    camStartFocusPos.z = 500.0f;    \

// boo_house.c
#define CUSTOM_BOO_HOUSE_HOST_MESS                                \
{                                                             \
    DATA_MAKE_NUM(DATADIR_BOARD, 0x0C),                       \
    DATA_MAKE_NUM(DATADIR_BOARD, 0x0D),                       \
    DATA_MAKE_NUM(DATADIR_BOARD, 0x0E),                       \
    DATA_MAKE_NUM(DATADIR_BOARD, 0x0F),                       \
    DATA_MAKE_NUM(DATADIR_BOARD, 0x10),                       \
    DATA_MAKE_NUM(DATADIR_BOARD, 0x11)                        \
}

#define CUSTOM_BOO_HOUSE_HOST { DATA_MAKE_NUM(DATADIR_BGUEST, 0x01), DATA_MAKE_NUM(DATADIR_BGUEST, 0x03), DATA_MAKE_NUM(DATADIR_BGUEST, 0x04) }

// boo.c hostMess
#define CUSTOM_BOO_MESS MAKE_MESSID(7, 14)

// lottery.c sp20 in CreateModel()
#define CUSTOM_LOTTERY_GUEST            \
{                                       \
    DATA_MAKE_NUM(DATADIR_BGUEST, 42),  \
    DATA_MAKE_NUM(DATADIR_BGUEST, 43),  \
    DATA_MAKE_NUM(DATADIR_BGUEST, 44),  \
    DATA_MAKE_NUM(DATADIR_BGUEST, 45)   \
 }      

// lottery.c Todo use GWBoardGet() to set per board
#define CUSTOM_LOTTERY_MESSID MAKE_MESSID(6, 82);

// start.c InitCamera() Todo use GWBoardGet() to set per board
#define CUSTOM_CAMERA_FOCUS        \
    camStartFocusPos.y = 100.0f;    \
    camStartFocusPos.z = 500.0f;    \

// board/main.c InitCamera() Todo use omcurovl == OVL_W## to set per board
#define CUSTOM_SET_BOARD_ID        \
    GWSystem.board = BOARD_ID_CUSTOM1; \

// UI elements
// pause.c boardLogoTbl
#define CUSTOM_BOARD_LOGO DATA_MAKE_NUM(DATADIR_BOARD, 94)
// start.c logoSprTbl
#define CUSTOM_BOARD_START_LOGO DATA_MAKE_NUM(DATADIR_BOARD, 94)
// start.c startMesTbl
#define CUSTOM_BOARD_START_MESS { MAKE_MESSID(0x15, 0x3B), MAKE_MESSID(0x15, 0x3C), MAKE_MESSID(0x15, 0x3D), MAKE_MESSID(0x15, 0x3E), MAKE_MESSID(0x15, 0x3F) }
// mg_setup.c luckyMessTbl
#define CUSTOM_LUCKY_MESS MAKE_MESSID(0x14, 0x00)

// shop.c hostMessTbl
#define CUSTOM_SHOP_MESSID MAKE_MESSID(0x0F, 0x04)
// shop.c shopMotTbl
#define CUSTOM_SHOP_MOT { DATA_MAKE_NUM(DATADIR_BGUEST, 0x01), DATA_MAKE_NUM(DATADIR_BGUEST, 0x03), DATA_MAKE_NUM(DATADIR_BGUEST, 0x04) },

// star.c
#define CUSTOM_STAR_HOST_MOT { DATA_MAKE_NUM(DATADIR_W01, 33), DATA_MAKE_NUM(DATADIR_BOARD, 157) }
#define CUSTOM_STAR_MESS1 MAKE_MESSID(12, 0)
#define CUSTOM_STAR_MESS2 { MAKE_MESSID(21, 34), MAKE_MESSID(21, 40) }


#if EXPAND_BOARD_PATCH
// Used in com.c for pathing and to allow star spaces in space.c
#define BOARD_IS_CUSTOM GWBoardGet() > BOARD_ID_EXTRA2
// view.c and start.c if user needs light hook reset on board
#define CUSTOM_RESET_LIGHT_HOOK GWBoardGet() == 100
// Used for patching in potential errors if the user makes export mistakes
// One patch fixes the mandatory 8 star spaces, so only one is needed for it to function.
#define CUSTOM_BOARD_FIXES 1

#else // disable for matching

#define BOARD_IS_CUSTOM 0
#define CUSTOM_RESET_LIGHT_HOOK 0
#define CUSTOM_BOARD_FIXES 0

#endif

#define WORLD_OVERLAY_TABLE \
{                   \
    OVL_W01,        \
    OVL_W02,        \
    OVL_W03,        \
    OVL_W04,        \
    OVL_W05,        \
    OVL_W06,        \
    OVL_W10,        \
    OVL_W20,        \
    OVL_W21,        \
    CUSTOM_OVERLAYS \
}
#define WORLD_DIR_TABLE                                   \
{                                                         \
    DATADIR_W01,                                          \
    DATADIR_W02,                                          \
    DATADIR_W03,                                          \
    DATADIR_W04,                                          \
    DATADIR_W05,                                          \
    DATADIR_W06,                                          \
    DATADIR_W10,                                          \
    DATADIR_W20,                                          \
    DATADIR_W21,                                          \
    CUSTOM_BOARD_DIRS                                     \
}

#endif // PARTY_EDITOR_MAIN_H