#ifndef GBA_MAP_H
#define GBA_MAP_H

#include <tonc.h>

typedef struct {
  FIXED x;
  int xmin, xmax, xpage;
  FIXED y;
  int ymin, ymax, ypage;
} GBA_Viewport;

typedef struct {
  union {
    u32 state;
    struct {
      u16 flags, cnt;
    };
  };

  SCR_ENTRY *dst_map, *src_map;
  u32 width, height;
  FIXED x, y; // .8f
} GBA_Map;

void GBA_initMap(GBA_Map *map, u32 bg, u32 ctrl, const void *src, u32 width,
                 u32 height);

INLINE void GBA_setMapPos(u32 bg, int x, int y) {
  REG_BG_OFS[bg].x = x;
  REG_BG_OFS[bg].y = y;
}

#endif // !GBA_MAP_H
