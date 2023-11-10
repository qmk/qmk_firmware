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
    GAMING,
    NAV_NUM,
    NUM_SYM_FN,
    APP_NAV,
    STAR
};

enum custom_keycodes {
    SELECT_LINE =  SAFE_RANGE,
    SSYM_CALL,
    NEXT_VIEW,
    PREV_VIEW
};

// TAP DANCE SETUP------------------------------------------------------------------------------------------------------------------------------------------------

void ctrl_left_home(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            tap_code16(LCTL(KC_LEFT));
            break;
        case 2:
            tap_code(KC_HOME);
    }
}

void ctrl_right_end(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            tap_code16(LCTL(KC_RIGHT));
            break;
        case 2:
            tap_code(KC_END);
    }
}

enum tap_dances {
    ND_LEFT = 0,
    ND_RIGHT
};

tap_dance_action_t tap_dance_actions[] = {
    [ND_LEFT] = ACTION_TAP_DANCE_FN(ctrl_left_home),
    [ND_RIGHT] = ACTION_TAP_DANCE_FN(ctrl_right_end),
};
// CONVENIENCE MACROS---------------------------------------------------------------------------------------------------------------------------------------------

#define BASE_SPACE LT(NAV_NUM,KC_SPC)
#define NN_SPACE LT(NUM_SYM_FN,KC_SPC)
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
#define ND_LEFT TD(ND_LEFT)
#define ND_RIGHT TD(ND_RIGHT)
#define APPNAV_MO MO(APP_NAV)

