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

void keyboard_post_init_kb(void) {
    // set pin based on active status
    writePin(SPEAKER_SHUTDOWN, audio_is_on());
    keyboard_post_init_user();
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
