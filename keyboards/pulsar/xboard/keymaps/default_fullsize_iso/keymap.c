/* Copyright 2021 Maxime Coirault, Don Kjer, Tyler Tidman
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
#include "analog.h"

#ifdef OLED_ENABLE      
    static void render_logo_font(void);
    void oled_rgb_mode(void);
#endif

bool isWinLock = false;             // WIN Lock LED
bool isWinLockLedOn = false;        //
static uint16_t WinLock_timer;      //

static bool     INIT3S_on = false;
static bool     INIT3S_led_on = false;
static uint16_t INIT3S_timer; // for custom key, INIT_3S

uint16_t        startup_timer;
static bool     finished_timer  = false;
static bool     bootloader_mode = false;

static bool     kvm_pc_sel      = false;
static uint16_t kvm_timer;
static bool     kvm_sel_on      = false;

static bool isMacMode = false;

#define kvm_deadtime    100
//------------------------------
typedef union {
    uint32_t raw;
    struct {
        bool     eeprom_kvm_pc_sel :1;
    };
} user_config_t;

user_config_t user_config;

//-=-------------------------------------------
    // Layer shorthand
    enum _layer { WIN_BASE = 0, WIN_FN, MAC_BASE, MAC_FN };

    enum K3x0_keycodes {
#ifdef VIA_ENABLE
        KC_TGUI = QK_KB_0,  // Ver 0.21.6에서 변경 (USER00,)  // Toggle between GUI Lock or Unlock
        KC_WIN_MODE,        // WINDOWS Keyboard로 변경
        KC_MAC_MODE,        // Machintosh Keyboard로 변경
        KC_TMODE,        // WINDOWS <--> Machintosh
// KC_MISSION_CONTROL, // MAC_key   // Ver 0.21.6에서 기본지원
// KC_LAUNCHPAD,       // MAC_key   // Ver 0.21.6에서 기본지원
        KC_SPOTLIGHT,       // MAC_key
        KC_DICTATION,       // MAC_key
        KC_DO_NOT_DISTURB,  // MAC_key
        KC_LOCK_SCREEN,     // MAC_key
        KC_LOPTN,           // MAC_key - left option   (win위치)
        KC_ROPTN,           // MAC_key - right option
        KC_LCMMD,           // MAC_key - left command  (ALT위치)
        KC_RCMMD,           // MAC_key - right command
        KC_TASK_VIEW,       // for win (gui + tap)
        KC_FILE_EXPLORER,   // for win (gui + e)
        KC_PC1,             // KM Switch PC1
        KC_PC2,             // KM Switch PC2
        KC_TPC,             // KM Switch PC1<-->PC2 Toggle
        INIT_3S,            // EE_CLR(EEPROM CLear)(공장초기화)를 3초이상 눌러야 동작
        NEW_SAFE_RANGE = SAFE_RANGE
#else
    KC_TGUI = SAFE_RANGE,   // Toggle between GUI Lock or Unlock
    KC_WIN_MODE,             // WINDOWS Keyboard로 변경
    KC_MAC_MODE,             // Machintosh Keyboard로 변경
    KC_TMODE,             // WINDOWS <--> Machintosh Toggle
// KC_MISSION_CONTROL, // MAC_key   // Ver 0.21.6에서 기본지원
// KC_LAUNCHPAD,       // MAC_key   // Ver 0.21.6에서 기본지원
KC_SPOTLIGHT,           // MAC_key
KC_DICTATION,           // MAC_key      
KC_DO_NOT_DISTURB,      // MAC_key
KC_LOCK_SCREEN,         // MAC_key
    KC_LOPTN,               // MAC_key 불필요한듯
    KC_ROPTN,               // MAC_key 불필요한듯
    KC_LCMMD,               // MAC_key 불필요한듯
    KC_RCMMD,               // MAC_key 불필요한듯
    KC_TASK_VIEW,           // for win (gui + tap)
    KC_FILE_EXPLORER,       // for win (gui + e)
    KC_PC1,                 // KM Switch PC1
    KC_PC2,                 // KM Switch PC2
    KC_TPC,                 // KM Switch PC1<-->PC2 Toggle
    INIT_3S,            // EE_CLR(EEPROM CLear)(공장초기화)를 3초이상 눌러야 동작    
    NEW_SAFE_RANGE
#endif
    };

// #undef SAFE_RANGE
// #define SAFE_RANGE NEW_SAFE_RANGE

#define KC_WINM KC_WIN_MODE
#define KC_MACM KC_MAC_MODE

#define KC_MCTL KC_MISSION_CONTROL
#define KC_LPAD KC_LAUNCHPAD

#define KC_SPLT KC_SPOTLIGHT
#define KC_SIRI KC_DICTATION
#define KC_DOND KC_DO_NOT_DISTURB
#define KC_LOCK_ KC_LOCK_SCREEN

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)
#define KC_DIC  LGUI(KC_H)    // 받아쓰기
#define KC_LOCK2 LGUI(KC_L)   // pc잠금

// Tap dance declarations (These must go above the keymaps)
enum {
  TD_NLCK_CALC = 0,
    TD_2,
    TD_3,
    TD_4,
    TD_5
};

void dance_test(tap_dance_state_t *state, void *user_data){    // Ver 0.21.6에서 변경
    if(state->count >=5){
        SEND_STRING("Tap Dance Test ok!");
        reset_tap_dance(state);
    }
}

tap_dance_action_t tap_dance_actions[] = {              // Ver 0.21.6에서 변경
    [TD_NLCK_CALC] = ACTION_TAP_DANCE_DOUBLE(KC_NUM_LOCK, KC_CALC),
    [TD_2] = ACTION_TAP_DANCE_DOUBLE(KC_MPLY, KC_MSEL),
    [TD_3] = ACTION_TAP_DANCE_DOUBLE(KC_FLXP, KC_MYCM),
    [TD_4] = ACTION_TAP_DANCE_DOUBLE(KC_MSEL, KC_MAIL),
    [TD_5] = ACTION_TAP_DANCE_FN(dance_test),
};

void kvm_switch(bool pc_num){
    writePinHigh(GPIO_KM_OE);
    writePinLow(GPIO_KM_PWEN);
    if (!pc_num) writePinLow(GPIO_KM_SEL);
    else   writePinHigh(GPIO_KM_SEL);
    writePinLow(GPIO_KM_OE);

    kvm_timer = timer_read();
    kvm_sel_on = true;
};

void keyboard_pre_init_user(void) {
};
//------------------------------------------
void keyboard_post_init_user(void) {
    user_config.raw = eeconfig_read_user();
    kvm_pc_sel      = user_config.eeprom_kvm_pc_sel;
    kvm_switch(kvm_pc_sel);
}
//-------------------------------------------------------------------------------------------------------
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

     [WIN_BASE] = LAYOUT_fullsize_iso(/* Base Layer */
                                                                                                                                                        KC_PC1, KC_PC2, KC_MUTE,
        KC_ESC,   KC_F1, KC_F2, KC_F3, KC_F4,    KC_F5, KC_F6, KC_F7, KC_F8,   KC_F9, KC_F10, KC_F11, KC_F12,  KC_TMODE,    KC_PSCR, KC_SCRL, KC_PAUS, 
        KC_GRV,  KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL,       KC_BSPC,     KC_INS, KC_HOME, KC_PGUP,     TD(TD_NLCK_CALC), KC_PSLS, KC_PAST, KC_PMNS, 
        KC_TAB,     KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC,                KC_DEL, KC_END, KC_PGDN,     KC_P7, KC_P8, KC_P9, KC_PPLS, 
        KC_CAPS,  KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_NUHS,    KC_ENT,                                  KC_P4, KC_P5, KC_P6, 
        KC_LSFT,     KC_NUBS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,    KC_RSFT,              KC_UP,              KC_P1, KC_P2, KC_P3, KC_PENT, 
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,            KC_RALT,  MO(WIN_FN), KC_APP, KC_RCTL,    KC_LEFT, KC_DOWN, KC_RGHT,    KC_P0, KC_PDOT),

     [WIN_FN] = LAYOUT_fullsize_iso(/* Function Layer */
                                                                                                                                            KC_PC1, KC_PC2, RGB_MOD,
        _______,  KC_BRID, KC_BRIU, KC_TASK, KC_FLXP,  KC_DIC, KC_MSEL, KC_MPRV, KC_MPLY, KC_MNXT, KC_WHOM, KC_CALC,   KC_WSCH,  KC_TMODE,  KC_WBAK, KC_WFWD, KC_LOCK2, 
        DM_RSTP, DM_REC1, DM_REC2, DM_PLY1, DM_PLY2, _______, _______, _______, _______, _______, _______,   NK_OFF,  NK_ON,   RGB_TOG,   RGB_SAI, RGB_HUI, RGB_MOD,      KC_CALC, KC_ACL0, KC_ACL1, KC_ACL2,
        _______, KC_BTN1, KC_MS_U, KC_BTN2, INIT_3S, _______, _______, _______, _______, _______, _______, _______, _______,                 RGB_SAD, RGB_HUD, RGB_RMOD,     KC_BTN4, KC_MS_U, KC_BTN5, KC_WH_U,
        _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______,                                   KC_MS_L, KC_BTN3, KC_MS_R,
        _______, _______, KC_BTN4, KC_BTN3, KC_BTN5, _______, _______, _______, _______,  _______, _______, _______,           _______,            RGB_VAI,               KC_WH_L, KC_MS_D, KC_WH_R, KC_WH_D, 
        _______, KC_TGUI, _______,                             _______,                            _______,_______, _______,    KC_TPC,   RGB_SPD, RGB_VAD, RGB_SPI,      KC_BTN1,       KC_BTN2),

    [MAC_BASE] = LAYOUT_fullsize_iso(/* Layer 3 */
                                                                                                                                                                            KC_PC1, KC_PC2, KC_MUTE,
        KC_ESC,     KC_BRID, KC_BRIU, KC_MCTL, KC_SPLT, KC_SIRI, KC_DOND, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, KC_TMODE, KC_LPAD, KC_SCRL, KC_LOCK_, 
        KC_GRV,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,    KC_INS,  KC_HOME, KC_PGUP,     TD(TD_NLCK_CALC), KC_PSLS, KC_PAST, KC_PMNS, 
        KC_TAB,  KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,              KC_DEL,  KC_END,  KC_PGDN,     KC_P7,    KC_P8,    KC_P9,   KC_PPLS, 
        KC_CAPS, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,                                    KC_P4,    KC_P5,    KC_P6, 
        KC_LSFT, KC_NUBS, KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,    KC_DOT,  KC_SLSH,          KC_RSFT,             KC_UP,                KC_P1,    KC_P2,    KC_P3,   KC_PENT, 
        KC_LCTL, KC_LALT, KC_LGUI,                           KC_SPC,                             KC_RGUI,MO(MAC_FN),KC_RALT,KC_RCTL,    KC_LEFT, KC_DOWN, KC_RGHT,     KC_P0,              KC_PDOT),

    [MAC_FN]   = LAYOUT_fullsize_iso(/* Layer 4 */
                                                                                                                                                                            KC_PC1, KC_PC2, RGB_MOD,
        _______,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, KC_TMODE,  KC_F13, KC_F14, KC_F15, 
        DM_RSTP, DM_REC1, DM_REC2, DM_PLY1, DM_PLY2, _______, _______, _______, _______, _______, _______, NK_OFF,   NK_ON,  RGB_TOG,    RGB_SAI, RGB_HUI, RGB_MOD,     KC_CALC, KC_ACL0, KC_ACL1, KC_ACL2, 
        _______, KC_BTN1, KC_MS_U, KC_BTN2, INIT_3S, _______, _______, _______, _______, _______, _______, _______, _______,                RGB_SAD, RGB_HUD, RGB_RMOD,    KC_BTN4, KC_MS_U, KC_BTN5, KC_WH_U, 
        _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                                   KC_MS_L, KC_BTN3, KC_MS_R, 
        _______, _______, KC_BTN4, KC_BTN3, KC_BTN5, _______, _______, _______, _______, _______, _______, _______,          _______,             RGB_VAI,              KC_WH_L, KC_MS_D, KC_WH_R, KC_WH_D,  
        _______, _______, KC_TGUI,                         _______,                               _______, _______, _______,  KC_TPC,    RGB_SPD, RGB_VAD, RGB_SPI,     KC_BTN1,       KC_BTN2)
        };

