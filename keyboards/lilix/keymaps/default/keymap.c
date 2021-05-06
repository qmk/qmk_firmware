/* Copyright 2021 Elizabeth Bodaneze
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include <stdio.h>

#define CAPSWORD_ENABLE
#define LGBT_FLAGS

#ifdef LGBT_FLAGS
    #include "lgbtflags.h"
#endif

/* Store handedness as a variable to avoid calling is_keyboard_master()
 * every time and saving space
 */
bool is_master;

// Backlight timeout feature
#ifdef RGBLIGHT_ENABLE
#define DEFAULT_RGBLIGHT_TIMEOUT 10     // in minutes
static uint16_t led_timer = 0;
static uint8_t old_rgblight_status = 0;
static bool led_on = true;
#endif

//Animation trackers
#ifdef OLED_DRIVER_ENABLE
static uint8_t col_tracker;
static uint8_t anim_frame;
static uint16_t anim_timer;
static uint8_t frame_delay = 25;
static bool loop_tracker = false;
static uint8_t key_tracker;
static uint16_t x;
static uint16_t global_timer = 0;
static uint16_t idle_timer = 0;
#endif


/* Each layer gets a name for readability, which is then used in the keymap matrix below.
 * The underscores don't mean anything - you can have a layer called STUFF or any other name.
 * Layer names don't all need to be of the same length, obviously, and you can also skip them
 * entirely and just use numbers.
 */
enum layer_names {
    _QWERTY = 0,
    _NUMPAD,
    _RAISE,
    _LOWER,
    _ADJUST
};;


// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  NUMPAD  = TG(_NUMPAD),
  LOWER   = MO(_LOWER),
  RAISE   = MO(_RAISE),
  ADJUST  = MO(_ADJUST),
  EISU    = KC_LANG2,
  KANA    = KC_LANG1,
  RGBRST,
  LGBT_FL,
  RGBTTOG,                   //toggle RGB timer
  TIM_INC,                   //increase RGB timer
  TIM_DEC,                   //decrease RGB timer
  BR_SCLN = KC_SLSH,         //semicolon (;) on brazillian keyboards
  BR_SLSH = KC_INT1,         //slash (/) ...
  BR_CDLL = KC_SCLN,         //cedilla (ç) ...
  BR_TIL  = KC_QUOT,         //tilde (~) ...
  BR_ACU  = KC_LBRC,         //acute (´)..
  BR_LBRC = KC_RBRC,         //left bracket ([) ...
  BR_RBRC = KC_BSLS,         //right bracket (]) ...
  BR_QUOT = KC_GRV,          //quote (") ...
  BR_CIRC = LSFT(BR_TIL),    //circumflex (^) ...
  BR_GRAV = LSFT(BR_ACU),    //grave (`) ...
  PARGRPH = RALT(KC_EQL),    //article/subsection (§) ...
  SSCPT_A = RALT(BR_LBRC),   //superscript minuscule a (ª) ...
  SSCPT_O = RALT(BR_RBRC),   //superscript minuscule o (º) ...
  BR_LONG = LSFT(SSCPT_A),   //long (¯) ...
  DEGREE  = RALT(BR_SLSH),   //degree symbol (°) ...
  ND_TILD = RALT(BR_TIL),    //non-dead tilde (~) ...
  ND_ACUT = RALT(BR_ACU),    //...      acute (´) ...
  ND_CIRC = RALT(BR_CIRC),   //...      circ. (^) ...
  ND_GRAV = RALT(BR_GRAV),   //...      grave (`) ...
  SYSRQ   = KC_SYSREQ,       // system request
  RCTLSLS = RCTL_T(BR_SLSH), //right control on hold, BR_SLSH on tap
  RSFTSCL = RSFT_T(BR_SCLN), //right shift on hold, BR_SCLN on tap
  BBACKWD = LALT(KC_LEFT),   //browser backward (alt + left)
  BUPWARD = LALT(KC_UP),     //browser upward   (alt + up)
  BFORWRD = LALT(KC_RIGHT),  //browser forward  (alt + right)
  AUTOCMP = MEH(KC_A),       //to run autocomplete
  WIN_SCR = LALT(KC_PSCR),   //window screenshot
  CLP_SCR = LSFT(KC_PSCR),   //screenshot to clipboard
  CWINSCR = LALT(CLP_SCR),   //window ...
  SEL_SCR = LCTL(CLP_SCR),   //selection ...
  CTRL_X  = LCTL(KC_X),      // Control + X
  CTRL_C  = LCTL(KC_C),      // Control + C
  CTRL_V  = LCTL(KC_V),      // Control + V
  CSHIF_C = LSFT(CTRL_C),    // Control + Shift + C (copy on terminals)
  CSHIF_V = LSFT(CTRL_V)     // Control + Shift + V (paste on terminals)
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Qwerty
     * ,-----------------------------------------.             ,-----------------------------------------.
     * | Esc|'|   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Del  |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  | Bksp |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   Ç  |Enter |
     * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   C  |   V  |   B  |Raise |Lower |   N  |   M  |   ,  |   .  |  Up  |Shft|;|
     * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
     * | Ctrl |   \  | Alt  | LGUI | KANA |Lower |Space |Space |Raise | RGUI |Ctrl|/| Left | Down |Right |
     * `-------------------------------------------------------------------------------------------------'
     */
    [_QWERTY] = LAYOUT( \
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,    \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,   \
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    BR_CDLL, KC_ENTER,  \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    RAISE,   LOWER,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   RSFTSCL,   \
        KC_LCTL, KC_NUBS, KC_LALT, KC_LGUI, KANA,    LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_RGUI, RCTLSLS, KC_LEFT, KC_DOWN, KC_RGHT    \
    ),

    /* Numpad
     * ,-----------------------------------------.             ,-----------------------------------------.
     * |      |      |      |      |      |      |             |NumLck| Esc  | Alt  |Shift |   *  | Del  |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * |      |      |      |      |      |      |             |   7  |   8  |   9  | Ctrl |   /  | Bksp |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * |NumPad|      |      |      |      |      |             |   4  |   5  |   6  | Ctrl |   +  |  -   |
     * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |NumPad|   .  |   1  |   2  |   3  |Enter |  Up  |  =   |
     * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |Space |      |   0  |   ,  | Left | Down |Right |
     * `-------------------------------------------------------------------------------------------------'
     */
    [_NUMPAD] =  LAYOUT( \
        _______, _______, _______, _______, _______, _______,                   KC_NLCK, KC_ESC,  KC_LALT, KC_LSFT, KC_PAST, KC_DEL,  \
        _______, _______, _______, _______, _______, _______,                   KC_P7,   KC_P8,   KC_P9,   KC_LCTL, KC_PSLS, KC_BSPC, \
        NUMPAD,  _______, _______, _______, _______, _______,                   KC_P4,   KC_P5,   KC_P6,   KC_LCTL, KC_PPLS, KC_PMNS, \
        _______, _______, _______, _______, _______, _______, NUMPAD,  KC_DOT,  KC_P1,   KC_P2,   KC_P3,   KC_PENT, KC_UP,   KC_PEQL, \
        _______, _______, _______, _______, _______, _______, _______, KC_SPC,  _______, KC_P0,   KC_PDOT, KC_LEFT, KC_DOWN, KC_RGHT  \
    ),

    /* Lower
     * ,-----------------------------------------.             ,-----------------------------------------.
     * |   '  | Web  | Mail | File | Calc |      |             |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * | Music| Prev | Play | Next | Stop | Pause|             | Vol- | Vol+ | Mute |  (`) |   ª  |   `  |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * | Caps |      |      |      |      |      |             |      |      |      |  (^) |   º  |   ^  |
     * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |SwapTg|      |      | C-V  | C-C  |      |   °  |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |AutCmp|      |Raise | Raise|      |      |      |      |      |      |
     * `-------------------------------------------------------------------------------------------------'
     */
    [_LOWER] = LAYOUT( \
        KC_GRV,  KC_WHOM, KC_MAIL, KC_WSCH, KC_CALC, _______,                    KC_F7,   KC_F8,    KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
        KC_MSEL, KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP, KC_PAUS,                    KC_VOLD, KC_VOLU,  KC_MUTE, ND_GRAV, SSCPT_A, BR_GRAV, \
        KC_CAPS, _______, _______, _______, _______, _______,                    _______, _______,  _______, ND_CIRC, SSCPT_O, BR_CIRC, \
        _______, _______, _______, _______, _______, _______,  SH_TT,   _______, _______, CSHIF_V,  CSHIF_C, _______, DEGREE,  _______, \
        _______, _______, _______, _______, AUTOCMP, _______,  RAISE,   RAISE,   _______, _______,  _______, _______, _______, _______  \
    ),

    /* Raise
     * ,-----------------------------------------.             ,-----------------------------------------.
     * |  F1  |  F2  |  F4  |  F4  |  F5  |  F6  |             |Power |Sleep | Wake |Insert|  -   |  =   |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * |      | Bprv |BAbove| Bfwd | Eject|      |             |      |      |      |  (´) |  [   |  ´   |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * |Scroll|      |      |      |      |      |             |      |      |      |  (~) |  ]   |  ~   |
     * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |ClpScr|WinScr|WinClp|SelScr|PrtScr|      |SwapTg| Menu |Paste | Copy | Cut  |PageUp|  /   |
     * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |Lower | Lower|      |AltGr |      | Home |PageDn| End  |
     * `-------------------------------------------------------------------------------------------------'
     */
    [_RAISE] = LAYOUT( \
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_PWR,  KC_SLEP, KC_WAKE, KC_INS,  KC_MINS, KC_EQL,  \
        _______, BBACKWD, BUPWARD, BFORWRD, KC_EJCT, _______,                   _______, _______, _______, ND_ACUT, BR_LBRC, BR_ACU,  \
        KC_SLCK, _______, _______, _______, _______, _______,                   _______, _______, _______, ND_TILD, BR_RBRC, BR_TIL,  \
        _______, CLP_SCR, WIN_SCR, CWINSCR, SEL_SCR, KC_PSCR, _______, SH_TT,   KC_APP,  CTRL_V,  CTRL_C,  CTRL_X,  KC_PGUP, _______, \
        _______, _______, _______, _______, _______, _______, LOWER,   LOWER,   _______, KC_RALT, _______, KC_HOME, KC_PGDN, KC_END   \
    ),

    /* Adjust (Lower + Raise)
     * ,-----------------------------------------.             ,-----------------------------------------.
     * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |             |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * |      |      | Bri+ |      |      |      |             |SysRq |      |      |  §   |  _   |  +   |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * |NumPad|      | Bri- |      |      |SwpOff|             |      |      |      |      |  ¯   |Reset |
     * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
     * |Timer+|RGBRST|      |      |      |      |      |      |      |LGBT++| MODE+| HUE+ | SAT+ | VAL+ |
     * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
     * |Timer-|TToggl|      |      |      |      |      |      |      |RGBTOG| MODE-| HUE- | SAT- | VAL- |
     * `-------------------------------------------------------------------------------------------------'
     */
    [_ADJUST] =  LAYOUT( \
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11,  KC_F12,  \
        _______, _______, KC_BRIU, _______, _______, _______,                   SYSRQ,   _______, _______,  PARGRPH, KC_UNDS, KC_PLUS, \
        NUMPAD,  _______, KC_BRID, _______, _______, SH_OFF,                    _______, _______, _______,  _______, BR_LONG, RESET,   \
        TIM_INC, RGBRST,  _______, _______, _______, _______, _______, _______, _______, LGBT_FL, RGB_MOD,  RGB_HUI, RGB_SAI, RGB_VAI, \
        TIM_DEC, RGBTTOG, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD  \
    )


    /* Empty
     * ,-----------------------------------------.             ,-----------------------------------------.
     * |      |      |      |      |      |      |             |      |      |      |      |      |      |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * |      |      |      |      |      |      |             |      |      |      |      |      |      |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * |      |      |      |      |      |      |             |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
     * `-------------------------------------------------------------------------------------------------'
     */
    /*
    [_EMPTY] =  LAYOUT( \
        _______, _______, _______, _______, _______, _______,                   _______, _______,  _______, _______, _______, _______,  \
        _______, _______, _______, _______, _______, _______,                   _______, _______,  _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______,                   _______, _______,  _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______  \
    )
    */
};


