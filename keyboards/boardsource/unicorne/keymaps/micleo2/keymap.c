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
  _BLN, // Blender
};

#define B _BSE
#define M _SYM
#define N _NAV
#define Y _SYS
#define U _NUM
#define L _BLN

// This denotes the key you used to enter into the layer.
// E for entry.
#define ___E___ _______

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BSE] = LAYOUT_split_3x6_3(
    CW_TOGG,       KC_Q,          KC_W,         KC_E,          KC_R,          KC_T,                 KC_Y,          KC_U,          KC_I,         KC_O,          KC_P,          KC_DEL,
    OSM(MOD_LSFT), KC_A,          LT(U, KC_S),  ALT_T(KC_D),   LT(N, KC_F),   KC_G,                 KC_H,          KC_J,          KC_K,         KC_L,          KC_SCLN,       OSL(Y),
    TG(_BLN),      KC_Z,          KC_X,         KC_C,          KC_V,          KC_B,                 KC_N,          KC_M,          KC_COMM,      KC_DOT,        KC_COLN,       C(G(KC_Q)),
                                                CTL_T(KC_ESC), GUI_T(KC_SPC), QK_LEAD,              HYPR_T(KC_ENT),SFT_T(KC_BSPC),OSL(M)
),

[_SYM] = LAYOUT_split_3x6_3(
    _______,       _______,       KC_LT,        KC_GT,         KC_ASTR,       KC_GRV,               _______,       KC_AMPR,       KC_LCBR,      KC_RCBR,       KC_PERC,       _______,
    _______,       KC_QUES,       KC_MINS,      KC_DQUO,       KC_QUOT,       KC_TILD,              KC_BSLS,       KC_PLUS,       KC_LPRN,      KC_RPRN,       KC_UNDS,       _______,
    _______,       _______,       KC_HASH,      KC_EQL,        KC_EXLM,       KC_CIRC,              KC_DLR,        KC_PIPE,       KC_LBRC,      KC_RBRC,       _______,       _______,
                                                KC_SLSH,       _______,       KC_AT,                _______,       _______,       ___E___
),

[_NAV] = LAYOUT_split_3x6_3(
    _______,       _______,       _______,      _______,       _______,       _______,              _______,       C(KC_TAB),     KC_TAB,       LSFT(KC_TAB),  C(S(KC_TAB)),  _______,
    _______,       _______,       _______,      _______,       ___E___,       _______,              KC_LEFT,       KC_DOWN,       KC_UP,        KC_RGHT,       _______,       _______,
    _______,       _______,       _______,      _______,       _______,       _______,              _______,       _______,       KC_HOME,      KC_END,        _______,       _______,
                                                _______,       _______,       _______,              _______,       KC_ENT,        _______
),

[_SYS] = LAYOUT_split_3x6_3(
    CW_TOGG,       _______,       _______,      _______,       KC_PSCR,       _______,              _______,       KC_F7,         KC_F8,        KC_F9,         KC_F12,        _______,
    _______,       _______,       KC_MPLY,      KC_VOLD,       KC_VOLU,       _______,              _______,       KC_F4,         KC_F5,        KC_F6,         KC_F11,        ___E___,
    QK_BOOT,       _______,       KC_MPRV,      KC_MNXT,       KC_MUTE,       _______,              _______,       KC_F1,         KC_F2,        KC_F3,         KC_F10,        _______,
                                                _______,       _______,       _______,              _______,       _______,       _______
),

[_NUM] = LAYOUT_split_3x6_3(
    _______,       _______,       _______,      _______,       _______,       _______,              _______,       KC_7,          KC_8,         KC_9,          KC_MINUS,      _______,
    _______,       _______,       ___E___,      _______,       _______,       _______,              _______,       KC_4,          KC_5,         KC_6,          KC_COMM,       _______,
    _______,       _______,       _______,      _______,       _______,       _______,              _______,       KC_1,          KC_2,         KC_3,          KC_PLUS,       _______,
                                                _______,       _______,       _______,              _______,       KC_0,          KC_BSPC
),

[_BLN] = LAYOUT_split_3x6_3(
    KC_GRV,        LT(0, KC_Q),   LT(0, KC_W),  LT(0, KC_E),   LT(0, KC_R),   LT(0, KC_T),          _______,       _______,       _______,      _______,       _______,       _______,
    SFT_T(KC_ENT), _______,       _______,      _______,       _______,       LT(0, KC_G),          _______,       _______,       _______,      _______,       _______,       _______,
    TG(_BLN),      _______,       LT(0, KC_X),  LT(0, KC_C),   LT(0, KC_V),   _______,              _______,       _______,       _______,      _______,       _______,       _______,
                                                _______,       _______,       SFT_T(KC_TAB),        _______,       _______,       _______
)

};

