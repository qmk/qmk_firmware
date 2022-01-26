#include QMK_KEYBOARD_H


//----------- Layer names -----------//
//-----------------------------------//
enum preonic_layers
{
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _PROTECTED_LYR
};


//----------- Sounds -----------//
//------------------------------//
#ifdef AUDIO_ENABLE
    float capslockToggleSound[][2] = SONG(CAPS_LOCK_ON_SOUND);
    float protectedLayerSound[][2] = SONG(MUSIC_SCALE_SOUND);
#endif  // AUDIO_ENABLE


//----------- Tapdance prelims -----------//
//----------------------------------------//
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_1_TAP,
    TD_1_HOLD,
    TD_2_TAP,
    TD_2_HOLD,
    TD_3_TAP,
    TD_4_TAP,
    TD_5_TAP
    // TD_DOUBLE_SINGLE_TAP, // Send two single taps
    // TD_TRIPLE_TAP,
    // TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

td_state_t cur_dance(qk_tap_dance_state_t* state);

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
td_state_t cur_dance(qk_tap_dance_state_t* state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_1_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_1_HOLD;
    }
    else if (state->count == 2)
    {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        //if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        //else
        if (state->pressed) return TD_2_HOLD;
        else return TD_2_TAP;
    }
    else if (state->count == 3)
    {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        //if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        //else
        if (state->pressed) return TD_3_TAP;
        else return TD_3_TAP;
    }
    else if (state->count == 4)
    {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        //if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        //else
        if (state->pressed) return TD_4_TAP;
        else return TD_4_TAP;
    }
    else if (state->count == 5)
    {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        //if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        //else
        if (state->pressed) return TD_5_TAP;
        else return TD_5_TAP;
    }
    
    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    /*if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    }*/
    //else
    return TD_UNKNOWN;
}


//----------- 2tap capslock --------------//
//----------------------------------------//
void twoCapsLock_finished(qk_tap_dance_state_t* state, void* user_data);
void twoCapsLock_reset(qk_tap_dance_state_t* state, void* user_data);

static td_tap_t twoCapsLock_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void twoCapsLock_finished(qk_tap_dance_state_t* state, void* user_data) {
    twoCapsLock_tap_state.state = cur_dance(state);
    switch (twoCapsLock_tap_state.state) {
    case TD_NONE: register_code(KC_LSFT); break;
    case TD_UNKNOWN: register_code(KC_LSFT); break;
    case TD_1_TAP: register_code(KC_LSFT); break;
    case TD_1_HOLD: register_code(KC_LSFT); break;
    case TD_2_TAP:
        register_code(KC_CAPS);
#ifdef AUDIO_ENABLE
        PLAY_SONG(capslockToggleSound);
#endif  // AUDIO_ENABLE
        break;
    case TD_2_HOLD: register_code(KC_LSFT); break; 
    case TD_3_TAP: register_code(KC_LSFT); break;
    case TD_4_TAP: register_code(KC_LSFT); break;
    case TD_5_TAP: register_code(KC_LSFT); break;
    //    // Last case is for fast typing. Assuming your key is `f`:
    //    // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //    // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
    //case TD_DOUBLE_SINGLE_TAP: tap_code(KC_X); register_code(KC_X);
    }
}

void twoCapsLock_reset(qk_tap_dance_state_t* state, void* user_data) {
    switch (twoCapsLock_tap_state.state) {
    case TD_UNKNOWN: unregister_code(KC_LSFT); break;
    case TD_NONE: unregister_code(KC_LSFT); break;
    case TD_1_TAP: unregister_code(KC_LSFT); break;
    case TD_1_HOLD: unregister_code(KC_LSFT); break;
    case TD_2_TAP:
        unregister_code(KC_CAPS);
#ifdef AUDIO_ENABLE
        PLAY_SONG(capslockToggleSound);
#endif  // AUDIO_ENABLE
        break;
    case TD_2_HOLD: unregister_code(KC_LSFT); break;
    case TD_3_TAP: unregister_code(KC_LSFT); break;
    case TD_4_TAP: unregister_code(KC_LSFT); break;
    case TD_5_TAP: unregister_code(KC_LSFT); break;
    //case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_X);
    }
    twoCapsLock_tap_state.state = TD_NONE;
}


//----------- Custom keycodes ------------//
//----------------------------------------//
enum
{    TD_2_CAPSLOCK      };

qk_tap_dance_action_t tap_dance_actions[] =
{    [TD_2_CAPSLOCK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, twoCapsLock_finished, twoCapsLock_reset)      };


// Intercepts and overrides
bool process_record_user(uint16_t keycode, keyrecord_t* record)
{
    switch (keycode)
    {
        case MO(_PROTECTED_LYR):

            // If pressed
            if (record->tap.count && record->event.pressed)
            {
            #ifdef AUDIO_ENABLE
                PLAY_SONG(protectedLayerSound); // Beep
            #endif  // AUDIO_ENABLE
            return true; // Let QMK send the enter press/release events
            }

            // If released
            else
            {
#ifdef AUDIO_ENABLE
                PLAY_SONG(protectedLayerSound); // Beep
#endif  // AUDIO_ENABLE    
            }
            //return false; // Skip all further processing of this key
        
    default:
        return true; // Process all other keycodes normally
    }
}


