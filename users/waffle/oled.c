/* Copyright 2021 @waffle#0007
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

#include "waffle.h"
#include <stdio.h>
static uint32_t oled_timer = 0;
uint8_t num_keypresses = 0;
uint8_t flower_frame = 0;
uint8_t current_idle_frame = 0;
uint8_t current_tap_frame = 0;
uint8_t current_frame = 0;
uint32_t anim_timer = 0;
uint32_t anim_sleep = 0;
int current_wpm = 0;
led_t led_usb_state;
bool isSneaking = false;
bool isJumping = false;
bool showedJump = true;
bool anim_phase = false;
char keylog_str[KEYLOG_LEN] = {};
uint8_t  keylogs_str_idx = 0;
uint16_t log_timer = 0;

void render_wpm(void) {
    uint8_t n = get_current_wpm();
    char wpm_counter[6];
    wpm_counter[5] = '\0';
    wpm_counter[4] = '0' + n % 10;
    wpm_counter[3] = ( n /= 10) % 10 ? '0' + (n) % 10 : (n / 10) % 10 ? '0' : ' ';
    wpm_counter[2] = n / 10 ? '0' + n / 10 : ' ';
    wpm_counter[1] = ' ';
    wpm_counter[0] = ' ';
    oled_write_P(PSTR("WPM:"), false);
    oled_write(wpm_counter, false);
}

void render_wpm_num(void) {
    char wpm_string[5];
    snprintf(wpm_string, sizeof(wpm_string), " %3d", get_current_wpm());
    oled_write(wpm_string, false);
}

void render_qmk_logo(void) {
    static const char PROGMEM font_qmk_logo[16] = {0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0};
    oled_write_P(font_qmk_logo, false);
};

void render_keyboard(void) {
    static const char PROGMEM font_keyboard[16] = {0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0};
    oled_write_P(font_keyboard, false);
};

void render_mod_ctrl(void) { // ^
    static const char PROGMEM font_ctrl[3] = {0x93, 0x94, 0};
    oled_write_P(font_ctrl, false);
};

void render_mod_alt(void) { // ⌥
    static const char PROGMEM font_alt[3] = {0xb3, 0xb4, 0};
    oled_write_P(font_alt, false);
};

void render_mod_shift(void) { // ⇧
    static const char PROGMEM font_shift[3] = {0xd3, 0xd4, 0};
    oled_write_P(font_shift, false);
};

void render_mod_gui(void) { // win symbol
    static const char PROGMEM font_gui[3] = {0x95, 0x96, 0};
    oled_write_P(font_gui, false);
};

void render_prompt(void) {
    bool blink = (timer_read() % 1000) < 500;
        if (layer_state_is(1)) {        oled_write_ln_P(blink ? PSTR("> lo_") : PSTR("> lo "), false);
        } else if (layer_state_is(2)) { oled_write_ln_P(blink ? PSTR("> hi_") : PSTR("> hi "), false);
        } else if (layer_state_is(3)) { oled_write_ln_P(blink ? PSTR("> ad_") : PSTR("> ad "), false);
        } else {                        oled_write_ln_P(blink ? PSTR("> _ ") : PSTR(">     "), false); }
};

void render_mod_status(void) {
    bool blink = (timer_read() % 1000) < 500;
    uint8_t modifiers = get_mods() | get_oneshot_mods();
        if (modifiers & MOD_MASK_CTRL) {            oled_write_ln_P(blink ? PSTR("$ ctl") : PSTR("$ _  "), false);
        } else if (modifiers & MOD_MASK_SHIFT) {    oled_write_ln_P(blink ? PSTR("$ sft") : PSTR("$ _  "), false);
        } else if (modifiers & MOD_MASK_ALT) {      oled_write_ln_P(blink ? PSTR("$ alt") : PSTR("$ _  "), false);
        } else if (modifiers & MOD_MASK_GUI) {      oled_write_ln_P(blink ? PSTR("$ gui") : PSTR("$ _  "), false);
        } else {                                    oled_write_ln_P(blink ? PSTR("$ _  ") : PSTR("$    "), false); }
}

void render_keylock_status(uint8_t led_usb_state) {
    bool blink = (timer_read() % 1000) < 500;
        if (led_usb_state & (1 << USB_LED_CAPS_LOCK)) {             oled_write_ln_P(blink ? PSTR("% cap") : PSTR("% _  "), false);
        } else if (led_usb_state & (1 << USB_LED_NUM_LOCK)) {       oled_write_ln_P(blink ? PSTR("% num") : PSTR("% _  "), false);
        } else if (led_usb_state & (1 << USB_LED_SCROLL_LOCK)) {    oled_write_ln_P(blink ? PSTR("% scr") : PSTR("% _  "), false);
        } else {                                                    oled_write_ln_P(blink ? PSTR("% _  ") : PSTR("%    "), false); }
}

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void add_keylog(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
    for (uint8_t i = KEYLOG_LEN - 1; i > 0; i--) { keylog_str[i] = keylog_str[i - 1]; }
    if (keycode < 60) { keylog_str[0] = code_to_name[keycode]; }
    keylog_str[KEYLOG_LEN - 1] = 0;
    log_timer = timer_read();
}

void update_log(void) { if (timer_elapsed(log_timer) > 750) { add_keylog(0); } }
void render_keylogger(void) { oled_write(keylog_str, false); }

void render_keylogger_status(void) {
    bool blink = (timer_read() % 1000) < 500;
    oled_write_ln_P(blink ? PSTR("~ _") : PSTR("~  "), false);
}

bool process_record_user_oled(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        oled_timer = timer_read32();
        add_keylog(keycode);
        num_keypresses = num_keypresses + 1;
        if (flower_frame < (FLOWER_FRAMES - 1)) { if (num_keypresses % GROW_RATE == 0) { flower_frame = flower_frame + 1; } }
    }
    return true;
    switch (keycode) {
        case KC_SPC:
            if (record->event.pressed) {
                isJumping = true;
                showedJump = false;
            } else {
                isJumping = false;
            }
            break;
        case KC_LCTL:
        case KC_RCTL:
            isSneaking = record->event.pressed;
        break;
    }
    return true;
}

void render_main(void) {
  oled_set_cursor(0, 0);
  render_wpm();
  oled_set_cursor(0, 3);
  render_qmk_logo();
  oled_set_cursor(0, 7);
  render_keyboard();
  oled_set_cursor(0, 9);
  render_prompt();
  oled_set_cursor(0, 11);
  render_mod_status();
  oled_set_cursor(0, 13);
  render_keylock_status(host_keyboard_leds());
  oled_set_cursor(1, 15);
  render_keylogger();
  oled_set_cursor(0, 15);
  render_keylogger_status();
}

static void render_bongo(void) {
    void animation_phase(void) {
        if (get_current_wpm() <= BONGO_IDLE_SPEED) {
            current_idle_frame = (current_idle_frame + 1) % BONGO_IDLE_FRAMES;
            oled_write_raw_P(idle[abs((BONGO_IDLE_FRAMES - 1) - current_idle_frame)], BONGO_SIZE);
        } if (get_current_wpm() > BONGO_IDLE_SPEED && get_current_wpm() < BONGO_TAP_SPEED) {
            oled_write_raw_P(prep[0], BONGO_SIZE);
        } if (get_current_wpm() >= BONGO_TAP_SPEED) {
            current_tap_frame = (current_tap_frame + 1) % BONGO_TAP_FRAMES;
            oled_write_raw_P(table_tap[abs((BONGO_TAP_FRAMES - 1) - current_tap_frame)], BONGO_SIZE);
        }
    }

    if (get_current_wpm() != 000) {
        if (timer_elapsed32(anim_timer) > BONGO_FELIX_FRAME_DURATION) {
            anim_timer = timer_read32();
            animation_phase();
        }
        anim_sleep = timer_read32();
    }  else if (timer_elapsed32(anim_timer) > BONGO_FELIX_FRAME_DURATION) {
        anim_timer = timer_read32();
        animation_phase();
    }
}

void render_cat(void) { render_bongo(); }

static void render_felix(int FELIX_X, int FELIX_Y) {
    void animation_phase (void) {
        if (isJumping || !showedJump) {
            oled_set_cursor(FELIX_X, FELIX_Y + 2);
            oled_write("     ", false);
            oled_set_cursor(FELIX_X, FELIX_Y - 1);
            showedJump = true;
        } else {
            oled_set_cursor(FELIX_X, FELIX_Y - 1);
            oled_write("     ", false);
            oled_set_cursor(FELIX_X, FELIX_Y);
        }
        current_frame = (current_frame + 1) % 2;

        if (led_usb_state.caps_lock) {              oled_write_raw_P(bark[abs(1 - current_frame)], FELIX_SIZE);
        } else if (isSneaking) {                    oled_write_raw_P(sneak[abs(1 - current_frame)], FELIX_SIZE);
        } else if (current_wpm <= MIN_WALK_SPEED) { oled_write_raw_P(sit[abs(1 - current_frame)], FELIX_SIZE);
        } else if (current_wpm <= MIN_RUN_SPEED) {  oled_write_raw_P(walk[abs(1 - current_frame)], FELIX_SIZE);
        } else {                                    oled_write_raw_P(run[abs(1 - current_frame)], FELIX_SIZE); }
    }

    if (timer_elapsed32(anim_timer) > BONGO_FELIX_FRAME_DURATION) {
        anim_timer = timer_read32();
        animation_phase();
    }
    if (current_wpm > 0) {
        oled_on();
        anim_sleep = timer_read32();
    } else if (timer_elapsed32(anim_sleep) > OLED_TIMEOUT) { oled_off(); }
}

void render_dog(void) { render_felix(0, 5); }

void animation_run(void) {
    if (timer_elapsed32(anim_sleep) > OLED_TIMEOUT) { oled_off(); } else {
        if (timer_elapsed32(anim_timer) > LAYER_FRAME_DURATION) {
            anim_timer = timer_read32();
            anim_phase = true;
        }
    }
}

static void render_anim_num(void) {
    if (anim_phase == true) {
        current_tap_frame = (current_tap_frame + 1) % LAYER_TAP_FRAMES;
	oled_write_raw_P(tap_num[abs((LAYER_TAP_FRAMES-1)-current_tap_frame)], LAYER_SIZE);
        anim_phase = false;
    }
    animation_run();
}

static void render_anim_sym(void) {
    if (anim_phase == true) {
        current_tap_frame = (current_tap_frame + 1) % (LAYER_TAP_FRAMES + 1);
        oled_write_raw_P(tap_sym[abs((LAYER_TAP_FRAMES - 1) - current_tap_frame)], XANIM_SIZE);
        anim_phase = false;
    }
    animation_run();
}

static void render_anim_sys(void) {
    if (anim_phase == true) {
        current_tap_frame = (current_tap_frame + 1) % (LAYER_TAP_FRAMES + 1);
        oled_write_raw_P(tap_sys[abs((LAYER_TAP_FRAMES - 1) - current_tap_frame)], LAYER_SIZE);
        anim_phase = false;
    }
    animation_run();
}

void render_secondary(void) {
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            render_bongo();
            break;
        case _LOWER:
            render_anim_num();
            break;
        case _RAISE:
            render_anim_sym();
            break;
        case _ADJUST:
            render_anim_sys();
            break;
    }
}

void flower_anim(void) { oled_write_raw_P(plant_anim[current_frame], FLOWER_SIZE); }

#ifdef KEYBOARD_crkbd
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) { return 3; } else { return 2; }
    return rotation;
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
      render_secondary();
    } else {
      render_main();
    }
}
#endif

