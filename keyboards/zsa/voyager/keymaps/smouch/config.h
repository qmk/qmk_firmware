/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/

#define COMBO_TERM 30
// #define COMBO_TERM_PER_KEY   // reduce for combos that misfire on rolls
// #define COMBO_MUST_HOLD_MODS // if a combo triggers a modifier, only trigger when the combo is held
// #define COMBO_HOLD_TERM 200  // how long at least one of the combo keys must be held to trigger
#define COMBO_ONLY_FROM_LAYER 0 // combos mapped to base layer only
#define COMBO_STRICT_TIMER

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
// When idle, turn off Caps Word after 10 seconds.
#define CAPS_WORD_IDLE_TIMEOUT 10000

// #undef RGB_MATRIX_TIMEOUT
// #define RGB_MATRIX_TIMEOUT 300000

#define USB_SUSPEND_WAKEUP_DELAY 0
#define SERIAL_NUMBER "RmgQl/B5Rbd"
#define LAYER_STATE_8BIT
// #define COMBO_COUNT 19

// Configure the global tapping term (default: 200ms)
#undef TAPPING_TERM // if not default
#define TAPPING_TERM 175
#define TAPPING_TERM_PER_KEY  // reduce for HRM Shifts

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define QUICK_TAP_TERM 0

// Apply the modifier on keys that are tapped during a short hold of a modtap
#define PERMISSIVE_HOLD_PER_KEY

#define CHORDAL_HOLD

// Don't apply custom shift keys when any non-shift mod is held.
#define CUSTOM_SHIFT_KEYS_NEGMODS ~MOD_MASK_SHIFT

/* Default to Mac hotkeys for Select_Word */
#define SELECT_WORD_OS_MAC

// #define RGB_MATRIX_STARTUP_SPD 60

