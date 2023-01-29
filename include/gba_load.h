#ifndef GBA_LOAD_H
#define GBA_LOAD_H

#include <tonc.h>

typedef struct {
  const void *tile, *pal;
  u32 tile_len, pal_len;
  u32 shape;
  bool bpp;
} GBA_Gfx;

#define GBA_initGfx(gfx, shape, bpp)                                           \
  (GBA_Gfx) { gfx##Tiles, gfx##Pal, gfx##TilesLen, gfx##PalLen, shape, bpp }

void GBA_loadObjects(GBA_Gfx gfx, u32 tile_id, u32 pal_bank);
void GBA_loadTiles(GBA_Gfx gfx, u32 cbb, u32 tile_id, u32 pal_bank);

#endif // !DEBUG