// clang-format on

void leader_start_user(void) {}

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_U)) {
        SEND_STRING("../");
    } else if (leader_sequence_one_key(KC_E)) {
    }
}

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {};
#endif

void b_key_pressed_cb(void);

void enter_key_pressed_cb(void);

void delete_key_pressed_cb(void);

void copy_key_pressed_cb(void);

void paste_key_pressed_cb(void);

void leftarrow_key_pressed_cb(bool mods_active);

void rightarrow_key_pressed_cb(bool mods_active);

void downarrow_key_pressed_cb(void);

void refresh_key_pressed_cb(void);

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
    // The following handlers simply notify callbacks.
    switch (QK_MODS_GET_BASIC_KEYCODE(keycode)) {
        case KC_B:
            if (record->event.pressed) {
                b_key_pressed_cb();
            }
            break;
        case KC_ENT:
            if (record->event.pressed) {
                enter_key_pressed_cb();
            }
            break;
        case KC_DEL:
            if (record->event.pressed) {
                delete_key_pressed_cb();
            }
            break;
        case KC_C: {
            bool copypaste_mod_held = get_mods() & copypaste_modifier;
            if (record->event.pressed && copypaste_mod_held) {
                copy_key_pressed_cb();
            }
            break;
        }
        case KC_R: {
            bool copypaste_mod_held = get_mods() & copypaste_modifier;
            if (record->event.pressed && copypaste_mod_held) {
                refresh_key_pressed_cb();
            }
            break;
        }
        case KC_V: {
            bool copypaste_mod_held = get_mods() & copypaste_modifier;
            if (record->event.pressed && copypaste_mod_held) {
                paste_key_pressed_cb();
            }
            break;
        }
        case KC_LEFT:
            if (record->event.pressed) {
                leftarrow_key_pressed_cb(get_mods());
            }
            break;
        case KC_RIGHT:
            if (record->event.pressed) {
                rightarrow_key_pressed_cb(get_mods());
            }
            break;
        case KC_DOWN:
            if (record->event.pressed) {
                downarrow_key_pressed_cb();
            }
            break;
        default:
            break;
    }

    // This switch can actually modify keypress behavior.
    switch (keycode) {
        case LT(0, KC_Q):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_1);
                return false;
            }
            return true;
        case LT(0, KC_W):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_2);
                return false;
            }
            return true;
        case LT(0, KC_E):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_3);
                return false;
            }
            return true;
        case LT(0, KC_R):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_4);
                return false;
            }
            return true;
        case LT(0, KC_T):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_Y);
                return false;
            }
            return true;
        case LT(0, KC_G):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_H);
                return false;
            }
            return true;
        case LT(0, KC_X):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_KP_7);
                return false;
            }
            return true;
        case LT(0, KC_C):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_KP_1);
                return false;
            }
            return true;
        case LT(0, KC_V):
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_KP_3);
                return false;
            }
            return true;
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
    /* return false; */
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
        case _BLN:
            SET_COLOR(RGB_ORANGE);
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
    int8_t        slow_factor = 1;
    if (cur_layer == _NUM) {
        // Decrease mouse sensitivity on num layer.
        slow_factor = 4;
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

// This is updated to the current time in ms every time we enter the render loop.
static uint32_t cur_render_time = 0;

// Render functions which return bool will optionally render. Returning true means the caller may
// continue rendering their own content.
bool render_downtaunt(void);
bool render_flash_seq(void);
void render_idle(void);
void render_parachute(void);

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
    cur_render_time = timer_read32();
    if (render_flash_seq() == false) {
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
            render_parachute();
            break;
        case _SYS:
            oled_write_raw(gw_bomb, sizeof(gw_bomb));
            break;
        case _NUM:
            oled_write_raw(gw_key, sizeof(gw_key));
            break;
        case _BLN:
            oled_write_raw(gw_flagman_right, sizeof(gw_flagman_right));
            break;
        default:
            render_idle();
            break;
    }

    return false;
}

enum IDLE_DIR { RIGHT, LEFT };
static uint8_t cur_arrow_dir = RIGHT;

// How long an individual idle frame lasts.
#    define IDLE_TOGGLE_FRAME_LEN_MS 1000
static uint8_t  cur_idle_pose          = 0;
static bool     must_do_crouch         = false;
static uint32_t change_idle_pose_timer = 0;

