#include "../include/gba_fx.h"
#include "tonc_video.h"

// Fade Effect

FIXED f_alpha_bg = 0, f_alpha_obj = 0;
bool f_obj_is_run = false, f_bg_is_run = false;

FIXED _updateFade(GBA_Fade *fade, void *dst, FIXED speed, FIXED init_a, FIXED *f_alpha, bool *f_is_run){
  if (!*f_is_run) *f_alpha = init_a;

  clr_fade(fade->src, CLR_BLACK, dst, 16 * fade->pal_bank_count, fx2int(*f_alpha));

  if (*f_alpha <= FADE_MAX){
    *f_is_run = true;
    *f_alpha = clamp(*f_alpha += speed, 0x00, FADE_MAX);
  } else {
    *f_is_run = false;
  }

  return *f_alpha;
}
