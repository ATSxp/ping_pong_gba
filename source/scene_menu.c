#include "../include/scene_menu.h"
#include "../include/scene_game.h"

#include "map_menu_tmp.h"

GBA_Gfx menu_gfx;
GBA_Map menu_map;

void initMenu() {
  GBA_setMode(0);
  GBA_enableBg(0);
  GBA_enableBg(1);

  menu_gfx = GBA_initGfx(map_menu_tmp, 0, true);
  GBA_loadTiles(menu_gfx, 0, 0, 0);
  GBA_initMap(&menu_map, 1, BG_CBB(0) | BG_SBB(28) | BG_8BPP, map_menu_tmpMap,
              32, 32);

  tte_init_se(0, BG_CBB(3) | BG_SBB(31), SE_PALBANK(15), CLR_RED, 0, NULL,
              (fnDrawg)se_drawg_s);

  tte_write("#{P:60,140}Press [ START ]");
}

void updateMenu() {
  if (key_hit(KEY_START))
    GBA_setScene(scene_game);
}

void endMenu() {
  RegisterRamReset(RESET_VRAM);
  RegisterRamReset(RESET_PALETTE);
}

GBA_Scene scene_menu = {initMenu, updateMenu, endMenu};
