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

//#define KC_TASK KC_TASK_VIEW
//#define KC_FLXP KC_FILE_EXPLORER
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
// void dance_test(qk_tap_dance_state_t *state, void *user_data){
void dance_test(tap_dance_state_t *state, void *user_data){    // Ver 0.21.6에서 변경
    if(state->count >=5){
        SEND_STRING("Tap Dance Test ok!");
        reset_tap_dance(state);
    }
}
// Tapdance definitions. Tap Dance F Keys.
// qk_tap_dance_action_t tap_dance_actions[] = {
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
    // while (timer_elapsed(kvm_timer) < 1000) {
    // }
    // writePinHigh(GPIO_KM_PWEN);
// 키보드 리셋이 필요
};

void keyboard_pre_init_user(void) {
    // kvm_pc_sel = 0;
    // kvm_switch(kvm_pc_sel);
};
//------------------------------------------
void keyboard_post_init_user(void) {
    // Read the user config from EEPROM
    // kvm_pc_sel = 0;
    // kvm_switch(kvm_pc_sel);

    user_config.raw = eeconfig_read_user();
    kvm_pc_sel      = user_config.eeprom_kvm_pc_sel;
    kvm_switch(kvm_pc_sel);
}

// void eeconfig_init_user(void) {  // EEPROM is getting reset!
//   user_config.raw = 0;
//   // user_config.rgb_layer_change = true; // We want this enabled by default
//   eeconfig_update_user(user_config.raw); // Write default value to EEPROM now
// }

