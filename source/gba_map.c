#include "../include/gba_map.h"

void GBA_initMap(GBA_Map *map, u32 bg, u32 ctrl, const void *src, u32 width,
                 u32 height) {
  memset16(map, 0, sizeof(GBA_Map) / 2);

  map->flags = bg;
  map->cnt = ctrl;
  map->dst_map = se_mem[BFN_GET(ctrl, BG_SBB)];

  REG_BGCNT[bg] = ctrl;
  REG_BG_OFS[bg].x = 0;
  REG_BG_OFS[bg].y = 0;

  map->src_map = (SCR_ENTRY *)src;
  map->width = width;
  map->height = height;

  SCR_ENTRY *_dst = map->dst_map, *_src = map->src_map;
  int iy, ix;
  for (iy = 0; iy < 32; iy++) {
    for (ix = 0; ix < 32; ix++) {
      _dst[iy * 32 + ix] = _src[iy * map->width + ix];
    }
  }
}
