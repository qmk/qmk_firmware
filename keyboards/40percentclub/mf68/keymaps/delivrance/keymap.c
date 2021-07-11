/*
 * Dan's Magicforce 68 (MF68) QMK Keyboard
 * Copyright (C) Dan <https://github.com/delivrance>
 *
 * This file is part of Dan's MF68 QMK Keyboard.
 *
 * Dan's MF68 QMK Keyboard is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Dan's MF68 QMK Keyboard is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Dan's MF68 QMK Keyboard.  If not, see <https://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

#define KC_ KC_TRNS

#define KC_FN1 MO(_FN)
#define KC_FN2 LT(_FN, KC_CAPS)

#define KC_BLUP BL_INC   // Backlight increase
#define KC_BLDN BL_DEC   // Backlight decrease
#define KC_BLTOG BL_TOGG // Backlight toggle
#define KC_TERM TERM_ON  // Terminal mode on
#define KC_REC1 DM_REC1  // Record macro 1
#define KC_PLY1 DM_PLY1  // Play macro 1
#define KC_REC2 DM_REC2  // Record macro 2
#define KC_PLY2 DM_PLY2  // Play macro 1
#define KC_RSTP DM_RSTP  // Stop macro recording

enum {
    _QWERTY,
    _FN
};

/* ┏━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━━━━━┓ ┏━━━━┳━━━━┓
   ┃Esc ┃ 1! ┃ 2@ ┃ 3# ┃ 4$ ┃ 5% ┃ 6^ ┃ 7& ┃ 8* ┃ 9( ┃ 0) ┃ -_ ┃ =+ ┃   ←─   ┃ ┃Ins ┃PgUp┃
   ┣━━━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━━━━━┫ ┣━━━━╋━━━━┫
   ┃ Tab  ┃ Q  ┃ W  ┃ E  ┃ R  ┃ T  ┃ Y  ┃ U  ┃ I  ┃ O  ┃ P  ┃ [{ ┃ ]} ┃  \|  ┃ ┃Del ┃PgDn┃
   ┣━━━━━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━━━━━━┫ ┗━━━━┻━━━━┛
   ┃  Caps  ┃ A  ┃ S  ┃ D  ┃ F  ┃ G  ┃ H  ┃ J  ┃ K  ┃ L  ┃ ;: ┃ '" ┃  Enter  ┃  Magicforce
   ┣━━━━━━━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━━━━━━━━━┫ ┏━━━━┓
   ┃   Shift  ┃ Z  ┃ X  ┃ C  ┃ V  ┃ B  ┃ N  ┃ M  ┃ ,< ┃ .> ┃ /? ┃    Shift   ┃ ┃ ↑  ┃ Dan
   ┣━━━━━┳━━━━┻┳━━━┻━┳━━┻━━━━┻━━━━┻━━━━┻━━━━┻━━━━┻━━━┳┻━━━━╋━━━━┻┳━━━━━┳━━┳━━┻━╋━━━━╋━━━━┓
   ┃Ctrl ┃ GUI ┃ Alt ┃             ━━━━━             ┃ Alt ┃ Fn  ┃Ctrl ┃  ┃ ←  ┃ ↓  ┃ →  ┃
   ┗━━━━━┻━━━━━┻━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━┻━━━━━┻━━━━━┛  ┗━━━━┻━━━━┻━━━━┛ */

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT_kc( /* Default layer
   ┏━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━━━━━┓ ┏━━━━┳━━━━┓ */
    GESC, 1  , 2  , 3  , 4  , 5  , 6  , 7  , 8  , 9  , 0  ,MINS,EQL ,  BSPC  ,  INS ,PGUP, /*
   ┣━━━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━━━━━┫ ┣━━━━╋━━━━┫ */
     TAB  , Q  , W  , E  , R  , T  , Y  , U  , I  , O  , P  ,LBRC,RBRC, BSLS ,  DEL ,PGDN, /*
   ┣━━━━━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━━━━━━┫ ┗━━━━┻━━━━┛ */
      FN2   , A  , S  , D  , F  , G  , H  , J  , K  , L  ,SCLN,QUOT,  ENTER  ,             /*
   ┣━━━━━━━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━┳━━┻━━━━━━━━━┫ ┏━━━━┓      */
       LSFT   , Z  , X  , C  , V  , B  , N  , M  ,COMM,DOT ,SLSH,    RSFT    ,   UP ,      /*
   ┣━━━━━┳━━━━┻┳━━━┻━┳━━┻━━━━┻━━━━┻━━━━┻━━━━┻━━━━┻━━━┳┻━━━━╋━━━━┻┳━━━━━┳━━┳━━┻━╋━━━━╋━━━━┓ */
    LCTL ,LGUI ,LALT ,             SPACE             ,RALT , FN1 ,RCTL ,   LEFT,DOWN,RGHT  /*
   ┗━━━━━┻━━━━━┻━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━┻━━━━━┻━━━━━┛  ┗━━━━┻━━━━┻━━━━┛ */),