/* =====  Sync code start ===== */
// Code to keep variables on both sides in synchrony
//#include <print.h>
#include <string.h>
#include <transactions.h>


typedef struct user_runtime_config {
    bool record_pressed;

    // Backlight off timer feature
    bool timer_on;
    uint8_t rgblight_timeout;
    uint8_t min_counter;
} user_runtime_config;


//_Static_assert(sizeof(user_runtime_config) == 1, "Invalid data transfer size for user sync data");


user_runtime_config user_state;


void rpc_user_sync_callback(uint8_t initiator2target_buffer_size, const void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(user_state)) {
        memcpy(&user_state, initiator2target_buffer, sizeof(user_runtime_config));
    }
}


void keyboard_post_init_user(void) {
    // Register keyboard state sync split transaction
    transaction_register_rpc(RPC_ID_SYNC_STATE_USER, rpc_user_sync_callback);

    // Backlight timeout feature
    user_state.timer_on = true;
    user_state.rgblight_timeout = DEFAULT_RGBLIGHT_TIMEOUT ;
    user_state.min_counter = 0;

    is_master = is_keyboard_master();

    //Enable RGB layers
    #ifdef LGBT_FLAGS
        rgblight_layers = lgbt_rgb_layers;
    #endif
}


// Not exactly sync code, but needs to be here
void rgb_off_timer(void) {
    #ifdef RGBLIGHT_ENABLE
        // Increase the RGB auto off timer

        if (idle_timer == 0) led_timer = timer_read();

        if (user_state.timer_on && led_on && idle_timer > 1000 && timer_elapsed(led_timer) > 60000) {
            if (is_master) {
                user_state.min_counter++;
            }
            led_timer = timer_read();
        }

        // Turn RGB on if it was on before and a key was pressed
        if (led_on == false && old_rgblight_status != 0 && user_state.record_pressed) {
            rgblight_enable_noeeprom();
            led_on = true;
        }

        // Turn RGB off if it was on, the timer was on and the timeout is reached
        if (user_state.timer_on && led_on && user_state.min_counter >= user_state.rgblight_timeout) {
            old_rgblight_status = rgblight_is_enabled();
            led_on = false;
            if (is_master) {
                user_state.min_counter = 0;
            }
            rgblight_disable_noeeprom();
        }

        // Reset timers whenever keys are pressed
        if (user_state.timer_on == true && user_state.record_pressed) {
            if (led_on == false || old_rgblight_status == 0) {
                if (old_rgblight_status != 0) { rgblight_enable_noeeprom(); }
                led_on = true;
            }

                led_timer = timer_read();
            if (is_master) {
                user_state.min_counter = 0;
            }
        }
    #endif
}


