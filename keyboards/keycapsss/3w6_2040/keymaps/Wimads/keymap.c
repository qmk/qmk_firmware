/*TO DO
 * implement dragscroll trigger via numlock
 * get into lighting layers to fix capsword led animation
 */

#include QMK_KEYBOARD_H

////DEFINITIONS////
// Layers:
enum layers {
    _QTY  = 0, // QwerTY
    _QTYe = 1, // Qwerty for monkytype emulation
    _CAD  = 2, // CAD mode
    _NUM  = 3, // NUMbers and symbols
    _RNUM = 4, // NUMpad Right hand only
    _MISC = 9, // MISCelaneous;
};

/// Custom keycodes..
// Tap-hold keys:
#define FFF_NUM LT(_NUM, KC_F)
#define JJJ_NUM LT(_NUM, KC_J)
#define SPC_SFT LSFT_T(KC_SPC)
#define UND_SFT LSFT_T(KC_UNDS) // further defined in macro (because shifted keycodes in _T() is not possible)
#define EQL_RLT RALT_T(KC_EQL)
// Auto-Dead-Key:   //auto-send space after deadkey, unless ADK_ key was held; requires "English(US)"+"Qwerty US" language+kbd settings in windows
#define ADK_A LT(11, KC_A)
#define ADK_E LT(11, KC_E)
#define ADK_U LT(11, KC_U)
#define ADK_I LT(11, KC_I)
#define ADK_O LT(11, KC_O)
#define ADK_N LT(11, KC_N)
// Other:
#define DOTCOMM LT(10, KC_DOT) // KC_DOT, KC_COMM on shif; swap behavoiur by double tap (further defined in macro)
// Macros:
enum custom_keycodes {
    CLEARKB = SAFE_RANGE, // clears all keys and/or layers that might be stuck
    EE_BOOT,              // clear eeprom, then boot mode
    CADTOGG,              // toggle CAD mode
    RNUMTOG,              // toggle RNUM layer
    QTYTOGG,              // toggle QTYe layer
};
// Combos:
#include "g/keymap_combo.h" //included after custom keycodes, so custom keycodes can be used in combos.def
///..custom keycodes

/// keymaps..
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
  //Qwerty:
  [_QTY] = LAYOUT_split_3x5_3(
	  KC_Q,    KC_W,    ADK_E,   KC_R,    KC_T,             KC_Y,    ADK_U,   ADK_I,   ADK_O,   KC_P,
	  ADK_A,   KC_S,    KC_D,    FFF_NUM, KC_G,             KC_H,    JJJ_NUM, KC_K,    KC_L,    KC_QUOT,
	  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             ADK_N,   KC_M,    KC_COMM, KC_DOT,  KC_EXLM,
						KC_LALT, SPC_SFT, KC_LCTL,          KC_RALT, SPC_SFT, MO(_MISC)
  ),
  //Qwerty e: (unmodified qwerty layout for emulation in for example monkeytype)
  [_QTYe] = LAYOUT_split_3x5_3(
	  KC_Q,    KC_W,    ADK_E,   KC_R,    KC_T,             KC_Y,    ADK_U,   ADK_I,   ADK_O,   KC_P,
	  ADK_A,   KC_S,    KC_D,    FFF_NUM, KC_G,             KC_H,    JJJ_NUM, KC_K,    KC_L,    KC_SCLN,
	  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
						KC_LALT, KC_LSFT, KC_LCTL,          KC_RALT, SPC_SFT, MO(_MISC)
  ),
  //CAD mode: (a mostly transparent layer, but will activate extra combos)
  [_CAD] = LAYOUT_split_3x5_3(
	  _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
	  _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
	  _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
						_______, _______, _______,          _______, _______, _______
  ),
  //Numbers and symbols:
  [_NUM] = LAYOUT_split_3x5_3(
	  KC_AT,   KC_DLR,  KC_AMPR, KC_PIPE, KC_TILD,          KC_CIRC, KC_7,    KC_8,    KC_9,    KC_PERC,
	  KC_LCBR, KC_LPRN, KC_RPRN, KC_RCBR, KC_GRV,           KC_PLUS, KC_4,    KC_5,    KC_6,    KC_MINS,
	  KC_LBRC, KC_LT,   KC_GT,   KC_RBRC, KC_HASH,          KC_ASTR, KC_1,    KC_2,    KC_3,    KC_SLSH,
						_______, UND_SFT, _______,          EQL_RLT, KC_0,    DOTCOMM
  ),
  [_RNUM] = LAYOUT_split_3x5_3(
	  _______, _______, _______, _______, _______,          KC_CIRC, KC_7,    KC_8,    KC_9,    KC_PERC,
	  _______, _______, _______, _______, _______,          KC_PLUS, KC_4,    KC_5,    KC_6,    KC_MINS,
	  _______, _______, _______, _______, _______,          KC_ASTR, KC_1,    KC_2,    KC_3,    KC_SLSH,
						_______, _______, _______,          EQL_RLT, KC_0,    DOTCOMM
  ),
  //OTHER:
  [_MISC] = LAYOUT_split_3x5_3(
	  QK_BOOT, XXXXXXX, EE_CLR,  XXXXXXX, XXXXXXX,          KC_PGUP, KC_BRIU, KC_INS,  KC_VOLU, KC_PSCR,
	  XXXXXXX, KC_SCRL, XXXXXXX, XXXXXXX, XXXXXXX,          KC_PGDN, KC_BRID, XXXXXXX, KC_VOLD, XXXXXXX,
	  XXXXXXX, XXXXXXX, KC_CAPS, XXXXXXX, KC_BRK,           KC_NUM,  KC_MENU, XXXXXXX, KC_MUTE, XXXXXXX,
						XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX
  ),
    // clang-format on
};
///..keymaps