void render_idle() {
    if (timer_expired32(cur_render_time, change_idle_pose_timer)) {
        change_idle_pose_timer = cur_render_time + IDLE_TOGGLE_FRAME_LEN_MS;
        // We emulate the idle animation behavior from smash. Most of the time is spent toggling between stand and crouch.
        // When you are in any pose other than stand, the only valid next pose is back to stand. Stand can then branch
        // into crouch, or backhand/outstreched (BO), but crouch is the most likely. If you have entered into stand from BO,
        // then you must perform a crouch before you are eligible to do another BO.
        if (cur_idle_pose == idle_stand_pose) {
            if (must_do_crouch) {
                cur_idle_pose  = idle_crouch_pose;
                must_do_crouch = false;
            } else {
                // 50% chance go into crouch, 25% backhand or outstreched individually.
                switch (rand() % 4) {
                    case 0:
                    case 1:
                        cur_idle_pose = idle_crouch_pose;
                        break;
                    case 2:
                        cur_idle_pose  = idle_backhand_pose;
                        must_do_crouch = true;
                        break;
                    case 3:
                        cur_idle_pose  = idle_outstretched_pose;
                        must_do_crouch = true;
                        break;
                }
            }
        } else {
            cur_idle_pose = idle_stand_pose;
        }
    };
    uint8_t idleIdx = cur_idle_pose * 2 + cur_arrow_dir;
    // All the poses should have the same size, so it doesn't matter which one we use sizeof on.
    oled_write_raw(gw_idle_poses[idleIdx], sizeof(gw_idle_A_right));
}

uint32_t next_parachute_frame_timer = 0;
uint16_t parachute_idx              = 0;

void render_parachute() {
#    define PARACHUTE_FRAME_LEN 550
    if (timer_expired32(cur_render_time, next_parachute_frame_timer)) {
        // If the frame timer is expired by a lot, that probably means that the parachute animation
        // hasn't been running for a while. So reset the animation.
        if (cur_render_time - next_parachute_frame_timer > PARACHUTE_FRAME_LEN * 2) {
            parachute_idx = 0;
        } else {
            parachute_idx++;
            parachute_idx %= PARACHUTE_SEQ_LEN;
        }
        next_parachute_frame_timer = cur_render_time + PARACHUTE_FRAME_LEN;
    }
    oled_write_raw(gw_parachute[parachute_idx], sizeof(gw_parachute1));
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
    if ((cur_render_time / TAUNT_TOGGLE_FRAME_LEN_MS) % 2 == 0) {
        oled_write_raw(gw_downtaunt_f1, sizeof(gw_downtaunt_f1));
    } else {
        oled_write_raw(gw_downtaunt_f2, sizeof(gw_downtaunt_f2));
    }
    return false;
}

// Contains all the frame data of the sequence.
static const char **flash_seq_data;
// When set, contains the end deadline for the flash sequence.
static uint32_t flash_img_end_timer = 0;
static uint32_t flash_seq_begin_time;
static uint16_t flash_num_frames;
static uint32_t flash_frame_len_ms;
static uint16_t flash_img_size;

// Support briefly flashing an image sequence on the display for a set amount of time. This ignores any layer information.
// Each frame of the sequence will have an equal amount of render time, based off the ratio of the sequence length and
// number of frames. Any leftover time not evenly divisible will be given to the last frame.
bool render_flash_seq() {
    if (flash_img_end_timer == 0) {
        return true;
    }
    if (timer_expired32(cur_render_time, flash_img_end_timer)) {
        flash_img_end_timer = 0;
        return true;
    }
    uint16_t seq_idx = (cur_render_time - flash_seq_begin_time) / flash_frame_len_ms;
    if (seq_idx >= flash_num_frames) {
        seq_idx = flash_num_frames - 1;
    }
    oled_write_raw(flash_seq_data[seq_idx], flash_img_size);
    return false;
}

void start_flash_seq(const char **data, uint32_t seq_len_ms, uint16_t num_frames, uint16_t img_size) {
    flash_seq_data       = data;
    flash_seq_begin_time = cur_render_time;
    flash_img_end_timer  = cur_render_time + seq_len_ms;
    flash_num_frames     = num_frames;
    flash_frame_len_ms   = seq_len_ms / num_frames;
    flash_img_size       = img_size;
}