/* Same as rgb_off_timer(), not exactly sync code, but needs to be
 * here, since it is referenced in user_state_sync() and requires
 * the user_state struct
 */
void update_anim_timers(void) {
    if (user_state.record_pressed) {
        /* Decrease frame_delay every 50ms when a key is pressed/held,
         * but keep to a minimum of 10ms
         */
        if (frame_delay > 10 && !(global_timer % 50)) frame_delay -= 1;
        if (key_tracker > 7 ) {
            loop_tracker = !loop_tracker;
            key_tracker = 0;
        }
        if (anim_timer > frame_delay * 7) {
            key_tracker += 1;
            anim_timer = 0;
        }
        idle_timer = 0;
    }
}


void user_state_sync(void) {
    if (is_master) {
        // Update RGB off and animation timers for the master half
        rgb_off_timer();
        update_anim_timers();

        // Keep track of the last state, so that we can tell if we need to propagate to slave
        static user_runtime_config last_user_state;
        static uint32_t            last_sync;
        bool                       needs_sync = false;

        // Check if the state values are different
        if (memcmp(&user_state, &last_user_state, sizeof(user_runtime_config))) {
            needs_sync = true;
            memcpy(&last_user_state, &user_state, sizeof(user_runtime_config));
        }

        // Send to slave every 125ms regardless of state change
        if (timer_elapsed32(last_sync) > 125) {
            needs_sync = true;
        }

        // Perform the sync if requested
        if (needs_sync) {
            // Is the if/else below really needed? Removing it doesn't change firmware size, probably debug stuff?
            //
            //if (transaction_rpc_send(RPC_ID_SYNC_STATE_USER, sizeof(user_runtime_config), &user_state)) {
            transaction_rpc_send(RPC_ID_SYNC_STATE_USER, sizeof(user_runtime_config), &user_state);
            last_sync = timer_read32();
            /*} else {
                print("Failed to perform rpc call\n");
            }*/
        }
    } else {
        // Update RGB off and animation timers for the slave half
        rgb_off_timer();
        update_anim_timers();
    }
}


void housekeeping_task_user(void) {
    // Data sync from master to slave
    user_state_sync();
}
/* ===== Sync code end ===== */


