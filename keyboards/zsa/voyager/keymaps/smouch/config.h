/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/

#define COMBO_TERM 30
// #define COMBO_TERM_PER_KEY   // reduce for combos that misfire on rolls
// #define COMBO_MUST_HOLD_MODS // if a combo triggers a modifier, only trigger when the combo is held
// #define COMBO_HOLD_TERM 200  // how long at least one of the combo keys must be held to trigger
#define COMBO_ONLY_FROM_LAYER 0 // combos mapped to base layer only
#define COMBO_STRICT_TIMER      // full combo must be pressed within the combo_term (less misfires)
// #define COMBO_COUNT 19

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
// Holding Shift while Caps Word is active inverts the shift state.
#define CAPS_WORD_INVERT_ON_SHIFT
// When idle, turn off Caps Word after 5 seconds.
#define CAPS_WORD_IDLE_TIMEOUT 5000

#define USB_SUSPEND_WAKEUP_DELAY 0
#define SERIAL_NUMBER "RmgQl/B5Rbd"
#define LAYER_STATE_8BIT

// Configure the global tapping term (default: 200ms)
#undef TAPPING_TERM // if not default
#define TAPPING_TERM 175
#define TAPPING_TERM_PER_KEY  // reduce for HRM Shifts

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define QUICK_TAP_TERM 0

// Apply the modifier on keys that are tapped during a short hold of a modtap
#define PERMISSIVE_HOLD_PER_KEY

// Opposite hands rule for HRM. Prevents misfires on same hand rolls.
#define CHORDAL_HOLD

// Default to Mac hotkeys for Select_word
#define SELECT_WORD_OS_MAC

// Don't apply custom shift keys when any non-shift mod is held.
#define CUSTOM_SHIFT_KEYS_NEGMODS ~MOD_MASK_SHIFT

#undef RGB_MATRIX_TIMEOUT
#define RGB_MATRIX_TIMEOUT 300000
// #define RGB_MATRIX_STARTUP_SPD 60

// Enable just the effects you want.
// #define PALETTEFX_GRADIENT_ENABLE
// #define PALETTEFX_FLOW_ENABLE
// #define PALETTEFX_RIPPLE_ENABLE
// #define PALETTEFX_SPARKLE_ENABLE
// #define PALETTEFX_VORTEX_ENABLE
// #define PALETTEFX_REACTIVE_ENABLE

// Or enable all effects with
// #define PALETTEFX_ENABLE_ALL_EFFECTS

// Enable just the palettes you want.
// #define PALETTEFX_AFTERBURN_ENABLE
// #define PALETTEFX_AMBER_ENABLE
// #define PALETTEFX_BADWOLF_ENABLE
// #define PALETTEFX_CARNIVAL_ENABLE
// #define PALETTEFX_CLASSIC_ENABLE
// #define PALETTEFX_DRACULA_ENABLE
// #define PALETTEFX_GROOVY_ENABLE
// #define PALETTEFX_NOTPINK_ENABLE
// #define PALETTEFX_PHOSPHOR_ENABLE
// #define PALETTEFX_POLARIZED_ENABLE
// #define PALETTEFX_ROSEGOLD_ENABLE
// #define PALETTEFX_SPORT_ENABLE
#define PALETTEFX_SYNTHWAVE_ENABLE
// #define PALETTEFX_THERMAL_ENABLE
// #define PALETTEFX_VIRIDIS_ENABLE
// #define PALETTEFX_WATERMELON_ENABLE

// Or enable all palettes with
// #define PALETTEFX_ENABLE_ALL_PALETTES
