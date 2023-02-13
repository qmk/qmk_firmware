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
    MATH_SYMBOLS
};

enum custom_keycodes {
    LT_APP_NAV_SYM_CALL = SAFE_RANGE,
    SELECT_LINE,
    NEXT_SENTENCE,
    ARROW,
};

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

void td_grv_boot_fn(qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
                tap_code16(KC_GRV);
            break;
        case 2:
                tap_code16(KC_GRV);
            break;
        case 3:
                tap_code16(QK_RBT);}
}

enum tap_dances {
    TD_MUSIC = 0,
    TD_GRV_BOOT,
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_MUSIC] = ACTION_TAP_DANCE_FN(td_music_fn),
    [TD_GRV_BOOT] = ACTION_TAP_DANCE_FN(td_grv_boot_fn),
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
#define MUSIC TD(TD_MUSIC)
#define GRV_BOOT TD(TD_GRV_BOOT)

// KEYMAP AND LAYERS----------------------------------------------------------------------------------------------------------------------------------------------

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_split_3x6_3( // Base QWERTY layer
        KC_ESC    , KC_Q      , KC_W      , KC_E      , KC_R      , KC_T         , KC_Y         , KC_U      , KC_I      , KC_O         , KC_P        , KC_BSPC      ,
        KC_TAB    , KC_A      , KC_S      , KC_D      , KC_F      , KC_G         , KC_H         , KC_J      , KC_K      , KC_L         , KC_QUOT     , KC_ENT       ,
        KC_LSFT   , KC_Z      , KC_X      , KC_C      , KC_V      , KC_B         , KC_N         , KC_M      , KC_COMM   , KC_DOT       , KC_SLSH     , KC_RSFT      ,
                                            KC_LCTL   , ALT_DEL   , BASE_SPACE   , BASE_SPACE   , KC_RGUI   , LT_APP_NAV_SYM_CALL
    ),
    [NAV_NUM] = LAYOUT_split_3x6_3( // Left-side navigation, right-side numpad layer
        GRV_BOOT  , KC_HOME   , KC_UP     , KC_END    , KC_PLUS   , KC_LPRN      , KC_RPRN      , KC_7      , KC_8      , KC_9         , KC_DEL      , KC_BSPC      ,
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
};

// KEY PRESS LOG SETUP--------------------------------------------------------------------------------------------------------------------------------------------

#define key_press_log_rows 2
#define key_press_log_columns 20

bool log_display_enabled = false;
bool all_selected = false;
int key_press_log_head = 0;
int key_press_log_array[key_press_log_rows][key_press_log_columns];
int backspace_press_count = 0;

void update_key_press_log_array(int press){

    if (press == -1 && key_press_log_head > 0){
        key_press_log_array[0][key_press_log_head - 1] = 26;
        key_press_log_array[1][key_press_log_head - 1] = 0;
        backspace_press_count++;

        if(backspace_press_count > 0){
            key_press_log_head -= 1;
        }
    } else {
        backspace_press_count = 0;

        if (key_press_log_head == key_press_log_columns) {

            for (int i = 0; i < key_press_log_rows; i ++) {
                for(int j = 0; j < (key_press_log_head - 1); j++){
                    key_press_log_array[i][j] = key_press_log_array[i][j + 1];
                }
            }

            key_press_log_array[0][key_press_log_head - 1] = press;
            key_press_log_array[1][key_press_log_head - 1] = ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT || host_keyboard_led_state().caps_lock)? 1 : 0;
        } else {
            key_press_log_array[0][key_press_log_head] = press;
            key_press_log_array[1][key_press_log_head] = ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT || host_keyboard_led_state().caps_lock)? 1 : 0;
            key_press_log_head += 1;
        }
    }

    all_selected = false;
}

void neutralize_log(void){
    if (key_press_log_head > 0 && key_press_log_array[0][key_press_log_head - 1] != 26) {
        key_press_log_array[0][key_press_log_head - 1] = -26;
        key_press_log_array[1][key_press_log_head - 1] = 0;
    }
}

void reset_log(void){
    backspace_press_count = 0;

    for(int i = 0; i < key_press_log_columns; i++){
        key_press_log_array[0][i] = 26;
        key_press_log_array[1][i] = 0;
        backspace_press_count = 0;
        key_press_log_head = 0;
    }
}