// Turn stuff off and on based on host state
void suspend_power_down_user(void) {
    oled_off();
}


void suspend_wakeup_init_user(void) {
    oled_on();
}


/* borrowed from filterpaper:
 * https://github.com/filterpaper/qmk_userspace/blob/main/filterpaper.c#L35-L63
 */
#ifdef CAPSWORD_ENABLE
// Deactivate caps lock following a word
static void process_caps_word(uint_fast16_t keycode, keyrecord_t const *record) {
	// Get base key code of mod or layer tap with bitmask
	if (((QK_MOD_TAP <= keycode && keycode <= QK_MOD_TAP_MAX) ||
		(QK_LAYER_TAP <= keycode && keycode <= QK_LAYER_TAP_MAX)) &&
		(record->tap.count)) { keycode = keycode & 0xFF; }
	// Toggle caps lock with the following key codes
	switch (keycode) {
		case KC_TAB:
		case KC_ESC:
		case KC_SPC:
		case KC_ENT:
		case KC_DOT:
		case KC_COMM:
		case KC_GESC:
			if (record->event.pressed) { tap_code(KC_CAPS); }
	}
}
#endif


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (record->event.pressed) {
        user_state.record_pressed = 1;
        #ifdef CAPSWORD_ENABLE // Monitor key codes to toggle caps lock
            if (host_keyboard_led_state().caps_lock) { process_caps_word(keycode, record); }
        #endif
    } else {
        user_state.record_pressed = 0;
    }

    switch (keycode) {
        case RGBRST:
            #ifdef RGBLIGHT_ENABLE
                if (record->event.pressed) {
                    eeconfig_update_rgblight_default();
                    rgblight_enable();
                }
            #endif
            break;
        case LGBT_FL:
            if (record->event.pressed) {
                if (LGBT_flag_tracker <= (LGBT_flags_total - 1) ) {
                    if (LGBT_flag_tracker > 0 ) {
                        rgblight_set_layer_state((LGBT_flag_tracker - 1), 0);
                    }
                    rgblight_set_layer_state(LGBT_flag_tracker, 1);
                    LGBT_flag_tracker++;
                } else {
                    rgblight_set_layer_state((LGBT_flag_tracker - 1), 0);
                    LGBT_flag_tracker = 0;
                }
            }
            return false;
            break;
        case RGBTTOG:
            #ifdef RGBLIGHT_ENABLE
                if (record->event.pressed) {
                   user_state.timer_on = !user_state.timer_on ;
                }
            #endif
            break;
        case TIM_INC:
            #ifdef RGBLIGHT_ENABLE
                if (record->event.pressed) {
                    if (user_state.rgblight_timeout == 0 ) {
                        user_state.timer_on = true ;
                    }
                if (user_state.rgblight_timeout < 255 ) {
                    user_state.rgblight_timeout++ ;
                }
            }
            #endif
            break;
        case TIM_DEC:
            #ifdef RGBLIGHT_ENABLE
               if (record->event.pressed) {
                    if (user_state.rgblight_timeout > 0 ) {
                        user_state.rgblight_timeout-- ;
                    }
                    if (user_state.rgblight_timeout == 0 ) {
                        user_state.timer_on = false ;
                    }
                }
            #endif
            break;
    }
    return true;
}


//Tri-state layers: switch to Adjust layer when Lower and Raise are held together
layer_state_t layer_state_set_user(layer_state_t state) {
   return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}


// Uncomment to enable debug flags
/*void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable=true;
    debug_matrix=true;
    debug_keyboard=true;
    //debug_mouse=true;
}*/


#ifdef OLED_DRIVER_ENABLE
/* Here we have both animation frames on a single array -
 * - the first index is the frame, and the second is a byte
 * representing the "on/off" state for eight vertical pixels
 * starting from the top left corner of the display. Each
 * line is eight horizontal pixels, so four lines equal to
 * an 8px tall by 32px wide area, filling the width of the
 * display.
 */