////LED INDICATORS////
/* LED numbering:
 * Left  hand LED = 0;
 * Right hand LED = 1;
 */
// rgb lighting variables:
int rgb_hue   = 40;
int rgb_sat   = 255;
int rgb_val   = 255;
int rgb_mode  = 1;   // initial values
int rgb_hue_q = 32;  // qwerty (yellow)
int rgb_hue_c = 60;  // CAD (lime)
int rgb_hue_n = 12;  // NUM (red/orange)
int rgb_hue_m = 185; // MISC (purple)
int rgb_hue_e = 165; // emulation (blue)

// animation speed:
const uint8_t RGBLED_BREATHING_INTERVALS[] PROGMEM = {2, 2, 2, 2};

// Set initial LED lighting state:
void matrix_init_user(void) {
    // initiate rgb underglow (default mode as per ASW_on true):
    rgblight_enable();
    rgblight_mode(rgb_mode);                    // set light effect for both LEDs
    rgblight_sethsv(rgb_hue, rgb_sat, rgb_val); // set HSV value for both LEDs
};

// Capsword indicator:
void caps_word_set_user(bool active) {
    if (active) {
        rgb_mode = 2;
        rgblight_mode(rgb_mode);
        if (IS_LAYER_ON(_RNUM)) {
            rgblight_sethsv(rgb_hue_n, rgb_sat, rgb_val); // override both LEDs, since can't override one when mode = 2;
        } else {
            rgblight_sethsv(rgb_hue, rgb_sat, rgb_val);
        }
    } else {
        rgb_mode = 1;
        rgblight_mode(rgb_mode);
        rgblight_sethsv(rgb_hue, rgb_sat, rgb_val);
        if (IS_LAYER_ON(_RNUM)) {
            rgblight_sethsv(rgb_hue_n, rgb_sat, rgb_val);
            rgblight_sethsv_at(rgb_hue, rgb_sat, rgb_val, 0);
        }
    }
};

// Layer indicators:
layer_state_t layer_state_set_user(layer_state_t state) {
    if (IS_LAYER_ON_STATE(state, _RNUM) && is_caps_word_on()) {
        rgblight_mode(rgb_mode);
        rgblight_sethsv(rgb_hue_n, rgb_sat, rgb_val); // override both LEDs, since can't override one when mode = 2;
    } else if (IS_LAYER_ON_STATE(state, _RNUM)) {
        if (IS_LAYER_ON_STATE(state, _MISC)) {
            rgb_hue = rgb_hue_m;
        } else if (IS_LAYER_ON_STATE(state, _NUM)) {
            rgb_hue = rgb_hue_n;
        } else if (IS_LAYER_ON_STATE(state, _CAD)) {
            rgb_hue = rgb_hue_c;
        } else if (IS_LAYER_ON_STATE(state, _QTYe)) {
            rgb_hue = rgb_hue_e;
        } else {
            rgb_hue = rgb_hue_q;
        }
        rgblight_mode(rgb_mode);
        rgblight_sethsv(rgb_hue_n, rgb_sat, rgb_val);
        rgblight_sethsv_at(rgb_hue, rgb_sat, rgb_val, 0);
    } else {
        if (IS_LAYER_ON_STATE(state, _MISC)) {
            rgb_hue = rgb_hue_m;
        } else if (IS_LAYER_ON_STATE(state, _NUM)) {
            rgb_hue = rgb_hue_n;
        } else if (IS_LAYER_ON_STATE(state, _CAD)) {
            rgb_hue = rgb_hue_c;
        } else if (IS_LAYER_ON_STATE(state, _QTYe)) {
            rgb_hue = rgb_hue_e;
        } else {
            rgb_hue = rgb_hue_q;
        }
        rgblight_mode(rgb_mode);
        rgblight_sethsv(rgb_hue, rgb_sat, rgb_val);
    }
    return state;
};

