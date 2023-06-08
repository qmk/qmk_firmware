#pragma once

/*
https://docs.qmk.fm/#/feature_combo

Explore these (there are way more)
#undef COMBO_MUST_PRESS_IN_ORDER
#undef COMBO_ONLY_FROM_LAYER
*/

//Clear variables we plan to use that might be set elsewhere
#undef EXTRA_SHORT_COMBOS
#undef COMBO_TERM

//Set common configuration for all keyboards
#define EXTRA_SHORT_COMBOS
#define COMBO_TERM 50

