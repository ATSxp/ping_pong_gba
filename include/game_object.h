#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "gba_oam.h"

typedef struct {
  int dx, dy;
  GBA_Sprite spr;
} GameObject;

#endif // !GAME_OBJECT_H
