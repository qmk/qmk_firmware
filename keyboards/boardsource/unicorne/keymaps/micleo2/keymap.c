#include QMK_KEYBOARD_H
#include "gw_oled.h"
#include "quantum.h"

// clang-format off

// template
/*  _______,       _______,       _______,      _______,       _______,       _______,              _______,       _______,       _______,      _______,       _______,       _______, */
// formatting macro:
// mk2kWjrf<t_ý>a`kWkvehyjPwkr <t_ý>aj

enum layers {
  _BSE, // Base
  _SYM, // Symbol
  _NAV, // Navigation
  _SYS, // Sysctrl
  _NUM, // Numpad
};

#define B _BSE
#define M _SYM
#define N _NAV
#define Y _SYS
#define U _NUM

// This denotes the key you used to enter into the layer.
// E for entry.
#define ___E___ _______
// Take a full screenshot on mac
#define FSCRNSHT G(S(KC_3))
// Take a partial screenshot on mac
#define SCRNSHT G(S(KC_4))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BSE] = LAYOUT_split_3x6_3(
    OSM(MOD_LSFT), KC_Q,          KC_W,         KC_E,          KC_R,          KC_T,                 KC_Y,          KC_U,          KC_I,         KC_O,          KC_P,          KC_DEL,
    HYPR_T(KC_ENT),KC_A,          LT(U, KC_S),  LALT_T(KC_D),  LT(N, KC_F),   KC_G,                 KC_H,          GUI_T(KC_J),   KC_K,         KC_L,          KC_SCLN,       OSL(Y),
    KC_TAB,        KC_Z,          KC_X,         KC_C,          KC_V,          KC_B,                 KC_N,          KC_M,          KC_COMM,      KC_DOT,        KC_COLN,       C(G(KC_Q)),
                                                CTL_T(KC_ESC), GUI_T(KC_SPC), QK_REP,               MEH_T(KC_ENT), SFT_T(KC_BSPC),OSL(M)
),

[_SYM] = LAYOUT_split_3x6_3(
    _______,       _______,       KC_LT,        KC_GT,         KC_ASTR,       KC_GRV,               _______,       KC_AMPR,       KC_LCBR,      KC_RCBR,       KC_PERC,       _______,
    _______,       KC_QUES,       KC_MINS,      KC_DQUO,       KC_QUOT,       KC_TILD,              KC_BSLS,       KC_PLUS,       KC_LPRN,      KC_RPRN,       KC_UNDS,       _______,
    _______,       KC_HASH,       _______,      KC_EQL,        KC_EXLM,       KC_CIRC,              KC_DLR,        KC_PIPE,       KC_LBRC,      KC_RBRC,       KC_AT,         _______,
                                                KC_SLSH,       _______,       _______,              _______,       _______,       ___E___
),

[_NAV] = LAYOUT_split_3x6_3(
    _______,       _______,       _______,      _______,       _______,       _______,              _______,       C(KC_TAB),     KC_TAB,       LSFT(KC_TAB),  C(S(KC_TAB)),  _______,
    _______,       _______,       _______,      _______,       ___E___,       _______,              KC_LEFT,       KC_DOWN,       KC_UP,        KC_RGHT,       _______,       _______,
    _______,       _______,       _______,      _______,       _______,       _______,              _______,       _______,       C(KC_LEFT),   C(KC_RGHT),    _______,       _______,
                                                _______,       _______,       _______,              _______,       KC_ENT,        _______
),

[_SYS] = LAYOUT_split_3x6_3(
    CW_TOGG,       _______,       FSCRNSHT,     SCRNSHT,       _______,       _______,              _______,       KC_F7,         KC_F8,        KC_F9,         KC_F12,        _______,
    _______,       _______,       KC_MPLY,      KC_VOLD,       KC_VOLU,       _______,              _______,       KC_F4,         KC_F5,        KC_F6,         KC_F11,        ___E___,
    QK_BOOT,       _______,       KC_MPRV,      KC_MNXT,       KC_MUTE,       _______,              _______,       KC_F1,         KC_F2,        KC_F3,         KC_F10,        QK_BOOT,
                                                _______,       _______,       _______,              _______,       _______,       _______
),

[_NUM] = LAYOUT_split_3x6_3(
    _______,       _______,       _______,      _______,       _______,       _______,              _______,       KC_7,          KC_8,         KC_9,          _______,       _______,
    _______,       _______,       ___E___,      _______,       _______,       _______,              _______,       KC_4,          KC_5,         KC_6,          _______,       _______,
    _______,       _______,       _______,      _______,       _______,       _______,              _______,       KC_1,          KC_2,         KC_3,          _______,       _______,
                                                _______,       _______,       _______,              _______,       _______,       KC_0
)

};

// clang-format on

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {};
#endif

// Callback to invoke when the enter key is pressed.
void enter_key_pressed_cb(void);

