// Copyright 2026 Anefecious
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _BASE = 0,
    _MEDIA,
    _NUMBERS,
    LAYER_COUNT
};

enum custom_keycodes {
    OS_TOGGLE = SAFE_RANGE,
    OS_COPY,
    OS_PASTE,
    OS_CUT,
    OS_UNDO,
    OS_REDO,
    OS_SELL,
    OS_SS,
    OS_DESK,
    OS_APP,
    OS_MIC,
    LYR_NEXT,
    LYR_PREV,
    LYR_HOME,
    // Numbers layer: tap = 0, hold = jump to BASE
    NUM_ZERO
};

typedef union {
    uint32_t raw;
    struct {
        // 0 (EEPROM default) = macOS, 1 = Windows
        bool is_win : 1;
    };
} user_config_t;

user_config_t user_config;

#define IS_MAC() (!user_config.is_win)

// Screenshot key toggles: 1st press starts capture, 2nd press sends Esc to cancel.
#define SCREENSHOT_ARM_MS 60000
static bool     screenshot_armed    = false;
static uint16_t screenshot_armed_at = 0;

// NUM_ZERO: short tap sends 0; hold returns to BASE.
#ifndef NUM_ZERO_HOLD_MS
#    define NUM_ZERO_HOLD_MS 400
#endif
static bool     num_zero_active     = false;
static bool     num_zero_long_fired = false;
static uint16_t num_zero_timer      = 0;

#ifdef OLED_ENABLE
// Rotated 128x32 => 5 characters wide.
#define OLED_LABEL_LEN 5
#define OLED_EYE_TICK_MS 160
#define OLED_EYE_ALERT_MS 900
static char     oled_key_label[OLED_LABEL_LEN + 1] = ".";
static bool     oled_dirty                         = true;
static uint16_t oled_last_key_time                 = 0;

static void oled_set_key_label(const char *label) {
    uint8_t i = 0;
    for (; label[i] != '\0' && i < OLED_LABEL_LEN; i++) {
        oled_key_label[i] = label[i];
    }
    for (; i < OLED_LABEL_LEN; i++) {
        oled_key_label[i] = ' ';
    }
    oled_key_label[OLED_LABEL_LEN] = '\0';
    oled_dirty                     = true;
    oled_last_key_time             = timer_read();
}

static void oled_set_key_from_keycode(uint16_t keycode) {
    switch (keycode) {
        case OS_TOGGLE:
            oled_set_key_label(">OS");
            break;
        case OS_COPY:
            oled_set_key_label(">COPY");
            break;
        case OS_PASTE:
            oled_set_key_label(">PSTE");
            break;
        case OS_CUT:
            oled_set_key_label(">CUT");
            break;
        case OS_UNDO:
            oled_set_key_label(">UNDO");
            break;
        case OS_REDO:
            oled_set_key_label(">REDO");
            break;
        case OS_SELL:
            oled_set_key_label(">ALL");
            break;
        case OS_SS:
            oled_set_key_label(">SHOT");
            break;
        case OS_DESK:
            oled_set_key_label(">DESK");
            break;
        case OS_APP:
            oled_set_key_label(">APP");
            break;
        case OS_MIC:
            oled_set_key_label(">MIC");
            break;
        case LYR_NEXT:
            oled_set_key_label(">NEXT");
            break;
        case LYR_PREV:
            oled_set_key_label(">PREV");
            break;
        case LYR_HOME:
            oled_set_key_label(">HOME");
            break;
        case NUM_ZERO:
        case KC_0:
            oled_set_key_label(">0");
            break;
        case KC_1:
            oled_set_key_label(">1");
            break;
        case KC_2:
            oled_set_key_label(">2");
            break;
        case KC_3:
            oled_set_key_label(">3");
            break;
        case KC_4:
            oled_set_key_label(">4");
            break;
        case KC_5:
            oled_set_key_label(">5");
            break;
        case KC_6:
            oled_set_key_label(">6");
            break;
        case KC_7:
            oled_set_key_label(">7");
            break;
        case KC_8:
            oled_set_key_label(">8");
            break;
        case KC_9:
            oled_set_key_label(">9");
            break;
        case KC_MUTE:
            oled_set_key_label(">MUTE");
            break;
        case KC_VOLD:
            oled_set_key_label(">VOL-");
            break;
        case KC_VOLU:
            oled_set_key_label(">VOL+");
            break;
        case KC_MPLY:
            oled_set_key_label(">PLAY");
            break;
        case KC_MPRV:
            oled_set_key_label(">MPRV");
            break;
        case KC_MNXT:
            oled_set_key_label(">MNXT");
            break;
        case KC_BRID:
            oled_set_key_label(">BRI-");
            break;
        case KC_BRIU:
            oled_set_key_label(">BRI+");
            break;
        case MS_WHLD:
            oled_set_key_label(">SCR-");
            break;
        case MS_WHLU:
            oled_set_key_label(">SCR+");
            break;
        default:
            oled_set_key_label(">KEY");
            break;
    }
}

