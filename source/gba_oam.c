#include "../include/gba_oam.h"
#include "../include/gba_mgba.h"

OBJ_ATTR oam_buffer[MAX_SPRITES];
OBJ_AFFINE *oam_aff_buffer = (OBJ_AFFINE *)oam_buffer;
u32 oam_count;

void GBA_createSprite(GBA_Sprite *spr, GBA_Gfx gfx, s32 oam_id, int x, int y,
                      u32 tile_id, u32 pal_bank, u32 prio, u32 size) {
  OBJ_ATTR *o;

  if (oam_count >= MAX_SPRITES) {
    mgba_printf(MGBA_LOG_WARN, "OAM it is full");
    return;
  }

  if (oam_id < 0) {
    o = &oam_buffer[oam_count++];
    oam_id = oam_count - 1;
  } else {
    o = &oam_buffer[oam_id];
  }
  spr->id = oam_id;

  o->attr0 = (gfx.bpp ? ATTR0_8BPP : ATTR0_4BPP) | (ATTR0_SHAPE(gfx.shape));
  o->attr1 = ATTR1_SIZE(spr->size = size);
  o->attr2 = ATTR2_BUILD(spr->tile_id = tile_id, spr->pal_bank = pal_bank,
                         spr->prio = prio);

  GBA_setSpritePos(spr, spr->x = x, spr->y = y);
  spr->gfx = gfx;

  if (oam_id < 0) {
    if (oam_id + 1 > oam_count) {
      oam_count += ABS((int)oam_count - (int)oam_id);
    }
  }

  mgba_printf(MGBA_LOG_DEBUG, "Add Object in slot %d of OAM Buffer", oam_id);
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