static const char lilian[][160] PROGMEM = {
    {   0,  0,  0, 60,192,  0, 16,152,  // first 8x8 "character"
      136,136,196, 68,  0,128,192,224,  // second character
      240, 88,  2, 60,200,  4, 52, 26,  // third character
      128, 96, 16, 16, 32, 32, 16, 12,  // fourth character
        0,  0,  0,  0,131,206,224,241,  // start of the second 8x32px "line"
      248,248,252,254,255,255,239,239,  // ...
      245,241,240,240,113,112,120,188,  // ...
       92,156,174,118, 22, 14,  7,  1,  // end of the second line
       16, 96, 64,255,229, 30,190,255,  // third line
      255,159, 15, 79,199, 66, 98, 38,  // ...
       36, 37, 37,  5,131,131,199,255,  // ...
      255,255,104, 64,  0,  0,  0,  0,  // ...
       16,141,103, 25,173,247,221,137,  // fourth line
      141,157,187,158,156,205,248, 40,  // ...
      108,212,215,187, 43,235,107, 91,  // ...
       55, 47,103,196,132,132,  4,  4,  // ...
        0,  0,  0,  0,  7,  0,  0,  0,  // fifth line
        1,  1,  1,  1,  3,  7,  7,  7,  // ...
        7,  6,  5, 15,  9,  0,  1,  3,  // ...
        2,  4, 12,  8,  0,  1,  0,  0}, // end of the frame at coords 40x32 giving 160 bytes
    {   0,  0,  0,  0, 80,191, 92,176,
      192,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,
      128,192, 96,184, 92,255,  0,  0,
        0,  0,  0,  0, 13,251,213,106,
      107,247,238,252,248,240,240,240,
      112,112,120,120,124,238,214,171,
      197,130, 65,168,255,  1,  0,  0,
        0,  0,  0,  0,252,253,255,255,
      135,255,255,255,255,  7,  3,  1,
      121,  1,  1,  3,  3,130,198,255,
      255,255,255,255,253, 80,  0,  0,
        0,144,144, 72, 42, 27, 63,119,
      189,185,201,221,183, 59,190,190,
      238,234,170,170,105,109,237,109,
       61, 45, 45,101, 66,  2,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  1,  1,  1,  3,  3,  3,
        3,  3,  3,  3,  3,  1,  1,  2,
        2,  0,  0,  0,  0,  0,  0,  0}
};


/* Similarly to the previous array, we have all the paw states
 * on a single array, frame and line, plus an empty frame
 */
static const char paws[][64] PROGMEM = {
    // Frame 1: left paw up, right paw down
    {  0,  0,  0,  0,112, 32,140,232,  // Left paw line 1
     226,247,246,224,132, 28,  0,  0,  // ...
       0,  0,  0,  0,  0,  0,  0,128,  // Right paw line 1
       0,  0,  0,  0,  0,  0,  0,  0,  // ...
       0,  0,  0,  0,  0,  0,  0,  1,  // Left paw line 2
       0,  0,  0,  1,  1,  0,  0,  0,  // ...
       0,  0,  0, 14,194,240,123,123,  // Right paw line 2
     113,244, 70, 16, 56,  0,  0,  0}, // ...
    // Frame 2: left paw down, right paw up
    {  0,  0,  0,  0,  0,  0,  0,  0,  // Left paw line 1
       0,128,  0,  0,  0,  0,  0,  0,  // ...
       0,  0,  0,  0, 28,132,224,246,  // Right paw line 1
     247,226,232,140, 32,112,  0,  0,  // ...
       0,  0,  0,  0, 56, 16, 70,244,  // Left paw line 2
     113,123,123,240,194, 14,  0,  0,  // ...
       0,  0,  0,  0,  0,  1,  1,  0,  // Right paw line 2
       0,  0,  1,  0,  0,  0,  0,  0}  // ...
};


/* Here we only store a single frame of the double helix -
 * only the data that's needed, just before it loops - in this
 * this case it's 6 collumns of the helix, a 6x8 area, and the
 * code below will take care of rendering the whole thing correctly
 * -- If you want to make your own scrolling pattern, it can be of
 * any lenght up to (display width - 1), after that you'll have to
 * adapt the rendering function below somehow.
 */
static const uint8_t helix[6] = {
    66, 90, 66, 36, 24, 36
};

// Lastly we have lilixxx21 logo
static const char lilix[] PROGMEM = {
      0,126,  0,104,  0,126,  0,104,
       0, 72, 48, 72, 48, 72, 48, 72,
      48, 72, 48, 72,  0, 16,  0, 68,
      98, 82, 76,  0,  0,126, 64,  0
};


/* Replace rand() with this to save some 300 bytes
 * from: https://github.com/tzarc/qmk_build/blob/bebe5e5b21e99bdb8ff41500ade1eac2d8417d8c/users-tzarc/tzarc_common.c#L57-L63
 */
