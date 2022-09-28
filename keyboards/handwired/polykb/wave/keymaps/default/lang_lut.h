#pragma once

enum {ALPHA = 26, NUM = 10, ADDITIONAL = 17};
enum lang_layer { LANG_EN = 0, LANG_KO = 1, LANG_JP = 2, LANG_AR = 3, NUM_LANG = 4};

const uint16_t* translate_keycode(uint8_t used_lang, uint16_t keycode, bool shift, bool caps_lock);
