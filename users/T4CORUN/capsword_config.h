#pragma once

/*
https://docs.qmk.fm/#/feature_caps_word

Explore these
#undef BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#undef CAPS_WORD_INVERT_ON_SHIFT
*/


//Clear variables we plan to use that might be set elsewhere
#undef DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
#undef CAPS_WORD_IDLE_TIMEOUT

//Set common configuration for all keyboards
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
#define CAPS_WORD_IDLE_TIMEOUT 3000