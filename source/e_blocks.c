#include "../include/e_blocks.h"
#include "../include/e_ball.h"

#include "gfx_blocks.h"

#define BLOCK_INIT_Y (SCREEN_HEIGHT - 32)/2
#define BLOCK_SPEED 2

GBA_Gfx blocks_gfx;
GBA_Sprite block_spr, block2_spr;

int dy1, dy2;
u32 point1, point2, b2_state;

void initBlocks() {
  blocks_gfx = GBA_initGfx(gfx_blocks, SPR_TALL, false);
  GBA_loadObjects(blocks_gfx, 5, 1);

  GBA_createSprite(&block_spr, blocks_gfx, -1, 16, BLOCK_INIT_Y, 5, 1, 1,
                   SPR_16X32);
  GBA_createSprite(&block2_spr, blocks_gfx, -1, SCREEN_WIDTH - 32, BLOCK_INIT_Y,
                   13, 1, 1, SPR_16X32);

  dy1 = dy2 = 0;
  point1 = point2 = 0;
}

void updateBlocks() {
  GBA_Sprite *p = &block_spr, *e = &block2_spr;

  dy1 = 0;
  dy2 = 0;

  // Player
  if (key_is_down(KEY_UP) && p->y > 0) {
    dy1 = -BLOCK_SPEED;
  } else if (key_is_down(KEY_DOWN) && p->y < SCREEN_HEIGHT - 32) {
    dy1 = BLOCK_SPEED;
  }

  // Rival
  int dy = ball_spr.y - e->y;

  if (e->y < 0) {
    e->y = 0;
  } else if (e->y > SCREEN_HEIGHT - 32) {
    e->y = SCREEN_HEIGHT - 32;
  }

  if (ball_spr.x > (SCREEN_WIDTH / 2) - 32) {
    mgba_printf(MGBA_LOG_DEBUG, "rnd: %d", b2_state); // Tmp

    if (ABS(dy) >= BLOCK_SPEED) {
      if (b2_state == 0) {
        dy2 = dy > 0 ? BLOCK_SPEED : -BLOCK_SPEED;
      } else {
        dy2 = dy > 0 ? 1 : -1;
      }
    }
  }

  p->y += dy1;
  e->y += dy2;

  GBA_updateSprite(p);
  GBA_updateSprite(e);
}
