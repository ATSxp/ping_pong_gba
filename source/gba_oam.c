#include "../include/gba_oam.h"
#include "../include/gba_mgba.h"

GBA_Sprite spr_buffer[MAX_SPRITES];
OBJ_ATTR oam_buffer[MAX_SPRITES];
OBJ_AFFINE *oam_aff_buffer = (OBJ_AFFINE *)oam_buffer;
u32 oam_count;

GBA_Sprite *GBA_createSprite(GBA_Gfx gfx, int x, int y,
                      u32 tile_id, u32 pal_bank, u32 prio, u32 size) {
  int oam_id;

  if (oam_count >= MAX_SPRITES) {
    mgba_printf(MGBA_LOG_WARN, "OAM it is full");
    return NULL;
  }

  OBJ_ATTR *o = &oam_buffer[oam_count++];

  GBA_Sprite *spr = &spr_buffer[oam_id = oam_count - 1];
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

  return spr;
}

// Ativa a animação do Objeto com base na estrutura TAnim
void GBA_setAnimSprite(GBA_Sprite *spr, GBA_Anim *anim) {
  if (anim->cur_frame > (int)anim->len) {
    if (!anim->loop)
      anim->finish = true;
  }

  if (!anim->finish)
    anim->ticks += anim->speed;

  if (anim->ticks > 0x0100) {
    anim->ticks = 0x00;
    anim->cur_frame++;
  }

  u32 frm =
      anim->loop ? anim->cur_frame % anim->len : anim->cur_frame;

  spr->tile_id = anim->frames[frm] * 1;
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
