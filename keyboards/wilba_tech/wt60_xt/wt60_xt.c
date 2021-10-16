/* Copyright 2020 Jason Williams (Wilba)
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

#include "wt60_xt.h"

#ifdef AUDIO_ENABLE
#include "audio.h"
#include "song_list.h"

float tone_caps_on[][2]    = SONG(CAPS_LOCK_ON_SOUND);
float tone_caps_off[][2]   = SONG(CAPS_LOCK_OFF_SOUND);
float tone_numlk_on[][2]   = SONG(NUM_LOCK_ON_SOUND);
float tone_numlk_off[][2]  = SONG(NUM_LOCK_OFF_SOUND);
float tone_scroll_on[][2]  = SONG(SCROLL_LOCK_ON_SOUND);
float tone_scroll_off[][2] = SONG(SCROLL_LOCK_OFF_SOUND);

#endif

// We want to enable audio clicky (i.e. compile it into firmware),
// but not have it "turned on" by default.
#ifdef AUDIO_CLICKY

#include "process_clicky.h"
extern audio_config_t audio_config;

void eeconfig_init_kb(void) {
    // Reset Keyboard EEPROM value to blank, rather than to a set value
    eeconfig_update_kb(0);

    // Need to read here because this isn't done before calling eeconfig_init_kb()
    audio_config.raw = eeconfig_read_audio();
    // ...and this call needs audio_config initialized.
    clicky_off();

    eeconfig_init_user();
}
#endif // AUDIO_CLICKY

void keyboard_pre_init_kb(void) {
    setPinOutput(F1);

    keyboard_pre_init_user();
}

bool led_update_kb(led_t led_state) {
    if (led_update_user(led_state)) {
        writePin(F1, led_state.caps_lock);
    }

#ifdef AUDIO_ENABLE
    static led_t old_led_state = { .raw = 0 };

    wait_ms(10); // gets rid of tick

    if (led_state.caps_lock && !old_led_state.caps_lock)
    {
        PLAY_SONG(tone_caps_on);
    }
    else if (!led_state.caps_lock && old_led_state.caps_lock)
    {
        PLAY_SONG(tone_caps_off);
    }
    else if (led_state.num_lock && !old_led_state.num_lock)
    {
        PLAY_SONG(tone_numlk_on);
    }
    else if (!led_state.num_lock && old_led_state.num_lock)
    {
        PLAY_SONG(tone_numlk_off);
    }
    else if (led_state.scroll_lock && !old_led_state.scroll_lock)
    {
        PLAY_SONG(tone_scroll_on);
    }
    else if (!led_state.scroll_lock && old_led_state.scroll_lock)
    {
        PLAY_SONG(tone_scroll_off);
    }

    old_led_state = led_state;
#endif // AUDIO_ENABLE

    return true;
}