////CUSTOM KEY BEHAVIOURS////
// Turn on/off CAD combos:
bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    switch (combo_index) {
        case CAD_START ... CAD_FINAL:
            if (!IS_LAYER_ON(_CAD)) {
                return false;
            }
            return true;
    }
    return true;
};

// Tap-hold per key config:
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case UND_SFT:
            return 250;
        case ADK_A:
        case ADK_E:
        case ADK_U:
        case ADK_I:
        case ADK_O:
        case ADK_N:
            return 200;
        default:
            return TAPPING_TERM;
    }
};

/// multifunc keycodes..
typedef struct _multifunc_keycode_t { // define multifunc keycode functions
    uint16_t kc_record;               // unmodified keycode
    uint16_t kc_shifted;              // alternate keycode on shift
    uint16_t kc_deadkey;              // alternate keycode on auto_dead_key
} multifunc_keycode_t;
// clang-format off
#define MULTIFUNC_COUNT 12 // number of multifunc keycodes in multifuncmap
multifunc_keycode_t multifuncmap[MULTIFUNC_COUNT] = {
    /* Multifunc mapping format:
    {kc_record, kc_shifted, kc_deadkey}*///_DEF L
    {KC_Z,      S(KC_Z),    S(KC_CIRC)}, // z Z ^
    {KC_X,      S(KC_X),    S(KC_QUOT)}, // x X "
    {KC_C,      S(KC_C),    KC_QUOT},    // c C '
    {KC_V,      S(KC_V),    KC_GRV},     // v V `
    {KC_B,      S(KC_B),    S(KC_GRV)},  // b B ~
                                        ///_DEF R
    {ADK_N,     S(KC_N),    S(KC_GRV)},  // n N ~
    {KC_M,      S(KC_M),    KC_GRV},     // m M `
    {KC_COMM,   KC_SCLN,    KC_QUOT},    // , ; '
    {KC_DOT,    S(KC_SCLN), S(KC_QUOT)}, // . : "
    {KC_EXLM,   KC_QUES,    S(KC_CIRC)}, // ! ? ^
                                        ///_NUM
    {KC_SLSH,   KC_BSLS,    S(KC_CIRC)}, // / \ ^
    {KC_DLR,    RALT(KC_5), KC_NO},      // $ €
};
// clang-format on
int get_index_multifunc(uint16_t kc_record) { // find corresponding item in multifunc map for pressed key
    for (int i = 0; i < MULTIFUNC_COUNT; i++) {
        if (multifuncmap[i].kc_record == kc_record) return i;
    }
    return -1; // return -1 if pressed key is not in multifunc map
};
///..multifunc keycodes

