#include "../include/gba_load.h"

void GBA_loadObjects(GBA_Gfx gfx, u32 tile_id, u32 pal_bank) {
  memcpy16(&pal_obj_bank[pal_bank], gfx.pal, gfx.pal_len / 2);

  if (gfx.bpp) {
    memcpy16(&tile8_mem[4][tile_id], gfx.tile, gfx.tile_len / 2);
  } else {
    memcpy16(&tile_mem[4][tile_id], gfx.tile, gfx.tile_len / 2);
  }
}

void GBA_loadTiles(GBA_Gfx gfx, u32 cbb, u32 tile_id, u32 pal_bank) {
  memcpy16(&pal_bg_bank[pal_bank], gfx.pal, gfx.pal_len / 2);

  if (gfx.bpp) {
    memcpy16(&tile8_mem[cbb][tile_id], gfx.tile, gfx.tile_len / 2);
  } else {
    memcpy16(&tile_mem[cbb][tile_id], gfx.tile, gfx.tile_len / 2);
  }
}
