#pragma once

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
#    include "rgb.c"
#endif

#ifdef AUDIO_ENABLE
extern audio_config_t audio_config;
#endif

// 5x3 Logos

void render_corne_logo(void) {
    static const char PROGMEM font_logo[16] = {0x80, 0x81, 0x82, 0x83, 0x84, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0};
    oled_write_P(font_logo, false);
};

void render_qmk_logo(void) {
    static const char PROGMEM font_qmk_logo[16] = {0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0};
    oled_write_P(font_qmk_logo, false);
};

// 5x2 Keyboard, Controller logos

void render_keyboard(void) {
    static const char PROGMEM font_keyboard[11] = {0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0};
    oled_write_P(font_keyboard, false);
};

void render_kb_split(void) {
    static const char PROGMEM font_kb_split[11] = {0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0};
    oled_write_P(font_kb_split, false);
};

// 5x1 Layer indicator

void render_layer(void) {
    static const char PROGMEM font_layer[4][6] = {
        {0x85, 0x86, 0x87, 0x88, 0x89, 0},
        {0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0},
        {0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0},
        {0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0},
    };
    uint8_t layer = 0;
    if (layer_state_is(_LOWER)) {
        layer = 1;
    } else if (layer_state_is(_RAISE)) {
        layer = 2;
    } else if (layer_state_is(_ADJUST)) {
        layer = 3;
    }
    oled_write_P(font_layer[layer], false);
};

    // 2x1 Audio, clicky and RGB status indicators

#ifdef AUDIO_ENABLE
void render_audio_status(void) {
    static const char PROGMEM font_audio_off[3] = {0x8f, 0x90, 0};
    static const char PROGMEM font_audio_on[3]  = {0x91, 0x92, 0};
    oled_write_P(audio_config.enable ? font_audio_on : font_audio_off, false);
};

void render_clicky_status(void) {
    static const char PROGMEM font_clicky_off[3] = {0xaf, 0xb0, 0};
    static const char PROGMEM font_clicky_on[3]  = {0xb1, 0xb2, 0};
    oled_write_P(audio_config.clicky_enable ? font_clicky_on : font_clicky_off, false);
};
#endif

#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
void render_rgb_status(void) {
    static const char PROGMEM font_rgb_off[3] = {0xcf, 0xd0, 0};
    static const char PROGMEM font_rgb_on[3]  = {0xd1, 0xd2, 0};
#    ifdef RGBLIGHT_ENABLE
    bool rgb_enabled = rgblight_config.enable;
#    elif RGB_MATRIX_ENABLE
    bool rgb_enabled = rgb_matrix_config.enable;
#    endif
    oled_write_P(rgb_enabled ? font_rgb_on : font_rgb_off, false);
};
#endif

// 2x1 Ctrl, Alt, Shift, GUI, Mouse

void render_mod_ctrl(void) {
    static const char PROGMEM font_ctrl[3] = {0x93, 0x94, 0};
    oled_write_P(font_ctrl, false);
};

void render_mod_alt(void) {
    static const char PROGMEM font_alt[3] = {0xb3, 0xb4, 0};
    oled_write_P(font_alt, false);
};

void render_mod_shift(void) {
    static const char PROGMEM font_shift[3] = {0xd3, 0xd4, 0};
    oled_write_P(font_shift, false);
};

void render_mod_gui(void) {
    static const char PROGMEM font_gui[3] = {0x95, 0x96, 0};
    oled_write_P(font_gui, false);
};

#ifdef MOUSEKEY_ENABLE
void render_mod_mouse(void) {
    static const char PROGMEM font_mouse[3] = {0x97, 0x98, 0};
    oled_write_P(font_mouse, false);
};
#endif

// 5x2 Mod and feature indicator clusters

void render_mod_status(void) {
#ifdef NO_ACTION_ONESHOT
    uint8_t modifiers = get_mods();
#else
    uint8_t modifiers = get_mods() | get_oneshot_mods();
#endif

    (modifiers & MOD_MASK_CTRL) ? render_mod_ctrl() : oled_write_P(PSTR("  "), false);
    oled_write_P(PSTR(" "), false);
    (modifiers & MOD_MASK_SHIFT) ? render_mod_shift() : oled_write_P(PSTR("  "), false);

    (modifiers & MOD_MASK_ALT) ? render_mod_alt() : oled_write_P(PSTR("  "), false);
    oled_write_P(PSTR(" "), false);
    (modifiers & MOD_MASK_GUI) ? render_mod_gui() : oled_write_P(PSTR("  "), false);
}

void render_feature_status(void) {
#if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE)
    render_rgb_status();
#endif

#ifdef AUDIO_ENABLE
    oled_write_P(PSTR(" "), false);
    render_audio_status();
#endif
};

// Keylogger
#define KEYLOGGER_LENGTH 5
static uint16_t oled_timer                       = 0;
static bool     is_key_processed                 = true;
static char     keylog_str[KEYLOGGER_LENGTH + 1] = {"\n"};
// clang-format off
static const char PROGMEM code_to_name[0xFF] = {
//   0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
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

  if (keycode < ARRAY_SIZE(code_to_name)) {
    keylog_str[0] = pgm_read_byte(&code_to_name[keycode]);
  }
}

void render_keylogger_status(void) {
  oled_write(keylog_str, false);
}

void render_prompt(void) {
    bool blink = (timer_read() % 1000) < 500;

    if (layer_state_is(_LOWER)) {
        oled_write_ln_P(blink ? PSTR("> lo_") : PSTR("> lo "), false);
    } else if (layer_state_is(_RAISE)) {
        oled_write_ln_P(blink ? PSTR("> hi_") : PSTR("> hi "), false);
    } else if (layer_state_is(_ADJUST)) {
        oled_write_ln_P(blink ? PSTR("> aj_") : PSTR("> aj "), false);
    } else {
        oled_write_ln_P(blink ? PSTR("> _  ") : PSTR(">    "), false);
    }
};

void render_status_secondary(void) {
    oled_write_ln("", false);
    oled_write_ln("", false);

    render_kb_split();

    oled_write_ln("", false);
    oled_write_ln("", false);
    oled_write_ln("", false);

    render_layer();

    oled_write_ln("", false);
    oled_write_ln("", false);
    oled_write_ln("", false);

    #if defined(RGB_MATRIX_ENABLE) || defined(RGBLIGHT_ENABLE) || defined(AUDIO_ENABLE)
        layer_state_is(_ADJUST) ? render_feature_status() : render_mod_status();
    #else
        render_mod_status();
    #endif
};

void render_status_main(void) {
    oled_write_ln("", false);
    oled_write_ln("", false);

    render_corne_logo();

    oled_write_ln("", false);
    oled_write_ln("", false);
    oled_write_ln("", false);

    render_qmk_logo();

    oled_write_ln("", false);
    oled_write_ln("", false);
    oled_write_ln("", false);

    render_prompt();
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        if (is_key_processed && (timer_elapsed(oled_timer) < OLED_KEY_TIMEOUT)) {
            render_status_main();
        } else {
            is_key_processed = false;
            oled_off();
        }
    } else {
        render_status_secondary();
    }
    return false;
}
