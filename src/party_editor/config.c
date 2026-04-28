#include <string.h>
#include <stdlib.h>
#include "party_editor/dvd.h"

void LoadConfig(void);
void* OpenConfig(u32* outSize);

void LoadConfig()
{
    void* configDataPtr;
    char* text;
    char* line;
    int i = 0;
    int start = 0;

    char* eq;
    char* key;
    char* value;
    u32 configSize;
    long l;

    configDataPtr = OpenConfig(&configSize);
    if (configDataPtr == NULL)
        return;

    // Null ptr at end for reading
    ((char*)configDataPtr)[configSize] = '\0';

    text = ((char*)configDataPtr);
    for (i = 0; i < configSize; i++) {
        if (text[i] == '\n' || i == configSize - 1)
        {
            int len = i - start + (text[i] == '\n' ? 0 : 1);

            char line_buf[256];
            memcpy(line_buf, &text[start], len);
            line_buf[len] = '\0';

            eq = strchr(line_buf, '=');
            if (eq != NULL)
            {
                key = line_buf;
                value = eq + 1;

                if (key == "GWPlayerCfg[0].character")
                {

                }
                OSReport("%s = %s\n", key, value);
            }
            start = i + 1;
        }
    }

    // Free after reading
    if (configDataPtr != 0) {
        HuMemDirectFree(configDataPtr);
        configDataPtr = 0;
    }
}

void* OpenConfig(u32* outSize)
{
    u32 size = 0;
    void* dvd_config;
    void* dataPtr;
    // Config txt
    dvd_config = HuDvdDataReadWithLength("config.txt", &size);
    if (dvd_config == NULL)
        return NULL;

    dataPtr = HuMemDirectMalloc(HEAP_SYSTEM, size);
    memcpy(dataPtr, dvd_config, size);
    HuMemDirectFree(dvd_config);
    *outSize = size;
    return dataPtr;
}