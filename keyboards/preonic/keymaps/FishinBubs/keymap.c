/* Copyright 2015-2017 Jack Humbert
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
#include "muse.h"

enum preonic_layers {
  _QWERTY,
  _PLOVER,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  PLOVER,
  LOWER,
  RAISE,
  BACKLIT,
  GIRAFFACT,
  GIRAFF,
  FFACT,
  EXT_PLV
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Caps |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid(
 KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,  KC_5,   KC_6,   KC_7,  KC_8,    KC_9,    KC_0,    KC_DEL,
 KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,   KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC, 
 KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,  KC_G,   KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT, 
 KC_CAPS, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,   KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_ENT, 
 KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, LOWER, KC_SPC, KC_SPC, RAISE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Plover layer (http://opensteno.org)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   A  |   R  |   S  |   T  |   *  |   *  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   Z  |   X  |   C  |   V  |   *  |   *  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Exit |      |      |   A  |   O  |    Space    |   E  |   U  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_PLOVER] = LAYOUT_preonic_grid(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_SCLN, KC_DEL,
  XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
  XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  EXT_PLV, XXXXXXX, XXXXXXX, KC_C,    KC_V,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |      |      |      |      |      |      |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |RShift|RCtrl | Ralt | RGUI |      |             |      | Home | PgDn | PgUp | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid(
 KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, 
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC, 
 KC_DEL,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, 
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
 KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |  n1  |  n2  |  n3  |  n4  |  n5  |  n6  |  n7  |  n8  |  n9  |  n0  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |      |      |      |      |      |      |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |RShift|RCtrl | RAlt | RGUI |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid(
  KC_TILD, KC_P1,   KC_P2,   KC_P3,   KC_P4,   KC_P5,   KC_P6,    KC_P7,   KC_P8,   KC_P9,   KC_P0,   KC_DEL,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC, 
  KC_DEL,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, 
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
  KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * | Play |Numlck|Scroll|Insert| Menu |Print |Scren+|Scren-|Game1 |Game2 |Game3 |Game4 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Reset | Debug| Hue+ | Hue- | Sat+ | Sat- | Bri+ | Bri- |Mode +|RGBTog|Plover| Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |BL Bth|MouseL|MouseD|MouseU|MouseR|Dacro1|Dacro2|Mouse1|Mouse2|Mouse3|Mouse4| LOCK |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |BL Cyc|Beeps-|Beeps+|Mus on|Musoff|Rec 1 |Rec 2 |MWhelL|MWhelD|MWhelU|MWhelR|Sleep |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |BL Tog|MUSmod|AudTog|Clicky|      |             |      |GIRAFF|GIRAF | FACT |Macro4|
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid(
 KC_MPLY, KC_NLCK, KC_SLCK, KC_INS , KC_APP , KC_PSCR,         KC_BRID,         KC_BRIU, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX,  
 RESET,   DEBUG,   RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,         RGB_VAI,         RGB_VAD, RGB_MODE_FORWARD, RGB_TOG, PLOVER,  KC_BSPC,
 BL_BRTG, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, DYN_MACRO_PLAY1, DYN_MACRO_PLAY2, KC_BTN1, KC_BTN2,          KC_BTN3, KC_BTN4, KC_LOCK,
 BL_STEP, CK_DOWN, CK_UP,   MU_ON,   MU_OFF,  DYN_REC_START1,  DYN_REC_START2,  KC_WH_L, KC_WH_D,          KC_WH_U, KC_WH_R, KC_SLEP,
 BL_TOGG, MU_MOD,  AU_TOG,  CK_TOGG, _______, _______,         _______,         _______, GIRAFFACT,        GIRAFF,  FFACT,   XXXXXXX
)

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif
        
layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

void matrix_init_user(void)
{
    set_voice(default_voice);
    startup_user();
    println("Matrix Init");
  //#ifdef RGB_MATRIX_ENABLE
    // Startup defaults
    //rgb_matrix_sethsv_noeeprom(HSV_RED);
    //rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS);
//#endif
}

void shutdown_user() {
  #ifdef RGBLIGHT_ENABLE
    rgblight_setrgb(RGB_RED);
  #endif
}

void rgb_matrix_indicators_user(void) {
  switch (get_highest_layer(layer_state)) {
     /*Planck rev6 LED index position:
       6   5   4   3
             0
       7   8   1   2 
       Planck rev6 LED physical position:
       14  15  16  17
             18
       20  21  22  19*/
    case _LOWER:
        rgb_matrix_set_color(6, 0x3A, 0x00, 0xFF);
        rgb_matrix_set_color(5, 0x3A, 0x00, 0xFF);
        rgb_matrix_set_color(7, 0x3A, 0x00, 0xFF);
        rgb_matrix_set_color(8, 0x3A, 0x00, 0xFF);
    if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
        rgb_matrix_set_color(0, RGB_RED);
    }
        break;
    case _RAISE:
        rgb_matrix_set_color(4, RGB_GREEN);
        rgb_matrix_set_color(3, RGB_GREEN);
        rgb_matrix_set_color(1, RGB_GREEN);
        rgb_matrix_set_color(2, RGB_GREEN);
    if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
        rgb_matrix_set_color(0, RGB_RED);
    }
        break;
    case _ADJUST:
        rgb_matrix_set_color(4, RGB_GREEN);
        rgb_matrix_set_color(3, RGB_GREEN);
        rgb_matrix_set_color(1, RGB_GREEN);
        rgb_matrix_set_color(2, RGB_GREEN);
        rgb_matrix_set_color(6, 0x3A, 0x00, 0xFF);
        rgb_matrix_set_color(5, 0x3A, 0x00, 0xFF);
        rgb_matrix_set_color(7, 0x3A, 0x00, 0xFF);
        rgb_matrix_set_color(8, 0x3A, 0x00, 0xFF);
    if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
        rgb_matrix_set_color(0, RGB_RED);
    }
        break;
    case _PLOVER:
        rgb_matrix_set_color(6, RGB_GOLDENROD);
        rgb_matrix_set_color(5, RGB_GOLDENROD);
        rgb_matrix_set_color(4, RGB_WHITE);
        rgb_matrix_set_color(3, RGB_WHITE);
        rgb_matrix_set_color(0, RGB_CHARTREUSE);
        rgb_matrix_set_color(7, RGB_WHITE);
        rgb_matrix_set_color(8, RGB_WHITE);
        rgb_matrix_set_color(1, RGB_GOLDENROD);
        rgb_matrix_set_color(2, RGB_GOLDENROD);
        break;
    case _QWERTY:
    if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
        rgb_matrix_set_color(0, RGB_RED);
    }
        break;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case GIRAFFACT:
      if (record->event.pressed) {
        SEND_STRING("Did you know that if you submerge a giraffe up to the point where its head is the only thing sticking out of the water, it will still suffocate due to the air-water pressure differential?");
      } else {
      }
      return true;
      break;
    case GIRAFF:
      if (record->event.pressed) {
        SEND_STRING("Did you know that if you submerge a giraffe up to the point where its head is the only thing");
      } else {
      }
      return true;
      break;
    case FFACT:
      if (record->event.pressed) {
        SEND_STRING("sticking out of the water, it will still suffocate due to the air-water pressure differential?");
      } else {
      }
      return true;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          writePinLow(E6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          writePinHigh(E6);
        #endif
      }
      return false;
      break;
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(plover_song);
        #endif
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_on(_PLOVER);
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_PLOVER);
      }
      return false;
      break;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_DOWN);
      #else
        tap_code(KC_PGDN);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_UP);
      #else
        tap_code(KC_PGUP);
      #endif
    }
  }
}

