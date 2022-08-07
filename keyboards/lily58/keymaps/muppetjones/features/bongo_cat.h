/**
 * BONGO CAT!

WPM-responsive animation of bongo cat!

Source:
  https://github.com/qmk/qmk_firmware/blob/master/keyboards/kyria/keymaps/j-inc/keymap.c
*/

#pragma once

const char *wpm_state(void);
void        animation_phase(uint8_t wpm);
void        render_bongo_cat(void);