//-----------------------------------------------------------------

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [WIN_FN]   = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [MAC_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [MAC_FN]   = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) }
};

 //-----------------------------------------------------------------------------

#define HCS(report) host_consumer_send(record->event.pressed ? report : 0); return false
#define HSS(report) host_system_send(record->event.pressed ? report : 0); return false

static bool win_key_locked = false;

 static uint8_t mac_keycode[4] = {KC_LOPT, KC_ROPT, KC_LCMD, KC_RCMD};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    finished_timer = true;

    switch (keycode) {
        case INIT_3S:
            if (record->event.pressed){
                INIT3S_timer = timer_read();
                INIT3S_on    = true;
            }
            else{
                INIT3S_on   = false;           
            }
            break;

        case KC_TGUI:
            if (record->event.pressed) { // Toggle GUI lock on key press
                win_key_locked = !win_key_locked;
                writePin(LED_WIN_LOCK_PIN, !win_key_locked);

                if (win_key_locked){                // LED를 Win키에 표시
                    isWinLock = true;               //
                    isWinLockLedOn = true;          //
                    WinLock_timer  = timer_read();  //
                }                                   //
                else {                              //
                    isWinLock = false;              //
                    isWinLockLedOn = false;         //
                }                                   //
            }
            break;
            
        case KC_LGUI:
            if (win_key_locked) { return false; }
            else{ return true; }

        case KC_MISSION_CONTROL:
            if (record->event.pressed) host_consumer_send(0x29F);
            else  host_consumer_send(0);
            return false; // Skip all further processing of this key
        case KC_LAUNCHPAD:
            if (record->event.pressed)  host_consumer_send(0x2A0);
            else   host_consumer_send(0);
            return false; // Skip all further processing of this key

        case KC_SPOTLIGHT:
            HCS(0x221);
        case KC_DICTATION:
            HCS(0xCF);
        case KC_DO_NOT_DISTURB:
            HSS(0x9B);
        case KC_LOCK_SCREEN:
            HCS(0x19E);

        case KC_LOPTN:
        case KC_ROPTN:
        case KC_LCMMD:
        case KC_RCMMD:
            if (record->event.pressed) {
                register_code(mac_keycode[keycode - KC_LOPTN]);
            } else {
                unregister_code(mac_keycode[keycode - KC_LOPTN]);
            }
            return false; // Skip all further processing of this key

        case KC_WIN_MODE:
            writePinHigh(LED_MR_LOCK_PIN);
            set_single_persistent_default_layer(0);
            isMacMode = false;
            return false;

        case KC_MAC_MODE:
            writePinLow(LED_MR_LOCK_PIN);
            set_single_persistent_default_layer(2);
            isMacMode = true;            
            return false;

        case KC_TMODE:
            if (record->event.pressed) {
                switch (get_highest_layer(layer_state|default_layer_state)) {
                    case 0:
                    case 1:
                        writePinLow(LED_MR_LOCK_PIN);
                        set_single_persistent_default_layer(2);
                        isMacMode = true;                        
                        break;
                    case 2:
                    case 3:
                    default:
                        writePinHigh(LED_MR_LOCK_PIN);
                        set_single_persistent_default_layer(0);
                        isMacMode = false;                    
                }
            }
            return false;

        case KC_PC1:
            if (record->event.pressed) { // Toggle GUI lock on key press
                if (kvm_pc_sel) {
                    kvm_pc_sel = 0;
                    kvm_switch(0);

                    user_config.eeprom_kvm_pc_sel = kvm_pc_sel; // 
                    eeconfig_update_user(user_config.raw); // Writes the new status to EEPROM                    
                }
            }
                return false;            

        case KC_PC2:
            if (record->event.pressed) { // Toggle GUI lock on key press
                if (!kvm_pc_sel){
                    kvm_pc_sel = 1;
                    kvm_switch(1);     

                    user_config.eeprom_kvm_pc_sel = kvm_pc_sel; // 
                    eeconfig_update_user(user_config.raw); // Writes the new status to EEPROM        
                }
                return false;
            }
            else {
                return true;
            }
        case KC_TPC:
            if (record->event.pressed) { // Toggle GUI lock on key press
                kvm_pc_sel = !kvm_pc_sel;                   
                if (kvm_pc_sel) kvm_switch(1);
                else kvm_switch(0);
            
                user_config.eeprom_kvm_pc_sel = kvm_pc_sel; // 
                eeconfig_update_user(user_config.raw); // Writes the new status to EEPROM 
            }
            return false;             

        case QK_BOOT:
            if (record->event.pressed) {
                #ifdef OLED_ENABLE
                    bootloader_mode = true;
                    finished_timer  = false;
                    return false;   
                #else
                    return true;
                #endif
            }
            return true; 

        default:
            return true;   // Process all other keycodes normally        
    }

    return true;
}
//-----------------------------------------------------------------------------