//-------------------------------------------------------------------------------------------------------
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap _BASE: Base Layer (Default Layer)
      * ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
      * │Esc│   │F1 │F2 │F3 │F4 │ │F5 │F6 │F7 │F8 │ │F9 │F10│F11│F12│ │PSc│Slk│Pse│
      * └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘
      * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐ ┌───┬───┬───┬───┐
      * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp│ │Ins│Hom│PgU│ │Num│ / │ * │ - │
      * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤ ├───┼───┼───┼───┤
      * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │ │Del│End│PgD│ │ 7 │ 8 │ 9 │   │
      * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬┈┈┈┈┤ └───┴───┴───┘ ├───┼───┼───┤ + │
      * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ # │Entr│               │ 4 │ 5 │ 6 │   │
      * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤     ┌───┐     ├───┼───┼───┼───┤
      * │Shft│ \ │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │    Shift │     │ ↑ │     │ 1 │ 2 │ 3 │   │
      * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤ ┌───┼───┼───┐ ├───┴───┼───┤Ent│
      * │Ctrl│GUI │Alt │                        │ Alt│Func│ App│Ctrl│ │ ← │ ↓ │ → │ │   0   │ . │   │
      * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘ └───────┴───┴───┘
        KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,     KC_PSCR, KC_SCRL, KC_PAUS,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,    KC_INS,  KC_HOME, KC_PGUP,  TD(TD_NLCK_CALC),KC_PSLS,KC_PAST,KC_PMNS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,    KC_DEL,  KC_END,  KC_PGDN,    KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        RALT_T(KC_CAPS), KC_A, KC_S, KC_D,   KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,                                  KC_P4,   KC_P5,   KC_P6,
        OSM(MOD_LSFT), KC_NUBS, KC_Z, KC_X, KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,             KC_UP,               KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        OSM(MOD_LCTL), OSM(MOD_LGUI), OSM(MOD_LALT),          KC_SPC,       KC_RALT, LT(WIN_FN,KC_TPC) or MO(WIN_FN),,KC_APP, KC_RCTL,    KC_LEFT, KC_DOWN, KC_RGHT,    KC_P0,            KC_PDOT
      */
     [WIN_BASE] = LAYOUT_all(/* Base Layer */
                                                                                                                                                        KC_PC1, KC_PC2, KC_MUTE,
        KC_ESC,   KC_F1, KC_F2, KC_F3, KC_F4,    KC_F5, KC_F6, KC_F7, KC_F8,   KC_F9, KC_F10, KC_F11, KC_F12,  KC_TMODE,    KC_PSCR, KC_SCRL, KC_PAUS, 
        KC_GRV,  KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL,       KC_BSPC,     KC_INS, KC_HOME, KC_PGUP,     TD(TD_NLCK_CALC), KC_PSLS, KC_PAST, KC_PMNS, 
        KC_TAB,     KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC,    KC_BSLS,     KC_DEL, KC_END, KC_PGDN,     KC_P7, KC_P8, KC_P9, KC_PPLS, 
        KC_CAPS,  KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_NUHS,    KC_ENT,                                  KC_P4, KC_P5, KC_P6, 
        KC_LSFT,     KC_NUBS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,    KC_RSFT,              KC_UP,              KC_P1, KC_P2, KC_P3, KC_PENT, 
        KC_LCTL, KC_LGUI, KC_LALT,                KC_SPC,       KC_RALT,  MO(WIN_FN), KC_APP, KC_RCTL,    KC_LEFT, KC_DOWN, KC_RGHT,    KC_P0, KC_PDOT),
    /* Keymap _FN: Function Layer
      * ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
      * │Firm   │Ply│Stp│Prv│Nxt│ │Mut│Vo+│Vo-│   │ │   │   │   │   │ │   │   │   │
      * └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘
      * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐ ┌───┬───┬───┬───┐
      * │   │   │   │   │   │   │   │   │   │   │   │   │   │       │ │   │   │   │ │   │   │   │   │
      * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤ ├───┼───┼───┼───┤
      * │     │   │   │   │   │   │   │   │   │   │   │   │   │     │ │   │   │   │ │   │   │   │   │
      * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬┈┈┈┈┤ └───┴───┴───┘ ├───┼───┼───┤   │
      * │      │   │   │   │   │   │   │   │   │   │   │   │   │    │               │   │   │   │   │
      * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤     ┌───┐     ├───┼───┼───┼───┤
      * │    │   │   │   │   │   │   │   │   │   │   │   │          │     │   │     │   │   │   │   │
      * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤ ┌───┼───┼───┐ ├───┴───┼───┤   │
      * │    │Lock│    │                        │    │Func│ Sys│    │ │   │   │   │ │       │   │   │
      * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘ └───────┴───┴───┘
                                파일탐색기  soso                                                                    OK       xxx        xxx        MAC        MAC     xxx        WIN      WIN     (WIN+H) (WIN+L)
                        win-tap   win-e  내PC              브라우져홈        플레이어 Previous   play     Next     검색_서치 컨트롤패널 런치어시스트 미션컨트롤 런치패드 Favorites     뒤로     앞으로  받아쓰기 계정잠금
    KC_BRID, KC_BRIU, KC_TASK, KC_FLXP, KC_MYCM, KC_MAIL, KC_WOME, KC_CALC, KC_MSEL, KC_MPRV, KC_MPLY, KC_MNXT,  KC_WSCH,   KC_CPNL, KC_ASST,  KC_MCTL, KC_LPAD,   KC_WFAV,   KC_WBAK,  KC_WFWD, KC_DIC, KC_LOCK2  
    TD(TD_2),TD(TD_5),KC_MPRV, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, KC_TASK,TD(TD_3),TD(TD_4), KC_BRIU, KC_BRID, 
    KC_BRID, KC_BRIU, KC_TASK, KC_FLXP,  KC_MYCM, KC_MSEL, KC_MPRV, KC_MPLY, KC_MNXT, KC_MAIL, KC_CALC,  KC_WSCH,   KC_WHOM, KC_WBAK,  KC_WFWD,     
*/
     [WIN_FN] = LAYOUT_all(/* Function Layer */
                                                                                                                                            KC_PC1, KC_PC2, RGB_MOD,
        _______,  KC_BRID, KC_BRIU, KC_TASK, KC_FLXP,  KC_DIC, KC_MSEL, KC_MPRV, KC_MPLY, KC_MNXT, KC_WHOM, KC_CALC,   KC_WSCH,  KC_TMODE,  KC_WBAK, KC_WFWD, KC_LOCK2, 
        DM_RSTP, DM_REC1, DM_REC2, DM_PLY1, DM_PLY2, _______, _______, _______, _______, _______, _______,   NK_OFF,  NK_ON,   RGB_TOG,   RGB_SAI, RGB_HUI, RGB_MOD,      KC_CALC, KC_ACL0, KC_ACL1, KC_ACL2,
        _______, KC_BTN1, KC_MS_U, KC_BTN2, INIT_3S, _______, _______, _______, _______, _______, _______, _______, _______,  _______,    RGB_SAD, RGB_HUD, RGB_RMOD,     KC_BTN4, KC_MS_U, KC_BTN5, KC_WH_U,
        _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______,                                   KC_MS_L, KC_BTN3, KC_MS_R,
        _______, _______, KC_BTN4, KC_BTN3, KC_BTN5, _______, _______, _______, _______,  _______, _______, _______,           _______,            RGB_VAI,               KC_WH_L, KC_MS_D, KC_WH_R, KC_WH_D, 
        _______, KC_TGUI, _______,                             _______,                            _______,_______, _______,    KC_TPC,   RGB_SPD, RGB_VAD, RGB_SPI,      KC_BTN1,       KC_BTN2),
