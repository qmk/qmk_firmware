#define TAPPING_TERM 250

/* Ignore Mod Tap Interrupt
https://beta.docs.qmk.fm/using-qmk/software-features/tap_hold

For Instance:
SFT_T(KC_A) Down
KC_X Down
SFT_T(KC_A) Up
KC_X Up
Normally, this would send a capital X (SHIFT+x), or, Mod + key. With Ignore Mod Tap Interrupt enabled,
holding both keys are required for the TAPPING_TERM to register the hold action.
A quick tap will output ax in this case, while a hold on both will still output capital X (SHIFT+x).
*/
#define IGNORE_MOD_TAP_INTERRUPT


/* Tapping Force Hold
When the user holds a key after tap, this repeats the tapped key rather to hold a modifier key. This allows to use auto repeat for the tapped key.

Example:

SFT_T(KC_A) Down
SFT_T(KC_A) Up
SFT_T(KC_A) Down
wait more than tapping term...
SFT_T(KC_A) Up
With default settings, a will be sent on the first release, then a will be sent on the second press allowing the computer to trigger its auto repeat function.

With TAPPING_FORCE_HOLD, the second press will be interpreted as a Shift, allowing to use it as a modifier shortly after having used it as a tap.

!> TAPPING_FORCE_HOLD will break anything that uses tapping toggles (Such as the TT layer keycode, and the One Shot Tapping Toggle).
*/

#define TAPPING_FORCE_HOLD
