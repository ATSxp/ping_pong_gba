#include <tonc.h>

#include "../include/gba_scene.h"
#include "../include/gba_sys.h"
#include "../include/scene_game.h"

int main() {
  GBA_setScene(scene_game);

  GBA_init();
  GBA_update();

  return 0;
}