uint_fast8_t prng(void) {
    static uint_fast8_t s = 0xAA, a = 0;
    s ^= s << 3;
    s ^= s >> 5;
    s ^= a++ >> 2;
    return s;
}


// Replace snprintf() with a better function to save some 1400 bytes of space
void pseudo_printf(const char *prefix_data, uint16_t input, bool print_leading_zeroes, uint8_t n_digits) {
    uint16_t digit = 1;
    uint8_t digit_p;

    if (prefix_data != NULL) {
        oled_write_P(prefix_data, false);
    }

    for (x = 1; x < n_digits; x++) {
        digit = digit * 10;
    }

    for (x = 0; x < n_digits; x++) {
        // Get the current digit and its corresponding ASCII value
        digit_p = ((input / digit) % 10) + 0x30 ;

        // Replace leading zeroes with spaces if the caller doesn't want them
        if (!print_leading_zeroes && digit_p == 0x30 && digit > input && digit > 1) { digit_p = 0x20; }

        oled_write_char(digit_p, false);
        digit = digit / 10;
    }
}


oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    //oled_clear();

    if (!is_keyboard_master()) {
        return OLED_ROTATION_270;  // flips the display 270 degrees if offhand
    }
    return rotation;
}


static void render_logo(void) {
    col_tracker = 0;

    // Render animations algorithmically =)
    oled_set_cursor(0, 0);

    // Print the nya~ frame if a key has been pressed in the past 300ms
    if (idle_timer < 300) {
        oled_write_raw_P(lilian[0], sizeof(lilian[0]));
    } else {
        oled_write_raw_P(lilian[1], sizeof(lilian[1]));
    }

    /* Draw the paws. If frame delay is 255, this will run for 8192ms,
     * which should give enough time to erase all the old paws
     */
    if (idle_timer < (frame_delay + 1) * 32 ) {
        col_tracker = 13 - key_tracker;
        if (col_tracker < 6) col_tracker = 13;

        // aternating the starting frame every time the screen gets looped
        if (loop_tracker) {
            anim_frame = key_tracker % 2;
        } else {
            anim_frame = (key_tracker + 1) % 2;
        }

        // Draw
        if (idle_timer < frame_delay) {
            oled_set_cursor(0, col_tracker - 1);
            oled_write_raw_P(paws[anim_frame], 64);
        // Fade by erasing random pixels
        } else if (global_timer % (frame_delay - 2 ) == 0) {
            /* Adapted from the example at:
             * https://beta.docs.qmk.fm/using-qmk/hardware-features/displays/feature_oled_driver#buffer-read-example
             */

            // Define the reader structure
            oled_buffer_reader_t reader;
            uint_fast8_t buff_char;

            /* Fetch a pointer for the buffer byte at index 160, since, unlike at
             * the example, we just want to fade the paws, which start at byte 160,
             * instead of fading the whole screen.
             */
            reader = oled_read_raw(160);

            // Loop over the required bytes and erase pixels as we go
            for (x = 160; x < 448; x++) {
                // Get the actual byte in the buffer by dereferencing the pointer
                buff_char = *reader.current_element;
                if (buff_char != 0) {
                    /* Who needs an array with single bit masks if we can create them
                     * on the fly like this? This is also easier to understand:
                     *
                     * To turn off just a single pixel on the display, we can AND the
                     * current byte, which is 8 pixels tall, with another byte that has
                     * just a single bit off, so we have 0b11111110, 0b11111101, ...
                     * 0b01111111 as possible masks. Those can be generated by shifting
                     * the value 0b1 by 0...7 positions left, and then inverting the
                     * result, i.e., ~(1 << [0...7]). Since we want random pixels to be
                     * turned off, we complete this by using a RNG and limiting its
                     * value to 0...7
                     */
                    oled_write_raw_byte(buff_char & ~(1 << (prng() % 8)), x);
                }
                // Increment the pointer to fetch a new byte during the next loop
                reader.current_element++;
            }
        }
    }

    // Spin the double helix for at least 10 seconds, at 20fps
    if (idle_timer < 10000) {
        oled_set_cursor(0, 14);
        for (x=0; x < 32; x++) {
            /* Here's where the magic happens:
             * In (global_timer/50 - x ) % 6, global_timer defines the starting
             * frame of the animation, 50 is the delay in ms to make 20FPS,
             * x advances the array position as we proceed with our for loop, and
             * %6 limits this value to 0...5 -- the bytes we have on our array --
             * if you want to make your own scrolling animation, you need to adapt
             * that 6 to match the number of "pieces" your animation has. If you
             * want to reverse the scrolling direction, just replace - x with + x.
             *
             * In (14 * 32) + x we have the current byte of the display we're writing
             * to -- we are on line 14, and each line is 32 bytes wide.
             */
            oled_write_raw_byte(helix[(global_timer / 50 - x) % 6], (14 * 32) + x);
        }
    }

    // Draw the lilixxx21 logo
    oled_set_cursor(0, 15);
    oled_write_raw_P(lilix, sizeof(lilix));
}


