#pragma once

/*
https://docs.qmk.fm/#/feature_combo

Explore these (there are way more)
#undef COMBO_MUST_PRESS_IN_ORDER
#undef COMBO_ONLY_FROM_LAYER
*/

//Clear variables we plan to use that might be set elsewhere
#undef COMBO_TERM
#undef COMBO_TERM_PER_COMBO
#undef COMBO_MUST_TAP_PER_COMBO
#undef EXTRA_SHORT_COMBOS
#undef COMBO_ONLY_FROM_LAYER

#undef COMBO_HOLD_TERM
#undef COMBO_MUST_HOLD_PER_COMBO

#undef COMBO_MUST_PRESS_IN_ORDER_PER_COMBO



//Set common configuration for all keyboards
#define COMBO_TERM 50
#define COMBO_TERM_PER_COMBO
#define COMBO_MUST_TAP_PER_COMBO
#define EXTRA_SHORT_COMBOS
#define COMBO_ONLY_FROM_LAYER 0 //this will always setup combos based off of QWERTY

#define COMBO_HOLD_TERM TAPPING_TERM
#define COMBO_MUST_HOLD_PER_COMBO

#define COMBO_MUST_PRESS_IN_ORDER_PER_COMBO