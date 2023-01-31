#include "../include/e_ball.h"
#include "../include/e_blocks.h"

#include "gfx_ball.h"

#define BALL_INIT_X ((SCREEN_WIDTH - 8) / 2)
#define BALL_INIT_Y ((SCREEN_HEIGHT - 8) / 2)
#define BALL_SPEED 2

GBA_Gfx ball_gfx;
GBA_Sprite ball_spr;
int ball_dx, ball_dy, rnd_dx, rnd_dy;

void ballRandomDeltaPos() {
  rnd_dx = qran_range(-BALL_SPEED, BALL_SPEED);
  rnd_dy = qran_range(-BALL_SPEED, BALL_SPEED);

  ball_dx = rnd_dx == 0 ? BALL_SPEED : rnd_dx;
  ball_dy = rnd_dy == 0 ? BALL_SPEED : rnd_dy;
}

void ballReset() {
  ball_spr.x = BALL_INIT_X;
  ball_spr.y = BALL_INIT_Y;

  ballRandomDeltaPos();
}

#define CHECK_UP(ball, block, block2)                                          \
  (ball.y + 8 >= block.y && ball_dy > 0) ||                                    \
      (ball.y + 8 >= block2.y && ball_dy > 0)
#define CHECK_BOTTOM(ball, block, block2)                                      \
  (block.y + 32 >= ball.y && ball_dy < 0) ||                                   \
      (block2.y + 32 >= ball.y && ball_dy < 0)

INLINE
bool aabb(int x1, int y1, u32 w1, u32 h1, int x2, int y2, u32 w2, u32 h2) {
  return (x1 + (int)w1 >= x2 && y1 + (int)h1 >= y2 && x2 + (int)w2 >= x1 &&
          y2 + (int)h2 >= y1);
}

void initBall() {
  ball_gfx = GBA_initGfx(gfx_ball, SPR_SQUARE, false);
  GBA_loadObjects(ball_gfx, 0, 0);

  GBA_createSprite(&ball_spr, ball_gfx, -1, BALL_INIT_X, BALL_INIT_Y, 0, 0, 1,
                   SPR_8X8);

  ballRandomDeltaPos();
}

void updateBall() {
  GBA_Sprite *b = &ball_spr;

  if (b->y < 0 || b->y > SCREEN_HEIGHT - 8)
    ball_dy = -ball_dy;

  if ((aabb(b->x, b->y, 8, 8, block_spr.x, block_spr.y, 16, 32) &&
       ball_dx < 0) ||
      (aabb(b->x, b->y, 8, 8, block2_spr.x, block2_spr.y, 16, 32) &&
       ball_dx > 0)) {

    if (CHECK_BOTTOM(ball_spr, block_spr, block2_spr)) {
      if (ball_dy < 0) {
        rnd_dy = qran_range(-BALL_SPEED, BALL_SPEED);
        ball_dy = rnd_dy == 0 ? BALL_SPEED : rnd_dy;
      }
    } else if (CHECK_UP(ball_spr, block_spr, block2_spr)) {
      if (ball_dy > 0) {
        rnd_dy = qran_range(-BALL_SPEED, BALL_SPEED);
        ball_dy = rnd_dy == 0 ? BALL_SPEED : rnd_dy;
      }
    }

    ball_dx = -ball_dx;
    b2_state = qran_range(0, 1);
  }

  if (b->x < 0) {
    ++point1;
    ballReset();
  } else if (b->x + 8 > SCREEN_WIDTH) {
    ++point2;
    ballReset();
  }

  b->x += ball_dx;
  b->y += ball_dy;
  GBA_updateSprite(b);
}
