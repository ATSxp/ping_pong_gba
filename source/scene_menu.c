#include <string.h>

#include "../include/scene_menu.h"
#include "../include/scene_game.h"

#include "map_menu_tmp.h"
#include "map_menu_bg1.h"
#include "map_menu_bg2.h"

GBA_Gfx menu_gfx, menu2_gfx;
GBA_Map menu_map, menu2_map;
FIXED menu2_x, menu2_y;

// char *substring(char *dst, const char *src, int beg, int n) {
//   while (n > 0) {
//     *dst = *(src + beg);
//     dst++;
//     src++;
//     n--;
//   }
//
//   *dst = '\0';
//
//   return dst;
// }

bool go_to_game;
GBA_Fade menu_f;
COLOR menu_bg_p[48];

void initMenu() {
  GBA_setMode(0);
  GBA_enableBg(0);
  GBA_enableBg(1);
  GBA_enableBg(2);

  menu_gfx = GBA_initGfx(map_menu_bg1, 0, true);
  GBA_loadTiles(menu_gfx, 0, 0, 0);
  GBA_initMap(&menu_map, 1, BG_CBB(0) | BG_SBB(28) | BG_4BPP, map_menu_bg1Map, 32, 32);

  menu2_gfx = GBA_initGfx(map_menu_bg2, 0, false);
  GBA_loadTiles(menu2_gfx, 0, 324, 1);
  GBA_initMap(&menu2_map, 2, BG_CBB(0) | BG_SBB(26) | BG_4BPP, map_menu_bg2Map, 32, 32);

  tte_init_se(0, BG_CBB(3) | BG_SBB(31), SE_PALBANK(2), CLR_WHITE, 2, &sys8Font, (fnDrawg)se_drawg_s);

  menu2_x = menu2_y = 0;

  menu_f = GBA_initFade(menu_bg_p, 3);
  GBA_cpyCurPalBg(&menu_f);

  tte_write("#{P:60,140}Press [ START ]");

  go_to_game = false;
}

void updateMenu() {
  FIXED a_out = 32 << 8, a_in = 0x00;

  if (!go_to_game) {
    a_out = GBA_fadeOutBg(&menu_f, 0x080);
  } else {
    a_in = GBA_fadeInBg(&menu_f, 0x080);
  }

  if (key_hit(KEY_START) && a_out <= 0x00) {
    go_to_game = true;
  }

  if (a_in >= 32 << 8 && go_to_game)
    GBA_setScene(scene_game);

  menu2_x = menu2_y += 0x060;

  GBA_setMapPos(2, fx2int(menu2_x), fx2int(menu2_y));
}

void endMenu() {
  // RegisterRamReset(RESET_VRAM);
  // RegisterRamReset(RESET_PALETTE);
}

GBA_Scene scene_menu = {initMenu, updateMenu, endMenu};
