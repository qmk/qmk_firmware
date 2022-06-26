/* Copyright 2021 Jonathan Rascher
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

#include "bcat_oled.h"

#include "quantum.h"
#include "bcat.h"

#if defined(BCAT_OLED_PET)
#    include "bcat_oled_pet.h"
#endif

#define TRIANGLE_UP 0x1e
#define TRIANGLE_DOWN 0x1f

#if defined(BCAT_OLED_PET)
static bool oled_pet_should_jump = false;
#endif

/* Should be overridden by the keymap to render the OLED contents. For split
 * keyboards, this function is only called on the master side.
 */
__attribute__((weak)) void oled_task_keymap(const oled_keyboard_state_t *keyboard_state) {}

bool oled_task_user(void) {
#if defined(SPLIT_KEYBOARD)
    if (is_keyboard_master()) {
#endif
        /* Custom OLED timeout implementation that only considers user activity.
         * Allows the OLED to turn off in the middle of a continuous animation.
         */
        static const uint16_t TIMEOUT_MILLIS = 60000 /* 1 min */;

        if (last_input_activity_elapsed() < TIMEOUT_MILLIS) {
            if (!is_oled_on()) {
                oled_on();
            }
            oled_keyboard_state_t keyboard_state = {
                .mods = get_mods(),
                .leds = host_keyboard_led_state(),
                .wpm  = get_current_wpm(),
            };
            oled_task_keymap(&keyboard_state);
        } else if (is_oled_on()) {
            oled_off();
        }
#if defined(SPLIT_KEYBOARD)
    } else {
        /* Display logo embedded at standard location in the OLED font on the
         * slave side. By default, this is a "QMK firmware" logo, but many
         * keyboards substitute their own logo. Occupies 21x3 character cells.
         *
         * Since the slave display buffer never changes, we don't need to worry
         * about oled_render incorrectly turning the OLED on. Instead, we rely
         * on SPLIT_OLED_ENABLE to propagate OLED on/off status from master.
         */
        static const char PROGMEM logo[] = {
            // clang-format off
            0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
            0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
            0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
            0x00,
            // clang-format on
        };

        oled_write_P(logo, /*invert=*/false);
    }
#endif

    return false;
}

void render_oled_layers(void) {
    oled_advance_char();
    oled_advance_char();
#if defined(BCAT_ORTHO_LAYERS)
    oled_write_char(IS_LAYER_ON(LAYER_LOWER) ? TRIANGLE_DOWN : ' ', /*invert=*/false);
    oled_advance_char();
    oled_write_char(IS_LAYER_ON(LAYER_RAISE) ? TRIANGLE_UP : ' ', /*invert=*/false);
#else
    switch (get_highest_layer(layer_state)) {
        case LAYER_FUNCTION_1:
            oled_write_P(PSTR("FN1"), /*invert=*/false);
            break;
        case LAYER_FUNCTION_2:
            oled_write_P(PSTR("FN2"), /*invert=*/false);
            break;
        default:
            oled_write_P(PSTR("   "), /*invert=*/false);
            break;
    }
#endif
}

void render_oled_indicators(led_t leds) {
    oled_advance_char();
    oled_advance_char();
    oled_write_P(leds.num_lock ? PSTR("NUM") : PSTR("   "), /*invert=*/false);
    oled_advance_char();
    oled_advance_char();
    oled_write_P(leds.caps_lock ? PSTR("CAP") : PSTR("   "), /*invert=*/false);
    oled_advance_char();
    oled_advance_char();
    oled_write_P(leds.scroll_lock ? PSTR("SCR") : PSTR("   "), /*invert=*/false);
}

void render_oled_wpm(uint8_t wpm) {
    static const uint16_t UPDATE_MILLIS  = 100;
    static uint32_t       update_timeout = 0;

    if (timer_expired32(timer_read32(), update_timeout)) {
        oled_advance_char();
        oled_advance_char();
        oled_write_P(wpm > 0 ? PSTR("WPM") : PSTR("   "), /*invert=*/false);
        if (wpm > 0) {
            oled_advance_char();
            oled_advance_char();
            oled_write(get_u8_str(wpm, ' '), /*invert=*/false);
        } else {
            oled_advance_page(/*clearPageRemainder=*/true);
        }

        update_timeout = timer_read32() + UPDATE_MILLIS;
    }
}

#if defined(BCAT_OLED_PET)
void process_record_oled(uint16_t keycode, const keyrecord_t *record) {
    switch (keycode) {
        case KC_SPACE:
            if (oled_pet_can_jump()) {
                oled_pet_should_jump = record->event.pressed;
            }
            break;
        default:
            break;
    }
}

static void redraw_oled_pet(uint8_t col, uint8_t line, bool jumping, oled_pet_state_t state) {
    oled_set_cursor(col, line);
    if (jumping) {
        oled_write_raw_P(oled_pet_frame(state), oled_pet_frame_bytes());
        oled_set_cursor(col, line + oled_pet_frame_lines());
        oled_advance_page(/*clearPageRemainder=*/true);
    } else {
        oled_advance_page(/*clearPageRemainder=*/true);
        oled_write_raw_P(oled_pet_frame(state), oled_pet_frame_bytes());
    }
}

void render_oled_pet(uint8_t col, uint8_t line, const oled_keyboard_state_t *keyboard_state) {
    /* Current animation to draw. We track changes to avoid redrawing the same
     * frame repeatedly, allowing oled_pet_post_render to draw over the
     * animation frame.
     */
    static oled_pet_state_t state         = 0;
    static bool             state_changed = true;

    /* Minimum time until the pet comes down after jumping. */
    static const uint16_t JUMP_MILLIS = 200;
    static bool           jumping     = false;

    /* Time until the next animation or jump state change. */
    static uint32_t update_timeout = 0;
    static uint32_t jump_timeout   = 0;

    /* If the user pressed the jump key, immediately redraw instead of waiting
     * for the animation frame to update. That way, the pet appears to respond
     * to jump commands quickly rather than lagging. If the user released the
     * jump key, wait for the jump timeout to avoid overly brief jumps.
     */
    bool redraw = state_changed;
    if (oled_pet_should_jump && !jumping) {
        redraw       = true;
        jumping      = true;
        jump_timeout = timer_read32() + JUMP_MILLIS;
    } else if (!oled_pet_should_jump && jumping && timer_expired32(timer_read32(), jump_timeout)) {
        redraw  = true;
        jumping = false;
    }

    /* Draw the actual animation, then move the cursor to the end of the
     * rendered area. (Note that we take up an extra line to account for
     * jumping, which shifts the animation up or down a line.)
     */
    if (redraw) {
        redraw_oled_pet(col, line, jumping, state);
    }
    oled_pet_post_render(col, line + !jumping, keyboard_state, redraw);
    oled_set_cursor(col, line + oled_pet_frame_lines() + 1);

    /* If the update timer expired, recompute the pet's animation state. */
    if (timer_expired32(timer_read32(), update_timeout)) {
        oled_pet_state_t new_state = oled_pet_next_state(state, keyboard_state);
        state_changed              = new_state != state;
        state                      = new_state;
        update_timeout             = timer_read32() + oled_pet_update_millis(keyboard_state);
    } else {
        state_changed = false;
    }
}
#endif