// Pad exactly to oled_max_chars() and let the driver wrap — never append '\n'
// after a full row (that skips a blank line on narrow rotated panels).
static void oled_write_line_P(const char *progmem_str) {
    const uint8_t width = oled_max_chars();
    char          buf[21];
    uint8_t       i     = 0;
    uint8_t       limit = width < 20 ? width : 20;

    while (i < limit) {
        char c = pgm_read_byte(progmem_str + i);
        if (c == '\0') {
            break;
        }
        buf[i++] = c;
    }
    while (i < limit) {
        buf[i++] = ' ';
    }
    buf[i] = '\0';
    oled_write(buf, false);
}

static void oled_write_line(const char *str) {
    const uint8_t width = oled_max_chars();
    char          buf[21];
    uint8_t       i     = 0;
    uint8_t       limit = width < 20 ? width : 20;

    while (i < limit && str[i] != '\0') {
        buf[i] = str[i];
        i++;
    }
    while (i < limit) {
        buf[i++] = ' ';
    }
    buf[i] = '\0';
    oled_write(buf, false);
}
#endif

static void tap_mod_key(uint16_t mod, uint16_t key) {
    register_code(mod);
    tap_code(key);
    unregister_code(mod);
}

static void tap_mods_key(uint16_t mod1, uint16_t mod2, uint16_t key) {
    register_code(mod1);
    register_code(mod2);
    tap_code(key);
    unregister_code(mod2);
    unregister_code(mod1);
}

static void screenshot_clear_armed(void) {
    screenshot_armed = false;
}

static void screenshot_toggle(void) {
    if (screenshot_armed) {
        tap_code(KC_ESC);
        screenshot_clear_armed();
#ifdef OLED_ENABLE
        oled_set_key_label(">ESC");
#endif
        return;
    }

    if (IS_MAC()) {
        tap_mods_key(KC_LGUI, KC_LSFT, KC_4);
    } else {
        tap_mods_key(KC_LGUI, KC_LSFT, KC_S);
    }
    screenshot_armed    = true;
    screenshot_armed_at = timer_read();
#ifdef OLED_ENABLE
    oled_set_key_label(">SHOT");
#endif
}

static void send_os_shortcut(uint16_t keycode) {
    const bool mac = IS_MAC();

    switch (keycode) {
        case OS_COPY:
            tap_mod_key(mac ? KC_LGUI : KC_LCTL, KC_C);
            break;
        case OS_PASTE:
            tap_mod_key(mac ? KC_LGUI : KC_LCTL, KC_V);
            break;
        case OS_CUT:
            tap_mod_key(mac ? KC_LGUI : KC_LCTL, KC_X);
            break;
        case OS_UNDO:
            tap_mod_key(mac ? KC_LGUI : KC_LCTL, KC_Z);
            break;
        case OS_REDO:
            if (mac) {
                tap_mods_key(KC_LGUI, KC_LSFT, KC_Z);
            } else {
                tap_mod_key(KC_LCTL, KC_Y);
            }
            break;
        case OS_SELL:
            tap_mod_key(mac ? KC_LGUI : KC_LCTL, KC_A);
            break;
        case OS_DESK:
            if (mac) {
                tap_mod_key(KC_LCTL, KC_UP);
            } else {
                tap_mod_key(KC_LGUI, KC_TAB);
            }
            break;
        case OS_APP:
            tap_mod_key(mac ? KC_LGUI : KC_LALT, KC_TAB);
            break;
        case OS_MIC:
            tap_mods_key(mac ? KC_LGUI : KC_LCTL, KC_LSFT, KC_M);
            break;
    }
}