// KEYMAP AND LAYERS----------------------------------------------------------------------------------------------------------------------------------------------

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT( // Base QWERTY layer
        KC_GRV    , KC_1      , KC_2      , KC_3      , KC_4      , KC_5                             , KC_6       , KC_7      , KC_8      , KC_9         , KC_0        , KC_MINS      ,
        KC_ESC    , KC_Q      , KC_W      , KC_E      , KC_R      , KC_T                             , KC_Y       , KC_U      , KC_I      , KC_O         , KC_P        , KC_BSPC      ,
        KC_TAB    , KC_A      , KC_S      , KC_D      , KC_F      , KC_G                             , KC_H       , KC_J      , KC_K      , KC_L         , KC_QUOT     , KC_ENT       ,
        KC_LSFT   , KC_Z      , KC_X      , KC_C      , KC_V      , KC_B    , KC_NO      , TO(GAMING), KC_N       , KC_M      , KC_COMM   , KC_DOT       , KC_SLSH     , KC_RSFT      ,
                                            KC_LCTL   , KC_RGUI   , ALT_DEL , BASE_SPACE , BASE_SPACE, KC_RALT    , KC_RGUI   , SSYM_CALL
    ),

    [GAMING] = LAYOUT( // Gaming layer
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS                          , KC_TRNS    , KC_TRNS   , KC_TRNS   , KC_TRNS      , KC_TRNS     , KC_TRNS      ,
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS                          , KC_TRNS    , KC_TRNS   , KC_TRNS   , KC_TRNS      , KC_TRNS     , KC_TRNS      ,
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS                          , KC_TRNS    , KC_TRNS   , KC_TRNS   , KC_TRNS      , KC_TRNS     , KC_TRNS      ,
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS ,  KC_NO     , TO(STAR)  , KC_TRNS    , KC_TRNS   , KC_TRNS   , KC_TRNS      , KC_TRNS     , KC_TRNS      ,
                                            KC_TRNS   , KC_NO     , KC_LALT ,  KC_SPACE  , BASE_SPACE, KC_TRNS    , KC_NO     , KC_TRNS
    ),

    [NAV_NUM] = LAYOUT( // Left-side navigation, right-side numpad layer
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS                          , KC_TRNS    , KC_TRNS   , KC_TRNS   , KC_TRNS      , KC_TRNS     , KC_TRNS      ,
        KC_GRV    , ND_LEFT   , KC_UP     , ND_RIGHT  , KC_PLUS   , KC_LPRN                          , KC_RPRN    , KC_7      , KC_8      , KC_9         , KC_DEL      , KC_BSPC      ,
        KC_TAB    , KC_LEFT   , KC_DOWN   , KC_RIGHT  , KC_EQL    , KC_LCBR                          , KC_RCBR    , KC_4      , KC_5      , KC_6         , KC_SCLN     , KC_ENT       ,
        KC_LSFT   , KC_PIPE   , KC_UNDS   , KC_COLN   , KC_MINS   , KC_LBRC ,  KC_TRNS   , KC_TRNS   , KC_RBRC    , KC_1      , KC_2      , KC_3         , KC_BSLS     , KC_RSFT      ,
                                            KC_TRNS   , KC_TRNS   , KC_TRNS ,  NN_SPACE  , NN_SPACE  , KC_0       , KC_TRNS   , KC_TRNS
    ),

    [NUM_SYM_FN] = LAYOUT( // Top-row numbers, middle-row symbols, bottom row function keys layer
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS                          , KC_TRNS    , KC_TRNS   , KC_TRNS   , KC_TRNS      , KC_TRNS     , KC_TRNS      ,
        KC_1      , KC_2      , KC_3      , KC_4      , KC_5      , KC_6                             , KC_7       , KC_8      , KC_9      , KC_0         , KC_MINS     , KC_EQL       ,
        KC_EXLM   , KC_AT     , KC_HASH   , KC_DLR    , KC_PERC   , KC_CIRC                          , KC_AMPR    , KC_ASTR   , KC_LPRN   , KC_RPRN      , KC_UNDS     , KC_PLUS      ,
        KC_F1     , KC_F2     , KC_F3     , KC_F4     , KC_F5     , KC_F6   ,  KC_TRNS   , KC_TRNS   , KC_F7      , KC_F8     , KC_F9     , KC_F10       , KC_F11      , KC_F12       ,
                                            KC_CAPS   , KC_TRNS   , KC_TRNS ,  KC_TRNS   , KC_TRNS   , KC_TRNS    , KC_TRNS   , KC_TRNS
    ),

    [APP_NAV] = LAYOUT( // Transparent left-side, application navigation right-side
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS                          , KC_TRNS    , KC_TRNS  , KC_TRNS    , KC_TRNS      , KC_TRNS     , KC_TRNS      ,
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS                          , TAB_LEFT   , TAB_RIGHT, KC_HOME    , KC_UP        , KC_END      , ALT_F4       ,
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS                          , BACK       , FORWARD  , KC_LEFT    , KC_DOWN      , KC_RIGHT    , SELECT_LINE  ,
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS ,  KC_TRNS   , KC_TRNS   , ZOOM_OUT   , ZOOM_IN  , KC_TRNS    , KC_TRNS      , DESKTOP_LEFT, DESKTOP_RIGHT,
                                            KC_TRNS   , KC_TRNS   , KC_TRNS ,  KC_TRNS   , KC_TRNS   , KC_TRNS    , KC_TRNS  , KC_TRNS
    ),

    [STAR] = LAYOUT( // Starcraft layer
        KC_ESC    , KC_1      , KC_2      , KC_3      , KC_4      , KC_5                             , KC_6       , KC_7      , KC_8      , KC_9         , KC_0        , KC_MINS      ,
        KC_DEL    , KC_Q      , KC_W      , KC_E      , KC_R      , KC_T                             , KC_Y       , KC_U      , KC_I      , KC_O         , KC_P        , KC_BSPC      ,
        KC_INS    , KC_A      , KC_S      , KC_D      , KC_F      , KC_G                             , KC_H       , KC_J      , KC_K      , KC_L         , KC_QUOT     , KC_ENT       ,
        KC_TRNS   , KC_Z      , KC_X      , KC_C      , KC_V      , KC_B    , KC_GRV     , TO(BASE)  , KC_N       , KC_M      , KC_COMM   , KC_DOT       , KC_SLSH     , KC_RSFT      ,
                                            KC_ENT    , KC_BSPC   , KC_LALT , KC_LCTL    , BASE_SPACE, KC_RALT    , KC_RGUI   , SSYM_CALL
    )
};

// KEY LOGGER SETUP-----------------------------------------------------------------------------------------------------------------------------------------------

#define key_log_rows 4
#define key_log_cols 20

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
     25, ' ',  17,  26, ' ', '-', '=', '[', ']','\\',
    ' ', ';','\'', '`', ',', '.', '/', ' ', ' ', ' '
};

const char code_to_name_shifted[60] = {
    ' ', ' ', ' ', ' ', 'A', 'B', 'C', 'D', 'E', 'F',
    'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    '!', '@', '#', '$', '%', '^', '&', '*', '(', ')',
    25, ' ',  17,  26, ' ', '_', '+', '{', '}', '|',
    ' ', ':', '\"', '~', '<', '>', '?', ' ', ' ', ' '
};

char key_log[key_log_rows][key_log_cols] = { // HARD-CODED TO MATCH OLED LANDSCAPE ROWS AND COLS
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
};

void send_key_log(void){
    SEND_STRING("\n<key_log: ");
    for(int i = 0; i < key_log_rows; i++){
        for(int j = 0; j < key_log_cols; j++){
            send_char(key_log[i][j]);
        }
    }

    SEND_STRING(">\n");
}