/// Macros..
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // variables:
    static bool     dotcomm_state = true;                         // true = dot; false = comma;
    const int       index         = get_index_multifunc(keycode); // check if keycode is in multifunc map
    const uint16_t  mod_shift     = get_mods() & MOD_MASK_SHIFT;  // track shift state for custom shift behaviours (defined in multifunc keycodes)
    static uint16_t auto_dead_key = KC_SPC;                       // keycode to send after dead key (defined in multifunc keycodes)
    static uint16_t adk_mod_shift = 0;                            // track shift state for auto_dead_key

    // macros:
    switch (keycode) {
        case CLEARKB: // clear keyboard
            if (record->event.pressed) {
                clear_keyboard(); // clears all keys and modifiers that might be stuck
                layer_clear();    // clears all layers that might be stuck
            }
            return false;
        case EE_BOOT: // clear eeprom and boot
            if (record->event.pressed) {
                eeconfig_init();  // clear eeprom
                wait_ms(10);      // wait 10 ms
                reset_keyboard(); // enter bootmode
            }
            return false;

        // layer toggles:
        case CADTOGG: // toggle CAD mode
            if (record->event.pressed) {
                layer_off(_RNUM);   // always turn off _RNUM when toggling CAD mode on/off
                layer_invert(_CAD); // toggle CAD mode on/off
            }
            return false;
        case RNUMTOG: // toggle numpad on/off (only right hand side)
            if (record->event.pressed) {
                layer_invert(_RNUM);
            }
            return false;
        case QTYTOGG: // toggle emulation mode (unmodified qwerty layout)
            if (record->event.pressed) {
                layer_invert(_QTYe);
            }
            return false;

        // special keycodes:
        case UND_SFT:
            if (record->event.pressed && record->tap.count) { // underscore when tapped
                tap_code16(S(KC_UNDS));
                return false;
            }
            return true; // shift when held
        case DOTCOMM:
            if (record->event.pressed && record->tap.count == 2) { // invert DOTCOMM state on double tap
                dotcomm_state = !dotcomm_state;                    // invert state
                tap_code16(KC_BSPC);                               // remove character output from first tap
            } else if (record->event.pressed && dotcomm_state) {   // when state is true
                if (mod_shift) {                                   // send comm when shifted
                    unregister_mods(mod_shift);
                    tap_code16(KC_COMM);
                    register_mods(mod_shift);
                } else { // send dot by default
                    tap_code16(KC_DOT);
                }
            } else if (record->event.pressed) { // when state is false
                if (mod_shift) {                // send dot when shifted
                    unregister_mods(mod_shift);
                    tap_code16(KC_DOT);
                    register_mods(mod_shift);
                } else { // send comm by default
                    tap_code16(KC_COMM);
                }
            }
            return false;

        // Auto-Dead-Keys:  // requires "English(NL)" or "Nederlands" language setting + "US International" keyboard setting in Windows.
        case ADK_A:
        case ADK_E:
        case ADK_U:
        case ADK_I:
        case ADK_O:
        case ADK_N:
            if (record->event.pressed && record->tap.count) {
                // ON TAP:
                if (index == -1 || auto_dead_key == KC_SPC) return true; // check for index and adk state to avoid conflict with multifunc keycodes
            } else if (record->event.pressed) {
                // ON HOLD:
                auto_dead_key = keycode; // store keycode as auto_dead_key
                if (is_caps_word_on()) {
                    adk_mod_shift = MOD_MASK_SHIFT; // store shift state of auto_dead_key
                } else {
                    adk_mod_shift = mod_shift; // store shift state of auto_dead_key
                }
                return false; // don't return keycode
            } else {
                // ON RELEASE:
                auto_dead_key = KC_SPC;
                return true;
            }
        case KC_QUOT:
        case KC_GRV:
        case KC_TILD:
        case KC_CIRC:
            if (record->event.pressed && index == -1) {
                tap_code16(keycode);            // tap dead key
                unregister_mods(mod_shift);     // unregister shift (if it was pressed)
                register_mods(adk_mod_shift);   // register auto_dead_key shift state
                tap_code16(auto_dead_key);      // tap auto_dead_key (KC_SPC if no ADK_ keycode was held)
                unregister_mods(adk_mod_shift); // unregister auto_dead_key shift state
                register_mods(mod_shift);       // re-register shift (if it was pressed)
                return false;                   // ignore default key behavior
            }

        default:
            // multifunc keycodes:
            if (index != -1) {
                if (record->event.pressed && auto_dead_key != KC_SPC) {
                    // when auto_dead_key is active:
                    unregister_mods(mod_shift);                 // unregister shift (if it was pressed)
                    tap_code16(multifuncmap[index].kc_deadkey); // tap dead key
                    register_mods(adk_mod_shift);               // register auto_dead_key shift state
                    tap_code16(auto_dead_key);                  // tap auto_dead_key (KC_SPC if no ADK_ keycode w
                    unregister_mods(adk_mod_shift);             // unregister auto_dead_key shift state
                    register_mods(mod_shift);                   // re-register shift (if it was pressed)
                    return false;                               // ignore default key behaviour
                } else if (record->event.pressed && mod_shift) {
                    // when shift is pressed:
                    unregister_mods(mod_shift);                 // unregister shift
                    tap_code16(multifuncmap[index].kc_shifted); // tap custom shift key
                    register_mods(mod_shift);                   // re-register shift
                    return false;                               // ignore default key behaviour
                }
                return true; // else return default keycode

            } //..if(index != -1)

    } //..switch(keycode)

    return true; // if key is not in multifunc map or other macro, return normal key behaviour
};
///..Macros
