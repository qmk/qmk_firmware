/* Copyright (C) 2021 @filterpaper
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

/* Graphical active layer and modifier status display. Module must be 
   rendered on primary OLED

   @soundmonster is the original author of this code 
   (qmk_firmware/keyboards/crkbd/keymaps/soundmonster)
*/

void render_space(void) {
	oled_write_P(PSTR("\n\n"), false);
}

void render_logo(void) {
	static const char PROGMEM corne_logo[] = {
		0x80, 0x81, 0x82, 0x83, 0x84,
		0xa0, 0xa1, 0xa2, 0xa3, 0xa4,
		0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0};
	oled_write_P(corne_logo, false);
	oled_write_P(PSTR("corne"), false);
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

	if (layer_state_is(_ADJUST)) oled_write_P(adjust_layer, false);
	else if (layer_state_is(_LOWER)) oled_write_P(lower_layer, false);
	else if (layer_state_is(_RAISE)) oled_write_P(raise_layer, false);
	else oled_write_P(default_layer, false);
}

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

	if (modifiers & MOD_MASK_GUI) oled_write_P(gui_on_1, false);
	else oled_write_P(gui_off_1, false);

	if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) oled_write_P(on_on_1, false);
	else if (modifiers & MOD_MASK_GUI) oled_write_P(on_off_1, false);
	else if (modifiers & MOD_MASK_ALT) oled_write_P(off_on_1, false);
	else oled_write_P(off_off_1, false);

	if (modifiers & MOD_MASK_ALT) oled_write_P(alt_on_1, false);
	else oled_write_P(alt_off_1, false);

	if (modifiers & MOD_MASK_GUI) oled_write_P(gui_on_2, false);
	else oled_write_P(gui_off_2, false);

	if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) oled_write_P(on_on_2, false);
	else if (modifiers & MOD_MASK_GUI) oled_write_P(on_off_2, false);
	else if (modifiers & MOD_MASK_ALT) oled_write_P(off_on_2, false);
	else oled_write_P(off_off_2, false);

	if (modifiers & MOD_MASK_ALT) oled_write_P(alt_on_2, false);
	else oled_write_P(alt_off_2, false);
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

	if (modifiers & MOD_MASK_CTRL) oled_write_P(ctrl_on_1, false);
	else oled_write_P(ctrl_off_1, false);

	if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) oled_write_P(on_on_1, false);
	else if (modifiers & MOD_MASK_CTRL) oled_write_P(on_off_1, false);
	else if (modifiers & MOD_MASK_SHIFT) oled_write_P(off_on_1, false);
	else oled_write_P(off_off_1, false);

	if (modifiers & MOD_MASK_SHIFT) oled_write_P(shift_on_1, false);
	else oled_write_P(shift_off_1, false);

	if (modifiers & MOD_MASK_CTRL) oled_write_P(ctrl_on_2, false);
	else oled_write_P(ctrl_off_2, false);

	if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) oled_write_P(on_on_2, false);
	else if (modifiers & MOD_MASK_CTRL) oled_write_P(on_off_2, false);
	else if (modifiers & MOD_MASK_SHIFT) oled_write_P(off_on_2, false);
	else oled_write_P(off_off_2, false);

	if (modifiers & MOD_MASK_SHIFT) oled_write_P(shift_on_2, false);
	else oled_write_P(shift_off_2, false);
}

// Render everything on OLED
static void render_mod_status(void) {
	render_logo();
	render_space();
	render_layer_state();
	render_space();
	render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
	render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
}