/*                 
                                        미션컨트롤 스포트라이트 딕테이션 Xdisturb                                                        LAUNCHPAD         lock-screen
                        KC_BRID, KC_BRIU, KC_MCTL, KC_SPLT, KC_SIRI, KC_DOND, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU,    KC_LPAD, KC_SCRL, KC_LOCK_,
                                                            KC_DIC(WIN+H)                                                                               KC_LOCK2(WIN+L)
*/
    [MAC_BASE] = LAYOUT_all(/* Layer 3 */
                                                                                                                                                                            KC_PC1, KC_PC2, KC_MUTE,
        KC_ESC,     KC_BRID, KC_BRIU, KC_MCTL, KC_SPLT, KC_SIRI, KC_DOND, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, KC_TMODE, KC_LPAD, KC_SCRL, KC_LOCK_, 
        KC_GRV,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,    KC_INS,  KC_HOME, KC_PGUP,     TD(TD_NLCK_CALC), KC_PSLS, KC_PAST, KC_PMNS, 
        KC_TAB,  KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,    KC_DEL,  KC_END,  KC_PGDN,     KC_P7,    KC_P8,    KC_P9,   KC_PPLS, 
        KC_CAPS, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,                                    KC_P4,    KC_P5,    KC_P6, 
        KC_LSFT, KC_NUBS, KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,    KC_DOT,  KC_SLSH,          KC_RSFT,             KC_UP,                KC_P1,    KC_P2,    KC_P3,   KC_PENT, 
        KC_LCTL, KC_LALT, KC_LGUI,                           KC_SPC,                             KC_RGUI,MO(MAC_FN),KC_RALT,KC_RCTL,    KC_LEFT, KC_DOWN, KC_RGHT,     KC_P0,              KC_PDOT),

    [MAC_FN]   = LAYOUT_all(/* Layer 4 */
                                                                                                                                                                            KC_PC1, KC_PC2, RGB_MOD,
        _______,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, KC_TMODE,  KC_F13, KC_F14, KC_F15, 
        DM_RSTP, DM_REC1, DM_REC2, DM_PLY1, DM_PLY2, _______, _______, _______, _______, _______, _______, NK_OFF,   NK_ON,  RGB_TOG,    RGB_SAI, RGB_HUI, RGB_MOD,     KC_CALC, KC_ACL0, KC_ACL1, KC_ACL2, 
        _______, KC_BTN1, KC_MS_U, KC_BTN2, INIT_3S, _______, _______, _______, _______, _______, _______, _______, _______, _______,    RGB_SAD, RGB_HUD, RGB_RMOD,    KC_BTN4, KC_MS_U, KC_BTN5, KC_WH_U, 
        _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                                   KC_MS_L, KC_BTN3, KC_MS_R, 
        _______, _______, KC_BTN4, KC_BTN3, KC_BTN5, _______, _______, _______, _______, _______, _______, _______,          _______,             RGB_VAI,              KC_WH_L, KC_MS_D, KC_WH_R, KC_WH_D,  
        _______, _______, KC_TGUI,                         _______,                               _______, _______, _______,  KC_TPC,    RGB_SPD, RGB_VAD, RGB_SPI,     KC_BTN1,       KC_BTN2)
        };

//-----------------------------------------------------------------
#ifdef JOYSTICK_ENABLE
    joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    //    [0] = JOYSTICK_AXIS_IN_OUT(C3, B8, 900, 575, 285), 
    //    [0] = JOYSTICK_AXIS_IN(A0, 256, 512, 700),
        [0] = JOYSTICK_AXIS_VIRTUAL,
        [1] = JOYSTICK_AXIS_VIRTUAL    
    };

    static bool precision = false;
    static uint16_t precision_mod = 1023;
    static uint16_t axis_val = 2047;
#endif
//-----------------------------------------------------------------
//#if defined(VIA_ENABLE) && defined(ENCODER_ENABLE)
#ifdef ENCODER_MAP_ENABLE

// #define NUM_ENCODERS 2
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [WIN_FN]   = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [MAC_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [MAC_FN]   = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) }
};
//#endif

