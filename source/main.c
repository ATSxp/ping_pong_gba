#include "../include/gba_scene.h"
#include "../include/gba_sys.h"
#include "../include/scene_intro.h"

int main() {
  mgba_open();

  GBA_init();
  GBA_setScene(scene_intro);

  GBA_update();

  mgba_close();

  return 0;
}
