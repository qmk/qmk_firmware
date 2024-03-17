#pragma once

// when you tap then hold - setting quick tap term to 0 means you get the hold action.
// otherwise the tap to hold time must be below this to activate autorepeat.
// NOTE this breaks the ONESHOT_TAP_TOGGLE on a key if set to 0 !!
#define QUICK_TAP_TERM_PER_KEY

// permissive hold means D(a), D(b), U(b), U(a) will always emit the modified version of b,
// without this if the above is within the tapping term you get ab instead.
#define PERMISSIVE_HOLD
// hold on other key press will mean that D(mod), D(b), U(mod), U(b) will emit the hold action on mod
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY


#define TAPPING_TERM 175

#define ONESHOT_TAP_TOGGLE 2
#define ONESHOT_TIMEOUT 3000
