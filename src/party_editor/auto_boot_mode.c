#include "ext_math.h"
#include "game/audio.h"
#include "game/chrman.h"
#include "game/board/main.h"
#include "game/data.h"
#include "game/gamework_data.h"
#include "game/hsfman.h"
#include "game/minigame_seq.h"
#include "game/memory.h"
#include "game/msm.h"
#include "game/object.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/window.h"
#include "math.h"
#include "game/armem.h"
#include "data_num/title.h"
#include "game/saveload.h"
#include "party_editor/main.h"
#include "party_editor/config.h"

Process* objman;
s32 CONFIG_HEAP_SIZE = 0x100;

void BootExec(void);
void LoadBoardAuto(void);
void InitBoardHeap(void);

void PartyEditorBoot(Process* process)
{
    objman = process;
    BootExec();
}

void BootExec()
{
    s16 i;
    void* group_samp;
    // Controller slots
    for (i = 0; i < 4; i++) {
        GWPlayerCfg[i].pad_idx = i;
    }

    // Init for boot
    CharManInit();
    HuWindowInit();
    MGSeqInit();
    HuWinInit(1);

    // Init group heap
    group_samp = HuMemDirectMalloc(HEAP_DATA, msmSysGetSampSize(0));
    msmSysLoadGroup(0, group_samp, 0);
    HuMemDirectFree(group_samp);

    for (i = 0; i < 4; i++) {
        GWPlayerCfg[i].character = -1;
    }

    LoadBoardAuto();

    HuPrcEnd();
    do {
        HuPrcVSleep();
    } while (1);
}

void LoadBoardAuto()
{
    s32 spC[MAX_BOARD_COUNT] = WORLD_OVERLAY_TABLE;
    s32 players[4] = { 0, 1, 2, 3 };
    s32 coms[4] = { 0, 1, 1, 1 };
    s32 board_id = AUTO_BOOT_BOARD_ID;
    // Configure settings
    s32 i = 0;
    s32 result = 0;

    for (i = 0; i < 4; i++) {
        GWPlayerCfg[i].character = players[i];
        GWPlayerCfg[i].diff = 0;
        GWPlayerCfg[i].group = 0;
        GWPlayerCfg[i].iscom = coms[i];
    }

    LoadConfig();

    GWSystem.max_turn = 0x14;
    BoardSaveInit(board_id);
    // Custom override
    // Skips intro
    _SetFlag(FLAG_ID_MAKE(1, 1));

    // Memory related functions based on ment dll
    // Init board data to ram
    HuPrcChildCreate(InitBoardHeap, 0x64, 0x3000, 0, objman);
    CharModelKill(-1);
    MGSeqKillAll();

    CharARAMOpen(GWPlayerCfg[0].character);
    CharARAMOpen(GWPlayerCfg[1].character);
    CharARAMOpen(GWPlayerCfg[2].character);
    CharARAMOpen(GWPlayerCfg[3].character);

    // Load the current save file
 /*   result = SLLoad();
    SLSaveFlagSet(1);
    // Load stats
    SLLoadGameStat();

    OSReport("Save Test party_continue  %d\n", GWGameStat.party_continue);

    // Retain the original save as an option
    if (GWGameStat.party_continue == 1)
    {
        SLLoadBoard();
    }*/

    omOvlCallEx(spC[GWSystem.board], 1, 0, 0);
}

void InitBoardHeap(void)
{
    s32 spC[MAX_BOARD_COUNT] = WORLD_OVERLAY_TABLE;
    s32 lbl_1_data_2B4[] = WORLD_DIR_TABLE;

    s32 var_r31 = HuDataDirReadAsync(DATADIR_BOARD);

    if (var_r31 != -1) {
        while (HuDataGetAsyncStat(var_r31) == 0) {
            HuPrcVSleep();
        }
    }
    HuAR_MRAMtoARAM(DATADIR_BOARD);
    while (HuARDMACheck() != 0) {
        HuPrcVSleep();
    }
    HuDataDirClose(DATADIR_BOARD);
    if (_CheckFlag(FLAG_ID_MAKE(1, 11)) != 0) {
        var_r31 = HuDataDirReadAsync(DATADIR_W10);
    }
    else {
        var_r31 = HuDataDirReadAsync(lbl_1_data_2B4[GWSystem.board]);
    }
    if (var_r31 != -1) {
        while (HuDataGetAsyncStat(var_r31) == 0) {
            HuPrcVSleep();
        }
    }
    HuPrcEnd();
    while (1) {
        HuPrcVSleep();
    }
}

static u16 progPosTbl[] = { 236, 313, 353, 313 };