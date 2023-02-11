#include "../include/e_blocks.h"
#include "../include/e_ball.h"

#include "gfx_blocks.h"
#include "tonc_input.h"

#define BLOCK_INIT_Y (SCREEN_HEIGHT - 32)/2
#define BLOCK_SPEED 0x0250

GBA_Gfx blocks_gfx;
GBA_Sprite *block_spr, *block2_spr;

FIXED b1_y, b2_y, dy1, dy2, boost_b1;
u32 point1, point2;
bool b2_stopped;

void initBlocks() {
  blocks_gfx = GBA_initGfx(gfx_blocks, SPR_TALL, false);
  GBA_loadObjects(blocks_gfx, 5, 1);

  block_spr = GBA_createSprite(blocks_gfx, 16, BLOCK_INIT_Y, 5, 1, 1,
                   SPR_16X32);
  block2_spr = GBA_createSprite(blocks_gfx, SCREEN_WIDTH - 32, BLOCK_INIT_Y,
                   21, 1, 1, SPR_16X32);

  dy1 = dy2 = 0x00;
  boost_b1 = 0x00;
  point1 = point2 = 0;
  b2_stopped = false;
}

void updateBlocks() {
  GBA_Sprite *p = block_spr, *e = block2_spr;

  dy1 = 0;
  dy2 = 0;

  // Player
  if (key_is_down(KEY_UP) && p->y > 0) {
    dy1 = -(BLOCK_SPEED + boost_b1);
  } else if (key_is_down(KEY_DOWN) && p->y < SCREEN_HEIGHT - 32) {
    dy1 = BLOCK_SPEED + boost_b1;
  }

  if (key_hit(KEY_B) && boost_b1 <= 0x00){
    boost_b1 = 0x0400;
    p->tile_id = 13;
    if (dy1 == 0x00) {
      e->tile_id = 29;
      b2_stopped = true;
    }
  }

  if(boost_b1 <= 0x00){
    boost_b1 = 0x00;
    p->tile_id = 5;
    if (e->tile_id != 21) {
      e->tile_id = 21;
      b2_stopped = false;
    };
  }

  // Rival
  int dy = ball_spr->y - e->y;

  if (e->y < 0) {
    e->y = 0;
  } else if (e->y > SCREEN_HEIGHT - 32) {
    e->y = SCREEN_HEIGHT - 32;
  }

  if (ball_spr->x > (SCREEN_WIDTH / 2) - 32) {
    FIXED dy_f = int2fx(dy);
    if (ABS(dy_f) >= BLOCK_SPEED && !b2_stopped) {
      dy2 = dy_f > 0 ? BLOCK_SPEED : -BLOCK_SPEED;
    }
  }

  b1_y = dy1;
  b2_y = dy2;
  boost_b1 -= 0x040;

  p->y += fx2int(b1_y);
  e->y += fx2int(b2_y);
}
