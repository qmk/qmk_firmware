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

#include QMK_KEYBOARD_H

enum layers {
    Base,
    NavNum,
    NavAppNav,
    NumCharFunc,
    AppNavMacro,
    Gaming,
    ControlGroups,
    AutoButtons,
};

enum custom_keycodes {
    ADD_SPACE_DOWN = SAFE_RANGE,
    SELECTION_DO_END,
    SELECTION_PAIR_PAREN,
    SELECTION_PAIR_BRACES,
    SELECTION_PAIR_BRACKETS,
    SELECTION_PAIR_QUOTES,
    SELECT_LINE,
    SELECT_WORD,
    SELECTION_BLOCK_COMMENT,
    SELECTION_PAIR_INEQUALITY,
    THIS_LINE_PAIR_PAREN,
    THIS_LINE_PAIR_BRACES,
    THIS_LINE_PAIR_BRACKETS,
    // CHROMESEARCH,
    POP_TAB_CHROME,
    OPEN_FOLDER_IN_CMD,
    REMOVE_CHARACTER_DOWN,
    MOVE_LINE_UP,
    MOVE_LINE_DOWN,
    // DELETE_WORD,
    SHIFT_CONTROL_LEFT,
    SHIFT_CONTROL_RIGHT,
    MOVE_MAX_WINDOW_LEFT,
    MOVE_MAX_WINDOW_RIGHT,
    OPEN_TASK_MANAGER,
    // POWERON_HTML,
    // REP_QUOTE,
    POP_TAB_VSCODE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [Base] = LAYOUT_split_3x6_3(
        KC_ESC    , KC_Q      , KC_W      , KC_E      , KC_R          , KC_T             , KC_Y                , KC_U      , KC_I      , KC_O      , KC_P      , KC_BSPC   ,
        KC_TAB    , KC_A      , KC_S      , KC_D      , KC_F          , KC_G             , KC_H                , KC_J      , KC_K      , KC_L      , KC_QUOT   , KC_ENT    ,
        KC_LSFT   , KC_Z      , KC_X      , KC_C      , KC_V          , KC_B             , KC_N                , KC_M      , KC_COMM   , KC_DOT    , KC_SLSH   , KC_RSFT   ,
                                            KC_LCTL   , LALT_T(KC_DEL), LT(NavNum,KC_SPC), LT(NavAppNav,KC_SPC), KC_RGUI   , MO(AppNavMacro) 
    ),
    [NavNum] = LAYOUT_split_3x6_3(
        KC_GRV    , KC_HOME   , KC_UP     , KC_END    , KC_PLUS   , KC_LPRN   , KC_RPRN               , KC_7      , KC_8      , KC_9      , KC_DEL    , KC_BSPC   ,
        KC_TAB    , KC_LEFT   , KC_DOWN   , KC_RIGHT  , KC_EQL    , KC_LCBR   , KC_RCBR               , KC_4      , KC_5      , KC_6      , KC_SCLN   , KC_ENT    ,
        KC_LSFT   , KC_PIPE   , KC_UNDS   , KC_COLN   , KC_MINS   , KC_LBRC   , KC_RBRC               , KC_1      , KC_2      , KC_3      , KC_BSLS   , KC_RSFT   ,
                                            KC_TRNS   , KC_TRNS   , KC_TRNS   , LT(NumCharFunc,KC_SPC), KC_0      , KC_TRNS  
    ),   
    [NavAppNav] = LAYOUT_split_3x6_3(
        KC_GRV    , KC_HOME   , KC_UP     , KC_END    , KC_PLUS   , THIS_LINE_PAIR_PAREN   , RCS(KC_TAB)  , LCTL(KC_TAB)  , KC_HOME   , KC_UP     , KC_END    , KC_BSPC   ,
        KC_TAB    , KC_LEFT   , KC_DOWN   , KC_RIGHT  , KC_EQL    , THIS_LINE_PAIR_BRACES  , LALT(KC_LEFT), LALT(KC_RIGHT), KC_LEFT   , KC_DOWN   , KC_RIGHT  , KC_PGUP   ,
        KC_LSFT   , KC_PIPE   , KC_UNDS   , KC_COLN   , KC_MINS   , THIS_LINE_PAIR_BRACKETS, LCTL(KC_PMNS), LCTL(KC_PPLS) , LCTL(KC_T), LCTL(KC_N), LCTL(KC_W), KC_PGDN   ,
                                            KC_TRNS   , KC_TRNS   , LT(NumCharFunc,KC_SPC) , KC_TRNS      , KC_TRNS       , KC_TRNS  
    ), 
    [NumCharFunc] = LAYOUT_split_3x6_3(
        KC_1      , KC_2      , KC_3      , KC_4      , KC_5      , KC_6      , KC_7      , KC_8      , KC_9      , KC_0      , KC_MINS   , KC_EQL    ,
        KC_EXLM   , KC_AT     , KC_HASH   , KC_DLR    , KC_PERC   , KC_CIRC   , KC_AMPR   , KC_ASTR   , KC_LPRN   , KC_RPRN   , KC_UNDS   , KC_PLUS   ,
        KC_F1     , KC_F2     , KC_F3     , KC_F4     , KC_F5     , KC_F6     , KC_F7     , KC_F8     , KC_F9     , KC_F10    , KC_F11    , KC_F12    ,
                                            KC_CAPS   , KC_MPLY   , KC_TRNS   , KC_TRNS   , KC_MPRV   , KC_MNXT
    ),
    [AppNavMacro] = LAYOUT_split_3x6_3(
        LALT(KC_F4)  , KC_HOME          , KC_UP          , KC_END            , RCS(KC_TAB)  , LCTL(KC_TAB)  , SELECTION_PAIR_PAREN   , ADD_SPACE_DOWN           , REMOVE_CHARACTER_DOWN  , MOVE_LINE_UP       , MOVE_LINE_DOWN       , POP_TAB_VSCODE       ,
        KC_PGUP      , KC_LEFT          , KC_DOWN        , KC_RIGHT          , LALT(KC_LEFT), LALT(KC_RIGHT), SELECTION_PAIR_BRACES  , SELECTION_PAIR_INEQUALITY, SELECTION_BLOCK_COMMENT, SELECTION_DO_END   , SELECTION_PAIR_QUOTES, SELECT_LINE          ,
        KC_PGDN      , OPEN_TASK_MANAGER, POP_TAB_CHROME , OPEN_FOLDER_IN_CMD, LCTL(KC_PMNS), LCTL(KC_PPLS) , SELECTION_PAIR_BRACKETS, SHIFT_CONTROL_LEFT       , SELECT_WORD            , SHIFT_CONTROL_RIGHT, MOVE_MAX_WINDOW_LEFT , MOVE_MAX_WINDOW_RIGHT,
                                                           KC_TRNS           , KC_TRNS      , KC_TRNS       , TO(Gaming)             , KC_TRNS                  , KC_TRNS      
    ),
    [Gaming] = LAYOUT_split_3x6_3(
        KC_ESC    , KC_Q      , KC_W      , KC_E      , KC_R      , KC_T      , KC_Y             , KC_U      , KC_I      , KC_O      , KC_P      , KC_BSPC   ,
        KC_TAB    , KC_A      , KC_S      , KC_D      , KC_F      , KC_G      , KC_H             , KC_J      , KC_K      , KC_L      , KC_QUOT   , KC_ENT    ,
        KC_LSFT   , KC_Z      , KC_X      , KC_C      , KC_V      , KC_B      , KC_N             , KC_M      , KC_COMM   , KC_DOT    , KC_SLSH   , KC_RSFT   ,
                                            KC_LCTL   , MO(ControlGroups)     , LT(NavNum,KC_SPC), KC_MPLY   , KC_MNXT   , TO(Base) 
    ),           
    [ControlGroups] = LAYOUT_split_3x6_3(
        KC_TRNS   , KC_1      , KC_2      , KC_3      , KC_4      , KC_5      , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , 
        KC_TRNS   , LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_4), LSFT(KC_5), KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , 
        KC_TRNS   , LCTL(KC_1), LCTL(KC_2), LCTL(KC_3), LCTL(KC_4), LCTL(KC_5), KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , 
                                            KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS    
    ),
    [AutoButtons] = LAYOUT_split_3x6_3(
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , 
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , 
        KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_TRNS   , 
                                            KC_TRNS   , KC_TRNS   , KC_TRNS   , KC_BTN1   , KC_BTN2   , KC_TRNS    
    ),       
};          

