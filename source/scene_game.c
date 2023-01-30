#include "../include/scene_game.h"
#include "../include/gba.h"

#include "../include/e_ball.h"
#include "../include/e_blocks.h"

#include "map_gameplay_bg0.h"
#include "map_gameplay_bg1.h"

GBA_Gfx map_g_bg0_gfx, map_g_bg1_gfx;
FIXED map_x, map_y;

void initGame() {
  GBA_setMode(0);
  GBA_enableBg(0);
  GBA_enableBg(1);
  GBA_enableBg(2);

  tte_init_se(0, BG_CBB(1) | BG_SBB(31) | BG_PRIO(0), SE_PALBANK(15), 0xFFFF, 0,
              NULL, NULL);
  tte_init_con();

  // Tmp
  map_g_bg0_gfx = GBA_initGfx(map_gameplay_bg0, 0, false);
  GBA_loadTiles(map_g_bg0_gfx, 0, 3, 1);
  REG_BG1CNT = BG_4BPP | BG_CBB(0) | BG_SBB(29) | BG_PRIO(1);
  memcpy16(&se_mem[29][0], map_gameplay_bg0Map, map_gameplay_bg0MapLen);

  map_g_bg1_gfx = GBA_initGfx(map_gameplay_bg1, 0, false);
  GBA_loadTiles(map_g_bg1_gfx, 0, 0, 0);
  REG_BG2CNT = BG_4BPP | BG_CBB(0) | BG_SBB(27) | BG_PRIO(2);
  memcpy16(&se_mem[27][0], map_gameplay_bg1Map, map_gameplay_bg1MapLen);

  map_x = map_y = 0x00;

  GBA_initOam(128);

  initBall();
  initBlocks();
}

void updateGame() {
  map_x = map_y += 0x080;

  REG_BG_OFS[2].x = fx2int(map_x);
  REG_BG_OFS[2].y = fx2int(map_y);

  updateBall();
  updateBlocks();
  GBA_updateOam();
}

void endGame() {}

GBA_Scene scene_game = {initGame, updateGame, endGame};

// TODO: Criar funções para adiministrar mapas
