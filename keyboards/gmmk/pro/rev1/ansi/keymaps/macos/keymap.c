/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

   GMMK Pro Standard keymap for macOS
   by zvuc <https://github.com/zvuc>

   with code snippets from
   Andre Brait <andrebrait@gmail.com>, stickandgum

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

enum my_keycodes {
  LED_TLDE = SAFE_RANGE,
  LED_1,
  LED_2,
  LED_3,
  LED_4,
  LED_5,
  LED_6,
  LED_7,
  LED_8,
  LED_9,
  LED_0,
  LED_MINS,
  LED_EQL
};

#ifdef RGB_MATRIX_ENABLE
  #ifndef RGB_CONFIRMATION_BLINKING_TIME
    #define RGB_CONFIRMATION_BLINKING_TIME 2000 // 2 seconds
  #endif
#endif // RGB_MATRIX_ENABLE

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12      Eject          Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)      BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       F13
//      Ct_L     Opt_L    Cmd_L                               SPACE                               Cmd_R    Opt_R    FN       Left     Down     Right


  // The FN key by default maps to a momentary toggle to layer 1 to provide access to the QK_BOOT key (to put the board into bootloader mode). Without
  // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
  // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
  // if that's your preference.
  //
  // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
  // it'll be back to normal when you plug it back in.
  //
  // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
  // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
  // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.
  [0] = LAYOUT(
    KC_ESC,  KC_BRID, KC_BRIU, XXXXXXX,    XXXXXXX, RGB_VAD, RGB_VAI, KC_F7,   KC_F8,   KC_MRWD, KC_MPLY, KC_MFFD, KC_F12,  KC_EJCT,          KC_MUTE,
    KC_GRV,  KC_1,    KC_2,    KC_3,       KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_DEL,
    KC_TAB,  KC_Q,    KC_W,    KC_E,       KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
    KC_CAPS, KC_A,    KC_S,    KC_D,       KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
    KC_LSFT,          KC_Z,    KC_X,       KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_F13,
    KC_LCTL, KC_LOPT, KC_LCMD,                               KC_SPC,                             KC_RCMD, KC_ROPT, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [1] = LAYOUT(
    _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,  _______,           RGB_TOG,
    LED_TLDE, LED_1,   LED_2,   LED_3,   LED_4,   LED_5,   LED_6,   LED_7,   LED_8,   LED_9,   LED_0,   LED_MINS, LED_EQL, _______,           KC_PSCR,
    _______,  RGB_HUI, RGB_VAI, RGB_SAI, _______, _______, _______, _______, _______, _______, _______, _______,  _______, QK_BOOT,           _______,
    _______,  RGB_HUD, RGB_VAD, RGB_SAD, TG(2),   _______, _______, _______, _______, _______, _______, _______,           _______,           _______,
    _______,           _______, _______, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,           _______, RGB_MOD,  RGB_TOG,
    _______,  _______, _______,                            _______,                            _______, _______,  _______, RGB_SPD, RGB_RMOD, RGB_SPI
  ),

  // This is an alternative togglable layer to change default function row to standard F keys
  [2] = LAYOUT(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_F24,           _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
    _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
  ),


};
// clang-format on

