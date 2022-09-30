#pragma once

enum {ALPHA = 26, NUM = 10, ADDITIONAL = 17};
enum lang_layer { LANG_EN = 0, LANG_DE, LANG_KO, LANG_JP, LANG_AR, NUM_LANG };

const uint16_t* translate_keycode(uint8_t used_lang, uint16_t keycode, bool shift, bool caps_lock);
