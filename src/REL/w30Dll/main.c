#include "game/board/space.h"
#include "game/board/model.h"
#include "game/board/main.h"
#include "game/board/star.h"
#include "game/board/shop.h"
#include "game/board/player.h"
#include "game/chrman.h"
#include "game/audio.h"
#include "game/board/view.h"

#include "game/data.h"
#include "datadir_enum.h"

enum {
	W30_SPACEDATA = DATA_MAKE_NUM(DATADIR_W30, 0),
	W30_BACKGROUND = DATA_MAKE_NUM(DATADIR_W30, 1),
	W30_BOARDMODEL = DATA_MAKE_NUM(DATADIR_W30, 2),
};

static s16 bgMdl = -1;
static s16 fgMdl = -1;
static s16 hostMdl = -1;
static s16 starHostMdl = -1;

static s32 starHostMotTbl[] = { DATA_MAKE_NUM(DATADIR_W01, 30), -1 };

static s32 hostMotTbl[] = {
	DATA_MAKE_NUM(DATADIR_BGUEST, 42),
	-1
};
static void ReadCustomFile(s32 data_num);
static void LightSetHook(void);
static void LightResetHook(void);
static s32 WalkEvent(void);
static s32 WalkMiniEvent(void);
static s32 LandEvent(void);

void BoardCreate(void)
{
	BoardSpaceInit(W30_SPACEDATA);
	bgMdl = BoardModelCreate(W30_BACKGROUND, NULL, 0);
	fn_8006DDE8(bgMdl, -1.0f);
	BoardModelMotionStart(bgMdl, 0, HU3D_MOTATTR_LOOP);
	fgMdl = BoardModelCreate(W30_BOARDMODEL, NULL, 0);
	fn_8006DDE8(fgMdl, -1.0f);
	BoardModelPosSet(fgMdl, 0.0f, 0.0f, 0.0f);
	BoardModelMotionStart(fgMdl, 0, HU3D_MOTATTR_LOOP);

	//ViewSetCameraTables(BOARD_ID_CUSTOM1, -2000.0, -2000.0, 7000.0, 2000.0, 10000.0, 0);
		
	starHostMdl = BoardModelCreate(DATA_MAKE_NUM(DATADIR_W01, 29), starHostMotTbl, 0);
	BoardModelPosSet(starHostMdl, 0.0f, 0.0f, 0.0f);
	BoardModelMotionStart(starHostMdl, 1, HU3D_MOTATTR_LOOP);

	hostMdl = BoardModelCreate(DATA_MAKE_NUM(DATADIR_BGUEST, 41), hostMotTbl, 0);
	BoardModelPosSet(hostMdl, 0.0f, 0.0f, 0.0f);
	BoardModelMotionStart(hostMdl, 1, HU3D_MOTATTR_LOOP);
	BoardLightHookSet(LightSetHook, LightResetHook);
	BoardSpaceWalkEventFuncSet(WalkEvent);
	BoardSpaceWalkMiniEventFuncSet(WalkMiniEvent);
	BoardSpaceLandEventFuncSet(LandEvent);
	BoardStarHostSet(starHostMdl);
	BoardShopHostSet(hostMdl);
}

s32 GetIndexByString()
{

}

void ReadStringTable(s32 data_num) {
	u8* data;
	u8* data_base;
	data_base = data = HuDataSelHeapReadNum(data_num, MEMORY_DEFAULT_NUM, HEAP_DATA);



	HuDataClose(data_base);
}

void BoardDestroy(void)
{
	if(hostMdl != -1) {
		BoardModelKill(hostMdl);
		hostMdl = -1;
	}
	if(bgMdl != -1) {
		BoardModelKill(bgMdl);
		bgMdl = -1;
	}
	if(fgMdl != -1) {
		BoardModelKill(fgMdl);
		fgMdl = -1;
	}
	if (starHostMdl != -1) {
		BoardModelKill(starHostMdl);
		starHostMdl = -1;
	}
}

static void LightSetHook(void)
{
	s16 id = BoardModelIDGet(bgMdl);
	Hu3DModelLightInfoSet(id, 1);
}

static void LightResetHook(void)
{
	Hu3DFogClear();
	Hu3DFogSet(100, 100, 1, 1, 1);
}

static s32 WalkEvent(void)
{
	s32 playerNo;
	BoardSpace* space;

	playerNo = GWSystem.player_curr;
	space = BoardSpaceGet(0, GWPlayer[playerNo].space_curr);

	BoardPlayerCoinsAdd(playerNo, 5);
	HuAudFXPlay(7);

	return 0;
}

static s32 WalkMiniEvent(void)
{
	
}

static s32 LandEvent(void)
{
	
}