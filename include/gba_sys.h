#ifndef GBA_SYS_H
#define GBA_SYS_H

#include <maxmod.h>
#include <tonc.h>

#include "gba_mgba.h"
#include "gba_scene.h"

// Enable Background (0-3)
#define GBA_enableBg(bg) BIT_SET(REG_DISPCNT, DCNT_BG##bg);

// Disable Background (0-3)
#define GBA_disableBg(bg) BIT_CLEAR(REG_DISPCNT, DCNT_BG##bg);

// Enable Video Mode (0-3)
INLINE void GBA_setMode(u32 mode) { REG_DISPCNT = DCNT_MODE(mode); }

// Init GBA library
INLINE void GBA_init() {
  irq_init(NULL);
  irq_add(II_VBLANK, mmVBlank);
  irq_enable(II_VBLANK);
}

// Update all GBA library
INLINE void GBA_update() {
  while (true) {
    key_poll();
    mmFrame();
    VBlankIntrWait();
    GBA_updateScene();
  }
}

#endif // !GBA_SYS_H
