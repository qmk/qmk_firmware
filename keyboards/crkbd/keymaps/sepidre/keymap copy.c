#include QMK_KEYBOARD_H
#include "enums.h"
#include "layer.h"
#include "keymap_german.h"

// [Init Variables] ----------------------------------------------------------//
extern uint8_t is_master;
// Oled timer similar to Drashna's
static uint32_t oled_timer = 0;
// Boolean to store LED state
bool user_led_enabled = true;
// Boolean to store the master LED clear so it only runs once.
bool master_oled_cleared = false;

// [Keymaps] -----------------------------------------------------------------//
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	  [_NEO] = LAYOUT(
      LT(_WEAPON, KC_ESC), DE_X,   DE_V,   DE_L,   DE_C,   DE_W,        /*|*/        DE_K, DE_H, DE_G,    DE_F,   DE_Q, DE_SS,
      LSFT_T(KC_TAB),      DE_U,   DE_I,   DE_A,   DE_E,   DE_O,        /*|*/        DE_S, DE_N, DE_R,    DE_T,   DE_D, DE_Y,
      KC_LCTRL,            DE_UE,  DE_OE,  DE_AE,  DE_P,   DE_Z,        /*|*/        DE_B, DE_M, DE_COMM, DE_DOT, DE_J, DE_MINS,
                                     LGUI_T(KC_PGUP), KC_SPC, MO(_NUM), /*|*/ MO(_SYM), KC_ENT, LALT_T(KC_PGDN)
    ),

      [_NUM] = LAYOUT(
      KC_ESC,     KC_HOME,  KC_BSPC,   KC_UP,    KC_DEL,   KC_END,        /*|*/        KC_PAST, KC_7, KC_8, KC_9, KC_PMNS, KC_PEQL,
      KC_ENT,     KC_UNDO,  KC_LEFT,   KC_DOWN,  KC_RIGHT, KC_PGDOWN,     /*|*/        KC_PSLS, KC_4, KC_5, KC_6, KC_PPLS, DE_Y,
      LCTL(KC_S), KC_AGAIN, LCA(DE_R), S(KC_F5), KC_F12,   KC_PGUP,       /*|*/        KC_0,    KC_1, KC_2, KC_3, KC_PDOT, KC_PCMM,
                                                 KC_F2, KC_SPC, MO(_NUM), /*|*/ MO(_SYM), KC_ENT, LALT_T(KC_PGDN)
    ),

      [_SYM] = LAYOUT(
      KC_ESC,     DE_AT,   DE_UNDS, DE_LBRC, DE_RBRC, DE_CIRC,        /*|*/         DE_EXLM, DE_LABK, DE_RABK, DE_EQL,  DE_AMPR, DE_SECT,
      LCTL(KC_Z), DE_BSLS, DE_SLSH, DE_LCBR, DE_RCBR, DE_ASTR,        /*|*/         DE_QUES, DE_LPRN, DE_RPRN, DE_MINS, DE_COLN, DE_EURO,
      LCTL(KC_S), DE_HASH, DE_DLR,  DE_PIPE, DE_TILD, DE_GRV,         /*|*/         DE_PLUS, DE_PERC, DE_DQUO, DE_QUOT, DE_SCLN, TG(_GAME),
          LGUI_T(KC_PGUP), LCTL(LGUI(KC_LEFT)), LCTL(LGUI(KC_RIGHT)), /*|*/ KC_TRNS, KC_ENT, LALT_T(KC_PGDN)
    ),

	  [_GAME] = LAYOUT(
      KC_ESC,  DE_X,    DE_V,   DE_L,  DE_C,   DE_W,       /*|*/         DE_K, DE_H, DE_G,    DE_F,   DE_Q, DE_SS,
      KC_LSFT, DE_U,    DE_I,   DE_A,  DE_E,   DE_O,       /*|*/         DE_S, DE_N, DE_R,    DE_T,   DE_D, DE_Y,
      KC_LCTL, DE_COMM, DE_DOT, DE_D,  DE_P,   DE_Z,       /*|*/         DE_B, DE_M, DE_COMM, DE_DOT, DE_J, DE_MINS,
                              KC_TAB, KC_SPC, MO(_WEAPON), /*|*/ MO(_SYM), KC_ENT, LALT_T(KC_PGDN)
    ),

	  [_WEAPON] = LAYOUT(
      KC_ESC,  KC_1,  KC_2,      KC_3, KC_4, KC_5,       /*|*/         KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
      KC_TAB,  KC_LSFT, DE_6,    KC_S, KC_7, KC_8,       /*|*/         KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
      KC_MSEL, KC_LCTL, DE_MINS, KC_X, DE_9, DE_0,       /*|*/         KC_PGUP, KC_PGDN, DE_B, DE_M, EEP_RST, TG(_GAME),
                              KC_MPRV, KC_MPLY, KC_MNXT, /*|*/ KC_ENT, KC_SPC, LALT_T(KC_PGDN)
    ),

      [_ADJ] = LAYOUT(
      KC_SYSTEM_WAKE, DE_X,  DE_V,  KC_SLCK, DE_C,   DE_W,        /*|*/        RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_MOD,  HIBER,
      KC_F7,          KC_F8, KC_F9, KC_F10,  KC_F11, KC_F12,      /*|*/        DE_S,    RGB_HUD, RGB_SAD, RGB_VAD, RGB_RMOD, DE_Y,
      KC_F1,          KC_F2, KC_F3, KC_F4,   KC_F5,  KC_F6,       /*|*/        DE_B,    DE_M,    DE_COMM, DE_DOT,  DE_J,     KC_LALT,
                               LGUI_T(KC_PGUP), KC_SPC, MO(_NUM), /*|*/ MO(_SYM), KC_ENT, LALT_T(KC_PGDN)
    )

};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _NUM, _SYM, _ADJ);
}

