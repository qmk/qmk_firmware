/* Copyright 2020 Harrison Chan (Xelus)
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

// Tested and verified working on ext65rev2
void matrix_io_delay(void) { __asm__ volatile("nop\nnop\nnop\n"); }

#ifdef OLED_ENABLE
void board_init(void) {
  SYSCFG->CFGR1 |= SYSCFG_CFGR1_I2C1_DMA_RMP;
  SYSCFG->CFGR1 &= ~(SYSCFG_CFGR1_SPI2_DMA_RMP);
}

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_90;  // rotates the display 90 degrees
}

void render_layer_state(void) {
    oled_write_ln(PSTR("LAYER"), false);
    oled_write_ln(PSTR("L1"), layer_state_is(1));
    oled_write_ln(PSTR("L2"), layer_state_is(2));
    oled_write_ln(PSTR("L3"), layer_state_is(3));
    oled_write_ln(PSTR(" "), false);
}

void render_keylock_status(led_t led_state) {
    oled_write_ln(PSTR("Lock:"), false);
    oled_write(PSTR("N"), led_state.num_lock);
    oled_write(PSTR("C"), led_state.caps_lock);
    oled_write_ln(PSTR("S"), led_state.scroll_lock);
    oled_write_ln(PSTR(" "), false);
}

void render_mod_status(uint8_t modifiers) {
    oled_write_ln(PSTR("Mods:"), false);
    oled_write(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
    oled_write(PSTR("C"), (modifiers & MOD_MASK_CTRL));
    oled_write(PSTR("A"), (modifiers & MOD_MASK_ALT));
    oled_write_ln(PSTR("G"), (modifiers & MOD_MASK_GUI));
    oled_write_ln(PSTR(" "), false);
}

bool oled_task_kb(void) {
    render_layer_state();
    render_keylock_status(host_keyboard_led_state());
    render_mod_status(get_mods()|get_oneshot_mods());
    return false;
}

#else

void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.
  // Set our LED pins as output
  setPinOutput(B4);
  setPinOutput(B3);
  setPinOutput(A15);
  setPinOutput(A14);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(B4, led_state.num_lock);
        writePin(B3, led_state.caps_lock);
        writePin(A15, led_state.scroll_lock);
    }
    return res;
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    switch (get_highest_layer(state)) {
      case 1:
        writePinHigh(A14);
        break;
      default: //  for any other layers, or the default layer
        writePinLow(A14);
        break;
      }
    return layer_state_set_user(state);
}
#endif

