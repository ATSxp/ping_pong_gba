#include "../include/gba_scene.h"
#include "../include/gba_sys.h"
#include "../include/scene_menu.h"

int main() {
  MGBA_DEBUG_ON = 1;
  mgba_open();

  GBA_init();
  GBA_setScene(scene_menu);

  GBA_update();

  mgba_close();

  return 0;
}
