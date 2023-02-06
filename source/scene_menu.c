#include <string.h>

#include "../include/scene_menu.h"
#include "../include/scene_game.h"

#include "map_menu_tmp.h"
#include "map_menu_bg1.h"
#include "map_menu_bg2.h"
#include "tonc_memdef.h"

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

  tte_init_se(0, BG_CBB(3) | BG_SBB(31), SE_PALBANK(15), CLR_WHITE, 0, &sys8Font, (fnDrawg)se_drawg_s);

  menu2_x = menu2_y = 0;

  tte_write("#{P:60,140}Press [ START ]");
}

void updateMenu() {
  if (key_hit(KEY_START))
    GBA_setScene(scene_game);

  menu2_x = menu2_y += 0x060;

  GBA_setMapPos(2, fx2int(menu2_x), fx2int(menu2_y));
}

void endMenu() {
  RegisterRamReset(RESET_VRAM);
  RegisterRamReset(RESET_PALETTE);
}

GBA_Scene scene_menu = {initMenu, updateMenu, endMenu};
