#include "../include/gba_fx.h"
#include "tonc_video.h"

// Fade Effect

static FIXED f_alpha = 0;
static bool f_is_run = false;

void GBA_fadeInBg(GBA_Fade *fade, FIXED speed) {
  int ii;
  u32 pal_count;

  if (!f_is_run) f_alpha = 0;
  f_is_run = true;

  for (ii = 0; ii < fade->len; ii++){
    pal_count = fade->pal_bank_count[ii];

    clr_fade(&fade->palettes[ii], CLR_BLACK, pal_bg_bank[pal_count], pal_count, fx2int(f_alpha));
  }

  if (f_alpha != 0x03200){
    f_alpha += speed;
    f_alpha = clamp(f_alpha, 0x00, 0x03300);
  }
}
