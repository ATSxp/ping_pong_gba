#include "../include/e_ball.h"
#include "../include/e_blocks.h"

#include "gfx_ball.h"

#define BALL_INIT_X ((SCREEN_WIDTH - 8) / 2)
#define BALL_INIT_Y ((SCREEN_HEIGHT - 8) / 2)
#define BALL_SPEED 2

GBA_Gfx ball_gfx;
GBA_Sprite ball_spr;
int ball_dx, ball_dy;

#define BALL_RESET()                                                           \
  ball_spr.x = BALL_INIT_X;                                                    \
  ball_spr.y = BALL_INIT_Y;                                                    \
  ball_dx = -ball_dx;

INLINE
bool aabb(int x1, int y1, u32 w1, u32 h1, int x2, int y2, u32 w2, u32 h2) {
  return (x1 + (int)w1 >= x2 && y1 + (int)h1 >= y2 && x2 + (int)w2 >= x1 &&
          y2 + (int)h2 >= y1);
}

void initBall() {
  ball_gfx = GBA_initGfx(gfx_ball, SPR_SQUARE, false);
  GBA_loadObjects(ball_gfx, 0, 0);

  GBA_createSprite(&ball_spr, ball_gfx, -1, BALL_INIT_X, BALL_INIT_Y, 0, 0, 2,
                   SPR_8X8);

  ball_dx = -BALL_SPEED;
  ball_dy = BALL_SPEED;
}

void updateBall() {
  GBA_Sprite *b = &ball_spr;

  if (b->y < 0 || b->y > SCREEN_HEIGHT - 8)
    ball_dy = -ball_dy;

  if ((aabb(b->x, b->y, 8, 8, block_spr.x, block_spr.y, 16, 32) &&
       ball_dx < 0) ||
      (aabb(b->x, b->y, 8, 8, block2_spr.x, block2_spr.y, 16, 32) &&
       ball_dx > 0)) {
    ball_dx = -ball_dx;
  }

  if (b->x < 0) {
    ++point1;
    BALL_RESET();
  } else if (b->x + 8 > SCREEN_WIDTH) {
    ++point2;
    BALL_RESET();
  }

  b->x += ball_dx;
  b->y += ball_dy;
  GBA_updateSprite(b);
}