bool isRecording = false;           // dynamic macro LED
bool isRecordingLedOn = false;
static uint16_t recording_timer;

//---------------------------
void matrix_scan_user(void) {
    
    if (kvm_sel_on == true){
        if (timer_elapsed(kvm_timer) > kvm_deadtime ) {
            writePinHigh(GPIO_KM_PWEN);
            kvm_sel_on = false;
        }
    }

    if (INIT3S_on == true){
        if (timer_elapsed(INIT3S_timer) > 3000){
            INIT3S_on = false;
            INIT3S_led_on = true;
            
            INIT3S_timer = timer_read();
            // eeconfig_init();
            // //  eeconfig_init_user();
            // soft_reset_keyboard();
        }
    }
    if (INIT3S_led_on == true){
        if(timer_elapsed(INIT3S_timer) > 2000){

            // INIT3S_on = false;
            // INIT3S_led_on = true;
            eeconfig_init();
            //  eeconfig_init_user();
            soft_reset_keyboard();
        }
    }

    if (isRecording){
        if(timer_elapsed(recording_timer) > 500)
        {
            isRecordingLedOn = !isRecordingLedOn;
            recording_timer  = timer_read();
            writePin(LED_WIN_LOCK_PIN, !isRecordingLedOn); 
        }
    }
    else{   
    }
}

