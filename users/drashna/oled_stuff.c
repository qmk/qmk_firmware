#include "drashna.h"

extern uint8_t is_master;

#ifndef KEYLOGGER_LENGTH
// #    ifdef OLED_DISPLAY_128X64
#    define KEYLOGGER_LENGTH ((int)(OLED_DISPLAY_HEIGHT / OLED_FONT_WIDTH))
// #    else
// #        define KEYLOGGER_LENGTH (uint8_t *(OLED_DISPLAY_WIDTH / OLED_FONT_HEIGHT))
// #    endif
#endif

static uint32_t oled_timer                       = 0;
static char     keylog_str[KEYLOGGER_LENGTH + 1] = {"\n"};
static uint16_t log_timer                        = 0;

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
// clang-format on

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

    log_timer = timer_read();
}

bool process_record_user_oled(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
        oled_timer = timer_read32();
        add_keylog(keycode);
#endif
    }
    return true;
}

void update_log(void) {
    if (timer_elapsed(log_timer) > 750) {
        // add_keylog(0);
    }
}

void render_keylogger_status(void) {
    oled_write_P(PSTR(OLED_RENDER_KEYLOGGER), false);
    oled_write(keylog_str, false);
}

void render_default_layer_state(void) {
    oled_write_P(PSTR(OLED_RENDER_LAYOUT_NAME), false);
    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR(OLED_RENDER_LAYOUT_QWERTY), false);
            break;
        case _COLEMAK:
            oled_write_P(PSTR(OLED_RENDER_LAYOUT_COLEMAK), false);
            break;
        case _DVORAK:
            oled_write_P(PSTR(OLED_RENDER_LAYOUT_DVORAK), false);
            break;
        case _WORKMAN:
            oled_write_P(PSTR(OLED_RENDER_LAYOUT_WORKMAN), false);
            break;
        case _NORMAN:
            oled_write_P(PSTR(OLED_RENDER_LAYOUT_NORMAN), false);
            break;
        case _MALTRON:
            oled_write_P(PSTR(OLED_RENDER_LAYOUT_MALTRON), false);
            break;
        case _EUCALYN:
            oled_write_P(PSTR(OLED_RENDER_LAYOUT_EUCALYN), false);
            break;
        case _CARPLAX:
            oled_write_P(PSTR(OLED_RENDER_LAYOUT_CARPLAX), false);
            break;
    }
#ifdef OLED_DISPLAY_128X64
    oled_advance_page(true);
#endif
}

void render_layer_state(void) {
    oled_write_P(PSTR(OLED_RENDER_LAYER_NAME), false);
#ifdef OLED_DISPLAY_128X64
    oled_write_P(PSTR(" "), false);
#endif
    oled_write_P(PSTR(OLED_RENDER_LAYER_LOWER), layer_state_is(_LOWER));
#ifdef OLED_DISPLAY_128X64
    oled_write_P(PSTR(" "), false);
#endif
    oled_write_P(PSTR(OLED_RENDER_LAYER_RAISE), layer_state_is(_RAISE));
#if _MODS
#    ifdef OLED_DISPLAY_128X64
    oled_write_P(PSTR(" "), false);
#    endif
    oled_write_P(PSTR(OLED_RENDER_LAYER_MODS), layer_state_is(_MODS));
#endif
#ifdef OLED_DISPLAY_128X64
    oled_advance_page(true);
#endif
}

void render_keylock_status(uint8_t led_usb_state) {
    oled_write_P(PSTR(OLED_RENDER_LOCK_NAME), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR(OLED_RENDER_LOCK_NUML), led_usb_state & (1 << USB_LED_NUM_LOCK));
#ifdef OLED_DISPLAY_128X64
    oled_write_P(PSTR(" "), false);
#endif
    oled_write_P(PSTR(OLED_RENDER_LOCK_CAPS), led_usb_state & (1 << USB_LED_CAPS_LOCK));
#ifdef OLED_DISPLAY_128X64
    oled_write_P(PSTR(" "), false);
#endif
    oled_write_P(PSTR(OLED_RENDER_LOCK_SCLK), led_usb_state & (1 << USB_LED_SCROLL_LOCK));
#ifndef OLED_DISPLAY_128X64
    oled_advance_page(true);
#endif
}