// bool encoder_update_user(uint8_t index, bool clockwise) {

//     if (index == 0) {
//         if (IS_LAYER_ON(WIN_FN)) {
//             if (clockwise) {
//                 tap_code_delay(KC_P8, 10);
//             } else {
//                 tap_code_delay(KC_P2, 10);
//             }
//         }
//         else {
//             if (clockwise) {
//                 tap_code_delay(KC_VOLU, 10);
//             } else {
//                 tap_code_delay(KC_VOLD, 10);
//             }
//         }
//     }
//     return false;
// }
//---------------------------
#else /////defined(VIA_ENABLE) && defined(ENCODER_ENABLE)  or #ifndef ENCODER_MAP_ENABLE

#define ENCODERS 1
static uint8_t  encoder_state[ENCODERS] = {0};
static keypos_t encoder_cw[ENCODERS]    = {{3, 5}};     // key matrix K53
static keypos_t encoder_ccw[ENCODERS]   = {{1, 5}};     // key matrix K51

void encoder_action_unregister(void) {
    for (int index = 0; index < ENCODERS; ++index) {
        if (encoder_state[index]) {
            keyevent_t encoder_event = (keyevent_t){
                .key = encoder_state[index] >> 1 ? encoder_cw[index] : encoder_ccw[index],
                .pressed = false,
                .time = (timer_read() | 1)
            };
            encoder_state[index]     = 0;
            action_exec(encoder_event);
        }
    }
}

void encoder_action_register(uint8_t index, bool clockwise){
    keyevent_t encoder_event = (keyevent_t){
        .key = clockwise ? encoder_cw[index] : encoder_ccw[index],
        .pressed = true,
        .time = (timer_read() | 1)
    };
    encoder_state[index] = (clockwise ^ 1) | (clockwise << 1);
    action_exec(encoder_event);
}

bool encoder_update_user(uint8_t index, bool clockwise) {

    encoder_action_register(index, clockwise);
    return false;
}

void matrix_scan_user(void) {
    
    encoder_action_unregister();
}
#endif///// end of defined(VIA_ENABLE) && defined(ENCODER_ENABLE)
 //-----------------------------------------------------------------------------

#define HCS(report) host_consumer_send(record->event.pressed ? report : 0); return false
#define HSS(report) host_system_send(record->event.pressed ? report : 0); return false

static bool win_key_locked = false;
// static bool all_key_locked = false;

 static uint8_t mac_keycode[4] = {KC_LOPT, KC_ROPT, KC_LCMD, KC_RCMD};

// typedef struct PACKED {
//     uint8_t len;
//     uint8_t keycode[2];
// } key_combination_t;

// key_combination_t key_comb_list[2] = {
//     {2, {KC_LWIN, KC_TAB}},
//     {2, {KC_LWIN, KC_E}}
// };

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    finished_timer = true;

#ifdef JOYSTICK_ENABLE
    int16_t precision_val = axis_val;
    if (precision) {
        precision_val -= precision_mod;
    }    
