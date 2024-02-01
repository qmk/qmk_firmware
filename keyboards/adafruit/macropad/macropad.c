/* Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
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

#ifdef AUDIO_ENABLE
void keyboard_pre_init_kb(void) {
    // ensure pin is set and enabled pre-audio init
    setPinOutput(SPEAKER_SHUTDOWN);
    writePinHigh(SPEAKER_SHUTDOWN);
    keyboard_pre_init_user();
}

void audio_on_user(void) {
    writePinHigh(SPEAKER_SHUTDOWN);
}

void audio_off_user(void) {
    // needs a delay or it runs right after play note.
    wait_ms(200);
    writePinLow(SPEAKER_SHUTDOWN);
}
#endif

#ifdef QUANTUM_PAINTER_ENABLE
painter_device_t oled_display;
#endif

void keyboard_post_init_kb(void) {
#ifdef QUANTUM_PAINTER_ENABLE
    // Init. oled display
    oled_display = qp_sh1106_make_spi_device(OLED_WIDTH + OLED_COLUMN_OFFSET, OLED_HEIGHT, OLED_CS_PIN, OLED_DC_PIN, OLED_RST_PIN, OLED_SPI_DIVISOR, OLED_SPI_MODE);
    qp_init(oled_display, 0);

    // Apply Offset
    qp_set_viewport_offsets(oled_display, OLED_COLUMN_OFFSET, 0);

    // Turn on the LCD and clear the display
    qp_power(oled_display, true);
    qp_rect(oled_display, 0, 0, OLED_WIDTH, OLED_HEIGHT, HSV_BLACK, true);
#endif

#ifdef AUDIO_ENABLE
    // set pin based on active status
    writePin(SPEAKER_SHUTDOWN, audio_is_on());
#endif

    keyboard_post_init_user();
}