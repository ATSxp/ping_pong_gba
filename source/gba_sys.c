#include "../include/gba_sys.h"
#include "../include/gba_scene.h"

// Init GBA library
void GBA_init() {
  irq_init(NULL);
  irq_add(II_VBLANK, mmVBlank);
  irq_enable(II_VBLANK);
}

// Update all GBA library
void GBA_update() {
  while (true) {
    VBlankIntrWait();
    key_poll();
    mmFrame();
    GBA_updateScene();
  }
}