[_FN] = LAYOUT_kc( /* FN & CAPS layer
   ┏━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━━━━━┓ ┏━━━━┳━━━━┓ */
    GRV , F1 , F2 , F3 , F4 , F5 , F6 , F7 , F8 , F9 , F10, F11, F12,  RSTP  ,  PSCR,HOME, /*
   ┣Esc ┻ 1! ┻ 2@ ┻ 3# ┻ 4$ ┻ 5% ┻ 6^ ┻ 7& ┻ 8* ┻ 9( ┻ 0) ┻ -_ ┻ =+ ┻━┳━ ←─ ━┫ ┣Ins ╋PgUp┫ */
          ,PLY1,PLY2,    ,    ,    ,    ,    , 7  , 8  , 9  ,BLDN,BLUP,BLTOG ,      ,END , /*
   ┣ Tab ━┻ Q ━┻ W ━┻ E ━┻ R ━┻ T ━┻ Y ━┻ U ━┻ I ━┻ O ━┻ P ━┻ [{ ┻ ]} ┻━ \| ━┫ ┗Del ┻PgDn┛ */
            ,    ,    ,    ,    ,    ,    ,    , 4  , 5  , 6  ,    ,   TERM  ,             /*
   ┣━ Caps ━┻ A ━┻ S ━┻ D ━┻ F ━┻ G ━┻ H ━┻ J ━┻ K ━┻ L ━┻ ;: ┻ '" ┻━ Enter ━┫ ┏━━━━┓      */
              ,REC1,REC2,    ,    ,MSTP,    ,MUTE, 1  , 2  , 3  ,            ,  VOLU,      /*
   ┣━━ Shift ━┻ Z ━┻ X ━┻ C ━┻ V ━┻ B ━┻ N ━┻ M ━┻ ,< ┻ .> ╋ /? ┻┳━━ Shift ━━┻━╋ ↑ ━╋━━━━┓ */
         ,     ,     ,             MPLY              ,  0  ,     ,     ,   MPRV,VOLD,MNXT  /*
   ┗Ctrl ┻ GUI ┻ Alt ┻━━━━━━━━━━━━ Space ━━━━━━━━━━━━┻ Alt ┻ Fn ━┻Ctrl ┛  ┗ ← ━┻ ↓ ━┻ → ━┛ */)
};
// clang-format on

// Initialization code
// -------------------

void keyboard_post_init_user(void) {
    backlight_level(2);
}

// Custom backlight driver
// -----------------------

// http://jared.geek.nz/2013/feb/linear-led-pwm
float cie1931(float x) {
    x *= 100.0 / BACKLIGHT_LEVELS;
    float y;

    if (x < 8) {
        y = x / 902.3;
    } else {
        y = (x + 16.0) / 116.0;
        y = y * y * y;
    }

    return round(y * 255);
}

void backlight_init_ports(void) {
    setPinOutput(BACKLIGHT_PIN);
    writePinLow(BACKLIGHT_PIN);

    TCCR1A = _BV(COM1A1) | _BV(WGM11);
    TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10);

    ICR1 = 0xFFU;  // Set PWM levels to 255 (enables high-frequency PWM)
}

void backlight_set(uint8_t level) {
    if (level > BACKLIGHT_LEVELS) {
        level = BACKLIGHT_LEVELS;
    }

    if (level == 0) {
        TCCR1A &= ~(_BV(COM1A1));  // Disable PWM
    } else {
        TCCR1A |= _BV(COM1A1);  // Enable PWM
    }

    OCR1A = cie1931(level);
}

// Custom macro hooks
// ------------------

// Redefine with lower delay
void led_blink(void) {
    backlight_toggle();
    wait_ms(25);
    backlight_toggle();
}

void dynamic_macro_record_start_user(void) {
    led_blink();
}

void dynamic_macro_play_user(int8_t direction) {
    led_blink();
}

void dynamic_macro_record_key_user(int8_t direction, keyrecord_t *record) {
    led_blink();
}

void dynamic_macro_record_end_user(int8_t direction) {
    led_blink();
}

// Custom Caps Lock backlight behaviour
// ------------------------------------

void led_set_user(uint8_t usb_led) {
    // This exists because I don't like the backlight to turn OFF when the Caps Lock is ON.
    // That is, this will turn the backlight ON (at half the brightness) when the Caps Lock is ON as well.
    static bool prev_is_caps_on;
    bool is_caps_on = IS_LED_ON(usb_led, USB_LED_CAPS_LOCK);

    if (prev_is_caps_on != is_caps_on) {
        prev_is_caps_on = is_caps_on;

        if (is_caps_on) {
            backlight_set(BACKLIGHT_LEVELS / 2);
        } else {
            if (is_backlight_enabled()) {
                backlight_set(get_backlight_level());
            } else {
                backlight_set(0);
            }
        }
    }

    // Turn on the Pro Micro's on-board LEDs for Caps Lock
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        // Set to low
        setPinOutput(B0);
        writePinLow(B0);
        setPinOutput(D5);
        writePinLow(D5);
    } else {
        // Set to Hi-Z
        setPinInput(B0);
        setPinInput(D5);
    }
}

// Backlight idle timeout feature
// ------------------------------

static uint32_t timer;
static bool is_idle;

void matrix_scan_user() {
    // Check the timer only if the keyboard is not idle
    if (!is_idle) {
        if (timer_elapsed32(timer) >= (uint32_t) BACKLIGHT_IDLE_TIMEOUT * 1000) {
            is_idle = true;

            // Both backlight_level and backlight_level_noeeprom modify the global backlight config (not useful)
            // Instead, use backlight_set in order to restore the current backlight level later on
            backlight_set(0);
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Reset timer on each keypress
    timer = timer_read32();

    // Enable backlight back only when keyboard is idling (which implies the backlight was turned off previously)
    if (is_idle) {
        is_idle = false;

        // Set back the original backlight level only if it is actually enabled globally
        if (is_backlight_enabled()) {
            // The current backlight level can be obtained with get_backlight_level
            backlight_set(get_backlight_level());
        }
    }

    return true;
}
