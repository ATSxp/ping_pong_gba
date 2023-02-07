#include "../include/e_ball.h"
#include "../include/e_blocks.h"
#include "../include/gba_mgba.h"

#include "gfx_ball.h"

#include "maxmod.h"
#include "soundbank.h"

#define BALL_INIT_X   (SCREEN_WIDTH - 8) / 2
#define BALL_INIT_Y   (SCREEN_HEIGHT - 8) / 2
#define BALL_SPEED     0x0150
#define BALL_EXTRA_SPD 0x0150
#define MAX_GOL_TM     0x0800

GBA_Gfx ball_gfx;
GBA_Sprite ball_spr;

u32 ball_frm[5] = {0,1,2,3,4};
GBA_Anim ball_anim = {5, ball_frm, 0x020, true};

int rnd_dx, rnd_dy, ball_speed_i;
FIXED ball_x, ball_y, ball_dx, ball_dy, ball_extra_speed, gol_timer;
bool gol;

mm_sound_effect ball_hit_snd;

INLINE bool aabb(int x1, int y1, u32 w1, u32 h1, int x2, int y2, u32 w2, u32 h2) {
  return (x1 + (int)w1 >= x2 && y1 + (int)h1 >= y2 && x2 + (int)w2 >= x1 &&
          y2 + (int)h2 >= y1);
}

void ballRandomDeltaPos() {
  ball_speed_i = fx2int(BALL_SPEED);
  rnd_dx = qran_range(-ball_speed_i, ball_speed_i);
  rnd_dy = qran_range(-ball_speed_i, ball_speed_i);

  ball_dx = (rnd_dx != ball_speed_i && rnd_dx != -ball_speed_i)
                ? BALL_SPEED
                : int2fx(rnd_dx);
  ball_dy = (rnd_dy != ball_speed_i && rnd_dy != -ball_speed_i)
                ? BALL_SPEED
                : int2fx(rnd_dy);
}

void ballReset() {
  GBA_disableBg(0);

  gol = false;
  gol_timer = MAX_GOL_TM;

  ball_x = int2fx(BALL_INIT_X);
  ball_y = int2fx(BALL_INIT_Y);

  ball_extra_speed = 0x00;

  ballRandomDeltaPos();
}

inline bool golEventIsOver(){
  if (gol)
    ball_dx = ball_dy = 0;

  return gol_timer <= 0x00;
}

bool checkBallOnBlock(GBA_Sprite *b, GBA_Sprite *bl, u32 x_offset){
  bool dx_is_left = x_offset > 0 ? ball_dx < 0 : ball_dx > 0;
  bool is_hit = false;
  bool can_check = x_offset > 0 ? b->x < SCREEN_WIDTH / 2 : b->x > SCREEN_WIDTH / 2;

  if (!can_check) return false;

  if ((aabb(b->x, b->y, 8, 8, bl->x + x_offset, bl->y, 1, 32) && dx_is_left)) {
    b->x = bl->x + x_offset;

    ball_extra_speed += 0x0100;
    ball_dx = -ball_dx;
    ball_dx += ball_dx > 0x00 ? ball_extra_speed : -ball_extra_speed;
    is_hit = true;

  } else if ((aabb(b->x, b->y, 8, 8, bl->x, bl->y, 16, 1) && ball_dy > 0)) {
    if (dy1 < 0) ball_extra_speed += 0x0100;

    ball_dy = -ball_dy;
    ball_dy += ball_dy > 0x00 ? ball_extra_speed : -ball_extra_speed;
    is_hit = true;

  } else if ((aabb(b->x, b->y, 8, 8, bl->x, bl->y + 32, 16, 1) &&
              ball_dy < 0)) {
    if (dy1 > 0) ball_extra_speed += 0x0100;

    ball_dy = -ball_dy;
    ball_dy += ball_dy > 0x00 ? ball_extra_speed : -ball_extra_speed;
    is_hit = true;

  } else {
    is_hit = false;
  }

  return is_hit;
}

void initBall() {
  ball_gfx = GBA_initGfx(gfx_ball, SPR_SQUARE, false);
  GBA_loadObjects(ball_gfx, 0, 0);

  ballReset();

  GBA_createSprite(&ball_spr, ball_gfx, -1, BALL_INIT_X, BALL_INIT_Y, 0, 0, 1,
                   SPR_8X8);

  ball_extra_speed = 0x00;

  ball_hit_snd = (mm_sound_effect){
      {SFX_BALL_HIT}, (int)(1.0f * (1 << 10)), 0, 255, 128,
  };
}

void updateBall() {
  GBA_Sprite *b = &ball_spr;
  GBA_setAnimSprite(b, &ball_anim);

  if ( b->y < 0) {
    mmEffectEx(&ball_hit_snd);
    b->y = 0;
    ball_dy = -ball_dy;
  }else if ( b->y > SCREEN_HEIGHT - 8) {
    mmEffectEx(&ball_hit_snd);
    b->y = SCREEN_HEIGHT - 8;
    ball_dy = -ball_dy;
  }
  
  if (checkBallOnBlock(b, &block_spr, 16) || checkBallOnBlock(b, &block2_spr, 0)) {
    mmEffectEx(&ball_hit_snd);
  }

  if (ball_extra_speed <= 0x00)
    ball_extra_speed = 0x00;

  if (b->x < 0) {
    if (!gol)
      ++point2;
    gol = true;
  } else if (b->x + 8 > SCREEN_WIDTH) {
    if (!gol)
      ++point1;
    gol = true;
  }

  if (gol) {
    GBA_enableBg(0);
    gol_timer -= 0x030;
  }

  if (golEventIsOver()) ballReset();

  ball_x += ball_dx;
  ball_y += ball_dy;
  ball_extra_speed -= 0x090;

  b->x = fx2int(ball_x);
  b->y = fx2int(ball_y);
  GBA_updateSprite(b);
}
