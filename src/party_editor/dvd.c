#include "game/dvd.h"
#include "game/data.h"

// Adjusted version of dvd.h but with method to get file size HuDvdDataReadWithLength().

static int CallBackStatus;

static void HuDVDReadAsyncCallBack(s32 result, DVDFileInfo* fileInfo)
{
    CallBackStatus = 1;
}

static void* HuDvdDataReadWait(DVDFileInfo* file, int heap, int mode, int num, DVDCallback cb, BOOL skip_wait)
{
    u32 len;
    void* buf;
    if (mode != 0 && mode != 1 && mode != 2) {
        OSReport("dvd.c: HuDvdDataReadWait Mode Error");
        buf = NULL;
        len = 0;
    }
    len = file->length;
    DirDataSize = len;
    if (mode == 1) {
        buf = HuMemDirectMallocNum(heap, OSRoundUp32B(len), num);
    }
    else {
        buf = HuMemDirectMalloc(heap, OSRoundUp32B(len));
    }
    if (!buf) {
        OSReport("dvd.c: Memory Allocation Error (Length %x) (mode %d)\n", len, mode);
        OSReport("Rest Memory %x\n", HuMemHeapSizeGet(3) - HuMemUsedMallocSizeGet(3));
        OSPanic("dvd.c", 75, "\n");
        return NULL;
    }

    DCInvalidateRange(buf, OSRoundUp32B(len));
    OSReport("Rest Memory %x\n", HuMemHeapSizeGet(3) - HuMemUsedMallocSizeGet(3));
    CallBackStatus = 0;
    DVDReadAsync(file, buf, OSRoundUp32B(len), 0, cb);
    if (!skip_wait) {
        while (!CallBackStatus) {
            HuDvdErrorWatch();
        }
        HuDvdErrorWatch();
    }

    return buf;
}



void* HuDvdDataReadWithLength(char* path, u32* size)
{
    DVDFileInfo file;
    void* data = NULL;
    if (!DVDOpen(path, &file)) {
        return NULL;
    }
    else {
        data = HuDvdDataReadWait(&file, HEAP_DVD, 0, 0, HuDVDReadAsyncCallBack, FALSE);
        size[0] = file.length;
        DVDClose(&file);
    }
    return data;
}