void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
#ifdef AUDIO_ENABLE
            static bool play_sound = false;
#endif
            if (active) {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_song); }
#endif
                layer_on(_ADJUST);
            } else {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_gb_song); }
#endif
                layer_off(_ADJUST);
            }
#ifdef AUDIO_ENABLE
            play_sound = true;
#endif
            break;
        }
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}

float tone_caps_on[][2]    = SONG(CAPS_LOCK_ON_SOUND);
float tone_caps_off[][2]   = SONG(CAPS_LOCK_OFF_SOUND);
float tone_numlk_on[][2]   = SONG(NUM_LOCK_ON_SOUND);
float tone_numlk_off[][2]  = SONG(NUM_LOCK_OFF_SOUND);
float tone_scroll_on[][2]  = SONG(SCROLL_LOCK_ON_SOUND);
float tone_scroll_off[][2] = SONG(SCROLL_LOCK_OFF_SOUND);

#ifdef AUDIO_ENABLE

void led_set_user(uint8_t usb_led)
{
    static uint8_t old_usb_led = 0;

    //_delay_ms(10); // gets rid of tick

    if (!is_playing_notes())
    {
        if ((usb_led & (1<<USB_LED_CAPS_LOCK)) && !(old_usb_led & (1<<USB_LED_CAPS_LOCK)))
        {
                // If CAPS LK LED is turning on...
                PLAY_SONG(tone_caps_on);
        }
        else if (!(usb_led & (1<<USB_LED_CAPS_LOCK)) && (old_usb_led & (1<<USB_LED_CAPS_LOCK)))
        {
                // If CAPS LK LED is turning off...
                PLAY_SONG(tone_caps_off);
        }
        else if ((usb_led & (1<<USB_LED_NUM_LOCK)) && !(old_usb_led & (1<<USB_LED_NUM_LOCK)))
        {
                // If NUM LK LED is turning on...
                PLAY_SONG(tone_numlk_on);
        }
        else if (!(usb_led & (1<<USB_LED_NUM_LOCK)) && (old_usb_led & (1<<USB_LED_NUM_LOCK)))
        {
                // If NUM LED is turning off...
                PLAY_SONG(tone_numlk_off);
        }
        else if ((usb_led & (1<<USB_LED_SCROLL_LOCK)) && !(old_usb_led & (1<<USB_LED_SCROLL_LOCK)))
        {
                // If SCROLL LK LED is turning on...
                PLAY_SONG(tone_scroll_on);
        }
        else if (!(usb_led & (1<<USB_LED_SCROLL_LOCK)) && (old_usb_led & (1<<USB_LED_SCROLL_LOCK)))
        {
                // If SCROLL LED is turning off...
                PLAY_SONG(tone_scroll_off);
        }
    }

    old_usb_led = usb_led;
}
#endif