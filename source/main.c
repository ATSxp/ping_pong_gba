#include <tonc.h>

#include "../include/gba_scene.h"
#include "../include/gba_sys.h"
#include "../include/scene_game.h"

int main() {
  if (mgba_open()) {
    mgba_printf(MGBA_LOG_INFO, "Debug log ON");
  }

  GBA_init();
  GBA_setScene(scene_game);
  GBA_update();

  mgba_close();

  return 0;
}