// The actual keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] =
{

	[_QWERTY] = LAYOUT_ortho_5x12   // main layer
    (
        KC_GRV,     KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_6,       KC_7,           KC_8,       KC_9,       KC_0,       KC_QUOT,
        KC_TAB,     KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           KC_Y,       KC_U,           KC_I,       KC_O,       KC_P,       KC_BSPC,
        KC_ESC,     KC_A,           KC_S,           KC_D,           KC_F,           KC_G,           KC_H,       KC_J,           KC_K,       KC_L,       KC_SCLN,    KC_ENT,

        TD
        (TD_2_CAPSLOCK),
                    KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_N,       KC_M,           KC_COMM,    KC_DOT,     KC_SLSH,    TD(TD_2_CAPSLOCK),

        KC_BTN1,    KC_LCTL,        KC_LGUI,        KC_LALT,        MO(_LOWER),     KC_SPC,         KC_SPC,     MO(_RAISE),     KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT
    ),

	[_LOWER] = LAYOUT_ortho_5x12    // lower key
    (
        KC_TRNS,    LGUI(KC_1),     LGUI(KC_2),     LGUI(KC_3),     LGUI(KC_4),     LGUI(KC_5),     KC_TRNS,    KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    MO(_PROTECTED_LYR),
        KC_GRV,     KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_6,       KC_7,           KC_8,       KC_9,       KC_0,       KC_DEL,
        KC_BSPC,    KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,      KC_MINS,        KC_EQL,     KC_LCBR,    KC_RCBR,    KC_TRNS,
        KC_TRNS,    KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         KC_F12,     KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_BSLS,    KC_TRNS,
        KC_WH_D,    KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,    MO(_ADJUST),    KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END
    ),

	[_RAISE] = LAYOUT_ortho_5x12    // raise key
    (
        KC_TRNS,    LGUI(KC_1),     LGUI(KC_2),     LGUI(KC_3),     LGUI(KC_4),     LGUI(KC_5),     KC_TRNS,    KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    MO(_PROTECTED_LYR),
        KC_TILD,    KC_EXLM,        KC_AT,          KC_HASH,        KC_DLR,         KC_PERC,        KC_CIRC,    KC_AMPR,        KC_ASTR,    KC_LPRN,    KC_RPRN,    KC_DEL,
        KC_DEL,     KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,      KC_UNDS,        KC_PLUS,    KC_LBRC,    KC_RBRC,    KC_TRNS,
        KC_TRNS,    KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         KC_F12,     KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_PIPE,    KC_TRNS,
        KC_WH_U,    KC_TRNS,        KC_TRNS,        KC_TRNS,        MO(_ADJUST),    KC_TRNS,        KC_TRNS,    KC_TRNS,        KC_MUTE,    KC_VOLD,    KC_VOLU,    KC_F24
    ),

	[_ADJUST] = LAYOUT_ortho_5x12   // hardw1are adjust layer, raise+lower
    (
        BL_TOGG,    BL_STEP,        BL_BRTG,        BL_ON,          BL_OFF,         BL_INC,         BL_DEC,     KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    RESET,          DEBUG,          KC_TRNS,        RGB_HUI,        RGB_HUD,        RGB_SAI,    RGB_SAD,        RGB_VAI,    RGB_VAD,    RGB_SPI,    RGB_SPD,
        KC_TRNS,    KC_TRNS,        MU_MOD,         AU_ON,          AU_OFF,         KC_TRNS,        KC_TRNS,    DF(0),          DF(1),      DF(2),      KC_TRNS,    KC_TRNS,
        KC_TRNS,    MUV_DE,         MUV_IN,         MU_ON,          MU_OFF,         MI_ON,          MI_OFF,     KC_TRNS,        KC_TRNS,    KC_TRNS,    RGB_M_B,    RGB_M_SN,
        RGB_TOG,    RGB_MOD,        RGB_RMOD,       RGB_M_P,        KC_TRNS,        RGB_M_R,        RGB_M_SW,   KC_TRNS,        RGB_M_K,    RGB_M_X,    RGB_M_G,    RGB_M_T
    ),

    [_PROTECTED_LYR] = LAYOUT_ortho_5x12   // Protected funcs, only acc from 5x tapdance
    (
        KC_SYSTEM_POWER,
                   KC_NO,            KC_NO,          KC_NO,            KC_NO,           KC_NO,           KC_NO,       KC_NO,           KC_NO,       KC_NO,       KC_NO,       KC_NO,

        KC_NO,     KC_NO,           KC_NO,           KC_NO,           KC_NO,           KC_NO,           KC_NO,       KC_NO,           KC_NO,       KC_NO,       KC_NO,       KC_NO,
        KC_NO,     KC_NO,           KC_NO,           KC_NO,           KC_NO,           KC_NO,           KC_NO,       KC_NO,           KC_NO,       KC_NO,       KC_NO,       KC_NO,
        KC_NO,     KC_NO,           KC_NO,           KC_NO,           KC_NO,           KC_NO,           KC_NO,       KC_NO,           KC_NO,       KC_NO,       KC_NO,       KC_NO,
        KC_NO,     KC_NO,           KC_NO,           KC_NO,           KC_NO,           KC_NO,           KC_NO,       KC_NO,           KC_NO,       KC_NO,       KC_NO,       KC_NO
    )


};