#endif 

    switch (keycode) {
        case INIT_3S:
            if (record->event.pressed){
                INIT3S_timer = timer_read();
                INIT3S_on    = true;
                // return false;
            }
            else{
                INIT3S_on   = false;
                // return false;              
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

        // case KC_TASK_VIEW:
        // case KC_FILE_EXPLORER:
        //     if (record->event.pressed) {
        //         for (uint8_t i = 0; i < key_comb_list[keycode - KC_TASK_VIEW].len; i++) {
        //             register_code(key_comb_list[keycode - KC_TASK_VIEW].keycode[i]);
        //         }
        //     } else {
        //         for (uint8_t i = 0; i < key_comb_list[keycode - KC_TASK_VIEW].len; i++) {
        //             unregister_code(key_comb_list[keycode - KC_TASK_VIEW].keycode[i]);
        //         }
        //     }
        //     return false;  // Skip all further processing of this key

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

        // case KC_TKEY:                        // 전체키 input off -> 좀 더  손을 봐야 함 위에 나열한 키는 입력이 되며, FN키는 동작되게 해야 할듯함
        //     if (record->event.pressed){
        //         all_key_locked = !all_key_locked;
        //         writePin(LED_MR_LOCK_PIN, !all_key_locked);
        //     }
        //     break;
        // default:
        //     if (all_key_locked) { return false; }

                    // case AS_ON:
                    //     //on_mr_leds();
                    //     writePinLow(LED_MR_LOCK_PIN);
                    //     return true; 
                    // case AS_OFF:
                    //     //off_mr_leds();                    
                    //     writePinHigh(LED_MR_LOCK_PIN);
                    //     return true; 
        case KC_PC1:
            if (record->event.pressed) { // Toggle GUI lock on key press
                        // writePinHigh(LED_MR_LOCK_PIN);
                if (kvm_pc_sel) {
                    kvm_pc_sel = 0;
                    kvm_switch(0);

                    user_config.eeprom_kvm_pc_sel = kvm_pc_sel; // 
                    eeconfig_update_user(user_config.raw); // Writes the new status to EEPROM                    
                }
            }
                return false;            
//           else {
//                return true;
//            }
        case KC_PC2:
            if (record->event.pressed) { // Toggle GUI lock on key press
                    // writePinLow(LED_MR_LOCK_PIN);
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
                // if (kvm_pc_sel) writePinLow(LED_MR_LOCK_PIN);
                // else                        writePinHigh(LED_MR_LOCK_PIN);                
                user_config.eeprom_kvm_pc_sel = kvm_pc_sel; // 
                eeconfig_update_user(user_config.raw); // Writes the new status to EEPROM 
            }
            return false;             
            // else {
            //     return true;
            // }

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

#ifdef JOYSTICK_ENABLE
        case KC_P8:
            joystick_set_axis(1, record->event.pressed ? -precision_val : 0);
            return false;
        case KC_P2:
            joystick_set_axis(1, record->event.pressed ? precision_val : 0);
            return false;
        case KC_P4:
            joystick_set_axis(0, record->event.pressed ? -precision_val : 0);
            return false;
        case KC_P6:
            joystick_set_axis(0, record->event.pressed ? precision_val : 0);
            return false;
        case KC_P0:
            precision = record->event.pressed;
            return false;
#endif

        default:
            return true;   // Process all other keycodes normally        
    }

    return true;
}
//-----------------------------------------------------------------------------

bool isRecording = false;           // dynamic macro LED
bool isRecordingLedOn = false;
static uint16_t recording_timer;

#ifdef AUTO_SHIFT_ENABLE
    bool isAutoShiftOn = false;         // AutoShift function LED
    bool AutoShiftLED  = false;
    static uint16_t AutoShift_timer;
#endif

//static bool win_key_locked = false;
//extern static bool win_key_locked;

#ifdef LEADER_ENABLE
    LEADER_EXTERNS();
#endif

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


#ifdef LEADER_ENABLE
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        SEQ_ONE_KEY(KC_D) {
            SEND_STRING("Metable K310 STD");
    //        did_leader_succeed = true;
        }
        SEQ_TWO_KEYS(KC_P, KC_1) {
            SEND_STRING("Durgod Keyboard");
    //        did_leader_succeed = true;
        }
        SEQ_TWO_KEYS(KC_P, KC_2) {
            SEND_STRING("Forida Multi Hub");
    //        did_leader_succeed = true;
        } 
        SEQ_THREE_KEYS(KC_C, KC_C, KC_C) {
            SEND_STRING("Metable is GREAT!!!");
        }
        SEQ_FOUR_KEYS(KC_F, KC_I, KC_R, KC_M) {
            bootloader_jump();
        }
        SEQ_FIVE_KEYS(KC_R, KC_E, KC_S, KC_E, KC_T) {
            SEND_STRING("ReBoot!!");
            soft_reset_keyboard();      // reset_keyboard()
        }
    }
#endif

#ifdef AUTO_SHIFT_ENABLE     
    if (get_autoshift_state()){
        if(isAutoShiftOn){
            if(timer_elapsed(AutoShift_timer) >500){
                AutoShift_timer = timer_read();
                AutoShiftLED    = !AutoShiftLED;
                writePin(LED_MR_LOCK_PIN, !AutoShiftLED);
            }
        }
        else{
            isAutoShiftOn = true;
            AutoShift_timer = timer_read();
            AutoShiftLED    = true;
            writePin(LED_MR_LOCK_PIN, !AutoShiftLED);
        }
    }
    else{
        isAutoShiftOn = false;
        switch (get_highest_layer(default_layer_state)) {    // default_layer_state -> FN layer는 체크되지 않는 문제 
            case WIN_BASE:    
            case WIN_FN:                                // Booting떄 초기화루틴에서는 잘못 가져옴
                writePinHigh(LED_MR_LOCK_PIN);
                break;
            case MAC_BASE:
            case MAC_FN:        
                writePinLow(LED_MR_LOCK_PIN);
            break;
        }
    }