void log_key(uint16_t keycode, uint8_t mods, uint8_t oneshot_mods){
    char shifted_sym = ' ';

    if(!((mods | oneshot_mods) & (MOD_MASK_ALT || MOD_MASK_CTRL || MOD_MASK_GUI))) {
        if(
            keycode < 60       ||
            keycode == KC_EXLM ||
            keycode == KC_AT   ||
            keycode == KC_HASH ||
            keycode == KC_DLR  ||
            keycode == KC_PERC ||
            keycode == KC_CIRC ||
            keycode == KC_AMPR ||
            keycode == KC_ASTR ||
            keycode == KC_LPRN ||
            keycode == KC_RPRN ||
            keycode == KC_UNDS ||
            keycode == KC_PLUS ||
            keycode == KC_COLN ||
            keycode == KC_LCBR ||
            keycode == KC_RCBR ||
            keycode == KC_PIPE
        ){
            for(int i = 0; i < key_log_rows; i++){
                for(int j = 0; j < key_log_cols; j++){
                    if(i == key_log_rows - 1 && j == key_log_cols - 1){
                        if(keycode < 60){
                            if(
                                ((mods | oneshot_mods) & MOD_MASK_SHIFT) ||
                                (keycode >= 4 && keycode <= 29 && host_keyboard_led_state().caps_lock)
                            ){
                                key_log[i][j] = code_to_name_shifted[keycode];
                            } else {
                                key_log[i][j] = code_to_name[keycode];
                            }
                        } else {
                            switch (keycode){
                                case KC_EXLM:
                                    shifted_sym = '!';
                                    break;
                                case KC_AT:
                                    shifted_sym = '@';
                                    break;
                                case KC_HASH:
                                    shifted_sym = '#';
                                    break;
                                case KC_DLR:
                                    shifted_sym = '$';
                                    break;
                                case KC_PERC:
                                    shifted_sym = '%';
                                    break;
                                case KC_CIRC:
                                    shifted_sym = '^';
                                    break;
                                case KC_AMPR:
                                    shifted_sym = '&';
                                    break;
                                case KC_ASTR:
                                    shifted_sym = '*';
                                    break;
                                case KC_LPRN:
                                    shifted_sym = '(';
                                    break;
                                case KC_RPRN:
                                    shifted_sym = ')';
                                    break;
                                case KC_UNDS:
                                    shifted_sym = '_';
                                    break;
                                case KC_PLUS:
                                    shifted_sym = '+';
                                    break;
                                case KC_COLN:
                                    shifted_sym = ':';
                                    break;
                                case KC_LCBR:
                                    shifted_sym = '{';
                                    break;
                                case KC_RCBR:
                                    shifted_sym = '}';
                                    break;
                                case KC_PIPE:
                                    shifted_sym = '|';
                            }

                            if(shifted_sym != ' '){
                                key_log[i][j] = shifted_sym;
                            }
                        }
                    } else {
                        key_log[i][j] = key_log[i][j+1];
                    }
                }
            }
        }
    }
};

void remove_space(void) {
    bool found_space = false;
    for(int i = key_log_rows - 1; i >= 0; i--){
        for(int j = key_log_cols - 1; j >= 0; j--){
            if(key_log[i][j] == ' '){
                found_space = true;
            }

            if(found_space){
                if(i == 0 && j == 0){
                    key_log[i][j] = ' ';
                } else {
                    key_log[i][j] = key_log[i][j-1];
                }
            }
        }
    }
};

// SSYM SETUP-----------------------------------------------------------------------------------------------------------------------------------------------

#define SSYM_table_rows 9
#define SSYM_table_cols 4

char SSYM[SSYM_table_cols] = {'~', 't', 'i', 'l'};

const char SSYM_table[SSYM_table_rows][SSYM_table_rows] = {
    {'!','e','x','c'},
    {'@','a','t','s'},
    {'#','p','o','u'},
    {'$','d','o','l'},
    {'%','p','e','r'},
    {'^','c','a','r'},
    {'&','a','m','p'},
    {'*','a','s','t'},
    {'~','t','i','l'},
};

const char SSYM_table_shifted[SSYM_table_rows][SSYM_table_rows] = {
    {'!','E','X','C'},
    {'@','A','T','S'},
    {'#','P','O','U'},
    {'$','D','O','L'},
    {'%','P','E','R'},
    {'^','C','A','R'},
    {'&','A','M','P'},
    {'*','A','S','T'},
    {'~','T','I','L'},
};

