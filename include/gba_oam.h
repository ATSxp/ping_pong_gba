#ifndef GBA_OAM_H
#define GBA_OAM_H

#include <tonc.h>

#include "gba_load.h"

#define MAX_SPRITES 128

enum GBA_SpriteShapes { SPR_SQUARE, SPR_TALL, SPR_WIDE };
enum GBA_SpriteSizes {
  SPR_8X8,
  SPR_16X16,
  SPR_32X32,
  SPR_64X64,
  SPR_8X16,
  SPR_8X32,
  SPR_16X32,
  SPR_32X64,
  SPR_16X8,
  SPR_32X8,
  SPR_32X16,
  SPR_64X32
};

typedef struct {
  u32 id; // Id for Oam Buffer
  int x, y;
  u32 size, tile_id, pal_bank,
      prio; // Size of sprite(8x8,16x16,etc..) / tile id(0-1024) /
            // pal_bank(0-15) / Background priority(0-3)
  bool fliph, flipv, hide;
  GBA_Gfx gfx;
} GBA_Sprite;

extern OBJ_ATTR oam_buffer[MAX_SPRITES];
extern OBJ_AFFINE *oam_aff_buffer;
extern u32 oam_count;

void GBA_createSprite(GBA_Sprite *spr, GBA_Gfx gfx, int x, int y, u32 oam_id,
                      u32 tile_id, u32 pal_bank, u32 prio, u32 size);
void GBA_flipSprite(GBA_Sprite *spr, bool h, bool v);
void GBA_updateSprite(GBA_Sprite *spr);

INLINE void GBA_initOam(u32 count) {
  oam_count = 0;
  oam_init(oam_buffer, count);
  REG_DISPCNT |= DCNT_OBJ | DCNT_OBJ_1D;
}

INLINE void GBA_updateOam() { oam_copy(oam_mem, oam_buffer, oam_count); }

INLINE void GBA_setSpritePos(GBA_Sprite *spr, int x, int y) {
  BFN_SET(oam_buffer[spr->id].attr1, x, ATTR1_X);
  BFN_SET(oam_buffer[spr->id].attr0, y, ATTR0_Y);
}

#endif // !GBA_OAM_H