#endif

    if (isRecording){
        if(timer_elapsed(recording_timer) > 500)
        {
            isRecordingLedOn = !isRecordingLedOn;
            recording_timer  = timer_read();
            writePin(LED_WIN_LOCK_PIN, !isRecordingLedOn); 
        }
    }
    else{
//            writePin(LED_WIN_LOCK_PIN, !win_key_locked);       
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
//----------------------------------

void leader_start_user(void){
//    writePinLow(LED_MR_LOCK_PIN); //동작안함
}

void leader_end_user(void){
//    writePinHigh(LED_MR_LOCK_PIN); //동작안함
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
//---------------------------------------------------------------------------

#ifdef OLED_ENABLE

// uint16_t startup_timer;
// static bool finished_timer = false;

static const char logo_MS[] = {0x97,0x98,0x00, 0xB7,0xB8,0x00}; 
static const char logo_APPLE[] = {0x95,0x96,0x00, 0xB5,0xB6,0x00};
static const char logo_Linux[] = {0x99,0x9A,0x00, 0xB9,0xBA,0x00}; 

// void init_timer(void){
//    startup_timer = timer_read32();
// };

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    startup_timer = timer_read();
    return rotation;                    //    return OLED_ROTATION_180; // flips the display 180 degrees if offhand 
}

// static void render_logo(void) {
//     static const char PROGMEM raw_logo[] = {
//         240,248,252,252,254,254,222,206,238,238,238,238,238,206,206, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,254,254,252,252,248,248,  0,  0,  0,  0, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,  0,  0,  0,  0,254,254,254,254,254,254,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
//         0,254,254,254,254,254,254,255,255,255,255,255,255,  1,  1,  1,  3,  3,  3,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,255,255,255,  0,  0,  0,  0, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 24,  0,  0,  0,  0,255,255,255,255,255,255, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56,
//         60,255,255,255,255,255,255, 31, 63, 63,127,127,127,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,127,127,127,127, 31, 31,  0,  0,  0,  0,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112, 96, 96,  0,  0,  0, 
//         0,127,127,127,127,127,127,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,127,127,127,127,127,127,
//     };
//     oled_write_raw_P(raw_logo, sizeof(raw_logo));
// }

// static void render_logo(void) {     // logo 1
//     static const char PROGMEM raw_logo[] = {
//         0,  0,  0,  0,  0,  0,240,248, 24, 24, 24, 24, 24,248,248, 24, 24, 24, 24, 24,240,224,  0,240,240, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,  0, 24, 24, 24, 24, 24, 24, 24,248,248, 24, 24, 24, 24, 24, 24, 24,  0,240,240, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,248,240,  0,248,248, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,240,240,  0,240,248,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,224,240, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,  0,  0,  0,  0,  0,  0,  0,  0,
//         0,  0,  0,  0, 63, 63,  0,  0,  0,  0,  0, 63, 63,  0,  0,  0,  0,  0, 63, 63,  0, 63, 63, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35,  0,  0,  0,  0,  0,  0,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0, 63, 63,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3, 63, 63,  0, 63, 63, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 63, 63,  0, 63, 63, 32, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48,  0, 31, 63, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35,  0,  0,  0,  0,  0,  0,
//     };
//     oled_write_raw_P(raw_logo, sizeof(raw_logo));
// }

static void render_logo_font(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };
    oled_write_P(qmk_logo, false);
}

void render_info(void){

    oled_set_cursor(0, 0);
//     oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state|default_layer_state)) {
        case WIN_BASE:
            oled_write_P(logo_MS, false);
            oled_write_P(PSTR(" Layer: WINdows\n"), false);    
            oled_write_P(logo_MS+3, false);      
            oled_write_ln_P(PSTR(" ---------------"), false);       // oled_write_ln_P 함수 테스트
            break;
        case WIN_FN:
            oled_write_P(logo_MS, false);        
            oled_write_P(PSTR(" Layer: WIN-FN\n"), false);
            break;
        case MAC_BASE:
            oled_write_P(logo_APPLE, false);
            oled_write_P(PSTR(" Layer: MACintosh\n"), false);
            oled_write_P(logo_APPLE+3, false);        
            oled_write_P(PSTR(" ---------------\n"), false);         
            break;
        case MAC_FN:
            oled_write_P(logo_APPLE, false);        
            oled_write_P(PSTR(" Layer: MAC-FN\n"), false);
            break;

        // case LINUX_BASE:
        //     oled_write_P(logo_Linux, false);
        //     oled_write_P(PSTR(" Layer: Linux\n"), false);
        //     oled_write_P(logo_Linux+3, false);        
        //     oled_write_P(PSTR(" ---------------\n"), false);         
        //     break;
        // case LINUX_FN:
        //     oled_write_P(logo_Linux, false);        
        //     oled_write_P(PSTR(" Layer: Linux-FN\n"), false);
        //     break;            
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("error?"), false);
    }
