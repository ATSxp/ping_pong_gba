#include "../include/gba_fx.h"
#include "tonc_video.h"

// Fade Effect

void GBA_fadeInBg(cu16 pals[], int len, int pal_bank_count) {
  int ii;
  for (ii = 0; ii < (int)len; ii++)
    clr_fade(&pals[ii], CLR_BLACK, pal_bg_bank[pal_bank_count], 16, 32);
}
