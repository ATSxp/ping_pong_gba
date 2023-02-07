#include "../include/hud.h"
#include "../include/point_board.h"

// #include "gfx_nums.h"

// #define HUD_TILE_ID 77
//
// GBA_Gfx hud_gfx;
// GBA_Sprite hud_spr;
//
// typedef struct {
//   GBA_Sprite spr;
//   int x, y;
//   u32 value;
// } Nums_group;
//
// Nums_group nums[3];
// u32 vals[3];
// u32 cente, deze, unid;
//
// void addNum(u32 num){
//   unid = num;
//
//   if (unid > 9){
//     ++deze;
//   }
//
//   if (deze > 9){
//     ++cente;
//     deze = 0;
//   }
//
// }

void initHud(){
  initBoard();

  // hud_gfx = GBA_initGfx(gfx_nums, SPR_SQUARE, false);
  // GBA_loadObjects(hud_gfx, 77, 4);
  //
  // cente = deze = unid = 0;
  //
  // int ii;
  // for (ii = 0; ii < 3; ii++)
  //   GBA_createSprite(&nums[ii].spr, hud_gfx, -1, 8 * ii + ( ( SCREEN_WIDTH - 24 ) / 2 ), 4, 77, 4, 0, SPR_8X8);

}

void updateHud(){
  updateBoard();
  // addNum(1);

  // nums[0].value = cente;
  // nums[1].value = deze;
  // nums[2].value = unid;
  //
  // int ii;
  // for (ii = 0; ii < 3; ii++){
  //   nums[ii].spr.tile_id = HUD_TILE_ID + (nums[ii].value % 10);
  //   GBA_updateSprite(&nums[ii].spr);
  // }
}
