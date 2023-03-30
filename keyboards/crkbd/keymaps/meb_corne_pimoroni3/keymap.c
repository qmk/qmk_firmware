 /*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

#include QMK_KEYBOARD_H

enum layers {
    BASE,
    NAV_NUM,
    NUM_SYM_FN,
    APP_NAV,
    MOUSE_LAYER,
};

enum custom_keycodes {
    LT_APP_NAV_SYM_CALL = SAFE_RANGE,
    SELECT_LINE,
    NEXT_SENTENCE,
    ARROW,
    CPI_CYCLE
};

// CONVENIENCE MACROS---------------------------------------------------------------------------------------------------------------------------------------------

#define BASE_SPACE LT(NAV_NUM,KC_SPC)
#define NAV_NUM_SPACE LT(NUM_SYM_FN,KC_SPC)
#define ALT_DEL LALT_T(KC_DEL)
#define TAB_LEFT RCS(KC_TAB)
#define TAB_RIGHT LCTL(KC_TAB)
#define BACK LALT(KC_LEFT)
#define FORWARD LALT(KC_RIGHT)
#define ZOOM_OUT LCTL(KC_PMNS)
#define ZOOM_IN LCTL(KC_PPLS)
#define DESKTOP_LEFT LCTL(LGUI(KC_LEFT))
#define DESKTOP_RIGHT LCTL(LGUI(KC_RIGHT))
#define ALT_F4 LALT(KC_F4)

// TAP DANCE SETUP------------------------------------------------------------------------------------------------------------------------------------------------

void td_music_fn(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
                tap_code16(KC_MPLY);
            break;
        case 2:
                tap_code16(KC_MNXT);
            break;
        case 3:
                tap_code16(KC_MPRV);}
}

enum tap_dances {
    TD_MUSIC = 0,
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_MUSIC] = ACTION_TAP_DANCE_FN(td_music_fn),
};

#define MUSIC TD(TD_MUSIC)

// KEYMAP AND LAYERS----------------------------------------------------------------------------------------------------------------------------------------------

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_split_3x6_3( // Base QWERTY layer
        KC_ESC    , KC_Q      , KC_W      , KC_E      , KC_R      , KC_T         , KC_Y         , KC_U      , KC_I      , KC_O         , KC_P        , KC_BSPC      ,
        KC_TAB    , KC_A      , KC_S      , KC_D      , KC_F      , KC_G         , KC_H         , KC_J      , KC_K      , KC_L         , KC_QUOT     , KC_ENT       ,
        KC_LSFT   , KC_Z      , KC_X      , KC_C      , KC_V      , KC_B         , KC_N         , KC_M      , KC_COMM   , KC_DOT       , KC_SLSH     , KC_RSFT      ,
                                            KC_LCTL   , ALT_DEL   , BASE_SPACE   , BASE_SPACE   , KC_RGUI   , LT_APP_NAV_SYM_CALL
    ),
    [NAV_NUM] = LAYOUT_split_3x6_3( // Left-side navigation, right-side numpad layer
        KC_GRV    , KC_HOME   , KC_UP     , KC_END    , KC_PLUS   , KC_LPRN      , KC_RPRN      , KC_7      , KC_8      , KC_9         , KC_DEL      , KC_BSPC      ,
        KC_TAB    , KC_LEFT   , KC_DOWN   , KC_RIGHT  , KC_EQL    , KC_LCBR      , KC_RCBR      , KC_4      , KC_5      , KC_6         , KC_SCLN     , KC_ENT       ,
        KC_LSFT   , KC_PIPE   , KC_UNDS   , KC_COLN   , KC_MINS   , KC_LBRC      , KC_RBRC      , KC_1      , KC_2      , KC_3         , KC_BSLS     , KC_RSFT      ,
                                            KC_TRNS   , KC_TRNS   , NAV_NUM_SPACE, NAV_NUM_SPACE, KC_0      , KC_TRNS
    ),
    [NUM_SYM_FN] = LAYOUT_split_3x6_3( // Top-row numbers, middle-row symbols, bottom row function keys layer
        KC_1      , KC_2      , KC_3      , KC_4      , KC_5      , KC_6         , KC_7         , KC_8      , KC_9      , KC_0         , KC_MINS     , KC_EQL       ,
        KC_EXLM   , KC_AT     , KC_HASH   , KC_DLR    , KC_PERC   , KC_CIRC      , KC_AMPR      , KC_ASTR   , KC_LPRN   , KC_RPRN      , KC_UNDS     , KC_PLUS      ,
        KC_F1     , KC_F2     , KC_F3     , KC_F4     , KC_F5     , KC_F6        , KC_F7        , KC_F8     , KC_F9     , KC_F10       , KC_F11      , KC_F12       ,
                                            KC_CAPS   , KC_MPLY   , KC_TRNS      , KC_TRNS      , KC_MPRV   , KC_MNXT
    ),
    [APP_NAV] = LAYOUT_split_3x6_3( // Transparent left-side, application navigation right-side
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS      , TAB_LEFT     , TAB_RIGHT, KC_HOME    , KC_UP        , KC_END      , ALT_F4       ,
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS      , BACK         , FORWARD  , KC_LEFT    , KC_DOWN      , KC_RIGHT    , SELECT_LINE  ,
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS      , ZOOM_OUT     , ZOOM_IN  , ARROW      , NEXT_SENTENCE, DESKTOP_LEFT, DESKTOP_RIGHT,
                                            KC_TRNS   , KC_TRNS   , KC_TRNS      , KC_TRNS      , MUSIC    , KC_TRNS
    ),
    [MOUSE_LAYER] = LAYOUT_split_3x6_3( // [AUTO_MOUSE_DEFAULT_LAYER] Transparent layer with left and right mouse buttons
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_BTN2      , KC_BTN1      , KC_TRNS   , KC_TRNS   , KC_TRNS      , KC_TRNS     , KC_TRNS      ,
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS      , KC_TRNS      , KC_TRNS   , KC_TRNS   , KC_TRNS      , KC_TRNS     , KC_TRNS      ,
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS      , KC_TRNS      , KC_TRNS   , KC_TRNS   , KC_TRNS      , KC_TRNS     , KC_TRNS      ,
                                            KC_TRNS   , KC_TRNS   , KC_TRNS      , KC_TRNS      , KC_TRNS   , KC_TRNS
    ),
};

// POINTER DEVICE SETUP-------------------------------------------------------------------------------------------------------------------------------------------

#define pointer_limit 25
#define max_track_cpi 5000
#define min_track_cpi 1000
#define track_cpi_increment 1000

bool set_scrolling = false;int pointer_magnitude = 0;
int track_factor = 1;
int track_cpi = 4000;
int scroll_cpi = 200;

void pointing_device_init_user(void) {
    set_auto_mouse_enable(true);
    pointing_device_set_cpi(track_cpi);
}

void housekeeping_task_user(void) {
    static i2c_status_t rgbw_status = I2C_STATUS_ERROR;
    if (rgbw_status != I2C_STATUS_SUCCESS){
        pimoroni_trackball_set_rgbw(255, 0, 0, 0);
    }
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (set_scrolling) {
        mouse_report.h = mouse_report.x;
        mouse_report.v = -mouse_report.y;
        mouse_report.x = mouse_report.y = 0;
    } else {
        pointer_magnitude = .5*sqrt(pow(mouse_report.x,2)+pow(mouse_report.y,2));
	    track_factor = pointer_magnitude < pointer_limit? pointer_magnitude : pointer_limit;
        mouse_report.x = track_factor * mouse_report.x;
        mouse_report.y = track_factor * mouse_report.y;
    }
    return mouse_report;
}

// KEY PRESS LOG SETUP--------------------------------------------------------------------------------------------------------------------------------------------

#define key_press_log_size 3

int key_press_log_array[key_press_log_size] = {-1,-1,-1};

void update_key_press_log_array(int new_press){
    for(int i = 0; i < (key_press_log_size - 1); i++){
        key_press_log_array[i] = key_press_log_array[i + 1];
    }
    key_press_log_array[key_press_log_size - 1] = new_press;
}

void reset_key_press_log_array(void){
    for(int i = 0; i < key_press_log_size; i++){
        key_press_log_array[i] = -1;
    }
}

void log_key_press(uint16_t keycode){
    switch (keycode) {
        case KC_A:
            update_key_press_log_array(0);
            break;
        case KC_B:
            update_key_press_log_array(1);
            break;
        case KC_C:
            update_key_press_log_array(2);
            break;
        case KC_D:
            update_key_press_log_array(3);
            break;
        case KC_E:
            update_key_press_log_array(4);
            break;
        case KC_F:
            update_key_press_log_array(5);
            break;
        case KC_G:
            update_key_press_log_array(6);
            break;
        case KC_H:
            update_key_press_log_array(7);
            break;
        case KC_I:
            update_key_press_log_array(8);
            break;
        case KC_J:
            update_key_press_log_array(9);
            break;
        case KC_K:
            update_key_press_log_array(10);
            break;
        case KC_L:
            update_key_press_log_array(11);
            break;
        case KC_M:
            update_key_press_log_array(12);
            break;
        case KC_N:
            update_key_press_log_array(13);
            break;
        case KC_O:
            update_key_press_log_array(14);
            break;
        case KC_P:
            update_key_press_log_array(15);
            break;
        case KC_Q:
            update_key_press_log_array(16);
            break;
        case KC_R:
            update_key_press_log_array(17);
            break;
        case KC_S:
            update_key_press_log_array(18);
            break;
        case KC_T:
            update_key_press_log_array(19);
            break;
        case KC_U:
            update_key_press_log_array(20);
            break;
        case KC_V:
            update_key_press_log_array(21);
            break;
        case KC_W:
            update_key_press_log_array(22);
            break;
        case KC_X:
            update_key_press_log_array(23);
            break;
        case KC_Y:
            update_key_press_log_array(24);
            break;
        case KC_Z:
            update_key_press_log_array(25);
            break;
        default:
            reset_key_press_log_array();
    }
}

// SYM_CALL SETUP--------------------------------------------------------------------------------------------------------------------------------------------------

#define sym_key_size 3
#define sym_key_count 10

bool sym_called = false;
int sym_key_index = 8;

int sym_key_array[sym_key_count][sym_key_size] = {
    {  4, 23,  2 }, // EXCLAMATION MARK
    {  0, 19, 18 }, // AT SYMBOL
    { 15, 14, 20 }, // POUND SIGN (HASH MARK)
    {  3, 14, 11 }, // DOLLAR SIGN
    { 15,  4, 17 }, // PERCENT SYMBOL
    {  2,  0, 17 }, // CARET SYMBOL
    {  0, 12, 15 }, // AMPERSAND SYMBOL
    {  0, 18, 19 }, // ASTERISK SYMBOL
    { 19,  8, 11 }, // TILDE SYMBOL
    {  0,  0,  0 }, // TEST
};

void sym_call_fn(void){
    for(int i = 0; i < sym_key_count; i++){
        int row_match_count = 0;

        for(int j = 0; j < sym_key_size; j++){
            if(sym_key_array[i][j] == key_press_log_array[j]){
                row_match_count ++;
            }
        }

        if(row_match_count == 3){
            for(int j = 0; j < sym_key_size; j++){
               tap_code(KC_BSPC);
            }

            reset_key_press_log_array();
            sym_key_index = i;
        }
    }

    switch (sym_key_index) {
        case 0:
            tap_code16(KC_EXLM);
            break;
        case 1:
            tap_code16(KC_AT);
            break;
        case 2:
            tap_code16(KC_HASH);
            break;
        case 3:
            tap_code16(KC_DLR);
            break;
        case 4:
            tap_code16(KC_PERC);
            break;
        case 5:
            tap_code16(KC_CIRC);
            break;
        case 6:
            tap_code16(KC_AMPR);
            break;
        case 7:
            tap_code16(KC_ASTR);
            break;
        case 8:
            tap_code16(KC_TILD);
            break;
        case 9:
            SEND_STRING("TEST");
    }
}

// USER SPACE-----------------------------------------------------------------------------------------------------------------------------------------------------


bool process_record_user(uint16_t keycode, keyrecord_t *record){
    const uint8_t mods = get_mods();
    const uint8_t oneshot_mods = get_oneshot_mods();

    static uint16_t lt_timer;

    switch (keycode) {
        case BASE_SPACE:
            if (record->event.pressed) {
                set_scrolling = true;
                pointing_device_set_cpi(scroll_cpi);
            } else {
                set_scrolling = false;
                pointing_device_set_cpi(track_cpi);
            }

            break;
        case SELECT_LINE:
            if (record->event.pressed ){
                tap_code(KC_HOME);
                tap_code16(LSFT(KC_END));
            }

            return false;
        case LT_APP_NAV_SYM_CALL:
            if (record->event.pressed) {
                lt_timer = timer_read();
                layer_on(APP_NAV);
            } else {
                if(timer_elapsed(lt_timer) < 200){
                    sym_call_fn();
                }
                layer_off(APP_NAV);
            }

            return false;
        case NEXT_SENTENCE:
            if (record->event.pressed) {
                SEND_STRING(". ");
                add_oneshot_mods(MOD_BIT(KC_LSFT));
            }
            return false;
        case ARROW:
            if (record->event.pressed) {
                if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {
                    del_oneshot_mods(MOD_MASK_SHIFT);
                    unregister_mods(MOD_MASK_SHIFT);
                    SEND_STRING("=>");
                    register_mods(mods);
                } else {
                    SEND_STRING("->");
                }
            }

            return false;
        case CPI_CYCLE:
            if (record->event.pressed) {
                if (track_cpi < max_track_cpi){
                    track_cpi += track_cpi_increment;
                } else {
                    track_cpi = min_track_cpi;
                }
            }

            return false;
    }

    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        log_key_press(keycode);
    }
}