// Callback to invoke when the copy hot-key is pressed.
void copy_key_pressed_cb(void);

// Callback to invoke when the paste hot-key is pressed.
void paste_key_pressed_cb(void);

/* ********************* */
/* KEYCODE SECTION BEGIN */
/* ********************* */

// return true to immediately select the hold action when another key is pressed.
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CTL_T(KC_ESC):
        case SFT_T(KC_BSPC):
            return true;
        default:
            return false;
    }
}

static uint8_t copypaste_modifier = 0;
// Register the platform-correct copy/paste modifier.
bool process_detected_host_os_user(os_variant_t detected_os) {
    switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
            copypaste_modifier = MOD_MASK_GUI;
            break;
        case OS_WINDOWS:
        case OS_LINUX:
            copypaste_modifier = MOD_MASK_CTRL;
            break;
        default:
            break;
    }
    return true;
}

// return true if qmk should continue processing the keycode as normal.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (QK_MODS_GET_BASIC_KEYCODE(keycode)) {
        case KC_ENT:
            if (record->event.pressed) {
                enter_key_pressed_cb();
            }
            return true;
        case KC_C: {
            bool copypaste_mod_held = get_mods() & copypaste_modifier;
            if (record->event.pressed && copypaste_mod_held) {
                copy_key_pressed_cb();
            }
            return true;
        }
        case KC_V: {
            bool copypaste_mod_held = get_mods() & copypaste_modifier;
            if (record->event.pressed && copypaste_mod_held) {
                paste_key_pressed_cb();
            }
            return true;
        }
        default:
            return true;
    }
}

/* ******************* */
/* KEYCODE SECTION END */
/* ******************* */

/* ****************** */
/* RGB SECTION BEGIN */
/* ****************** */

#ifdef RGB_MATRIX_ENABLE
#    define RGB_LIGHT_BLUE 0x4c, 0xa8, 0xfc
#    define BASE_COL RGB_LIGHT_BLUE

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);
    uint8_t red;
    uint8_t green;
    uint8_t blue;
#    define SET_COLOR_INNER(r, g, b) \
        red   = r;                   \
        green = g;                   \
        blue  = b;

#    define SET_COLOR(...) SET_COLOR_INNER(__VA_ARGS__)

    switch (layer) {
        case _BSE:
            SET_COLOR(BASE_COL)
            break;
        case _SYM:
            SET_COLOR(RGB_PURPLE);
            break;
        case _NAV:
            SET_COLOR(RGB_BLUE);
            break;
        case _SYS:
            SET_COLOR(RGB_RED);
            break;
        case _NUM:
            SET_COLOR(RGB_GREEN);
            break;
        default:
            SET_COLOR(BASE_COL);
    }

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t index = g_led_config.matrix_co[row][col];
            if (!(index >= led_min && index < led_max && index != NO_LED)) {
                continue;
            }
            uint16_t kc = keymap_key_to_keycode(layer, (keypos_t){col, row});
            if (kc == KC_NO) {
                rgb_matrix_set_color(index, RGB_OFF);
                continue;
            }
            if (kc == KC_TRNS) {
                rgb_matrix_set_color(index, BASE_COL);
                continue;
            }
            rgb_matrix_set_color(index, red, green, blue);
        }
    }
    return false;
}
#endif

/* ****************** */
/* RGB SECTION END */
/* ****************** */

/* ***************************** */
/* POINTING_DEVICE SECTION BEGIN */
/* ***************************** */

// Convert mouse movement to scrolling.
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    const uint8_t cur_layer   = get_highest_layer(layer_state);
    int8_t        slow_factor = 8;
    if (cur_layer == _NUM) {
        // Decrease mouse sensitivity on num layer.
        slow_factor = 16;
    }
    mouse_report.h = mouse_report.x;
    mouse_report.v = -mouse_report.y / slow_factor;
    mouse_report.x = 0;
    mouse_report.y = 0;
    return mouse_report;
}

/* ***************************** */
/* POINTING_DEVICE SECTION END */
/* ***************************** */

/* ****************** */
/* OLED SECTION BEGIN */
/* ****************** */

#ifdef OLED_ENABLE

bool render_downtaunt(void);
void render_idle(void);
bool render_flash_img(void);

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
#    ifdef MASTER_RIGHT
    if (is_keyboard_master()) {
        return OLED_ROTATION_180;
    }
#    else
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;
    }
#    endif
    return rotation;
}

void oled_render_boot(bool bootloader) {
    oled_clear();
    for (int i = 0; i < 16; i++) {
        oled_set_cursor(0, i);
        if (bootloader) {
            oled_write_P(PSTR("Awaiting New Firmware "), false);
        } else {
            oled_write_P(PSTR("Rebooting "), false);
        }
    }

    oled_render_dirty(true);
}

