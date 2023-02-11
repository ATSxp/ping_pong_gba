#include "../include/point_board.h"

#include "gfx_board.h"

#define BOARD_TILE_ID 37

GBA_Gfx board;

u32 dec_pt, dec_pt2, pt_mul, pt_mul2;

typedef struct {
  GBA_Sprite *spr;
  int offsetx;
  u32 pal_bank;
} Boards_spr;

Boards_spr b_sprs[4] = {
    {NULL, -16, 2},
    {NULL, 16, 3},
    {NULL, -32, 2},
    {NULL, 32, 3},
};

void initBoard() {
  board = GBA_initGfx(gfx_board, SPR_SQUARE, false);
  GBA_loadObjects(board, BOARD_TILE_ID, 2);

  dec_pt = dec_pt2 = 0;
  pt_mul = pt_mul2 = 1;

  // Create new palette for other board
  clr_rgbscale(pal_obj_bank[3], gfx_boardPal, 6, CLR_GREEN);

  int ii;
  for (ii = 4; ii < 6; ii++)
    pal_obj_bank[3][ii] = gfx_boardPal[ii];

  for (ii = 0; ii < 4; ii++) {
    b_sprs[ii].spr = GBA_createSprite(board, ((SCREEN_WIDTH - 16) >> 1) + b_sprs[ii].offsetx,
                     160 - 20, BOARD_TILE_ID, b_sprs[ii].pal_bank, 0, SPR_16X16);
  }
}

void updateBoard() {
  GBA_Sprite *b1 = b_sprs[0].spr, *b2 = b_sprs[1].spr, *b3 = b_sprs[2].spr,
             *b4 = b_sprs[3].spr;

  if (point1 < 100 || point2 < 100) {
    b1->tile_id = BOARD_TILE_ID + ((point1 % 10) * 4);
    b2->tile_id = BOARD_TILE_ID + (dec_pt2 * 4);
    b3->tile_id = BOARD_TILE_ID + (dec_pt * 4);
    b4->tile_id = BOARD_TILE_ID + ((point2 % 10) * 4);
  }

  if (point1 >= (10 * pt_mul)) {
    ++dec_pt;
    ++pt_mul;
  }

  if (point2 >= (10 * pt_mul2)) {
    ++dec_pt2;
    ++pt_mul2;
  }
}
