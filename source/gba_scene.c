#include "../include/gba_scene.h"
#include "../include/gba_mgba.h"

#define FUNC_IS_NULL(func)                                                     \
  if (func)                                                                    \
    func();

static bool change_scene = false;
static GBA_Scene cur_scene = {NULL, NULL, NULL},
                 next_scene = {NULL, NULL, NULL};

void GBA_setScene(GBA_Scene new_scene) {
  change_scene = true;
  next_scene = new_scene;
  mgba_printf(MGBA_LOG_INFO, "Scene changed");
}

void GBA_updateScene() {
  if (change_scene) {
    change_scene = false;

    FUNC_IS_NULL(cur_scene.end);

    cur_scene = next_scene;

    FUNC_IS_NULL(cur_scene.init);
  }

  FUNC_IS_NULL(cur_scene.update);
}
