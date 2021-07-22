#include QMK_KEYBOARD_H
#include "print.h"

// START Luna vars
#define MIN_WALK_SPEED 10
#define MIN_RUN_SPEED 40

#define ANIM_FRAME_DURATION 200 // how long each frame lasts in ms
#define ANIM_SIZE 96 // number of bytes in array, minimize for adequate firmware size, max is 1024

uint32_t anim_timer = 0;
uint32_t anim_sleep = 0;

uint8_t current_frame = 0;
bool isSneaking = false;
bool isJumping = false;
bool showedJump = true;
int current_wpm = 0;

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0
    };

    oled_write_P(qmk_logo, false);
}

static void render_luna(int LUNA_X, int LUNA_Y) {

    static const char PROGMEM sit[2][ANIM_SIZE] = {
        // 'sit1', 32x22px
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c,
            0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x68, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28,
            0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },

        // 'sit2', 32x22px
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c,
            0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x90, 0x08, 0x18, 0x60, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28,
            0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        }
    };

    static const char PROGMEM walk[2][ANIM_SIZE] = {
        // 'walk1', 32x22px
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x90, 0x90, 0x90, 0xa0, 0xc0, 0x80, 0x80,
            0x80, 0x70, 0x08, 0x14, 0x08, 0x90, 0x10, 0x10, 0x08, 0xa4, 0x78, 0x80, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0xfc, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00,
            0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0xea, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x03,
            0x06, 0x18, 0x20, 0x20, 0x3c, 0x0c, 0x12, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },

        // 'walk2', 32x22px
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x20, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00,
            0x00, 0xe0, 0x10, 0x28, 0x10, 0x20, 0x20, 0x20, 0x10, 0x48, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x20, 0xf8, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
            0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x30, 0xd5, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e,
            0x02, 0x1c, 0x14, 0x08, 0x10, 0x20, 0x2c, 0x32, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        }
    };

    static const char PROGMEM run[2][ANIM_SIZE] = {
        // 'run1', 32x22px
        {
            0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x08, 0xc8, 0xb0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
            0x80, 0x40, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0xc4, 0xa4, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x58, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x09, 0x04, 0x04, 0x04, 0x04, 0x02, 0x03, 0x02, 0x01, 0x01,
            0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
        },

        // 'run2', 32x22px
        {
            0x00, 0x00, 0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
            0x80, 0x80, 0x78, 0x28, 0x08, 0x10, 0x20, 0x30, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0xb0, 0x50, 0x55, 0x20, 0x1f, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37,
            0x02, 0x1e, 0x20, 0x20, 0x18, 0x0c, 0x14, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        }
    };

    static const char PROGMEM sneak[2][ANIM_SIZE] = {
        // 'sneak1', 32x22px
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0xc0, 0x40, 0x40, 0x80, 0x00, 0x80, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x1e, 0x21, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x04,
            0x04, 0x04, 0x03, 0x01, 0x00, 0x00, 0x09, 0x01, 0x80, 0x80, 0xab, 0x04, 0xf8, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x02, 0x06,
            0x18, 0x20, 0x20, 0x38, 0x08, 0x10, 0x18, 0x04, 0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
        },

        // 'sneak2', 32x22px
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0xe0, 0xa0, 0x20, 0x40, 0x80, 0xc0, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x3e, 0x41, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x04,
            0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x40, 0x40, 0x55, 0x82, 0x7c, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x04,
            0x18, 0x10, 0x08, 0x10, 0x20, 0x28, 0x34, 0x06, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
        }
    };

    // animation state
    void animation_phase(void) {

        if (isJumping || !showedJump) {

            // clear
            oled_set_cursor(LUNA_X,LUNA_Y +2);
            oled_write("     ", false);

            oled_set_cursor(LUNA_X,LUNA_Y -1);

            showedJump = true;
        } else {

            // clear
            oled_set_cursor(LUNA_X,LUNA_Y -1);
            oled_write("     ", false);

            oled_set_cursor(LUNA_X,LUNA_Y);
        }

        current_frame = (current_frame + 1) % 2;

        if(isSneaking) {
            oled_write_raw_P(sneak[abs(1 - current_frame)], ANIM_SIZE);

        } else if(current_wpm <= MIN_WALK_SPEED) {
            oled_write_raw_P(sit[abs(1 - current_frame)], ANIM_SIZE);

        } else if(current_wpm <= MIN_RUN_SPEED) {
            oled_write_raw_P(walk[abs(1 - current_frame)], ANIM_SIZE);

        } else {
            oled_write_raw_P(run[abs(1 - current_frame)], ANIM_SIZE);
        }
    }

    // animation timer
    if(timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
        anim_timer = timer_read32();
        animation_phase();
    }