bool shutdown_user(bool jump_to_bootloader) {
    oled_render_boot(jump_to_bootloader);
    return true;
}

bool oled_task_user() {
    if (render_flash_img() == false) {
        return false;
    }

    const uint8_t cur_layer = get_highest_layer(layer_state);
    switch (cur_layer) {
        case _BSE:
            if (render_downtaunt()) {
                render_idle();
            }
            break;
        case _SYM:
            oled_write_raw(gw_diver, sizeof(gw_diver));
            break;
        case _NAV:
            oled_write_raw(gw_parachute, sizeof(gw_parachute));
            break;
        case _SYS:
            oled_write_raw(gw_bomb, sizeof(gw_bomb));
            break;
        case _NUM:
            oled_write_raw(gw_key, sizeof(gw_key));
            break;
        default:
            render_idle();
            break;
    }

    return false;
}

// Delay to wait after kb inactivity to begin taunt animation.
#    define IDLE_TOGGLE_FRAME_LEN_MS 2500
void render_idle() {
    if ((timer_read32() / IDLE_TOGGLE_FRAME_LEN_MS) % 2 == 0) {
        oled_write_raw(gw_idle_A, sizeof(gw_idle_A));
    } else {
        oled_write_raw(gw_idle_B, sizeof(gw_idle_B));
    }
}

// Delay to wait after kb inactivity to begin taunt animation.
#    define TAUNT_WAIT_MS 60 * 1000
// Length of a single frame of the taunt animation.
#    define TAUNT_TOGGLE_FRAME_LEN_MS 1500

bool render_downtaunt() {
    const uint32_t idle_time_ms = last_matrix_activity_elapsed();
    if (idle_time_ms <= TAUNT_WAIT_MS) {
        return true;
    }
    if ((timer_read32() / TAUNT_TOGGLE_FRAME_LEN_MS) % 2 == 0) {
        oled_write_raw(gw_downtaunt_f1, sizeof(gw_downtaunt_f1));
    } else {
        oled_write_raw(gw_downtaunt_f2, sizeof(gw_downtaunt_f2));
    }
    return false;
}

// When set, contains the end deadline for the flash image.
uint32_t    flash_img_anim_timer = 0;
const char *flash_img_data;
uint16_t    flash_img_size;

// Support briefly flashing an image on the display for a set amount of time. This ignores any layer information.
// Currently these are only triggered by key events.
// return true if the caller can continue rendering their own content.
bool render_flash_img() {
    if (flash_img_anim_timer == 0) {
        return true;
    }
    if (timer_expired32(timer_read32(), flash_img_anim_timer)) {
        flash_img_anim_timer = 0;
        return true;
    }
    oled_write_raw(flash_img_data, flash_img_size);
    return false;
}

void enter_key_pressed_cb(void) {
#    define JUDGE9_LEN_MS 1100
    uint32_t cur_time_ms = timer_read32();
    // Treat the time at which the enter key is pressed as RNG.
    // We have a 1/9 chance of flashing the judge9.
    if (cur_time_ms % 9 == 0) {
        flash_img_anim_timer = cur_time_ms + JUDGE9_LEN_MS;
        flash_img_data       = gw_judge9;
        flash_img_size       = sizeof(gw_judge9);
    }
}

// The current charged state of the bucket.
static uint8_t charge_state = 0;
// The bucket's fully charged state.
#    define MAX_CHARGE_STATE 3

void flash_current_charge_state(void) {
#    define BUCKET_CHARGE_LEN_MS 500
    flash_img_anim_timer = timer_read32() + BUCKET_CHARGE_LEN_MS;
    switch (charge_state) {
        case 0:
            flash_img_data = gw_bucket_charged1;
            flash_img_size = sizeof(gw_bucket_charged1);
            break;
        case 1:
            flash_img_data = gw_bucket_charged2;
            flash_img_size = sizeof(gw_bucket_charged2);
            break;
        default:
            flash_img_data = gw_bucket_charged3;
            flash_img_size = sizeof(gw_bucket_charged3);
            break;
    }
}

void copy_key_pressed_cb(void) {
    flash_current_charge_state();
    if (charge_state < MAX_CHARGE_STATE) {
        charge_state++;
    }
}

void paste_key_pressed_cb(void) {
#    define BUCKET_THROW_LEN_MS 900
    if (charge_state == MAX_CHARGE_STATE) {
        flash_img_anim_timer = timer_read32() + BUCKET_THROW_LEN_MS;
        flash_img_data       = gw_bucket_throw;
        flash_img_size       = sizeof(gw_bucket_throw);
        charge_state         = 0;
    } else {
        flash_current_charge_state();
    }
}

#else
// Stub impls.
void enter_key_pressed_cb(void) {}
void copy_key_pressed_cb(void) {}
void paste_key_pressed_cb(void) {}
#endif
/* ****************** */
/* OLED SECTION END */
/* ****************** */