void send_SSYM_array(void){
    SEND_STRING("\n<SSYM: {");

    for(int i = 0; i < SSYM_table_cols; i++){
        send_char('\'');
        send_char(SSYM[i]);
        send_char('\'');

        if(i != SSYM_table_cols - 1){
            send_char(',');
        }
    }

    SEND_STRING("}>\n");
}

bool update_SSYM(void){
    for(int i = 0; i < SSYM_table_rows; i++){
        if(
            (
                (key_log[key_log_rows-1][key_log_cols-3] == SSYM_table[i][1] || key_log[key_log_rows-1][key_log_cols-3] == SSYM_table_shifted[i][1]) &&
                (key_log[key_log_rows-1][key_log_cols-2] == SSYM_table[i][2] || key_log[key_log_rows-1][key_log_cols-2] == SSYM_table_shifted[i][2]) &&
                (key_log[key_log_rows-1][key_log_cols-1] == SSYM_table[i][3] || key_log[key_log_rows-1][key_log_cols-1] == SSYM_table_shifted[i][3])
            ) && !(
                (SSYM_table[i][1] == SSYM[1] || SSYM_table_shifted[i][1] == SSYM[1]) &&
                (SSYM_table[i][2] == SSYM[2] || SSYM_table_shifted[i][2] == SSYM[2]) &&
                (SSYM_table[i][3] == SSYM[3] || SSYM_table_shifted[i][3] == SSYM[3])
            )
        ) {
            for(int j = 0; j < SSYM_table_cols; j++){
                SSYM[j] = SSYM_table[i][j];
            }

            for(int j = 0; j < SSYM_table_cols - 1; j++){
                tap_code(KC_BSPC);
            }

            return true;
        }
    }

    return false;
};

void SSYM_fn(void){
    update_SSYM();
    if(SSYM[0] != ' '){
        send_char(SSYM[0]);

        for(int i = 0; i < key_log_rows; i++){
            for(int j = 0; j < key_log_cols; j++){
                if(i == key_log_rows - 1 && j == key_log_cols - 1){
                    key_log[i][j] = SSYM[0];
                } else {
                    key_log[i][j] = key_log[i][j+1];
                }
            }
        }
    }
};

// OLED SETUP-----------------------------------------------------------------------------------------------------------------------------------------------------

