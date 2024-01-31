#pragma once

////KEYMAP CONFIG////
//Tap Hold:
#define PERMISSIVE_HOLD
#define TAPPING_TERM 185
#define TAPPING_TERM_PER_KEY
#define TAP_CODE_DELAY 17

//Combos:
#define COMBO_VARIABLE_LEN
#define COMBO_TERM 60
#define COMBO_SHOULD_TRIGGER

#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
#define CAPS_WORD_IDLE_TIMEOUT 0

////HARDWARE CONFIG////
#undef EE_HANDS //automatic detection of master/slave doesn't work, so undefine
#define MASTER_LEFT //set master manually
