#include "../include/scene_game.h"
#include "../include/gba.h"

#include "../include/e_ball.h"
#include "../include/e_blocks.h"
#include "../include/hud.h"

#include "map_gameplay_bg0.h"
#include "map_gameplay_bg1.h"
#include "map_gol.h"

#include "soundbank_bin.h"
#include "tonc_memdef.h"

GBA_Map bg1_map, gol_map;
GBA_Gfx map_g_bg0_gfx, map_g_bg1_gfx, gol_gfx;
FIXED map_x, map_y;

void initGame() {
  GBA_setMode(0);
  GBA_enableBg(1);

  // tte_init_se(0, BG_CBB(1) | BG_SBB(31) | BG_PRIO(0), SE_PALBANK(15), 0xFFFF,
  // 0,
  //             NULL, NULL);

  mmInitDefault((mm_addr)soundbank_bin, 8);

  gol_gfx = GBA_initGfx(map_gol, 0, false);
  GBA_loadTiles(gol_gfx, 0, 3, 1);
  GBA_initMap(&gol_map, 0, BG_CBB(0)|BG_SBB(29), map_golMap, 32, 32);

  map_g_bg1_gfx = GBA_initGfx(map_gameplay_bg1, 0, false);
  GBA_loadTiles(map_g_bg1_gfx, 0, 0, 0);
  GBA_initMap(&bg1_map, 1, BG_CBB(0) | BG_SBB(27) | BG_PRIO(1) | BG_4BPP,
              map_gameplay_bg1Map, 32, 32);

  map_x = map_y = 0x00;

  GBA_initOam(128);

  initBall();
  initBlocks();
  initHud();
}

void updateGame() {
  map_x = map_y += 0x080;

  GBA_setMapPos(1, fx2int(map_x), fx2int(map_y));

  updateBall();
  updateBlocks();
  updateHud();

  GBA_updateOam();
}

void endGame() {}

GBA_Scene scene_game = {initGame, updateGame, endGame};
