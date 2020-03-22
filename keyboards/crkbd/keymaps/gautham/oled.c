#pragma once

extern uint8_t is_master;


#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
#   include "rgb.c"
#endif

#ifdef AUDIO_ENABLE
  extern audio_config_t audio_config;
#endif


#define KEYLOGGER_LENGTH 5
static uint32_t oled_timer                       = 0;
static char     keylog_str[KEYLOGGER_LENGTH + 1] = {"\n"};
// clang-format off
static const char PROGMEM code_to_name[0xFF] = {
//   0    1    2    3    4    5    6    7    8    9    A    B    c    D    E    F
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',  // 0x
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2',  // 1x
    '3', '4', '5', '6', '7', '8', '9', '0',  20,  19,  27,  26,  22, '-', '=', '[',  // 2x
    ']','\\', '#', ';','\'', '`', ',', '.', '/', 128, ' ', ' ', ' ', ' ', ' ', ' ',  // 3x
    ' ', ' ', ' ', ' ', ' ', ' ', 'P', 'S', ' ', ' ', ' ', ' ',  16, ' ', ' ', ' ',  // 4x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 5x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 6x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 7x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 8x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 9x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ax
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Bx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Cx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Dx
    'C', 'S', 'A', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ex
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '        // Fx
};

void add_keylog(uint16_t keycode) {
  if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) || (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) {
    keycode = keycode & 0xFF;
  } else if (keycode > 0xFF) {
    keycode = 0;
  }

  for (uint8_t i = (KEYLOGGER_LENGTH - 1); i > 0; --i) {
    keylog_str[i] = keylog_str[i - 1];
  }

  if (keycode < (sizeof(code_to_name) / sizeof(char))) {
    keylog_str[0] = pgm_read_byte(&code_to_name[keycode]);
  }
}

void render_keylogger_status(void) {
  oled_write_P(PSTR("Log: "), false);
  oled_write(keylog_str, false);
}





oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}





void render_layer_state(void) {
  oled_write_P(PSTR("Layr:"), false);
  oled_write_P(PSTR("  Num"), layer_state_is(_LOWER));
  oled_write_P(PSTR("  Sym"), layer_state_is(_RAISE));
  oled_write_P(PSTR("   Fn"), layer_state_is(_ADJUST));
}

void render_mod_status(uint8_t modifiers) {
  oled_write_P(PSTR("Mods:"), false);
  oled_write_P(PSTR(" "), false);
  oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
  oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
  oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
  oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
}

#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
void render_effect_status(void) {
    oled_write_P(PSTR("RGB: "), false);
    #ifdef RGBLIGHT_ENABLE
      oled_write_P(rgblight_config.enable ? PSTR("  On") : PSTR("  Off"), false);
    #elif RGB_MATRIX_ENABLE
      oled_write_P(rgb_matrix_config.enable ? PSTR("  On") : PSTR("  Off"), false);
    #endif
    oled_write_ln_P(PSTR(""), false);
}
#endif

#ifdef AUDIO_ENABLE
void render_audio_status(void) {
    oled_write_P(PSTR("Aud: "), false);
    if (audio_config.enable) {
      oled_write_P(PSTR("   On"), false);
    } else {
      oled_write_P(PSTR("  Off"), false);
    }
    oled_write_ln_P(PSTR(""), false);
}
#endif

void render_status_main(void) {
    render_layer_state();

    oled_write_ln_P(PSTR(""), false);

    #if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
    render_effect_status();
    oled_write_ln_P(PSTR(""), false);
    #endif

    // static char timer_str[5] = {0};
    // snprintf(timer_str, sizeof(timer_str), "%5lu", timer_elapsed32(oled_timer));
    // oled_write_ln(timer_str, false);

    render_keylogger_status();
}

void render_status_secondary(void) {
    render_layer_state();

    oled_write_ln_P(PSTR(""), false);

    #ifdef NO_ACTION_ONESHOT
      render_mod_status(get_mods());
    #else
      render_mod_status(get_mods() | get_oneshot_mods());
    #endif

    oled_write_ln_P(PSTR(""), false);

    #ifdef AUDIO_ENABLE
    render_audio_status();
    #endif
}

void oled_task_user(void) {
    if (timer_elapsed32(oled_timer) > 10000) {
        oled_off();
        return;
    }
    #ifndef SPLIT_KEYBOARD
    else {
        oled_on();
    }
    #endif

    if (is_master) {
        render_status_main();
    } else {
        render_status_secondary();
    }
}
