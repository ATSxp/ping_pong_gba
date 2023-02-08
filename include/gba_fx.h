#ifndef GBA_FX_H
#define GBA_FX_H

#include <tonc.h>
#include "gba_oam.h"
#include "gba_load.h"

typedef struct {
  u16 *palettes;
  int len;
  u32 *pal_bank_count;
} GBA_Fade;

void GBA_fadeIn(GBA_Fade *fade);

#endif // !GBA_FX_H