#ifdef ENCODER_ENABLE
  bool encoder_update_user(uint8_t index, bool clockwise) {
    // https://beta.docs.qmk.fm/using-qmk/simple-keycodes/feature_advanced_keycodes#alt-escape-for-alt-tab-id-alt-escape-for-alt-tab
    if (get_mods() & MOD_MASK_CTRL) { // If CTRL is held
      uint8_t mod_state = get_mods(); // Store all  modifiers that are held
      unregister_mods(MOD_MASK_CTRL); // Immediately unregister the CRTL key (don't send CTRL-PgDn) - del_mods doesn't work here (not immediate)
      if (clockwise) {
        rgblight_increase_hue();
      } else {
        rgblight_decrease_hue();
      }
      set_mods(mod_state); // Add back in the CTRL key - so ctrl-key will work if ctrl was never released after paging.
    } else if (get_mods() & MOD_MASK_ALT) {
      uint8_t mod_state = get_mods();
      unregister_mods(MOD_MASK_ALT);
      if (clockwise) {
        rgblight_increase_sat();
      } else {
        rgblight_decrease_sat();
      }
      set_mods(mod_state);
    } else if (get_mods() & MOD_MASK_GUI) {
      uint8_t mod_state = get_mods();
      unregister_mods(MOD_MASK_GUI);
      if (clockwise) {
        rgblight_increase_val();
      } else {
        rgblight_decrease_val();
      }
      set_mods(mod_state);
    } else if (get_mods() & MOD_MASK_SHIFT) {
      uint8_t mod_state = get_mods();
      unregister_mods(MOD_MASK_SHIFT);
      if (clockwise) {
        rgblight_increase_speed();
      } else {
        rgblight_decrease_speed();
      }
      set_mods(mod_state);
    } else if (clockwise) { // All else volume.
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
    //return true; //set to return false to counteract enabled encoder in pro.c
    return false;
  }
#endif //ENCODER_ENABLE

#ifdef RGB_MATRIX_ENABLE

  // Called on powerup and is the last _init that is run.
  void keyboard_post_init_user(void) {

     int mods[35] = {0,2,3,4,5,11,17,33,49,55,65,95,97,79,94,85,93,96,90,69,92,67,76,80,91,75,86,68,77,81,92,28,34,39,44};
     int j;

     /* output each array element's value */
     for (j = 0; j < 35; j++ ) {
        g_led_config.flags[mods[j]] = LED_FLAG_MODIFIER;
     }

    if (!rgb_matrix_is_enabled()) {
        rgb_matrix_enable();
        #ifdef CONSOLE_ENABLE
          uprintf("ERROR! RGB Matrix Enabled and wrote to EEPROM! -How was the RGB Matrix Disabled?");
        #endif
    }
  }

  /* Renaming those to make the purpose on this keymap clearer */
  #define LED_FLAG_CAPS LED_FLAG_NONE
  #define LED_FLAG_EFFECTS LED_FLAG_INDICATOR

  static void set_rgb_caps_leds(void);

  #if RGB_CONFIRMATION_BLINKING_TIME > 0
    static uint16_t effect_started_time = 0;
    static uint8_t r_effect = 0x0, g_effect = 0x0, b_effect = 0x0;
    static void start_effects(void);

    /* The higher this is, the slower the blinking will be */
    #ifndef TIME_SELECTED_BIT
      #define TIME_SELECTED_BIT 8
    #endif
    #if TIME_SELECTED_BIT < 0 || TIME_SELECTED_BIT >= 16
      #error "TIME_SELECTED_BIT must be a positive integer smaller than 16"
    #endif
    #define effect_red() r_effect = 0xFF, g_effect = 0x0, b_effect = 0x0
    #define effect_green() r_effect = 0x0, g_effect = 0xFF, b_effect = 0x0
  #endif // RGB_CONFIRMATION_BLINKING_TIME > 0

  bool led_update_user(led_t led_state) {
    if (led_state.caps_lock) {
      if (!rgb_matrix_is_enabled()) {
        /* Turn ON the RGB Matrix for CAPS LOCK */
        rgb_matrix_set_flags(LED_FLAG_CAPS);
        rgb_matrix_enable();
      }
    } else if (rgb_matrix_get_flags() == LED_FLAG_CAPS) {
      /* RGB Matrix was only ON because of CAPS LOCK. Turn it OFF. */
      rgb_matrix_set_flags(LED_FLAG_ALL);
      rgb_matrix_disable();
    }
    return true;
  }

  bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      #ifdef NKRO_ENABLE
        #if RGB_CONFIRMATION_BLINKING_TIME > 0
          case NK_TOGG:
            if (record->event.pressed) {
              if (keymap_config.nkro) {
                /* Turning NKRO OFF */
                effect_red();
              } else {
                /* Turning NKRO ON */
                effect_green();
              }
              start_effects();
            }
            break;
        #endif // RGB_CONFIRMATION_BLINKING_TIME > 0
      #endif // NKRO_ENABLE

      #if RGB_CONFIRMATION_BLINKING_TIME > 0
        case TG(2):
          if (record->event.pressed) {
            if (IS_LAYER_OFF(2)) {
              effect_red();
            } else {
              effect_green();
            }
            start_effects();
          }
          break;
      #endif // RGB_CONFIRMATION_BLINKING_TIME > 0

      /* LED quick preset keys assignments */
      case LED_TLDE:
        rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);          // Can use RGB_M_P built-in keycode instead.
        break;
      case LED_1:
        rgb_matrix_mode(RGB_MATRIX_ALPHAS_MODS);
        break;
      case LED_2:
        rgb_matrix_mode(RGB_MATRIX_GRADIENT_UP_DOWN);
        break;
      case LED_3:
        rgb_matrix_mode(RGB_MATRIX_JELLYBEAN_RAINDROPS);
        break;
      case LED_4:
        rgb_matrix_mode(RGB_MATRIX_BAND_SAT);
        break;
      case LED_5:
        rgb_matrix_mode(RGB_MATRIX_BAND_VAL);
        break;
      case LED_6:
        rgb_matrix_mode(RGB_MATRIX_BAND_SPIRAL_VAL);
        break;
      case LED_7:
        rgb_matrix_mode(RGB_MATRIX_CYCLE_LEFT_RIGHT);    // Can use RGB_M_R built-in keycode instead.
        break;
      case LED_8:
        rgb_matrix_mode(RGB_MATRIX_CYCLE_PINWHEEL);      // Can use RGB_M_SW built-in keycode instead.
        break;
      case LED_9:
         rgb_matrix_mode(RGB_MATRIX_BREATHING);          // Can use RGB_M_B built-in keycode instead.
        break;

      #ifdef RGB_MATRIX_KEYPRESSES                         // Reactive effects require RGB_MATRIX_KEYPRESSES in config.h
        case LED_0:
          rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_WIDE);
          break;
      #endif //RGB_MATRIX_KEYPRESSES

      #ifdef RGB_MATRIX_FRAMEBUFFER_EFFECTS               // Heatmap and Rain require #define RGB_MATRIX_FRAMEBUFFER_EFFECTS in config.h
        case LED_MINS:
          rgb_matrix_mode(RGB_MATRIX_DIGITAL_RAIN);
          break;
        case LED_EQL:
          rgb_matrix_mode(RGB_MATRIX_TYPING_HEATMAP);
          break;
      #endif //RGB_MATRIX_FRAMEBUFFER_EFFECTS


      // case RGB_MOD:
      // case RGB_RMOD:
      // case RGB_HUI:
      // case RGB_HUD:
      // case RGB_SAI:
      // case RGB_SAD:
      // case RGB_VAI:
      // case RGB_VAD:
      // case RGB_SPI:
      case RGB_SPD:
        if (record->event.pressed) {
          if (rgb_matrix_get_flags() != LED_FLAG_ALL) {
            /* Ignore changes to RGB settings while only it's supposed to be OFF */
            return false;
          }
        }
        break;

      case RGB_TOG:
        // if (record->event.pressed) {
        //     if (rgb_matrix_get_flags() == LED_FLAG_ALL) {
        //         rgb_matrix_set_flags(LED_FLAG_NONE);
        //         rgb_matrix_set_color_all(0, 0, 0);
        //     } else {
        //         rgb_matrix_set_flags(LED_FLAG_ALL);
        //     }
        // }
        // return false;
        if (record->event.pressed) {
          if (rgb_matrix_is_enabled()) {
            switch (rgb_matrix_get_flags()) {
              #if RGB_CONFIRMATION_BLINKING_TIME > 0
              case LED_FLAG_EFFECTS:
              #endif
              case LED_FLAG_CAPS:
                /* Turned ON because of EFFECTS or CAPS, is actually OFF */
                /* Change to LED_FLAG_ALL to signal it's really ON */
                rgb_matrix_set_flags(LED_FLAG_ALL);
                /* Will be re-enabled by the processing of the toggle */
                rgb_matrix_disable_noeeprom();
                break;
              case LED_FLAG_ALL:
                /* Is actually ON */
                #if RGB_CONFIRMATION_BLINKING_TIME > 0
                if (effect_started_time > 0) {
                  /* Signal EFFECTS */
                  rgb_matrix_set_flags(LED_FLAG_EFFECTS);
                  /* Will be re-enabled by the processing of the toggle */
                  rgb_matrix_disable_noeeprom();
                } else
                #endif
                if (host_keyboard_led_state().caps_lock) {
                  /* Signal CAPS */
                  rgb_matrix_set_flags(LED_FLAG_CAPS);
                  /* Will be re-enabled by the processing of the toggle */
                  rgb_matrix_disable_noeeprom();
                }
                break;
            }
          }
        }
        break;

    }
    return true;
  }


  bool rgb_matrix_indicators_user(void) {
    #if RGB_CONFIRMATION_BLINKING_TIME > 0
    if (effect_started_time > 0) {
      /* Render blinking EFFECTS */
      uint16_t deltaTime = sync_timer_elapsed(effect_started_time);
      if (deltaTime <= RGB_CONFIRMATION_BLINKING_TIME) {
        uint8_t led_state = ((~deltaTime) >> TIME_SELECTED_BIT) & 0x01;
        uint8_t val_r = led_state * r_effect;
        uint8_t val_g = led_state * g_effect;
        uint8_t val_b = led_state * b_effect;
        rgb_matrix_set_color_all(val_r, val_g, val_b);
        if (host_keyboard_led_state().caps_lock) {
          set_rgb_caps_leds();
        }
        return false;
      } else {
        /* EFFECTS duration is finished */
        effect_started_time = 0;
        if (rgb_matrix_get_flags() == LED_FLAG_EFFECTS) {
          /* It was turned ON because of EFFECTS */
          if (host_keyboard_led_state().caps_lock) {
            /* CAPS is still ON. Demote to CAPS */
            rgb_matrix_set_flags(LED_FLAG_CAPS);
          } else {
            /* There is nothing else keeping RGB enabled. Reset flags and turn if off. */
            rgb_matrix_set_flags(LED_FLAG_ALL);
            rgb_matrix_disable_noeeprom();
          }
        }
      }
    }
    #endif // RGB_CONFIRMATION_BLINKING_TIME > 0
    if (rgb_matrix_get_flags() == LED_FLAG_CAPS) {
      rgb_matrix_set_color_all(0x0, 0x0, 0x0);
    }
    if (host_keyboard_led_state().caps_lock) {
      set_rgb_caps_leds();
    }
    return false;
  }

  #if RGB_CONFIRMATION_BLINKING_TIME > 0
  static void start_effects(void) {
    effect_started_time = sync_timer_read();
    if (!rgb_matrix_is_enabled()) {
      /* Turn it ON, signal the cause (EFFECTS) */
      rgb_matrix_set_flags(LED_FLAG_EFFECTS);
      rgb_matrix_enable_noeeprom();
    } else if (rgb_matrix_get_flags() == LED_FLAG_CAPS) {
      /* It's already ON, promote the cause from CAPS to EFFECTS */
      rgb_matrix_set_flags(LED_FLAG_EFFECTS);
    }
  }
  #endif // RGB_CONFIRMATION_BLINKING_TIME > 0

  static void set_rgb_caps_leds(void) {
    rgb_matrix_set_color(67, 0xFF, 0x0, 0x0); // Left side LED 1
    rgb_matrix_set_color(68, 0xFF, 0x0, 0x0); // Right side LED 1
    rgb_matrix_set_color(70, 0xFF, 0x0, 0x0); // Left side LED 2
    rgb_matrix_set_color(71, 0xFF, 0x0, 0x0); // Right side LED 2
    rgb_matrix_set_color(73, 0xFF, 0x0, 0x0); // Left side LED 3
    rgb_matrix_set_color(74, 0xFF, 0x0, 0x0); // Right side LED 3
    rgb_matrix_set_color(76, 0xFF, 0x0, 0x0); // Left side LED 4
    rgb_matrix_set_color(77, 0xFF, 0x0, 0x0); // Right side LED 4
    rgb_matrix_set_color(80, 0xFF, 0x0, 0x0); // Left side LED 5
    rgb_matrix_set_color(81, 0xFF, 0x0, 0x0); // Right side LED 5
    rgb_matrix_set_color(83, 0xFF, 0x0, 0x0); // Left side LED 6
    rgb_matrix_set_color(84, 0xFF, 0x0, 0x0); // Right side LED 6
    rgb_matrix_set_color(87, 0xFF, 0x0, 0x0); // Left side LED 7
    rgb_matrix_set_color(88, 0xFF, 0x0, 0x0); // Right side LED 7
    rgb_matrix_set_color(91, 0xFF, 0x0, 0x0); // Left side LED 8
    rgb_matrix_set_color(92, 0xFF, 0x0, 0x0); // Right side LED 8
    rgb_matrix_set_color(3, 0xFF, 0x0, 0x0); // CAPS LED
  }

#endif // RGB_MATRIX_ENABLE