void log_key_press(uint16_t keycode){
    bool search_for_space = false;

    if ((get_mods() | get_oneshot_mods()) & MOD_MASK_CTRL) {
        switch (keycode) {
            case KC_A:
                all_selected = true;
                break;
            case KC_BSPC:
                for (int i = key_press_log_head - 1; i>= 0; i--) {
                    if (key_press_log_array[0][i] == 26) {
                        update_key_press_log_array(-1);
                        if (search_for_space) {
                            break;
                        } else {
                            search_for_space = true;
                        }
                    } else {
                        search_for_space = true;
                        update_key_press_log_array(-1);
                    }
                }
                key_press_log_head++;

            // THE BELOW REFACTOR ATTEMPT DOES NOT WORK FOR SEQUENCES OF CTRL(KC_BSPC) > 1

            // case KC_BSPC:
            //     for (int i = key_press_log_head - 1; i>= 0; i--) {
            //         if (key_press_log_array[0][i] == 26 && search_for_space) {
            //             break;
            //         }

            //         search_for_space = true;
            //         update_key_press_log_array(-1);
            //     }

            //     key_press_log_head++;
        }
    }

    if (!((get_mods() | get_oneshot_mods()) & (MOD_MASK_ALT ||
                                               MOD_MASK_GUI ||
                                               MOD_MASK_CTRL
    ))) {
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
            case KC_SPC:
            case BASE_SPACE:
            case NAV_NUM_SPACE:
                update_key_press_log_array(26);
                break;
            case KC_BSPC:
                if (all_selected){
                    reset_log();
                } else {
                    update_key_press_log_array(-1);
                }

                break;
            case KC_EXLM:
                update_key_press_log_array(27);
                break;
            case KC_HASH:
                update_key_press_log_array(28);
                break;
            case KC_DLR:
                update_key_press_log_array(29);
                break;
            case KC_PERC:
                update_key_press_log_array(30);
                break;
            case KC_CIRC:
                update_key_press_log_array(31);
                break;
            case KC_AMPR:
                update_key_press_log_array(32);
                break;
            case KC_ASTR:
                update_key_press_log_array(33);
                break;
            case KC_LPRN:
                update_key_press_log_array(34);
                break;
            case KC_RPRN:
                update_key_press_log_array(35);
                break;
            case KC_MINS:
                update_key_press_log_array(36);
                break;
            case KC_UNDS:
                update_key_press_log_array(37);
                break;
            case KC_PLUS:
                update_key_press_log_array(38);
                break;
            case KC_EQL:
                update_key_press_log_array(39);
                break;
            case KC_LCBR:
                update_key_press_log_array(40);
                break;
            case KC_RCBR:
                update_key_press_log_array(41);
                break;
            case KC_LBRC:
                update_key_press_log_array(42);
                break;
            case KC_RBRC:
                update_key_press_log_array(43);
                break;
            case KC_DOT:
                update_key_press_log_array(44);
                break;
            case KC_COMM:
                update_key_press_log_array(45);
                break;
            case KC_RABK:
                update_key_press_log_array(46);
                break;
            case KC_LABK:
                update_key_press_log_array(47);
                break;
            case KC_QUES:
                update_key_press_log_array(48);
                break;
            case KC_SCLN:
                update_key_press_log_array(49);
                break;
            case KC_COLN:
                update_key_press_log_array(50);
                break;
            case KC_QUOT:
                update_key_press_log_array(51);
                break;
            case KC_DQT:
                update_key_press_log_array(52);
                break;
            case KC_PIPE:
                update_key_press_log_array(53);
                break;
            case KC_1:
                update_key_press_log_array(54);
                break;
            case KC_2:
                update_key_press_log_array(55);
                break;
            case KC_3:
                update_key_press_log_array(56);
                break;
            case KC_4:
                update_key_press_log_array(57);
                break;
            case KC_5:
                update_key_press_log_array(58);
                break;
            case KC_6:
                update_key_press_log_array(59);
                break;
            case KC_7:
                update_key_press_log_array(60);
                break;
            case KC_8:
                update_key_press_log_array(61);
                break;
            case KC_9:
                update_key_press_log_array(62);
                break;
            case KC_0:
                update_key_press_log_array(63);
                break;
            default:
                neutralize_log();
        }
    }
}

// SYM_CALL SETUP--------------------------------------------------------------------------------------------------------------------------------------------------

#define sym_key_size 3
#define sym_key_count 11

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
    {  2, 11,  4 }, // RESET LOG
    { 19, 14,  6 }, // TOGGLE LOG
};

