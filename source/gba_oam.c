#include "../include/gba_oam.h"

OBJ_ATTR oam_buffer[MAX_SPRITES];
OBJ_AFFINE *oam_aff_buffer = (OBJ_AFFINE *)oam_buffer;
u32 oam_count;

u16 _getSpriteShape(u32 shape) {
  switch (shape) {
  case SPR_SQUARE:
    return ATTR0_SQUARE;
    break;
  case SPR_TALL:
    return ATTR0_TALL;
    break;
  case SPR_WIDE:
    return ATTR0_WIDE;
    break;
  }
  return 0;
}

void GBA_createSprite(GBA_Sprite *spr, GBA_Gfx gfx, int x, int y, u32 oam_id,
                      u32 tile_id, u32 pal_bank, u32 prio, u32 size) {
  if (oam_count >= MAX_SPRITES)
    return;

  OBJ_ATTR *o = &oam_buffer[oam_id];
  ++oam_count;

  o->attr0 = (gfx.bpp ? ATTR0_8BPP : ATTR0_4BPP) | (_getSpriteShape(gfx.shape));
  o->attr1 = ATTR1_SIZE(spr->size = size);
  o->attr2 = ATTR2_BUILD(spr->tile_id = tile_id, spr->pal_bank = pal_bank,
                         spr->prio = prio);

  GBA_setSpritePos(spr, spr->x = x, spr->y = y);
  spr->gfx = gfx;

  if (oam_id + 1 > oam_count) {
    int tmp = (int)oam_count - (int)oam_id;
    oam_count = ABS(tmp);
  }
}

void GBA_flipSprite(GBA_Sprite *spr, bool h, bool v) {
  if (h) {
    BIT_SET(oam_buffer[spr->id].attr1, ATTR1_HFLIP);
  } else {
    BIT_CLEAR(oam_buffer[spr->id].attr1, ATTR1_HFLIP);
  }

  if (v) {
    BIT_SET(oam_buffer[spr->id].attr1, ATTR1_VFLIP);
  } else {
    BIT_CLEAR(oam_buffer[spr->id].attr1, ATTR1_VFLIP);
  }

  spr->fliph = h;
  spr->flipv = v;
}

void GBA_updateSprite(GBA_Sprite *spr) {
  u32 tile_id_offset = (spr->gfx.bpp ? 2 : 1);

  oam_buffer[spr->id].attr2 =
      ATTR2_BUILD(spr->tile_id * tile_id_offset, spr->pal_bank, spr->prio);

  GBA_setSpritePos(spr, spr->x, spr->y);
}
