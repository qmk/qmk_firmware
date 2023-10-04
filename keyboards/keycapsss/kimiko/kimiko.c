/* Copyright 2023 @BenRoe (keycapsss.com)
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

 #include "quantum.h"

#ifdef KEYBOARD_keycapsss_kimiko_rev1
#ifdef RGB_MATRIX_ENABLE

//Thanks to Ben (keycapsss) for helpipng me to create g_led_config

// Physical LED position
// X 0   16  32  48  64  80  96    112 128 144 160 176 208 224
//   -----------------------------------------------------------|  Y
//   5   4   3   2   1   0             0   1   2   3   4   5    |  0
//   6   7   8   9   10  11            11  10  9   8   7   6    |  16
//   17  16  15  14  13  12            12  13  14  15  16  17   |  32
//   18  19  20  21  22  23  24    24  23  22  21  20  19  18   |  48
//           29  28  27  26  25    25  26  27  28  29           |  64

led_config_t g_led_config = { {
    // Key Matrix to LED Index
    { 5,  4,  3,  2,  1,  0  },
    { 6,  7,  8,  9,  10, 11 },
    { 17, 16, 15, 14, 13, 12 },
    { 18, 19, 20, 21, 22, 23 },
    { 29, 28, 27, 26, 25, 24 },
    { 35, 34, 33, 32, 31, 30 },
    { 36, 37, 38, 39, 40, 41 },
    { 47, 46, 45, 44, 43, 42 },
    { 48, 49, 50, 51, 52, 53 },
    { 59, 58, 57, 56, 55, 54 }
}, {
    // LED Index to Physical Position
    // Left half
    { 80, 0 },  { 64, 0 },  { 48, 0 },  { 32, 0 },  { 16, 0 },  { 0, 0 },
    { 0, 16 },  { 16, 16 }, { 32, 16 }, { 48, 16 }, { 64, 16 }, { 80, 16 },
    { 80, 32 }, { 64, 32 }, { 48, 32 }, { 32, 32 }, { 16, 32 }, { 0, 32 },
    { 0, 48 },  { 16, 48 }, { 32, 48 }, { 48, 48 }, { 64, 48 }, { 80, 48 },
    { 96, 48 }, { 96, 64 }, { 80, 64 }, { 64, 64 }, { 48, 64 }, { 32, 64 },
    // Right half
    { 128, 0 }, { 144, 0 }, { 160, 0 }, { 176, 0 }, { 208, 0 }, { 224, 0 },
    { 224, 16 }, { 208, 16 }, { 176, 16 }, { 160, 16 }, { 144, 16 }, { 128, 16 },
    { 128, 32 }, { 144, 32 }, { 160, 32 }, { 176, 32 }, { 208, 32 }, { 224, 32 },
    { 224, 48 }, { 208, 48 }, { 176, 48 }, { 160, 48 }, { 144, 48 }, { 128, 48 },
    { 112, 48 }, { 112, 64 }, { 128, 64 }, { 144, 64 }, { 160, 64 }, { 176, 64 }

}, {
    // LED Index to Flag
    // 0x01 = 1 = modifier key
    // 0x02 = 2 = underglow
    // 0x04 = 4 = key backlight
    // 0x08 = 8 = keyboard state indication
    // Left half
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 1,
    4, 4, 4, 4, 4, 1,
    4, 4, 1, 1, 1, 1,
    // Right half
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    1, 4, 4, 4, 4, 4,
    4, 4, 1, 1, 1, 1
} };

#endif // RGB_MATRIX_ENABLE
#endif // KEYBOARD_keycapsss_kimiko_rev1

#ifdef KEYBOARD_keycapsss_kimiko_rev2
enum layers {
   _QWERTY,
   _LOWER,
   _RAISE,
   _ADJUST
};

#ifdef OLED_ENABLE

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

// NOTE: Most of the OLED code was originally written by Soundmonster for the Corne,
// and has been copied directly from `crkbd/soundmonster/keymap.c`

void render_mod_status_gui_alt(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[] = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[] = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[] = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[] = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }

    if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}

void render_mod_status_ctrl_shift(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
    static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
    static const char PROGMEM ctrl_on_1[] = {0x91, 0x92, 0};
    static const char PROGMEM ctrl_on_2[] = {0xb1, 0xb2, 0};

    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM shift_on_1[] = {0xcd, 0xce, 0};
    static const char PROGMEM shift_on_2[] = {0xcf, 0xd0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }

    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_1, false);
    } else {
        oled_write_P(shift_off_1, false);
    }

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }

    if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_2, false);
    } else {
        oled_write_P(shift_off_2, false);
    }
}


void render_logo(void) {
    static const char PROGMEM kimiko_logo[] = {
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0};
    oled_advance_page(false);
    oled_advance_page(false);
    oled_write_P(kimiko_logo, false);
    // oled_write_P(PSTR("Kimiko"), false);
}

void render_layer_state(void) {
	static const char PROGMEM default_layer[] = {
		0x20, 0x94, 0x95, 0x96, 0x20,
		0x20, 0xb4, 0xb5, 0xb6, 0x20,
		0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
	static const char PROGMEM raise_layer[] = {
		0x20, 0x97, 0x98, 0x99, 0x20,
		0x20, 0xb7, 0xb8, 0xb9, 0x20,
		0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
	static const char PROGMEM lower_layer[] = {
		0x20, 0x9a, 0x9b, 0x9c, 0x20,
		0x20, 0xba, 0xbb, 0xbc, 0x20,
		0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
	static const char PROGMEM adjust_layer[] = {
		0x20, 0x9d, 0x9e, 0x9f, 0x20,
		0x20, 0xbd, 0xbe, 0xbf, 0x20,
		0x20, 0xdd, 0xde, 0xdf, 0x20, 0};

	if(layer_state_is(_ADJUST)) {
		oled_write_P(adjust_layer, false);
	} else if(layer_state_is(_LOWER)) {
		oled_write_P(lower_layer, false);
	} else if(layer_state_is(_RAISE)) {
		oled_write_P(raise_layer, false);
	} else {
		oled_write_P(default_layer, false);
	}
}

void render_status_main(void) {
    render_logo();
    oled_advance_page(false);
    render_layer_state();
    oled_advance_page(false);
    render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
    render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }

    if (is_keyboard_master()) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_logo();
    }

    return true;
}
#endif // OLED_ENABLE
#endif // keyboard keycapsss_kimiko_rev2