static void handle_custom_keycode(uint16_t keycode, bool pressed) {
    if (!pressed) {
        return;
    }

    switch (keycode) {
        case OS_TOGGLE:
            user_config.is_win ^= 1;
            eeconfig_update_user(user_config.raw);
#ifdef OLED_ENABLE
            oled_dirty = true;
#endif
            break;
        case OS_SS:
            screenshot_toggle();
            break;
        case OS_COPY:
        case OS_PASTE:
        case OS_CUT:
        case OS_UNDO:
        case OS_REDO:
        case OS_SELL:
        case OS_DESK:
        case OS_APP:
        case OS_MIC:
            send_os_shortcut(keycode);
            break;
        case LYR_NEXT:
            layer_move((get_highest_layer(layer_state) + 1) % LAYER_COUNT);
#ifdef OLED_ENABLE
            oled_dirty = true;
#endif
            break;
        case LYR_PREV:
            layer_move((get_highest_layer(layer_state) + LAYER_COUNT - 1) % LAYER_COUNT);
#ifdef OLED_ENABLE
            oled_dirty = true;
#endif
            break;
        case LYR_HOME:
            layer_move(_BASE);
#ifdef OLED_ENABLE
            oled_dirty = true;
#endif
            break;
        case NUM_ZERO:
            // Handled in process_record_user / matrix_scan_user (tap vs hold).
            break;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        OS_COPY,  OS_PASTE, OS_CUT,
        OS_UNDO,  OS_REDO,  OS_SELL,
        OS_SS,    OS_DESK,  OS_APP,
        LYR_PREV, LYR_HOME, LYR_NEXT
    ),
    [_MEDIA] = LAYOUT(
        KC_MPLY,  KC_MPRV,  KC_MNXT,
        KC_MUTE,  KC_VOLD,  KC_VOLU,
        OS_MIC,   KC_BRID,  KC_BRIU,
        LYR_PREV, LYR_HOME, LYR_NEXT
    ),
    [_NUMBERS] = LAYOUT(
        KC_1,     KC_2,     KC_3,
        KC_4,     KC_5,     KC_6,
        KC_7,     KC_8,     KC_9,
        LYR_PREV, NUM_ZERO, LYR_NEXT
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE]    = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(MS_WHLD, MS_WHLU)},
    [_MEDIA]   = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(MS_WHLD, MS_WHLU)},
    [_NUMBERS] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(MS_WHLD, MS_WHLU)}
};
#endif

void eeconfig_init_user(void) {
    user_config.raw    = 0;
    user_config.is_win = false;
    eeconfig_update_user(user_config.raw);
}

void keyboard_post_init_user(void) {
    user_config.raw = eeconfig_read_user();
#ifdef OLED_ENABLE
    oled_set_key_label("-");
    oled_dirty = true;
#endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef OLED_ENABLE
        oled_set_key_from_keycode(keycode);
#endif
    }

    switch (keycode) {
        case NUM_ZERO:
            if (record->event.pressed) {
                num_zero_active     = true;
                num_zero_long_fired = false;
                num_zero_timer      = timer_read();
            } else {
                if (num_zero_active && !num_zero_long_fired) {
                    tap_code(KC_0);
#ifdef OLED_ENABLE
                    oled_set_key_label(">0");
#endif
                }
                num_zero_active = false;
            }
            return false;
        case OS_TOGGLE:
        case OS_COPY:
        case OS_PASTE:
        case OS_CUT:
        case OS_UNDO:
        case OS_REDO:
        case OS_SELL:
        case OS_SS:
        case OS_DESK:
        case OS_APP:
        case OS_MIC:
        case LYR_NEXT:
        case LYR_PREV:
        case LYR_HOME:
            handle_custom_keycode(keycode, record->event.pressed);
            return false;
    }
    return true;
}

// Encoder push-buttons are GPIO-to-GND and bounce hard — debounce + cooldown.
#define ENC_BTN_DEBOUNCE_MS 40
#define ENC_BTN_TOGGLE_COOLDOWN_MS 450

typedef struct {
    bool     stable;      // debounced pressed state
    bool     raw_prev;    // last raw sample
    uint16_t changed_at;  // when raw last flipped
} enc_btn_t;

// Returns true once when debounced state changes.
static bool enc_btn_update(enc_btn_t *btn, pin_t pin) {
    bool raw = !gpio_read_pin(pin);

    if (raw != btn->raw_prev) {
        btn->raw_prev   = raw;
        btn->changed_at = timer_read();
    }

    if (timer_elapsed(btn->changed_at) < ENC_BTN_DEBOUNCE_MS) {
        return false;
    }

    if (raw == btn->stable) {
        return false;
    }

    btn->stable = raw;
    return true;
}

void matrix_scan_user(void) {
    if (screenshot_armed && timer_elapsed(screenshot_armed_at) > SCREENSHOT_ARM_MS) {
        screenshot_clear_armed();
    }

    // NUM_ZERO hold → BASE (fires while still held, past threshold).
    if (num_zero_active && !num_zero_long_fired && timer_elapsed(num_zero_timer) > NUM_ZERO_HOLD_MS) {
        num_zero_long_fired = true;
        layer_move(_BASE);
#ifdef OLED_ENABLE
        oled_set_key_label(">HOME");
        oled_dirty = true;
#endif
    }

    static enc_btn_t left_btn       = {0};
    static enc_btn_t right_btn      = {0};
    static uint16_t  os_cooldown_at = 0;
    static bool      os_cooled      = false;

    if (enc_btn_update(&left_btn, ENC_L_BTN_PIN)) {
        if (left_btn.stable) {
#ifdef OLED_ENABLE
            oled_set_key_label(">MUTE");
#endif
            register_code(KC_MUTE);
        } else {
            unregister_code(KC_MUTE);
        }
    }

    if (enc_btn_update(&right_btn, ENC_R_BTN_PIN)) {
        // OS toggle only on press; ignore bounce / double-fires for a bit.
        bool cooled = !os_cooled || timer_elapsed(os_cooldown_at) > ENC_BTN_TOGGLE_COOLDOWN_MS;
        if (right_btn.stable && cooled) {
            os_cooled      = true;
            os_cooldown_at = timer_read();
#ifdef OLED_ENABLE
            oled_set_key_label(">OS");
#endif
            handle_custom_keycode(OS_TOGGLE, true);
        }
    }
}