// Helper function to launch a "sequence" which is really just one frame of data.
static const char *helper_img_wrapper[1] = {NULL};
void               start_flash_img(const char *data, uint32_t img_len_ms, uint16_t img_size) {
    helper_img_wrapper[0] = data;
    start_flash_seq(helper_img_wrapper, img_len_ms, 1, img_size);
}

void refresh_key_pressed_cb(void) {
#    define PUFF_LEN_MS 200 * 3
    start_flash_seq(gw_puffs, PUFF_LEN_MS, PUFF_SEQ_LEN, sizeof(gw_puff_f1));
}

// Start judge9 anim on enter key.
void enter_key_pressed_cb(void) {
#    define VERMIN_LEN_MS 300 * VERMIN_SEQ_LEN
    start_flash_seq(gw_vermin, VERMIN_LEN_MS, VERMIN_SEQ_LEN, sizeof(gw_vermin_hi));
}

void delete_key_pressed_cb(void) {
#    define JUDGE9_LEN_MS 1100
    // Treat the time at which the enter key is pressed as RNG.
    // We have a 1/9 chance of flashing the judge9.
    if (cur_render_time % 9 == 0) {
        start_flash_img(gw_judge9, JUDGE9_LEN_MS, sizeof(gw_judge9));
    }
}

void b_key_pressed_cb(void) {
#    define BACON_LEN_MS 300 * BACON_SEQ_LEN
    // 1/2 chance of cooking bacon on b.
    if (cur_render_time % 2 == 0) {
        start_flash_seq(gw_bacon, BACON_LEN_MS, BACON_SEQ_LEN, sizeof(gw_bacon0));
    }
}

// The current charged state of the bucket.
static uint8_t charge_state = 0;
// The bucket's fully charged state.
#    define MAX_CHARGE_STATE 3

void flash_current_charge_state(void) {
#    define BUCKET_CHARGE_LEN_MS 500
    switch (charge_state) {
        case 0:
            start_flash_img(gw_bucket_charged0, BUCKET_CHARGE_LEN_MS, sizeof(gw_bucket_charged0));
            break;
        case 1:
            start_flash_img(gw_bucket_charged1, BUCKET_CHARGE_LEN_MS, sizeof(gw_bucket_charged1));
            break;
        case 2:
            start_flash_img(gw_bucket_charged2, BUCKET_CHARGE_LEN_MS, sizeof(gw_bucket_charged2));
            break;
        case 3:
            start_flash_img(gw_bucket_charged3, BUCKET_CHARGE_LEN_MS, sizeof(gw_bucket_charged3));
            break;
    }
}

void copy_key_pressed_cb(void) {
    if (charge_state < MAX_CHARGE_STATE) {
        charge_state++;
    }
    flash_current_charge_state();
}

void paste_key_pressed_cb(void) {
#    define BUCKET_THROW_LEN_MS 200 * THROW_SEQ_LEN
    if (charge_state == MAX_CHARGE_STATE) {
        start_flash_seq(gw_bucket_throws, BUCKET_THROW_LEN_MS, THROW_SEQ_LEN, sizeof(gw_bucket_throw1));
        charge_state = 0;
    } else {
        flash_current_charge_state();
    }
}

#    define CHAIR_LEN_MS 600
void leftarrow_key_pressed_cb(bool mods_active) {
    cur_arrow_dir = LEFT;
    if (mods_active) {
        start_flash_img(gw_chair_left, CHAIR_LEN_MS, sizeof(gw_chair_left));
    }
}

void rightarrow_key_pressed_cb(bool mods_active) {
    cur_arrow_dir = RIGHT;
    if (mods_active) {
        start_flash_img(gw_chair_right, CHAIR_LEN_MS, sizeof(gw_chair_right));
    }
}

void downarrow_key_pressed_cb() {
    if (cur_arrow_dir == RIGHT) {
        start_flash_img(gw_down_squat_right, CHAIR_LEN_MS, sizeof(gw_down_squat_right));
    } else {
        start_flash_img(gw_down_squat_left, CHAIR_LEN_MS, sizeof(gw_down_squat_left));
    }
}

#else
// Stub impls.
void b_key_pressed_cb(void) {}
void enter_key_pressed_cb(void) {}
void delete_key_pressed_cb(void) {}
void copy_key_pressed_cb(void) {}
void paste_key_pressed_cb(void) {}
void leftarrow_key_pressed_cb(bool) {}
void rightarrow_key_pressed_cb(bool) {}
void downarrow_key_pressed_cb(void) {}
void refresh_key_pressed_cb(void) {}
#endif
/* ****************** */
/* OLED SECTION END */
/* ****************** */
