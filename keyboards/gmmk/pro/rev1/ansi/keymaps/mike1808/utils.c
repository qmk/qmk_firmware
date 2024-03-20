/* Copyright 2021 Mikael Manukyan <arm.localhost@gmail.com>
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
#include "utils.h"

void store_rgb_state_to_eeprom(void) {
    uint8_t mode  = rgb_matrix_get_mode();
    uint8_t speed = rgb_matrix_get_speed();
    HSV     color = rgb_matrix_get_hsv();

    rgb_matrix_mode(mode);
    rgb_matrix_set_speed(speed);
    rgb_matrix_sethsv(color.h, color.s, color.v);
}

void press(KeyPressState *self) {
    self->_count++;

    dprintf("KPS: press: %d\n", self->_count);

    // pressed the first time
    if (self->_count == 1) {
        self->hander(true);
    }
}

void release(KeyPressState *self) {
    self->_count--;

    dprintf("KPS: release: %d\n", self->_count);

    // all keys are relased
    if (self->_count == 0) {
        self->hander(false);
    }
}

void reset(KeyPressState *self) {
    self->_count = 0;
}

KeyPressState *NewKeyPressState(key_press_handler handler) {
    KeyPressState *kps = (KeyPressState *)(malloc(sizeof(KeyPressState)));

    kps->_count = 0;
    kps->press = press;
    kps->release = release;
    kps->reset = reset;
    kps->hander = handler;

    return kps;
}