void render_mod_status(uint8_t modifiers) {
    oled_write_P(PSTR(OLED_RENDER_MODS_NAME), false);
    oled_write_P(PSTR(OLED_RENDER_MODS_SFT), (modifiers & MOD_MASK_SHIFT));
#ifdef OLED_DISPLAY_128X64
    oled_write_P(PSTR(" "), false);
#endif
    oled_write_P(PSTR(OLED_RENDER_MODS_CTL), (modifiers & MOD_MASK_CTRL));
#ifdef OLED_DISPLAY_128X64
    oled_write_P(PSTR(" "), false);
#endif
    oled_write_P(PSTR(OLED_RENDER_MODS_ALT), (modifiers & MOD_MASK_ALT));
#ifdef OLED_DISPLAY_128X64
    oled_write_P(PSTR(" "), false);
#endif
    oled_write_P(PSTR(OLED_RENDER_MODS_GUI), (modifiers & MOD_MASK_GUI));
}

void render_bootmagic_status(void) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };

    oled_write_P(PSTR(OLED_RENDER_BOOTMAGIC_NAME), false);
#ifdef OLED_DISPLAY_128X64
    if (keymap_config.swap_lctl_lgui)
#else
    oled_write_P(PSTR(" "), false);
#endif
    {
        oled_write_P(logo[1][0], false);
#ifdef OLED_DISPLAY_128X64
    } else {
#endif
        oled_write_P(logo[0][0], false);
    }
    oled_write_P(PSTR(" "), false);
#ifdef OLED_DISPLAY_128X64
    oled_write_P(PSTR(OLED_RENDER_BOOTMAGIC_NKRO), keymap_config.nkro);
    oled_write_P(PSTR(" "), false);
    oled_write_ln_P(PSTR(OLED_RENDER_BOOTMAGIC_NOGUI), !keymap_config.no_gui);
    oled_write_P(PSTR("Magic "), false);
    if (keymap_config.swap_lctl_lgui)
#endif
    {
        oled_write_P(logo[1][1], false);
#ifdef OLED_DISPLAY_128X64
    } else {
#endif
        oled_write_P(logo[0][1], false);
    }
    oled_write_P(PSTR(" "), false);
#ifdef OLED_DISPLAY_128X64
    oled_write_P(PSTR(OLED_RENDER_BOOTMAGIC_GRV), keymap_config.swap_grave_esc);
    oled_write_P(PSTR("  "), false);
    oled_write_P(PSTR(OLED_RENDER_BOOTMAGIC_CAPS), keymap_config.swap_control_capslock);
    oled_advance_page(true);
#else
    oled_write_P(PSTR(OLED_RENDER_BOOTMAGIC_NKRO), keymap_config.nkro);
#endif
}

void render_user_status(void) {
    oled_write_P(PSTR(OLED_RENDER_USER_NAME), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR(OLED_RENDER_USER_ANIM), userspace_config.rgb_matrix_idle_anim);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR(OLED_RENDER_USER_LAYR), userspace_config.rgb_layer_change);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR(OLED_RENDER_USER_NUKE), userspace_config.nuke_switch);
#ifdef OLED_DISPLAY_128X64
    oled_advance_page(true);
#endif
}

__attribute__((weak)) void oled_driver_render_logo(void) {
    // clang-format off
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
    // clang-format on
    oled_write_P(qmk_logo, false);
}

void render_status_secondary(void) {
#if !defined(SPLIT_TRANSPORT_MIRROR) || defined(OLED_DRIVER_128x64)
    oled_driver_render_logo();
#endif
#ifdef SPLIT_TRANSPORT_MIRROR
    /* Show Keyboard Layout  */
    render_default_layer_state();
    render_layer_state();
    render_mod_status(get_mods() | get_oneshot_mods());
    render_keylogger_status();

#endif
}
// clang-format on

void render_status_main(void) {
    /* Show Keyboard Layout  */
    render_default_layer_state();
    render_keylock_status(host_keyboard_leds());
    render_bootmagic_status();
    render_user_status();

    render_keylogger_status();
}

void oled_task_user(void) {
    if (timer_elapsed32(oled_timer) > 30000) {
        oled_off();
        return;
    }
#ifndef SPLIT_KEYBOARD
    else {
        oled_on();
    }
#endif

    update_log();

    if (is_master) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_status_secondary();
    }
}