//    oled_write_P(PSTR("---------------\n"), false);
      oled_set_cursor(3, 2);   
    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM  ") : PSTR("     "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP  ") : PSTR("     "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR  ") : PSTR("     "), false);
}
//---------------------------------------
static void render_rgbled_status(void) {
    char string[4];

    oled_set_cursor(0, 3);
    if (rgb_matrix_is_enabled()) {
        oled_write("RGB", true);    
        uint16_t m = rgb_matrix_get_mode();
        string[3] = '\0';
        string[2] = '0' + m % 10;
        string[1] = ( m /= 10) % 10 ? '0' + (m) % 10 : (m / 10) % 10 ? '0' : ' ';
        string[0] =  m / 10 ? '0' + m / 10 : ' ';
        oled_write_P(PSTR(" -"), false);
        oled_write(string, false);

        uint16_t h = rgb_matrix_get_hue()/RGBLIGHT_HUE_STEP;
        string[3] = '\0';
        string[2] = '0' + h % 10;
        string[1] = ( h /= 10) % 10 ? '0' + (h) % 10 : (h / 10) % 10 ? '0' : ' ';
        string[0] =  h / 10 ? '0' + h / 10 : ' ';
        oled_write_P(PSTR(","), false);
        oled_write(string, false);

        uint16_t s = rgb_matrix_get_sat()/RGBLIGHT_SAT_STEP;
        string[3] = '\0';
        string[2] = '0' + s % 10;
        string[1] = ( s /= 10) % 10 ? '0' + (s) % 10 : (s / 10) % 10 ? '0' : ' ';
        string[0] =  s / 10 ? '0' + s / 10 : ' ';
        oled_write_P(PSTR(","), false);
        oled_write(string, false);

        uint16_t v = rgb_matrix_get_val()/RGBLIGHT_VAL_STEP;
        string[3] = '\0';
        string[2] = '0' + v % 10;
        string[1] = ( v /= 10) % 10 ? '0' + (v) % 10 : (v / 10) % 10 ? '0' : ' ';
        string[0] =  v / 10 ? '0' + v / 10 : ' ';
        oled_write_P(PSTR(","), false);
        oled_write(string, false);
        // oled_write_ln_P(PSTR("\n     MOD HUE SAT VAR"), false);
    } else {
        oled_write_P(PSTR("RGB off , WPM = "), false);
            oled_write(get_u8_str(get_current_wpm(), '0'), false);  //예제 키보드= adpenrose-akemipad
    }

#ifndef  OLED_DISPLAY_128X64
    return;
#endif

    oled_set_cursor(0, 4);
    oled_rgb_mode();
}

// 참고키보드 = 0xcb-1377, 0xcb-STATIC, adafruit-macropad
bool oled_task_user(void) {

    if (bootloader_mode){
            if (!finished_timer){
                on_all_leds();
                oled_clear();                    //
                render_logo_font();
                oled_scroll_off();
                oled_set_cursor(3, 3); 
                oled_write_P(PSTR("Firmware Update\n"), false);
                finished_timer = true;
                startup_timer = timer_read();
            }
            else if(timer_elapsed(startup_timer) > 500) { 
                bootloader_jump();                          // reset_keyboard();
            }
    }
    else if(!finished_timer && (timer_elapsed(startup_timer) < 20000)) {
//        render_logo();
        render_logo_font();  
        oled_set_cursor(5, 3); 
        oled_write_P(PSTR("K310 RGB QMK\n"), false);        
//        oled_scroll_left(); // Turns on scrolling      // scroll하면 아래로 안감? oled_scroll_off();을 먼저해야 함
    } else {
        if (!finished_timer){
//            oled_scroll_off();
            oled_clear();
            finished_timer = true;
        }
        render_info();
        oled_scroll_off();        
        render_rgbled_status();
    }
    return false;
}

// 1upkeyboard-pi40

