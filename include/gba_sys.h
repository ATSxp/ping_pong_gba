#ifndef GBA_SYS_H
#define GBA_SYS_H

#include <tonc.h>

#define GBA_setMode(mode) REG_DISPCNT = DCNT_MODE(mode);
#define GBA_enableBg(bg) BIT_SET(REG_DISPCNT, DCNT_BG##bg);
#define GBA_disableBg(bg) BIT_CLEAR(REG_DISPCNT, DCNT_BG##bg);

#endif // !GBA_SYS_H
