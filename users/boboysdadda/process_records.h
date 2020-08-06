#pragma once

enum userspace_custom_keycodes {
    UC_DISA = SAFE_RANGE,
    UC_FLIP,
    UC_SHRG,
    UC_TABL,
    CP_PST,
    KC_QWERTY,
    KC_DVORAK, 
    NEW_SAFE_RANGE
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record);


#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define QWERTY KC_QWERTY
#define DVORAK KC_DVORAK