// [Post Init] --------------------------------------------------------------//
void keyboard_post_init_user(void) {
    // Set RGB to known state
    rgb_matrix_enable_noeeprom();
    rgb_matrix_set_color_all(RGB_GREEN);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    user_led_enabled = true;
}
// [Process User Input] ------------------------------------------------------//
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
switch (keycode) {
    case ALT_TAB:
        if (record->event.pressed) {
            if (!is_alt_tab_active) {
                is_alt_tab_active = true;
                unregister_code(KC_LSHIFT);
                register_code(KC_LALT);
            }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
        } else {
            unregister_code(KC_TAB);
        }
        break;
   case HIBER:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTRL(" "));
            SEND_STRING("hibernate");
            register_code(KC_ENT);
            return false;
        }
        break;
    // Handle RGB Changes sans eeprom - necessary due to the layer dependent RGB color
    // changes in marrix_scan_user
    case RGB_TOG:
        if (record->event.pressed) {
            // Toggle matrix on key press
            user_led_enabled ? rgb_matrix_disable_noeeprom() : rgb_matrix_enable_noeeprom();
            // Toggle boolean flag
            user_led_enabled = !user_led_enabled;
        }
        return false;
    default:
    // Use process_record_keymap to reset timer on all other keypresses to awaken from idle.
        if (record->event.pressed) {
            #ifdef OLED_DRIVER_ENABLE
                oled_timer = timer_read32();
            #endif
            // Restore LEDs if they are enabled by user
            if (user_led_enabled) {
                rgb_matrix_enable_noeeprom();
            }
        }
  }
  return true;


}

// [Matrix Scan] ------------------------------------------------------------//
void matrix_scan_user(void) {
     // Iddle timer to return to default layer if left on game layer
     if (timer_elapsed32(oled_timer) > 380000 && timer_elapsed32(oled_timer) < 479999) {
         // Reset layer in case it got left on _GAME
         // This prevents the issue where the master side sometimes wont switch off as expected
         // in the next step.
         if (get_highest_layer(layer_state) == _GAME) {
             layer_off(_GAME);
             layer_on(_NEO);
         }
         return;
     }
     // Timeout to turn off LEDs
     else if (timer_elapsed32(oled_timer) > 480000) {
         rgb_matrix_disable_noeeprom();
         return;
     }
     // Set RGB Matrix color based on layers
     if (user_led_enabled) {
         switch (get_highest_layer(layer_state)){
            case _GAME:
                rgb_matrix_set_color_all(RGB_PURPLE);
                break;
            case _NUM:
                rgb_matrix_set_color_all(RGB_ORANGE);
                break;
            case _SYM:
                rgb_matrix_set_color_all(RGB_GOLD);
                break;
            case _NEO:
                rgb_matrix_set_color_all(RGB_GREEN);
                break;
            case _WEAPON:
                rgb_matrix_set_color_all(RGB_MAGENTA);
                break;
            default:
                rgb_matrix_set_color_all(RGB_GREEN);
                break;

          }
     } else {
         rgb_matrix_disable_noeeprom();
         return;
     }
}
// [OLED Configuration] ------------------------------------------------------//
#ifdef OLED_DRIVER_ENABLE
// Init Oled and Rotate....
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!has_usb())
      return OLED_ROTATION_180;  // flips the display 180 to see it from my side
    return rotation;
}

// Read logo from font file
const char *read_logo(void);

// {OLED helpers} -----------------------------------------------//
// Render Logo
void render_logo(void) {
    oled_write(read_logo(), false);
}

// Master OLED Screen (Left Hand )
void render_master_oled(void) {
    // Switch display based on Layer
    switch (get_highest_layer(layer_state)){
        case _GAME:
            render_separator();
            render_layer_state();
            render_separator();
            render_separator();
            break;
        case _WEAPON:
            render_separator();
            render_separator();
            render_layer_state();
            render_separator();
            break;
        default:
            render_separator();
            render_layer_state();
            render_separator();
            render_usb_state();
    }
}

// Slave OLED scren (Right Hand)
void render_slave_oled(void) {
    render_logo();
}

// {OLED Task} -----------------------------------------------//
void oled_task_user(void) {
    // First time out switches to logo as first indication of iddle.
    if (timer_elapsed32(oled_timer) > 100000 && timer_elapsed32(oled_timer) < 479999) {
        // Render logo on both halves before full timeout
        if (is_master && !master_oled_cleared) {
            // Clear master OLED once so the logo renders properly
            oled_clear();
            master_oled_cleared = true;
        }
        render_logo();
        return;
    }
    // Drashna style timeout for LED and OLED Roughly 8mins
    else if (timer_elapsed32(oled_timer) > 480000) {
        oled_off();
        rgb_matrix_disable_noeeprom();
        return;
    }
    else {
        oled_on();
        // Reset OLED Clear flag
        master_oled_cleared = false;
        // Show logo when USB dormant
        switch (USB_DeviceState) {
            case DEVICE_STATE_Unattached:
            case DEVICE_STATE_Powered:
            case DEVICE_STATE_Suspended:
                render_logo();
                break;
            default:
                if (is_master) {
                    render_master_oled();
                } else {
                    render_slave_oled();
                }
        }
    }
}
#endif