#ifdef OLED_ENABLE
// Status at top (with blank gaps between rows); eyes near the bottom.
#define OLED_STATUS_LINES 7 // 4 text rows + 3 gap rows
#define OLED_MASCOT_LINES 5

// Blink phases: long open stare, then a slow close/open.
enum {
    EYE_OPEN = 0,
    EYE_HALF_DOWN,
    EYE_CLOSED,
    EYE_HALF_UP,
    EYE_PHASE_COUNT
};

// Dwell time per phase, in OLED_EYE_TICK_MS ticks (~160ms).
static const uint8_t eye_phase_ticks[EYE_PHASE_COUNT] = {
    14, // open ~2.2s
    2,  // closing
    2,  // shut
    2   // opening
};

static void oled_render_mascot(uint8_t phase, bool alert) {
    // 5-char-wide eyes; keep the slow blink + mouth the user liked.
    oled_write_line_P(PSTR(" "));

    if (alert) {
        oled_write_line_P(PSTR("0   0"));
        oled_write_line_P(PSTR("0   0"));
        oled_write_line_P(PSTR(" "));
        oled_write_line_P(PSTR(" ^_^ "));
        return;
    }

    switch (phase) {
        case EYE_HALF_DOWN:
            oled_write_line_P(PSTR("-   -"));
            oled_write_line_P(PSTR("O   O"));
            break;
        case EYE_CLOSED:
            oled_write_line_P(PSTR("-   -"));
            oled_write_line_P(PSTR("-   -"));
            break;
        case EYE_HALF_UP:
            oled_write_line_P(PSTR("O   O"));
            oled_write_line_P(PSTR("-   -"));
            break;
        case EYE_OPEN:
        default:
            oled_write_line_P(PSTR("O   O"));
            oled_write_line_P(PSTR("O   O"));
            break;
    }

    oled_write_line_P(PSTR(" "));
    oled_write_line_P(PSTR(" --- "));
}

static void oled_render_screen(uint8_t eye_phase, bool alert) {
    const uint8_t max_lines = oled_max_lines();
    uint8_t       spacer    = 0;

    if (max_lines > OLED_STATUS_LINES + OLED_MASCOT_LINES) {
        spacer = max_lines - OLED_STATUS_LINES - OLED_MASCOT_LINES;
    }

    oled_set_cursor(0, 0);
    oled_write_line_P(PSTR("KCPro"));
    oled_write_line_P(PSTR(" "));

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_line_P(PSTR("BASE"));
            break;
        case _MEDIA:
            oled_write_line_P(PSTR("MEDIA"));
            break;
        case _NUMBERS:
            oled_write_line_P(PSTR("NUMS"));
            break;
        default:
            oled_write_line_P(PSTR("???"));
            break;
    }
    oled_write_line_P(PSTR(" "));

    if (IS_MAC()) {
        oled_write_line_P(PSTR("MAC"));
    } else {
        oled_write_line_P(PSTR("WIN"));
    }
    oled_write_line_P(PSTR(" "));

    // Last key / encoder action (e.g. >SCR+)
    oled_write_line(oled_key_label);

    // Clear remaining space above the eyes.
    for (uint8_t i = 0; i < spacer; i++) {
        oled_write_line_P(PSTR(" "));
    }

    oled_render_mascot(eye_phase, alert);
}

bool oled_task_user(void) {
    static uint16_t eye_timer = 0;
    static uint8_t  eye_phase = EYE_OPEN;
    static uint8_t  eye_dwell = 0;

    bool anim_tick = timer_elapsed(eye_timer) > OLED_EYE_TICK_MS;
    if (!oled_dirty && !anim_tick) {
        return false;
    }

    if (anim_tick) {
        eye_timer = timer_read();
        eye_dwell++;
        if (eye_dwell >= eye_phase_ticks[eye_phase]) {
            eye_dwell = 0;
            eye_phase = (eye_phase + 1) % EYE_PHASE_COUNT;
        }
    }

    oled_dirty  = false;
    bool alert = timer_elapsed(oled_last_key_time) < OLED_EYE_ALERT_MS;
    oled_render_screen(eye_phase, alert);

    return false;
}
#endif
