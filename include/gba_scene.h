#ifndef GBA_SCENE_H
#define GBA_SCENE_H

#include <tonc.h>

typedef struct {
  fnptr init, update, end;
} GBA_Scene;

void GBA_setScene(GBA_Scene new_scene);
void GBA_updateScene();

#endif // !GBA_SCENE_H