#ifdef OLED_ENABLE

    #define oled_portrait_rows 16
    #define oled_portrait_cols 5
    #define oled_landscape_rows 4
    #define oled_landscape_cols 20

    int max_wpm = 0;

    int view_selection = 0;

    // STATS VIEW----------------------------------------------------------------------------------

    void render_status(void) {

        // 0/5 VIEW HEADER------------------------------------------------

        oled_set_cursor(0,0);
        oled_write("STATS",false);
        oled_set_cursor(0,1);
        oled_write("-----",false);

        // 1/5 LAYER------------------------------------------------------

        oled_set_cursor(0,2);
        oled_write("LAYR:", false);
        oled_set_cursor(0,3);

        switch (get_highest_layer(layer_state)) {
            case BASE:
                oled_write("Base", false);
                break;
            case GAMING:
                oled_write("Game", false);
                break;
            case NAV_NUM:
                oled_write("NNum", false);
                break;
            case NUM_SYM_FN:
                oled_write("NSFn", false);
                break;
            case APP_NAV:
                oled_write("ANav", false);
                break;
            case STAR:
                oled_write("Star", false);
                break;                
        }

        // 2/5 CAPS LOCK--------------------------------------------------

        oled_set_cursor(0,5);
        oled_write("CAPS:", false);
        oled_set_cursor(0,6);
        led_t led_state = host_keyboard_led_state();
        oled_write_P(led_state.caps_lock ? PSTR("On ") : PSTR("Off"), false);

        // 3/5 SSYM-------------------------------------------------

        oled_set_cursor(0,8);
        oled_write("SSYM:", false);

        for(int i = 0; i < SSYM_table_cols; i++) {
            oled_set_cursor(i,9);
            oled_write((char[2]) { (char) SSYM[i], '\0' },false);
        }

        // 4,5/5 WPM------------------------------------------------------

        oled_set_cursor(0,11);
        oled_write("MWPM:",false);
        oled_set_cursor(0,12);
        oled_write(get_u8_str(max_wpm,' '),false);

        oled_set_cursor(0,14);
        oled_write("CWPM:",false);
        oled_set_cursor(0,15);
        oled_write(get_u8_str(get_current_wpm(),' '),false);
    };

    // KEY LOG VIEW--------------------------------------------------------------------------------

    void render_key_log(void) {

        // VIEW HEADER----------------------------------------------------

        oled_set_cursor(0,0);
        oled_write("-------KEYLOG-------",false);

        // RENDER KEY LOG-------------------------------------------------

        for(int i = 1; i < oled_landscape_rows; i++) {
            for(int j = 0; j < oled_landscape_cols; j++) {
                oled_set_cursor(j,i);
                oled_write((char[2]) { (char) key_log[i][j], '\0' },false);            }
        }
    };

    //STICKY SYM TABLE VIEW------------------------------------------------------------------------

    void render_SSYM_table(void){

        // VIEW HEADER----------------------------------------------------

        oled_set_cursor(0,0);
        oled_write("SYMBS", false);
        oled_set_cursor(0,1);
        oled_write("-----", false);

        // RENDER TABLE---------------------------------------------------

        for(int i = 0; i < oled_portrait_rows; i++){
            for(int j = 0; j < oled_portrait_cols; j++){
                if(i < SSYM_table_rows){
                        oled_set_cursor(j,i+2);
                    if(j == 0) {
                        oled_write((char[2]) { (char) SSYM_table[i][j], '\0' },false);
                    } else if(j == 1) {
                        oled_write(" ", false);
                    } else {
                        oled_write((char[2]) { (char) SSYM_table[i][j-1], '\0' },false);
                    }
                }
            }
        }

        // VIEW FOOTER----------------------------------------------------

        if(SSYM_table_rows < oled_portrait_rows - 2){
            oled_set_cursor(0,SSYM_table_rows+2);
            oled_write("-----",false);
        }
    };

    // DRAW TO OLEDs-------------------------------------------------------------------------------

    bool is_portrait = true;

    bool oled_task_user(void) {
        max_wpm = get_current_wpm() > max_wpm? get_current_wpm(): max_wpm;

        if(is_keyboard_master()){
            switch(view_selection){
                case 0:
                    if(!is_portrait){
                        oled_init(135);
                        is_portrait = true;
                    }

                    render_status();
                    break;
                case 1:
                    if(is_portrait){
                        oled_init(0);
                        is_portrait = false;
                    }

                    render_key_log();
                    break;
                case 2:
                    if(!is_portrait){
                        oled_init(135);
                        is_portrait = true;
                    }

                    render_SSYM_table();
                    break;
            }
        }else{
            render_SSYM_table();
        }

        return false;
    };

    void clear_oled(void){
        oled_init(135);
        is_portrait = true;

        for(int i = 0; i < oled_portrait_rows; i++){
            for(int j = 0; j < oled_portrait_cols; j++){
                oled_set_cursor(j,i);
                oled_write(" ",false);
            }
        }
    };

#endif

// POST INITIALIZATION--------------------------------------------------------------------------------------------------------------------------------------------

void keyboard_post_init_user(void) {
    oled_init(135);
};

// USER SPACE-----------------------------------------------------------------------------------------------------------------------------------------------------

bool process_record_user(uint16_t keycode, keyrecord_t *record){
    const uint8_t mods = get_mods();
    const uint8_t oneshot_mods = get_oneshot_mods();
    bool other_key_pressed = false;
    static uint16_t press_timer;

    if(keycode != BASE_SPACE && keycode != NN_SPACE){
        if(record->event.pressed){
            other_key_pressed = true;
        }
    }

    switch (keycode) {
        case BASE_SPACE:
        case NN_SPACE:
            if (record->event.pressed) {
                other_key_pressed = false;
                press_timer = timer_read();
                log_key(KC_SPC,mods,oneshot_mods);
            } else {
                if(timer_elapsed(press_timer) > 200 || other_key_pressed){
                    remove_space();
                }

            }

            break;
        case SELECT_LINE:
            if (record->event.pressed ){
                tap_code(KC_HOME);
                tap_code16(LSFT(KC_END));
            }

            return false;

        case SSYM_CALL:
            if (record->event.pressed) {
                press_timer = timer_read();
                layer_on(APP_NAV);
            } else {
                if(timer_elapsed(press_timer) < 200){
                    SSYM_fn();
                }

                layer_off(APP_NAV);
            }

            return false;

        #ifdef OLED_ENABLE
            case PREV_VIEW:
                if(record->event.pressed){
                    clear_oled();
                    view_selection = view_selection > 0? view_selection - 1 : 2;
                }

                break;
            case NEXT_VIEW:
                if(record->event.pressed){
                   clear_oled();
                   view_selection = view_selection < 2? view_selection + 1 : 0;
                }

                break;
        #endif

        default:
            if (record->event.pressed) {
                log_key(keycode,mods,oneshot_mods);
            }
    }

    return true;
};




