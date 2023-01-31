#include "../include/point_board.h"

#include "gfx_board.h"

#define BOARD_TILE_ID 17

GBA_Gfx board;
GBA_Sprite board_spr, board2_spr, board3_spr, board4_spr;

u32 dec_pt, dec_pt2, pt_mul, pt_mul2;

void initBoard() {
  board = GBA_initGfx(gfx_board, SPR_SQUARE, false);
  GBA_loadObjects(board, 17, 2);

  dec_pt = dec_pt2 = 0;
  pt_mul = pt_mul2 = 1;

  GBA_createSprite(&board_spr, board, -1, ((SCREEN_WIDTH - 16) >> 1) - 16,
                   160 - 20, BOARD_TILE_ID, 2, 0, SPR_16X16);
  GBA_createSprite(&board2_spr, board, -1, ((SCREEN_WIDTH - 16) >> 1) + 16,
                   160 - 20, BOARD_TILE_ID, 2, 0, SPR_16X16);
  GBA_createSprite(&board3_spr, board, -1, ((SCREEN_WIDTH - 16) >> 1) - 32,
                   160 - 20, BOARD_TILE_ID, 2, 0, SPR_16X16);
  GBA_createSprite(&board4_spr, board, -1, ((SCREEN_WIDTH - 16) >> 1) + 32,
                   160 - 20, BOARD_TILE_ID, 2, 0, SPR_16X16);
}

void updateBoard() {
  GBA_Sprite *b1 = &board_spr, *b2 = &board2_spr, *b3 = &board3_spr,
             *b4 = &board4_spr;

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

  GBA_updateSprite(b1);
  GBA_updateSprite(b2);
  GBA_updateSprite(b3);
  GBA_updateSprite(b4);
}