// void dynamic_macro_record_start_user(void) {        
void dynamic_macro_record_start_user(int8_t direction) {   // Ver 0.21.6에서 변경
    isRecording = true;
    isRecordingLedOn = true;
                writePin(LED_WIN_LOCK_PIN, !isRecordingLedOn); 

    recording_timer = timer_read();
}
void dynamic_macro_record_end_user(int8_t direction)
{
    isRecording = false;
    isRecordingLedOn = false;
}

//---------------------------------------------------------------------------
#ifdef RGB_MATRIX_ENABLE

// __attribute__ ((weak)) 
bool rgb_matrix_indicators_user(void)  {

    uint8_t layer = get_highest_layer(layer_state|default_layer_state);

    if (INIT3S_led_on == true){
        rgb_matrix_set_color_all(0xff, 0, 0);
            // eeconfig_init();
            // //  eeconfig_init_user();
            // soft_reset_keyboard();        
    }


    if (isWinLock){         // WIN key Lock LED Blink
        if(timer_elapsed(WinLock_timer) > 1000){
            isWinLockLedOn = !isWinLockLedOn;
            WinLock_timer  = timer_read();
        }
        if (isWinLockLedOn) {
            if (isMacMode) rgb_matrix_set_color(100, 0x40, 0, 0);
            else  rgb_matrix_set_color(99, 0x40, 0, 0);
        }
    }

    if (isRecordingLedOn) {                 // Dynamic Macro Recording LED Blink 
        rgb_matrix_set_color(38, 0x40, 0x0, 0x40);            
    }
    if (bootloader_mode) { 
        rgb_matrix_set_color(0, 0x40, 0x0, 0x40);            
    }


// rgb_matrix_set_color(pgm_read_byte(&convert_led_location2number[11]),  RGB_RED);         //  RGB_TOG  <- too heavy.
    switch (layer) {
        case 0:
        case 1:
            if (kvm_pc_sel)  rgb_matrix_set_color(103,0,0,40);
            else            rgb_matrix_set_color(101,0,0,40);
            break;   

        case 2:
        case 3:
            if (kvm_pc_sel)  rgb_matrix_set_color(103,40,0,0);
            else            rgb_matrix_set_color(101,40,0,0);
            break;          
    }
    return TRUE;
}

#endif
