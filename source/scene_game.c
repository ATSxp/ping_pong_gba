#include "../include/scene_game.h"
#include "../include/gba.h"

#include "gfx_ball.h"
#include "gfx_blocks.h"

GBA_Gfx ball_gfx;
GBA_Sprite ball_spr;

GBA_Gfx block_gfx;
GBA_Sprite block_spr;

void initGame() {
  GBA_setMode(0);
  GBA_enableBg(0);

  GBA_initOam(128);

  ball_gfx = GBA_initGfx(gfx_ball, SPR_SQUARE, false);
  GBA_loadObjects(ball_gfx, 0, 0);

  block_gfx = GBA_initGfx(gfx_blocks, SPR_TALL, false);
  GBA_loadObjects(block_gfx, 1, 1);

  GBA_createSprite(&ball_spr, ball_gfx, 0, 0, 0, 0, 0, 0, SPR_8X8);
  GBA_createSprite(&block_spr, block_gfx, 0, 8, 1, 1, 1, 0, SPR_16X32);
}

void updateGame() {
  key_poll();

  ball_spr.x++;

  GBA_updateSprite(&ball_spr);
  GBA_updateOam();
}

void endGame() {}

GBA_Scene scene_game = {initGame, updateGame, endGame};
