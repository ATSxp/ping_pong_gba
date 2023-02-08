#ifndef GBA_FX_H
#define GBA_FX_H

#include <tonc.h>
#include "gba_oam.h"
#include "gba_load.h"

#define FADE_MAX (33 << 8)

typedef struct {
  const void *src;
  u32 pal_bank_count;
} GBA_Fade;

#define GBA_initFade(src, pal_count) \
  (GBA_Fade){src, pal_count}

extern FIXED f_alpha_bg, f_alpha_obj;
extern bool f_obj_is_run, f_bg_is_run;

INLINE void GBA_cpyCurPalBg(GBA_Fade *fade)
{ memcpy16((COLOR*)fade->src, pal_bg_mem, ( 32 * fade->pal_bank_count ) / 2); }

INLINE void GBA_cpyCurPalObj(GBA_Fade *fade)
{ memcpy16((COLOR*)fade->src, pal_obj_mem, ( 32 * fade->pal_bank_count ) / 2); }

FIXED _updateFade(GBA_Fade *fade, void *dst, FIXED speed, FIXED init_a, FIXED *f_alpha, bool *f_is_run);

INLINE FIXED GBA_fadeInBg(GBA_Fade *fade, FIXED speed) 
{ return _updateFade(fade, pal_bg_mem, speed, 0, &f_alpha_bg, &f_bg_is_run); }

INLINE FIXED GBA_fadeOutBg(GBA_Fade *fade, FIXED speed) 
{ return _updateFade(fade, pal_bg_mem, -speed, FADE_MAX, &f_alpha_bg, &f_bg_is_run); }

INLINE FIXED GBA_fadeInObj(GBA_Fade *fade, FIXED speed)
{ return _updateFade(fade, pal_obj_mem, speed, 0, &f_alpha_obj, &f_obj_is_run); }

INLINE FIXED GBA_fadeOutObj(GBA_Fade *fade, FIXED speed)
{ return _updateFade(fade, pal_obj_mem, -speed, FADE_MAX, &f_alpha_obj, &f_obj_is_run); }

#endif // !GBA_FX_H