void oled_rgb_mode(){
    switch (rgb_matrix_get_mode()) {
        case 1:
            oled_write_P(PSTR("Solid Color\n                  "), false);
            break;
        case 2:
            oled_write_P(PSTR("Alphas Mods\n                  "), false);
            break;
        case 3:
            oled_write_P(PSTR("Gradient Up Down\n                  "), false);
            break;
        case 4:
            oled_write_P(PSTR("Gradient Left Right\n                  "), false);
            break;
        case 5:
            oled_write_P(PSTR("Breathing\n                  "), false);
            break;
        case 6:
            oled_write_P(PSTR("Band Sat\n                  "), false);
            break;
        case 7:
            oled_write_P(PSTR("Band Val\n                  "), false);
            break;
        case 8:
            oled_write_P(PSTR("Band Pinwheel Sat\n                  "), false);
            break;
        case 9:
            oled_write_P(PSTR("Band Pinwheel Val\n                  "), false);
            break;
        case 10:
            oled_write_P(PSTR("Band Spiral Sat\n                  "), false);
            break;
        case 11:
            oled_write_P(PSTR("Band Spiral Val\n                  "), false);
            break;
        case 12:
            oled_write_P(PSTR("Cycle All\n                  "), false);
            break;
        case 13:
            oled_write_P(PSTR("Cycle Left Right\n                  "), false);
            break;
        case 14:
            oled_write_P(PSTR("Cycle Up Down\n                  "), false);
            break;
        case 15:
            oled_write_P(PSTR("Rainbow\nMoving Chevron    "), false);
            break;
        case 16:
            oled_write_P(PSTR("Cycle Out In\n                  "), false);
            break;
        case 17:
            oled_write_P(PSTR("Cycle Out In Dual\n                  "), false);
            break;
        case 18:
            oled_write_P(PSTR("Cycle Pinwheel\n                  "), false);
            break;
        case 19:
            oled_write_P(PSTR("Cycle Spiral\n                  "), false);
            break;
        case 20:
            oled_write_P(PSTR("Dual Beacon\n                  "), false);
            break;
        case 21:
            oled_write_P(PSTR("Rainbow Beacon\n                  "), false);
            break;
        case 22:
            oled_write_P(PSTR("Rainbow Pinwheels\n                  "), false);
            break;
        case 23:
            oled_write_P(PSTR("Raindrops\n                  "), false);
            break;
        case 24:
            oled_write_P(PSTR("Jellybean Raindrops\n                  "), false);
            break;
        case 25:
            oled_write_P(PSTR("Hue Breathing\n                  "), false);
            break;
        case 26:
            oled_write_P(PSTR("Hue Pendulum\n                  "), false);
            break;
        case 27:
            oled_write_P(PSTR("Hue Wave\n                  "), false);
            break;
        case 28:
            oled_write_P(PSTR("Pixel Rain\n                  "), false);
            break;
        case 29:
            oled_write_P(PSTR("Pixel Flow\n                  "), false);
            break;
        case 30:
            oled_write_P(PSTR("Pixel Fractal\n                  "), false);
            break;
        case 31:
            oled_write_P(PSTR("Typing Heatmap\n                  "), false);
            break;
        case 32:
            oled_write_P(PSTR("Digital Rain\n                  "), false);
            break;
        case 33:
            oled_write_P(PSTR("Solid Reactive\nSimple            "), false);
            break;
        case 34:
            oled_write_P(PSTR("Solid Reactive\n                  "), false);
            break;
        case 35:
            oled_write_P(PSTR("Solid Reactive\nWide              "), false);
            break;
        case 36:
            oled_write_P(PSTR("Solid Reactive\nMultiwide         "), false);
            break;
        case 37:
            oled_write_P(PSTR("Solid Reactive\nCross             "), false);
            break;
        case 38:
            oled_write_P(PSTR("Solid Reactive\nMulticross        "), false);
            break;
        case 39:
            oled_write_P(PSTR("Solid Reactive\nNexus             "), false);
            break;
        case 40:
            oled_write_P(PSTR("Solid Reactive\nMultinexus        "), false);
            break;
        case 41:
            oled_write_P(PSTR("Splash\n                  "), false);
            break;
        case 42:
            oled_write_P(PSTR("Multisplash\n                  "), false);
            break;
        case 43:
            oled_write_P(PSTR("Solid Splash\n                  "), false);
            break;
        case 44:
            oled_write_P(PSTR("Solid Multisplash\n                  "), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined\n                  "), false);
    }
}
#endif
//----------------------------------