/*
    // screen on and off
    if (current_wpm > 0) {
        oled_on();
        anim_sleep = timer_read32();
    } else if(timer_elapsed32(anim_sleep) > OLED_TIMEOUT) {
        oled_off();
    }
    */
}
// END Luna vars

enum _layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _BASE,
    _MOUS,
    _SYMS,
    _MDIA,
    _NPAD,
    _GAME,
};

enum custom_keycodes {
    _COMP1  = SAFE_RANGE,
    _COMP2,
    V_C_W,
    T_M_A,
    V_FS,
    T_FS,
};

enum custom_tapdance {
    TD_PLAY,
    TD_HOME,
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_PLAY] = ACTION_TAP_DANCE_DOUBLE(KC_MPLY, KC_MNXT),
    [TD_HOME] = ACTION_TAP_DANCE_DOUBLE(KC_HOME, KC_END),
};

#define KC_TPLY TD(TD_PLAY)
#define KC_THME TD(TD_HOME)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * BASE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |~/MDIA|   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |Alt/Tb|   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LCtrl |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |+/SHFT|
 * `-----------------------------------------/       /     \Enter \-----------------------------------------'
 *            |Gaming| LGUI | LAlt | ESC/ | /Space  /       \ or   \  | Bspc | Alt +|Delete|NUMPAD|
 *            |      |      |      |Number|/       /         \Mouse \ |      |Shift |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_BASE] = LAYOUT(
  LT(_MDIA,KC_GRV), KC_1,      KC_2,    KC_3,              KC_4,    KC_5,                   KC_6,               KC_7,    KC_8,          KC_9,   KC_0,     KC_MINS,
  LALT_T(KC_TAB),   KC_Q,      KC_W,    KC_E,              KC_R,    KC_T,                   KC_Y,               KC_U,    KC_I,          KC_O,   KC_P,     KC_BSLS,
  KC_LSFT,          KC_A,      KC_S,    KC_D,              KC_F,    KC_G,                   KC_H,               KC_J,    KC_K,          KC_L,   KC_SCLN,  KC_QUOT,
  KC_LCTRL,         KC_Z,      KC_X,    KC_C,              KC_V,    KC_B, KC_TPLY, KC_THME, KC_N,               KC_M,    KC_COMM,       KC_DOT, KC_SLSH,  RSFT_T(KC_PLUS),
                    TG(_GAME), KC_LALT, LT(_SYMS,KC_ESC),  KC_LGUI, KC_SPC,                 LT(_MOUS, KC_ENT),  KC_BSPC, LALT(KC_LSFT), KC_DEL, TG(_NPAD)
),
/*
 * MOUS
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  | F6   |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      | M UP | HOME | PGUP |                    |M Wl U|M Wl D|M Wl L|M Wl R| HOME |COMP1 |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TRNS |PRNTSC|M LFT |M DWN |M RGHT|SC LCK|-------.    ,-------|  UP  | DOWN | LEFT |RIGHT | END  |COMP2 |
 * |------+------+------+------+------+------| TRNS  |    | TRNS  |------+------+------+------+------+------|
 * |      |      |      |      | END  | PGDN |-------|    |-------|MOUS1 |MOUS2 |      |      |PAUSE |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | TRNS | TRNS | TRNS |TRNS  | / TRNS  /       \ TRNS \  |MOUS3 |MOUS4 |MOUS5 |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_MOUS] = LAYOUT(
  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,                        KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,   KC_F12,
  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_MS_U,  KC_HOME,  KC_PGUP,                      KC_WH_U,  KC_WH_D,  KC_WH_L,  KC_WH_R,   KC_HOME,  _COMP1,
  _______,  KC_PSCR,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_SLCK,                      KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT,  KC_END,   _COMP2,
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_END,   KC_PGDOWN, _______,  _______, KC_BTN1,  KC_BTN2,  XXXXXXX,  XXXXXXX,   KC_PAUS,  XXXXXXX,
            _______,  _______,  _______,  _______,  _______,                      _______,  KC_BTN3,  KC_BTN4,  KC_BTN5,   XXXXXXX
),
/* SYMS
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |V_C_W |T_M_A |      |      |      |      |                    |      |      |      |   [  |   ]  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TRNS |      |      |      |      |      |                    |      |      |      |   {  |   }  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TRNS |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+------| TRNS  |    | TRNS  |------+------+------+------+------+------|
   | TRNS | V_FS | T_FS |      |      |      |-------|    |-------|      |      |      |   <  |   >  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | TRNS | TRNS | TRNS | TRNS | / TRNS  /       \ TRNS \  | TRNS | TRNS | TRNS | TRNS |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
/*
 * ideas for macros -
 * switch keys around so parens and square braces line up
 */
[_SYMS] = LAYOUT(+\
  V_C_W,    T_M_A,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                          XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_LBRC,  KC_RBRC,  XXXXXXX,
  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                          XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_LCBR,  KC_RCBR,  XXXXXXX,
  _______,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,                          KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  XXXXXXX,
  _______,  V_FS,     T_FS,     XXXXXXX,  XXXXXXX,  XXXXXXX,   _______,    _______,   XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_LT,    KC_GT,    XXXXXXX,
                _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______
),

/* MDIA
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | TRNS |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |VOLUP |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|MUTE  | PREV | PLAY | NEXT |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|VOLDN |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |      |      |      |Reset |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
  [_MDIA] = LAYOUT(
  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                     KC_VOLU,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                     KC_MPRV,  KC_MPLY,  KC_MNXT,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  _______, KC_VOLD,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                     XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  RESET
),

/* NPAD
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  | HOME |N Lck |  /   |  *   |  -   |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  | End  |  7   |  8   |  9   |  +   |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShft |Pg Up |  4   |  5   |  6   |  ,   |-------.    ,-------|  UP  | DOWN | LEFT |RIGHT |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LCtrl |Pg Dn |  1   |  2   |  3   |  =   |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | TRNS |  0   |  .   |ENTER | / TRNS  /       \      \  |      |      |      | TRNS |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
  [_NPAD] = LAYOUT(
  KC_ESC,   KC_HOME,  KC_NLCK,  KC_PSLS,  KC_PAST,  KC_PMNS,                      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,  XXXXXXX,
  KC_TAB,   KC_END,   KC_P7,    KC_P8,    KC_P9,    KC_PPLS,                      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,  XXXXXXX,
  KC_LSFT,  KC_PGUP,  KC_P4,    KC_P5,    KC_P6,    KC_PCMM,                      KC_DOWN,  KC_UP,    KC_LEFT,  KC_RIGHT,  XXXXXXX,  XXXXXXX,
  KC_LCTL,  KC_PGDN,  KC_P1,    KC_P2,    KC_P3,    KC_PEQL,  _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,  XXXXXXX,
            _______,  KC_P0,    KC_PDOT,  KC_PENT,  _______,                      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   _______
),

/* GAME
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | MEDIA|   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   T  |Alt/Tb|   Q  |   W  |   E  |   R  |                    |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------|------+------+------+------+------+                    |------+------+------+------+------+------|
 * |   G  |LShift|   A  |   S  |   D  |   F  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------|------+------+------+------+------+       |    |       |------+------+------+------+------+------|
 * |   B  |LCtrl |   Z  |   X  |   C  |   V  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \Enter \-----------------------------------------'
 *            | TRNS |      |      | LAlt | /Space  /       \      \  |PrnScr|      |      | TRNS |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_GAME] = LAYOUT(
  KC_ESC,  KC_1,            KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,       KC_7,       KC_8,          KC_9,          KC_0,          KC_BSPC,
  KC_T,    KC_TAB,          KC_Q,    KC_W,    KC_E,    KC_R,                        MEH(KC_Y),  MEH(KC_U),  MEH(KC_I),     MEH(KC_O),     MEH(KC_P),     KC_PGUP,
  KC_G,    KC_LSFT,         KC_A,    KC_S,    KC_D,    KC_F,                        MEH(KC_H),  MEH(KC_J),  MEH(KC_K),     MEH(KC_L),     MEH(KC_SCLN),  KC_PGDN,
  KC_B,    KC_LCTRL,        KC_Z,    KC_X,    KC_C,    KC_V,  _______,    _______,  MEH(KC_N),  MEH(KC_M),  MEH(KC_COMM),  MEH(KC_DOT),   MEH(KC_SLSH),  KC_RIGHT,
           _______,         XXXXXXX, XXXXXXX, KC_LALT, KC_SPC,                      KC_ENT,     KC_PSCR,    XXXXXXX,       XXXXXXX,       _______
)
};

#ifdef OLED_DRIVER_ENABLE
static void print_status_narrow(void) {
    isSneaking = false;
    // Print current mode
    oled_write_P(PSTR("\n\n"), false);
    oled_write_ln_P(PSTR("Flare"), false);
    oled_write_ln_P(PSTR("Sofle"), false);
    oled_write_P(PSTR("\n"), false);
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    int layer = get_highest_layer(layer_state);
    switch (layer) {
        case _BASE:
            oled_write_ln_P(PSTR("ALL"), false);
            oled_write_P(PSTR(" YOUR"), false);
            oled_write_ln_P(PSTR("BASE"), false);
            break;
        case _MOUS:
            isSneaking = true;
            oled_write_ln_P(PSTR("Mouse"), false);
            break;
        case _SYMS:
            oled_write_ln_P(PSTR("@$*&#"), false);
            break;
        case _MDIA:
            oled_write_ln_P(PSTR("Media"), false);
            break;
        case _NPAD:
            oled_write_ln_P(PSTR("Num Pad"), false);
            break;
        case _GAME:
            oled_write_ln_P(PSTR("Gamez"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    if (layer != _BASE) {
        oled_write_P(PSTR("\n"), false);
    }

    render_luna(0,13);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

void oled_task_user(void) {
    current_wpm = get_current_wpm();
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    /*
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
*/
    switch (keycode) {
        case _COMP1:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_LCTRL) SS_DELAY(100) SS_TAP(X_LCTRL) SS_DELAY(100) "1");
            }
            return false;
        case _COMP2:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_LCTRL) SS_DELAY(100) SS_TAP(X_LCTRL) SS_DELAY(100) "2");
            }
            return false;
        case V_C_W:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("w"));
            }
            return false;
        case T_M_A:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT("a"));
            }
            return false;
        case V_FS:
            if (record->event.pressed) {
                SEND_STRING(",\n");
            }
            return false;
        case T_FS:
            if (record->event.pressed) {
                SEND_STRING(SS_LALT("a") "\n");
            }
            return false;
        case KC_SPC:
            if (record->event.pressed) {
                isJumping = true;
                showedJump = false;
            } else {
                isJumping = false;
            }
            break;
    }
    return true;
}
/*
void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
    debug_enable=true;
    debug_matrix=true;
    debug_keyboard=true;
}
*/

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_THME:
        case KC_TPLY:
            return TAPPING_TERM + 250;
        default:
            return TAPPING_TERM;
    }
}

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_PGDOWN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return true;
}

#endif
