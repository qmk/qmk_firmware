#pragma once

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _COLEMAK,
    _DVORAK,
    _EUCALYN,
    _KEYPAD,
    _AUX,
    _KAUX,
    _LOWER,
    _RAISE,
    _PADFUNC,
    _ADJUST,
};

#if defined(SSD1306OLED)
extern void init_helix_oled(void);
#   define INIT_HELIX_OLED() init_helix_oled();
#else
#   define INIT_HELIX_OLED()
#endif
