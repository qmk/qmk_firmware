/* Copyright 2026 Javier Domingo
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

#ifdef RULE_LIGHTING_ENABLE
#    define RGB_MATRIX_EFFECT_RULE_LIGHTING
RGB_MATRIX_EFFECT(RULE_LIGHTING)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#        include "rule_lighting.h"
#        include "action_layer.h"
#        include "action_util.h"
#        include "host.h"

/**
 * Find a matching rule for a key (first-match-wins)
 */
static int8_t rule_lighting_find_match(uint16_t keycode, uint8_t current_layer, uint8_t current_mods, bool caps_on) {
    const rule_lighting_entry_t *rules = rule_lighting_get_rules();

    for (uint8_t i = 0; i < RULE_LIGHTING_ENTRIES; i++) {
        const rule_lighting_entry_t *rule = &rules[i];

        /* Skip empty entries */
        if (!RGB_MATRIX_SAT_IS_ON(rule->sat_idle) && !RGB_MATRIX_SAT_IS_ON(rule->sat_pressed)) {
            continue;
        }

        /* Layer check */
        if (rule->layer_enable && current_layer != rule->layer) {
            continue;
        }

        /* Mods check (OR logic) */
        if (rule->mods != 0 && (current_mods & rule->mods) == 0) {
            continue;
        }

        /* Caps check */
        if (rule->caps_enable && !caps_on) {
            continue;
        }

        /* Keycode range check */
        if (keycode >= rule->keycode_start && keycode <= rule->keycode_end) {
            return i;
        }
    }
    return -1;
}

/**
 * Get the tick (time since last press) for an LED
 */
static uint16_t rule_lighting_get_tick(uint8_t led_index, uint8_t speed) {
#        ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
    uint16_t max_tick = 65535 / qadd8(speed, 1);

    for (int8_t j = g_last_hit_tracker.count - 1; j >= 0; j--) {
        if (g_last_hit_tracker.index[j] == led_index) {
            return g_last_hit_tracker.tick[j];
        }
    }
    return max_tick;
#        else
    return 65535;
#        endif
}

/**
 * Calculate color for a key based on its rule and press state
 */
static void rule_lighting_calc_color(const rule_lighting_entry_t *rule, uint16_t tick, uint8_t speed, uint8_t *h, uint8_t *s, uint8_t *v) {
    uint16_t scaled_time = scale16by8(tick, qadd8(speed, 1));
    uint8_t  blend       = (scaled_time > 255) ? 255 : (uint8_t)scaled_time;

    uint8_t brightness = rgb_matrix_get_val();

    uint8_t h_idle    = RGB_MATRIX_HUE_6TO8(rule->h_idle);
    uint8_t h_pressed = RGB_MATRIX_HUE_6TO8(rule->h_pressed);
    uint8_t s_idle    = rgb_matrix_sat_to_value(rule->sat_idle);
    uint8_t s_pressed = rgb_matrix_sat_to_value(rule->sat_pressed);

    bool pressed_off = !RGB_MATRIX_SAT_IS_ON(rule->sat_pressed);
    bool idle_off    = !RGB_MATRIX_SAT_IS_ON(rule->sat_idle);

    if (blend < 255) {
        if (pressed_off) {
            *h = h_idle;
            *s = s_idle;
            *v = scale8(brightness, blend);
        } else if (idle_off) {
            *h = h_pressed;
            *s = s_pressed;
            *v = scale8(brightness, 255 - blend);
        } else {
            *h = lerp8by8(h_pressed, h_idle, blend);
            *s = lerp8by8(s_pressed, s_idle, blend);
            *v = brightness;
        }
    } else {
        if (idle_off) {
            *h = 0;
            *s = 0;
            *v = 0;
        } else {
            *h = h_idle;
            *s = s_idle;
            *v = brightness;
        }
    }
}

bool RULE_LIGHTING(effect_params_t *params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    /* Get current keyboard state */
    uint8_t current_layer = get_highest_layer(layer_state);
    uint8_t current_mods  = get_mods() | get_weak_mods();
#        ifndef NO_ACTION_ONESHOT
    current_mods |= get_oneshot_mods();
#        endif
    bool caps_on = host_keyboard_led_state().caps_lock;

    /* Iterate over the key matrix, but only process LEDs in our range */
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint8_t led_index = g_led_config.matrix_co[row][col];

            /* Skip if no LED or outside our processing range */
            if (led_index == NO_LED || led_index < led_min || led_index >= led_max) {
                continue;
            }

            /* Check LED flags */
            if (!HAS_ANY_FLAGS(g_led_config.flags[led_index], params->flags)) {
                continue;
            }

            /* Get the keycode for this key on the current layer
             * Uses synced keymap for split keyboard support */
            uint16_t keycode = get_synced_keycode(current_layer, row, col);

            /* Find matching rule */
            int8_t rule_idx = rule_lighting_find_match(keycode, current_layer, current_mods, caps_on);

            if (rule_idx >= 0) {
                const rule_lighting_entry_t *rules = rule_lighting_get_rules();
                const rule_lighting_entry_t *rule  = &rules[rule_idx];
                uint8_t                      speed = rgb_matrix_get_speed();
                uint16_t                     tick  = rule_lighting_get_tick(led_index, speed);

                uint8_t h, s, v;
                rule_lighting_calc_color(rule, tick, speed, &h, &s, &v);

                hsv_t hsv = {.h = h, .s = s, .v = v};
                rgb_t rgb = rgb_matrix_hsv_to_rgb(hsv);
                rgb_matrix_set_color(led_index, rgb.r, rgb.g, rgb.b);
            } else {
                /* No matching rule - set to black */
                rgb_matrix_set_color(led_index, 0, 0, 0);
            }
        }
    }

    return rgb_matrix_check_finished_leds(led_max);
}

#    endif /* RGB_MATRIX_CUSTOM_EFFECT_IMPLS */
#endif     /* RULE_LIGHTING_ENABLE */
