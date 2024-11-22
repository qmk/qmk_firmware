// Copyright 2024 SDK (@sdk66)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rgb_effect.h"

void rgblight_effect_breathing(animation_status_t *anim) {
    static uint8_t i, r, g, b, dir;

    switch (i) {
        case 0: {
            if (dir == 0) {
                if (r < BREATHING_VAL - 1)
                    r += 2;
                else
                    r++;
            }
            if (r == BREATHING_VAL) dir = 1;
            if (dir == 1) {
                if (r > 1)
                    r -= 2;
                else
                    r--;
                if (r == 0) {
                    dir = 0;
                    i   = 1;
                }
            }
        } break;
        case 1: {
            if (dir == 0) {
                if (g < BREATHING_VAL - 1)
                    g += 2;
                else
                    g++;
            }
            if (g == BREATHING_VAL) dir = 1;
            if (dir == 1) {
                if (g > 1)
                    g -= 2;
                else
                    g--;
                if (g == 0) {
                    dir = 0;
                    i   = 2;
                }
            }
        } break;
        case 2: {
            if (dir == 0) {
                if (b < BREATHING_VAL - 1)
                    b += 2;
                else
                    b++;
            }
            if (b == BREATHING_VAL) dir = 1;
            if (dir == 1) {
                if (b > 1)
                    b -= 2;
                else
                    b--;

                if (b == 0) {
                    dir = 0;
                    i   = 3;
                }
            }
        } break;
        case 3: {
            if (dir == 0) {
                if (r < BREATHING_VAL - 1) {
                    r += 2;
                    b += 2;
                } else {
                    r++;
                    b++;
                }
            }
            if (r == BREATHING_VAL) dir = 1;
            if (dir == 1) {
                if (r > 1) {
                    r -= 2;
                    b -= 2;
                } else {
                    r--;
                    b--;
                }
                if (r == 0) {
                    dir = 0;
                    i   = 4;
                }
            }
        } break;
        case 4: {
            if (dir == 0) {
                if (r < BREATHING_VAL - 1) {
                    r += 2;
                    g += 2;
                } else {
                    r++;
                    g++;
                }
            }
            if (r == BREATHING_VAL) dir = 1;
            if (dir == 1) {
                if (r > 1) {
                    r -= 2;
                    g -= 2;
                } else {
                    r--;
                    g--;
                }
                if (r == 0) {
                    dir = 0;
                    i   = 5;
                }
            }
        } break;
        case 5: {
            if (dir == 0) {
                if (g < BREATHING_VAL - 1) {
                    g += 2;
                    b += 2;
                } else {
                    g++;
                    b++;
                }
            }
            if (g == BREATHING_VAL) dir = 1;
            if (dir == 1) {
                if (g > 1) {
                    g -= 2;
                    b -= 2;
                } else {
                    g--;
                    b--;
                }
                if (g == 0) {
                    dir = 0;
                    i   = 6;
                }
            }
        } break;
        case 6: {
            if (dir == 0) {
                if (g < BREATHING_VAL - 1) {
                    g += 2;
                    b += 2;
                    r += 2;
                } else {
                    g++;
                    r++;
                    b++;
                }
            }
            if (g == BREATHING_VAL) dir = 1;
            if (dir == 1) {
                if (g > 1) {
                    g -= 2;
                    b -= 2;
                    r -= 2;
                } else {
                    g--;
                    r--;
                    b--;
                }
                if (g == 0) {
                    dir = 0;
                    i   = 0;
                }
            }
        } break;
        default:
            break;
    }
    for (uint8_t j = 0; j < RGBLED_NUM; j++)
        rgblight_setrgb_at(r, g, b, j);
}

void rgblight_effect_rainbow_mood(animation_status_t *anim) {
    static uint8_t i = 0, r = RAINBOW_MOOD, g = 0, b = 0;

    if (rgblight_config.enable) {
        for (uint8_t j = 0; j < RGBLED_NUM; j++)
            rgblight_setrgb_at(r, g, b, j);

        if (i == 0) {
            if (g < RAINBOW_MOOD - 1) {
                r -= 2;
                g += 2;
            } else {
                r--;
                g++;
            }
            if (g == RAINBOW_MOOD) i = 1;
        }
        if (i == 1) {
            if (b < RAINBOW_MOOD - 1) {
                g -= 2;
                b += 2;
            } else {
                g--;
                b++;
            }
            if (b == RAINBOW_MOOD) i = 2;
        }
        if (i == 2) {
            if (r < RAINBOW_MOOD - 1) {
                b -= 2;
                r += 2;
            } else {
                b--;
                r++;
            }
            if (r == RAINBOW_MOOD) i = 0;
        }
    }
}

bool rgblight_effect_custom_rainbow_swirl(animation_status_t *anim) {
    uint8_t hue;
    uint8_t i;

    for (i = 0; i < rgblight_ranges.effect_num_leds / 2; i++) {
        hue = (RGBLIGHT_RAINBOW_SWIRL_RANGE / rgblight_ranges.effect_num_leds * i + anim->current_hue);
        sethsv(hue, rgblight_config.sat, rgblight_config.val, (LED_TYPE *)&led[i + rgblight_ranges.effect_start_pos]);
        sethsv(hue, rgblight_config.sat, rgblight_config.val, (LED_TYPE *)&led[rgblight_ranges.effect_num_leds - 1 - i + rgblight_ranges.effect_start_pos]);
    }
    rgblight_set();

    if (anim->delta % 2) {
        anim->current_hue++;
        anim->current_hue++;
        anim->current_hue++;
    } else {
        anim->current_hue--;
        anim->current_hue--;
        anim->current_hue--;
    }

    return false;
}