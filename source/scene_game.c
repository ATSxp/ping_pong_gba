#include "../include/scene_game.h"
#include "../include/scene_menu.h"
#include "../include/gba.h"

#include "../include/e_ball.h"
#include "../include/e_blocks.h"
#include "../include/hud.h"

#include "map_gameplay_bg0.h"
#include "map_gameplay_bg1.h"
#include "map_gol.h"

#include "soundbank_bin.h"

GBA_Map bg1_map, gol_map;
GBA_Gfx map_g_bg0_gfx, map_g_bg1_gfx, gol_gfx;
FIXED map_x, map_y;

COLOR game_bg_p[32], game_obj_p[64];
GBA_Fade game_f_bg = GBA_initFade(game_bg_p, 2), game_f_obj = GBA_initFade(game_obj_p, 4);

bool go_to_menu;

void initGame() {
  GBA_setMode(0);
  GBA_enableBg(1);

  mmInitDefault((mm_addr)soundbank_bin, 8);

  gol_gfx = GBA_initGfx(map_gol, 0, false);
  map_g_bg1_gfx = GBA_initGfx(map_gameplay_bg1, 0, false);

  GBA_loadTiles(gol_gfx, 0, 3, 1);
  GBA_loadTiles(map_g_bg1_gfx, 0, 0, 0);

  GBA_initMap(&gol_map, 0, BG_CBB(0) | BG_SBB(29), map_golMap, 32, 32);
  GBA_initMap(&bg1_map, 1, BG_CBB(0) | BG_SBB(27) | BG_PRIO(1),
              map_gameplay_bg1Map, 32, 32);

  map_x = map_y = 0x00;
  go_to_menu = false;

  GBA_cpyCurPalBg(&game_f_bg);

  GBA_initOam(128);

  initBall();
  initBlocks();
  initHud();

  GBA_cpyCurPalObj(&game_f_obj);
}

void updateGame() {
  FIXED g_bg_a;

  if (!go_to_menu) {
    g_bg_a = GBA_fadeOutBg(&game_f_bg, 0x0120);
    GBA_fadeOutObj(&game_f_obj, 0x0120);
  } else {
    g_bg_a = GBA_fadeInBg(&game_f_bg, 0x0120);
    GBA_fadeInObj(&game_f_obj, 0x0120);
  }

  map_x = map_y += 0x060;

  GBA_setMapPos(1, fx2int(map_x), fx2int(map_y));

  if (g_bg_a <= 0x00) {
    updateBall();
    updateBlocks();
    updateHud();

    if (key_hit(KEY_START)) {
      go_to_menu = true;
    }
  }

  if (go_to_menu && g_bg_a >= FADE_MAX - 0x100) {
    VBlankIntrDelay(20);
    GBA_setScene(scene_menu);
  }

  GBA_updateOam();
}

void endGame() {
  RegisterRamReset(RESET_OAM);
}

GBA_Scene scene_game = {initGame, updateGame, endGame};