void pointing_device_init_user(void) {
    set_auto_mouse_enable(true);
}

void housekeeping_task_user(void) {
    static i2c_status_t rgbw_status = I2C_STATUS_ERROR;
    if (rgbw_status != I2C_STATUS_SUCCESS){
        pimoroni_trackball_set_rgbw(0, 0, 0, 100);
    }
}

bool set_scrolling = false;
int pointer_magnitude = 0;
int pointer_limit = 25;
int track_factor = 1;

int calculate_magnitude(int mouse_report_x, int mouse_report_y) {
    return sqrt(pow(mouse_report_x,2)+pow(mouse_report_y,2));
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (set_scrolling) {
        mouse_report.h = mouse_report.x;
        mouse_report.v = -mouse_report.y;
        mouse_report.x = mouse_report.y = 0;
    } else {
        pointer_magnitude = calculate_magnitude(mouse_report.x, mouse_report.y);
	    track_factor = pointer_magnitude < pointer_limit? pointer_magnitude : pointer_limit;
        mouse_report.x = track_factor * mouse_report.x;
        mouse_report.y = track_factor * mouse_report.y;
    }
    return mouse_report;      
}
 
bool process_record_user(uint16_t keycode, keyrecord_t *record){

  switch (keycode){
    case LT(NavNum,KC_SPC):
    case LT(NavAppNav,KC_SPC):
        if(record->event.pressed){
            set_scrolling = true;
        } else {
            set_scrolling = false;
        }
        break;
    case ADD_SPACE_DOWN:
        if(record->event.pressed){
            tap_code(KC_HOME);
            SEND_STRING (" ");
            tap_code(KC_DOWN);
        }
        return false;
    case SELECTION_DO_END:
        if(record->event.pressed){
            tap_code16(LCTL(KC_X));
            SEND_STRING("DO");
            tap_code(KC_ENT);
            tap_code16(LCTL(KC_V));
            tap_code(KC_ENT);
            SEND_STRING("END");
        }
        return false;        
    case SELECTION_PAIR_PAREN:
        if(record->event.pressed){
            tap_code16(LCTL(KC_X));
            SEND_STRING("(");
            tap_code16(LCTL(KC_V));
            SEND_STRING(")");
        }
        return false;
    case SELECTION_PAIR_BRACES:
        if(record->event.pressed){
            tap_code16(LCTL(KC_X));
            SEND_STRING("{");
            tap_code16(LCTL(KC_V));
            SEND_STRING("}");
        }
        return false;   
    case SELECTION_PAIR_BRACKETS:
        if(record->event.pressed){
            tap_code16(LCTL(KC_X));
            SEND_STRING("[");
            tap_code16(LCTL(KC_V));
            SEND_STRING("]");
        }
        return false;   
    case SELECTION_PAIR_QUOTES:
        if(record->event.pressed){
            tap_code16(LCTL(KC_X));
            SEND_STRING("\"");
            tap_code16(LCTL(KC_V));
            SEND_STRING("\"");
        }
        return false;
    case SELECT_LINE:
        if(record->event.pressed){
            tap_code(KC_HOME);
            tap_code16(LSFT(KC_END));
        }
        return false;
    case SELECT_WORD:
        if(record->event.pressed){
            tap_code16(LCTL(KC_LEFT));
            tap_code16(RCS(KC_RIGHT));
        }
        return false;
    case SELECTION_BLOCK_COMMENT:
        if(record->event.pressed){
            tap_code16(LCTL(KC_X));
            SEND_STRING("/*");
            tap_code16(RCS(KC_V));
            SEND_STRING("*/");
        }
        return false;
    case SELECTION_PAIR_INEQUALITY:
        if(record->event.pressed){
            tap_code16(LCTL(KC_X));
            SEND_STRING("<");
            tap_code16(RCS(KC_V));
            SEND_STRING(">");
        }
        return false;
    case THIS_LINE_PAIR_PAREN:
        if(record->event.pressed){
            tap_code(KC_HOME);
            tap_code16(LSFT(KC_END));
            tap_code16(LCTL(KC_X));
            SEND_STRING("(");
            tap_code16(RCS(KC_V));
            SEND_STRING(")");
        }
        return false;
    case THIS_LINE_PAIR_BRACES:
        if(record->event.pressed){
            tap_code(KC_HOME);
            tap_code16(LSFT(KC_END));
            tap_code16(LCTL(KC_X));
            SEND_STRING("{");
            tap_code16(RCS(KC_V));
            SEND_STRING("}");
        }
        return false;
    case THIS_LINE_PAIR_BRACKETS:
        if(record->event.pressed){
            tap_code(KC_HOME);
            tap_code16(LSFT(KC_END));
            tap_code16(LCTL(KC_X));
            SEND_STRING("[");
            tap_code16(RCS(KC_V));
            SEND_STRING("]");
        }
        return false;
    case POP_TAB_CHROME:
        if(record->event.pressed){
            tap_code16(LALT(KC_D));
            tap_code16(LCTL(KC_C));
            tap_code16(LCTL(KC_W));
            tap_code16(LCTL(KC_N));
            tap_code16(LCTL(KC_V));
            tap_code(KC_ENTER);
        }
        return false;
    case OPEN_FOLDER_IN_CMD:
        if(record->event.pressed){
            tap_code16(LALT(KC_D));
            SEND_STRING("cmd");
            tap_code(KC_ENTER);
        }
        return false;
    case REMOVE_CHARACTER_DOWN:
        if(record->event.pressed){
            tap_code(KC_HOME);
            tap_code(KC_DEL);
            tap_code(KC_DOWN);
        }
        return false;
    case MOVE_LINE_UP:
        if(record->event.pressed){
            tap_code16(SELECT_LINE);
            tap_code16(LCTL(KC_X));
            tap_code(KC_BSPC);
            tap_code(KC_HOME);
            tap_code(KC_ENTER);
            tap_code(KC_UP);
            tap_code16(LCTL(KC_V));
        }
        return false;
    case MOVE_LINE_DOWN:
        if(record->event.pressed){
            tap_code16(SELECT_LINE);
            tap_code16(LCTL(KC_X));
            tap_code(KC_BSPC);
            tap_code(KC_DOWN);
            tap_code(KC_END);
            tap_code(KC_ENTER);
            tap_code16(LCTL(KC_V));
        }
        return false;   
    // case DELETE_WORD:
    //     if(record->event.pressed){
    //         tap_code16(RCS(KC_LEFT));
    //         tap_code(KC_BSPC);
    //     }
    //     return false;
    case SHIFT_CONTROL_LEFT:
        if(record->event.pressed){
            tap_code16(RCS(KC_LEFT));
        }
        return false;
    case SHIFT_CONTROL_RIGHT:
        if(record->event.pressed){
            tap_code16(RCS(KC_RIGHT));
        }
        return false;   
    case MOVE_MAX_WINDOW_LEFT:
        if(record->event.pressed){
            tap_code16(LSG(KC_LEFT));
        }
        return false;                             
    case MOVE_MAX_WINDOW_RIGHT:
        if(record->event.pressed){
            tap_code16(LSG(KC_RIGHT));
        }
        return false;  
    case OPEN_TASK_MANAGER:
        if(record->event.pressed){
            tap_code16(RCS(KC_ESC));
        }
        return false;  
    case POP_TAB_VSCODE:
        if(record->event.pressed){
            tap_code16(LCTL(KC_K));
            tap_code(KC_O);
        }
        return false;                         
  }  
  return true;

}