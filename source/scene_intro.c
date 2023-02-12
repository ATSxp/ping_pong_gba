#include "../include/scene_intro.h"
#include "../include/scene_menu.h"
#include "tonc_bios.h"
#include "tonc_core.h"
#include "tonc_memdef.h"
#include "tonc_memmap.h"
#include "tonc_tte.h"

bool go_intro;
COLOR intro_bg_p[16];
GBA_Fade intro_f = GBA_initFade(intro_bg_p, 1);

void initIntro(){
  GBA_setMode(0);
  GBA_enableBg(0);

  go_intro = false;
  pal_bg_mem[0] = CLR_WHITE;

  tte_init_chr4c(
      0, 
      BG_CBB(0) | BG_SBB(31), 
      SE_PALBANK(0), 
      bytes2word(1, 2, 0, 0), 
      CLR_BLACK | CLR_RED << 16,
      &verdana9Font, 
      (fnDrawg)chr4c_drawg_b1cts_fast
    );

    pal_bg_mem[3] = CLR_ORANGE;
    pal_bg_mem[4] = CLR_BLUE;
    pal_bg_mem[5] = CLR_GRAY;

  GBA_cpyCurPalBg(&intro_f);

  const TFont *font_table[3] = {
    &verdana9Font, &verdana9iFont, &verdana9bFont
  };

  CSTR intro_text = 
    "#{P:2,2}Game made with #{ci:2}DevkitARM and #{ci:3}Libtonc#{ci:1}.\n"
    "In this game, I was able to learn a lot about the\n"
    "#{f:2}GBA#{f:0} and it was a lot of fun!! During the progress of the "
    "project I tried to give a more '#{f:1}high level#{f:0}' view\n"
    "to the code, #{f:1}I hope it's optimized =)#{f:0}\n\n"
    "If you have a dream/goal,\n#{f:2}never give up on it!!\n"
    "#{P:2,144;f:1}Twitter: #{ci:4}@ATS_xp #{ci:1}| Github: #{ci:5}ATSxp";

  tte_set_font_table(font_table);
  tte_set_margins(2, 2, 240 - 4, 160 - 4);
  tte_write(intro_text);
}

void updateIntro(){
  FIXED a_out_i = FADE_MAX - 0x0100;

  if (!go_intro) {
    a_out_i = GBA_fadeOutBg(&intro_f, 0x080);
  } else {
    a_out_i = GBA_fadeInBg(&intro_f, 0x080);
  }

  if (a_out_i <= 0x00){
    VBlankIntrDelay(130);
    go_intro = true;
  } else if (go_intro && a_out_i >= FADE_MAX - 0x0100) {
    GBA_setScene(scene_menu);
  }
}

void endIntro(){
  tte_erase_screen();
  RegisterRamReset(RESET_VRAM);
}

GBA_Scene scene_intro = {initIntro, updateIntro, endIntro};
