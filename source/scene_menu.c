#include <string.h>

#include "../include/scene_menu.h"
#include "../include/scene_game.h"

#include "map_menu_tmp.h"
#include "map_menu_bg1.h"
#include "map_menu_bg2.h"
#include "tonc_core.h"

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
COLOR menu_bg_p[48];
GBA_Fade menu_f = GBA_initFade(menu_bg_p, 3);

void initMenu() {
  GBA_setMode(0);
  GBA_enableBg(0);
  GBA_enableBg(1);
  GBA_enableBg(2);

  go_to_game = false;
  menu2_x = menu2_y = 0;

  menu_gfx = GBA_initGfx(map_menu_bg1, 0, true);
  menu2_gfx = GBA_initGfx(map_menu_bg2, 0, false);

  GBA_loadTiles(menu_gfx, 0, 0, 0);
  GBA_loadTiles(menu2_gfx, 0, 324, 1);

  GBA_initMap(&menu_map, 1, BG_CBB(0) | BG_SBB(28), map_menu_bg1Map, 32, 32);
  GBA_initMap(&menu2_map, 2, BG_CBB(0) | BG_SBB(26), map_menu_bg2Map, 32, 32);

  tte_init_se(0, BG_CBB(3) | BG_SBB(31), SE_PALBANK(2), CLR_WHITE, 2, &sys8Font, (fnDrawg)se_drawg_s);

  GBA_cpyCurPalBg(&menu_f);

  tte_write("#{P:60,140}Press [ START ]");
}

void updateMenu() {
  FIXED a_out = FADE_MAX - 0x0100;

  if (!go_to_game) {
    a_out = GBA_fadeOutBg(&menu_f, 0x095);
  } else {
    a_out = GBA_fadeInBg(&menu_f, 0x080);
  }

  if (key_hit(KEY_START) && a_out <= 0x00) {
    go_to_game = true;
  } else if (a_out >= FADE_MAX - 0x0100 && go_to_game){
    VBlankIntrDelay(30);
    GBA_setScene(scene_game);
  }

  menu2_x = menu2_y += 0x060;

  GBA_setMapPos(2, fx2int(menu2_x), fx2int(menu2_y));
}

void endMenu() {
  // RegisterRamReset(RESET_VRAM);
  GBA_disableBg(0);
  GBA_disableBg(2);
  // RegisterRamReset(RESET_PALETTE);
}

GBA_Scene scene_menu = {initMenu, updateMenu, endMenu};