void render_rgb_status(void) {
#ifdef RGBLIGHT_ENABLE
    if (RGBLIGHT_MODES > 1 && rgblight_is_enabled()) {
        pseudo_printf(PSTR("LED "), rgblight_get_mode(), false, 2);
        pseudo_printf(PSTR(" |"), rgblight_get_hue()/RGBLIGHT_HUE_STEP, false, 2);
        pseudo_printf(PSTR(" "), rgblight_get_sat()/RGBLIGHT_SAT_STEP, false, 2);
        pseudo_printf(PSTR(" "), rgblight_get_val()/RGBLIGHT_VAL_STEP, false, 1);
        oled_write_P(PSTR(" |\n"), false);

        if (user_state.timer_on) {
            pseudo_printf(PSTR("Timer: |"), user_state.rgblight_timeout, false, 3);
            oled_write_P(PSTR(" mins|\n"), false);
        } else {
            oled_write_P(PSTR("\n"), false);
        }

    } else {
        // Erase stuff
        oled_write_P(PSTR("\n\n"), false);
    }
#endif
}


void render_layer_status(void) {
    // Render layer names and a little numpad drawing if we're on the master half
    uint8_t current_layer = get_highest_layer(layer_state);

    static const char numpad[][5] PROGMEM = {
         {0x9b,0x9c,0x9d,0x9e,0},
         {0xbb,0xbc,0xbd,0xbe,0},
         {0xdb,0xdc,0xdd,0xde,0}
        };

    if (current_layer != _NUMPAD) {
        // Erase the numpad
        for (x=0;x<=2;x++) {
            oled_set_cursor(17, x);
            oled_write_P(PSTR("    "), false);
        }
        oled_set_cursor(0, 0);

        // Host Keyboard LED Status
        led_t led_state = host_keyboard_led_state();
        oled_write_P(led_state.num_lock ? PSTR("\x9f") : PSTR(" "), false);
        oled_write_P(led_state.caps_lock ? PSTR("\xbf") : PSTR(" "), false);
        oled_write_P(led_state.scroll_lock ? PSTR("\xdf") : PSTR(" "), false);

        oled_write_P(PSTR("Layer: "), false);
    }


    switch (current_layer) {
        case _QWERTY:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _NUMPAD:
            oled_write_P(PSTR("NumPad          "), false);
            // Draw the numpad
            for (x=0;x<=2;x++) {
                oled_set_cursor(17, x);
                oled_write_P(numpad[x], false);
            }
            oled_set_cursor(0, 1);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undef\n"), false);
            break;
    }

    if (current_layer != _NUMPAD && is_master) {
        /* Only draw RGB status if we're not on on NumPad mode,
         * because drawing with "oled_set_cursor()" is pretty finnicky
         */
        render_rgb_status();
    }
}


void oled_task_user(void) {
    //Update timers in sync with the OLED display
    global_timer = timer_read();
    idle_timer += 1 ;
    anim_timer += 1 ;

    // Reset timers to 10k when we are just about to overflow back to zero
    if (anim_timer >= 65500 ) { anim_timer = 10000; }
    if (idle_timer >= 65500 ) { idle_timer = 10000; }

    if (frame_delay < 255 && idle_timer > 1000 && !(idle_timer % 300)) {
        frame_delay += 255 / frame_delay;
    }

    if (is_master) {
        render_layer_status();
        pseudo_printf(NULL, (frame_delay ^ 255) , false, 3);
    } else {
        render_logo();
        //char buf[20];
        //snprintf(buf, sizeof(buf), "%07d        ", frame_delay);
        //oled_write(buf, false);
    }
}
#endif
