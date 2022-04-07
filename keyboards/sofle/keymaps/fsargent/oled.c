/* Copyright 2020 Josef Adamcik
 * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
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

// Sets up what the OLED screens display.

#ifdef OLED_ENABLE

static void print_status_narrow(void) {
    // Print current layer
    // enum layers { BASE,WIN, GAME, SYM, NAV, WINNAV};
    // enum encoder_modes { ARROWS, TASKS, MUSIC, PAGES };

    // 32x128 OLED
    // font width 6 height 8
    // 32/6 = 5
    // 128/8 = 16
    void oled_set_cursor(uint8_t col, uint8_t line);
    switch (get_highest_layer(layer_state)) {
        oled_write_P(PSTR("Layer\n"), false);
        case 0:
            oled_write_P(PSTR("OS X\n"), true);
            oled_write_P(PSTR("WIN\n"), false);
            oled_write_P(PSTR("GAME\n"), false);
            oled_write_P(PSTR("SHFT\n\n"), false);
            oled_write_P(PSTR("NAV\n"), false);
            oled_write_P(PSTR("SYM\n"), false);
            break;
        case 1:
            oled_write_P(PSTR("OS X\n"), false);
            oled_write_P(PSTR("WIN\n"), true);
            oled_write_P(PSTR("GAME\n"), false);
            oled_write_P(PSTR("SHFT\n\n"), false);
            oled_write_P(PSTR("NAV\n"), false);
            oled_write_P(PSTR("SYM\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("OS X\n"), false);
            oled_write_P(PSTR("WIN\n"), false);
            oled_write_P(PSTR("GAME\n"), true);
            oled_write_P(PSTR("SHFT\n\n"), false);
            oled_write_P(PSTR("NAV\n"), false);
            oled_write_P(PSTR("SYM\n"), false);
            break;
        case 3:
            oled_write_P(PSTR("OS X\n"), false);
            oled_write_P(PSTR("WIN\n"), false);
            oled_write_P(PSTR("GAME\n"), false);
            oled_write_P(PSTR("SHFT\n\n"), false);
            oled_write_P(PSTR("NAV\n"), false);
            oled_write_P(PSTR("SYM\n"), true);
            break;
        case 4:
            oled_write_P(PSTR("OS X\n"), false);
            oled_write_P(PSTR("WIN\n"), false);
            oled_write_P(PSTR("GAME\n"), false);
            oled_write_P(PSTR("SHFT\n\n"), false);
            oled_write_P(PSTR("NAV\n"), true);
            oled_write_P(PSTR("SYM\n"), false);
            break;
        case 5:
            oled_write_P(PSTR("OS X\n"), false);
            oled_write_P(PSTR("WIN\n"), false);
            oled_write_P(PSTR("GAME\n"), false);
            oled_write_P(PSTR("SHFT\n\n"), false);
            oled_write_P(PSTR("NAV\n"), true);
            oled_write_P(PSTR("SYM\n"), false);
            break;
        case 6:
            oled_write_P(PSTR("OS X\n"), false);
            oled_write_P(PSTR("WIN\n"), false);
            oled_write_P(PSTR("GAME\n"), false);
            oled_write_P(PSTR("SHFT\n\n"), true);
            oled_write_P(PSTR("NAV\n"), false);
            oled_write_P(PSTR("SYM\n"), false);
            break;

        default:
            oled_write_P(PSTR("OS X\n"), false);
            oled_write_P(PSTR("WIN\n"), false);
            oled_write_P(PSTR("GAME\n"), false);
            oled_write_P(PSTR("SHFT\n\n"), false);
            oled_write_P(PSTR("NAV\n"), false);
            oled_write_P(PSTR("SYM\n"), false);
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

void render_mod_status(void) {
    bool    blink     = (timer_read() % 1000) < 500;
    uint8_t modifiers = get_mods();
    if (modifiers & MOD_MASK_SHIFT & MOD_MASK_ALT & MOD_MASK_CTRL) {
        oled_write_ln_P(blink ? PSTR("$meh_") : PSTR("$meh "), false);
    } else if (modifiers & MOD_MASK_CTRL) {
        oled_write_ln_P(blink ? PSTR("$ctl_") : PSTR("$ctl "), false);
    } else if (modifiers & MOD_MASK_SHIFT) {
        oled_write_ln_P(blink ? PSTR("$sft_") : PSTR("$sft "), false);
    } else if (modifiers & MOD_MASK_ALT) {
        oled_write_ln_P(blink ? PSTR("$alt_") : PSTR("$alt "), false);
    } else if (modifiers & MOD_MASK_GUI) {
        oled_write_ln_P(blink ? PSTR("$gui_") : PSTR("$gui "), false);
    } else {
        oled_write_ln_P(blink ? PSTR("$_  ") : PSTR("$    "), false);
    }
}

// enum encoder_modes { ARROWS, TASKS, MUSIC, PAGES };
void render_encoder_status(void) {
    // oled_write_P(PSTR("KNOB\n"), false);
	// \x18 Up Arrow   \x19 Down Arrow
	// \x1B Left Arrow \x1A Right Arrow
    if (encoder_mode == ARROWS) {  // Arrows
        if (!is_keyboard_master()) {
            oled_write_ln_P(PSTR("\x18\x19"), false);
        } else {
            oled_write_ln_P(PSTR("\x1B\x1A"), false);
        }
    } else if (encoder_mode == TASKS) {  // Tasks

        if (!is_keyboard_master()) {
            oled_write_ln_P(PSTR("Tabs"), false);
        } else {
            oled_write_P(PSTR("Wndws"), false);
        }
    } else if (encoder_mode == MUSIC) {  // Music

        if (!is_keyboard_master()) {
        	oled_write_ln_P(PSTR("Vol"), false);
            // oled_write_P(PSTR(" \x0E\x0E\x0E "), false);
        } else {
			oled_write_P(PSTR("Track"), false);
            // oled_write_P(PSTR("\x1B \x0E \x1A"), false);
        }
    } else if (encoder_mode == PAGES) {  // Pages
        if (!is_keyboard_master()) {
            oled_write_ln_P(PSTR("Pg\x18\x19"), false);
        } else {
            oled_write_ln_P(PSTR("Pg\x1B\x1A"), false);
        }
    } else if (encoder_mode == WHEEL) {  // Pages
        if (!is_keyboard_master()) {
            oled_write_ln_P(PSTR("MW\x18\x19"), false);// up down
        } else {
            oled_write_ln_P(PSTR("MW\x1B\x1A"), false); // left right
        }
    }
}
void oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
        oled_set_cursor(0, 15);
        render_encoder_status();
    } else {
        print_status_narrow();
        oled_set_cursor(0, 15);
        render_encoder_status();
    }
}

#endif