void sym_call_fn(void){
    for(int i = 0; i < sym_key_count; i++){
        int row_match_count = 0;

        for(int j = 0; j < sym_key_size; j++){
            if(sym_key_array[i][j] == key_press_log_array[0][key_press_log_head-(sym_key_size)+j]){
                row_match_count ++;
            }
        }

        if(row_match_count == 3){
            for(int j = 0; j < sym_key_size; j++){
               tap_code(KC_BSPC);
               update_key_press_log_array(-1);
            }

            neutralize_log();
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
            reset_log();
            break;
        case 10:
            reset_log();
            log_display_enabled = !log_display_enabled;
    }
}

// OLED SETUP-----------------------------------------------------------------------------------------------------------------------------------------------------

#ifdef OLED_ENABLE

    // RENDER STATUS FUNCTION FOR MASTER

    void render_status(void) {

        // ROW INDEX 0 - CURRENT LAYER

        oled_set_cursor(0, 0);
        oled_write("Layer: ", false);
        oled_set_cursor(7, 0);

        switch (get_highest_layer(layer_state)) {
            case BASE:
                oled_write("QWERTY    ", false);
                break;
            case NAV_NUM:
                oled_write("Nav Num   ", false);
                break;
            case NUM_SYM_FN:
                oled_write("Nav Sym Fn", false);
                break;
            case APP_NAV:
                oled_write("App Nav   ", false);
                break;
        }

        // ROW INDEX 1 - CAPS LOCK STATUS

        oled_set_cursor(0,1);
        oled_write("Caps Lock: ", false);
        oled_set_cursor(11,1);
        led_t led_state = host_keyboard_led_state();
        oled_write_P(led_state.caps_lock ? PSTR("ON ") : PSTR("OFF"), false);

        // ROW INDEX 2 - STICKY SYMBOL STATUS

        oled_set_cursor(0,2);
        oled_write("Sticky Symbol: ", false);
        oled_set_cursor(15,2);

        switch (sym_key_index) {
            case 0:
                oled_write("!     ", false);
                break;
            case 1:
                oled_write("@     ", false);
                break;
            case 2:
                oled_write("#     ", false);
                break;
            case 3:
                oled_write("$     ", false);
                break;
            case 4:
                oled_write("%     ", false);
                break;
            case 5:
                oled_write("^     ", false);
                break;
            case 6:
                oled_write("&     ", false);
                break;
            case 7:
                oled_write("*     ", false);
                break;
            case 8:
                oled_write("~     ", false);
                break;
            case 9:
                oled_write("CLEAR ", false);
            case 10:
                oled_write("TOGGLE", false);
        }

        // ROW INDEX 3 - ALPHA HISTORY

        if (log_display_enabled){
            for(int i = 0; i < key_press_log_columns; i++){
                oled_set_cursor(i,3);

                switch (key_press_log_array[0][i]){
                    case 0:
                        oled_write_P(key_press_log_array[1][i] == 1? PSTR("A") : PSTR("a"), false);
                        break;
                    case 1:
                        oled_write_P(key_press_log_array[1][i] == 1? PSTR("B") : PSTR("b"), false);
                        break;
                    case 2:
                        oled_write_P(key_press_log_array[1][i] == 1? PSTR("C") : PSTR("c"), false);
                        break;
                    case 3:
                        oled_write_P(key_press_log_array[1][i] == 1? PSTR("D") : PSTR("d"), false);
                        break;
                    case 4:
                        oled_write_P(key_press_log_array[1][i] == 1? PSTR("E") : PSTR("e"), false);
                        break;
                    case 5:
                        oled_write_P(key_press_log_array[1][i] == 1? PSTR("F") : PSTR("f"), false);
                        break;
                    case 6:
                        oled_write_P(key_press_log_array[1][i] == 1? PSTR("G") : PSTR("g"), false);
                        break;
                    case 7:
                        oled_write_P(key_press_log_array[1][i] == 1? PSTR("H") : PSTR("h"), false);
                        break;
                    case 8:
                        oled_write_P(key_press_log_array[1][i] == 1? PSTR("I") : PSTR("i"), false);
                        break;
                    case 9:
                        oled_write_P(key_press_log_array[1][i] == 1? PSTR("J") : PSTR("j"), false);
                        break;
                    case 10:
                        oled_write_P(key_press_log_array[1][i] == 1? PSTR("K") : PSTR("k"), false);
                        break;
                    case 11:
                        oled_write_P(key_press_log_array[1][i] == 1? PSTR("L") : PSTR("l"), false);
                        break;
                    case 12:
                        oled_write_P(key_press_log_array[1][i] == 1? PSTR("M") : PSTR("m"), false);
                        break;
                    case 13:
                        oled_write_P(key_press_log_array[1][i] == 1? PSTR("N") : PSTR("n"), false);
                        break;
                    case 14:
                        oled_write_P(key_press_log_array[1][i] == 1? PSTR("O") : PSTR("o"), false);
                        break;
                    case 15:
                        oled_write_P(key_press_log_array[1][i] == 1? PSTR("P") : PSTR("p"), false);
                        break;
                    case 16:
                        oled_write_P(key_press_log_array[1][i] == 1? PSTR("Q") : PSTR("q"), false);
                        break;
                    case 17:
                        oled_write_P(key_press_log_array[1][i] == 1? PSTR("R") : PSTR("r"), false);
                        break;
                    case 18:
                        oled_write_P(key_press_log_array[1][i] == 1? PSTR("S") : PSTR("s"), false);
                        break;
                    case 19:
                        oled_write_P(key_press_log_array[1][i] == 1? PSTR("T") : PSTR("t"), false);
                        break;
                    case 20:
                        oled_write_P(key_press_log_array[1][i] == 1? PSTR("U") : PSTR("u"), false);
                        break;
                    case 21:
                        oled_write_P(key_press_log_array[1][i] == 1? PSTR("V") : PSTR("v"), false);
                        break;
                    case 22:
                        oled_write_P(key_press_log_array[1][i] == 1? PSTR("W") : PSTR("w"), false);
                        break;
                    case 23:
                        oled_write_P(key_press_log_array[1][i] == 1? PSTR("X") : PSTR("x"), false);
                        break;
                    case 24:
                        oled_write_P(key_press_log_array[1][i] == 1? PSTR("Y") : PSTR("y"), false);
                        break;
                    case 25:
                        oled_write_P(key_press_log_array[1][i] == 1? PSTR("Z") : PSTR("z"), false);
                        break;
                    case 26:
                        oled_write(" ", false);
                        break;
                    case 27:
                        oled_write("!", false);
                        break;
                    case 28:
                        oled_write("#", false);

                        break;
                    case 29:
                        oled_write("$", false);
                        break;
                    case 30:
                        oled_write("%", false);
                        break;
                    case 31:
                        oled_write("^", false);
                        break;
                    case 32:
                        oled_write("&", false);
                        break;
                    case 33:
                        oled_write("*", false);
                        break;
                    case 34:
                        oled_write("(", false);
                        break;
                    case 35:
                        oled_write(")", false);
                        break;
                    case 36:
                        oled_write("-", false);
                        break;
                    case 37:
                        oled_write("_", false);
                        break;
                    case 38:
                        oled_write("+", false);
                        break;
                    case 39:
                        oled_write("=", false);
                        break;
                    case 40:
                        oled_write("{", false);
                        break;
                    case 41:
                        oled_write("}", false);
                        break;
                    case 42:
                        oled_write("[", false);
                        break;
                    case 43:
                        oled_write("]", false);
                        break;
                    case 44:
                        oled_write(".", false);
                        break;
                    case 45:
                        oled_write(",", false);
                        break;
                    case 46:
                        oled_write(">", false);
                        break;
                    case 47:
                        oled_write("<", false);
                        break;
                    case 48:
                        oled_write("?", false);
                        break;
                    case 49:
                        oled_write(" ;", false);
                        break;
                    case 50:
                        oled_write(":", false);
                        break;
                    case 51:
                        oled_write("", false);
                        break;
                    case 52:
                        oled_write("\"", false);
                        break;
                    case 53:
                        oled_write("|", false);
                        break;
                    case 54:
                        oled_write("1", false);
                        break;
                    case 55:
                        oled_write("2", false);
                        break;
                    case 56:
                        oled_write("3", false);
                        break;
                    case 57:
                        oled_write("4", false);
                        break;
                    case 58:
                        oled_write("5", false);
                        break;
                    case 59:
                        oled_write("6", false);
                        break;
                    case 60:
                        oled_write("7", false);
                        break;
                    case 61:
                        oled_write("8", false);
                        break;
                    case 62:
                        oled_write("9", false);
                        break;
                    case 63:
                        oled_write("0", false);
                        break;
                }
            }
        } else {
            oled_set_cursor(0,3);
            oled_write("------DISABLED------", false);
        }

    }

    // RENDER STATIC FUNCTION FOR SLAVE
    void render_static(void){
        oled_set_cursor(0,0);
        oled_write("Michael Bissonnette", false);
        oled_set_cursor(0,1);
        oled_write("4107 Windsor Street", false);
        oled_set_cursor(0,2);
        oled_write("Pittsburgh, PA 15217", false);
        oled_set_cursor(0,3);
        oled_write("mbissonn@gmail.com", false);
    }

    // DRAW TO OLEDs
    bool oled_task_user(void) {
        if(is_keyboard_master()){
            render_status();
        }else{

            render_static();
            // oled_scroll_right();
        }

        return false;
    }

#endif

// POST INITIALIZATION--------------------------------------------------------------------------------------------------------------------------------------------

void keyboard_post_init_user(void) {
    reset_log();
}

// USER SPACE-----------------------------------------------------------------------------------------------------------------------------------------------------

bool process_record_user(uint16_t keycode, keyrecord_t *record){
    const uint8_t mods = get_mods();
    const uint8_t oneshot_mods = get_oneshot_mods();

    static uint16_t lt_timer;

    switch (keycode) {
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
    }

    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        log_key_press(keycode);
    }
}


