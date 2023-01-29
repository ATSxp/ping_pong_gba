#include <tonc.h>

#include "../include/gba_scene.h"
#include "../include/scene_game.h"

int main() {
  GBA_setScene(scene_game);

  irq_init(NULL);
  irq_add(II_VBLANK, GBA_updateScene);
  irq_enable(II_VBLANK);

  while (true) {
    VBlankIntrWait();
  }
  return 0;
}
