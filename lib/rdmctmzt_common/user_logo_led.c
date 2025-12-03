/* Copyright 2024 Finalkey
 * Copyright 2024 LiWenLiu <https://github.com/LiuLiuQMK>
 * Copyright 2025 Carlos Eduardo de Paula <carlosedp@gmail.com>
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

#include "rdmctmzt_common.h"

#if LOGO_LED_ENABLE

// Logo LED animation state
static uint16_t logo_animation_timer = 0;
static uint8_t logo_animation_step = 0;

// Logo LED effect functions
void Logo_Led_Set_Color(uint8_t r, uint8_t g, uint8_t b) {
    for (uint8_t i = 0; i < LOGO_LED_COUNT; i++) {
        rgb_matrix_set_color(LED_LOGO_INDEX + i, r, g, b);
    }
}

void Logo_Led_Effect_Solid(void) {
    if (!Keyboard_Info.Logo_On_Off) {
        Logo_Led_Set_Color(0, 0, 0);
        return;
    }
    
    HSV hsv = {Keyboard_Info.Logo_Hue, Keyboard_Info.Logo_Saturation, Keyboard_Info.Logo_Brightness};
    RGB rgb = hsv_to_rgb(hsv);
    Logo_Led_Set_Color(rgb.r, rgb.g, rgb.b);
}

void Logo_Led_Effect_Breathe(void) {
    if (!Keyboard_Info.Logo_On_Off) {
        Logo_Led_Set_Color(0, 0, 0);
        return;
    }
    
    // Breathing effect - varies brightness
    uint8_t speed_multiplier = (Keyboard_Info.Logo_Speed + 1) * 10;
    uint8_t breath_val = Led_Wave_Pwm_Tab[(logo_animation_step * speed_multiplier / 10) % 128];
    uint8_t scaled_val = (breath_val * Keyboard_Info.Logo_Brightness) / 255;
    
    HSV hsv = {Keyboard_Info.Logo_Hue, Keyboard_Info.Logo_Saturation, scaled_val};
    RGB rgb = hsv_to_rgb(hsv);
    Logo_Led_Set_Color(rgb.r, rgb.g, rgb.b);
}

void Logo_Led_Effect_Breathe_RGB(void) {
    if (!Keyboard_Info.Logo_On_Off) {
        Logo_Led_Set_Color(0, 0, 0);
        return;
    }
    
    // RGB breathing - cycles through hues while breathing
    uint8_t speed_multiplier = (Keyboard_Info.Logo_Speed + 1) * 10;
    uint8_t breath_val = Led_Wave_Pwm_Tab[(logo_animation_step * speed_multiplier / 10) % 128];
    uint8_t scaled_val = (breath_val * Keyboard_Info.Logo_Brightness) / 255;
    uint8_t hue = (logo_animation_step * speed_multiplier / 5) % 256;
    
    HSV hsv = {hue, Keyboard_Info.Logo_Saturation, scaled_val};
    RGB rgb = hsv_to_rgb(hsv);
    Logo_Led_Set_Color(rgb.r, rgb.g, rgb.b);
}

void Logo_Led_Effect_Spectrum(void) {
    if (!Keyboard_Info.Logo_On_Off) {
        Logo_Led_Set_Color(0, 0, 0);
        return;
    }
    
    // Spectrum/rainbow cycle - smoothly cycles through all hues
    uint8_t speed_multiplier = (Keyboard_Info.Logo_Speed + 1) * 5;
    uint8_t hue = (logo_animation_step * speed_multiplier / 5) % 256;
    
    HSV hsv = {hue, Keyboard_Info.Logo_Saturation, Keyboard_Info.Logo_Brightness};
    RGB rgb = hsv_to_rgb(hsv);
    Logo_Led_Set_Color(rgb.r, rgb.g, rgb.b);
}

void Logo_Led_Effect_Wave(void) {
    if (!Keyboard_Info.Logo_On_Off) {
        Logo_Led_Set_Color(0, 0, 0);
        return;
    }
    
    // Wave effect - each LED slightly offset in brightness
    uint8_t speed_multiplier = (Keyboard_Info.Logo_Speed + 1) * 10;
    
    for (uint8_t i = 0; i < LOGO_LED_COUNT; i++) {
        uint8_t offset = (logo_animation_step * speed_multiplier / 10 + i * 25) % 128;
        uint8_t wave_val = Led_Wave_Pwm_Tab[offset];
        uint8_t scaled_val = (wave_val * Keyboard_Info.Logo_Brightness) / 255;
        
        HSV hsv = {Keyboard_Info.Logo_Hue, Keyboard_Info.Logo_Saturation, scaled_val};
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(LED_LOGO_INDEX + i, rgb.r, rgb.g, rgb.b);
    }
}

void Logo_Led_Effect_Wave_RGB(void) {
    if (!Keyboard_Info.Logo_On_Off) {
        Logo_Led_Set_Color(0, 0, 0);
        return;
    }
    
    // Wave RGB - wave effect with cycling hues
    uint8_t speed_multiplier = (Keyboard_Info.Logo_Speed + 1) * 10;
    
    for (uint8_t i = 0; i < LOGO_LED_COUNT; i++) {
        uint8_t offset = (logo_animation_step * speed_multiplier / 10 + i * 25) % 128;
        uint8_t wave_val = Led_Wave_Pwm_Tab[offset];
        uint8_t scaled_val = (wave_val * Keyboard_Info.Logo_Brightness) / 255;
        uint8_t hue = (logo_animation_step * speed_multiplier / 10 + i * 50) % 256;
        
        HSV hsv = {hue, Keyboard_Info.Logo_Saturation, scaled_val};
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(LED_LOGO_INDEX + i, rgb.r, rgb.g, rgb.b);
    }
}

// Main Logo LED update function - call from rgb_matrix_indicators_advanced_user
void Logo_Led_Update(void) {
    // Update animation step (called from rgb_matrix_indicators)
    if (timer_elapsed(logo_animation_timer) > 20) { // Update every 20ms
        logo_animation_timer = timer_read();
        logo_animation_step++;
        if (logo_animation_step > 255) {
            logo_animation_step = 0;
        }
    }
    
    // Apply the current effect
    switch (Keyboard_Info.Logo_Mode) {
        case LOGO_MODE_NONE:
            Logo_Led_Set_Color(0, 0, 0);
            break;
        case LOGO_MODE_WAVE:
        case LOGO_MODE_WAVE1:
        case LOGO_MODE_WAVE2:
        case LOGO_MODE_FIXED_WAVE:
            Logo_Led_Effect_Wave();
            break;
        case LOGO_MODE_WAVE_RGB:
            Logo_Led_Effect_Wave_RGB();
            break;
        case LOGO_MODE_SPECTRUM:
            Logo_Led_Effect_Spectrum();
            break;
        case LOGO_MODE_BREATHE:
            Logo_Led_Effect_Breathe();
            break;
        case LOGO_MODE_BREATHE_RGB:
            Logo_Led_Effect_Breathe_RGB();
            break;
        case LOGO_MODE_LIGHT:
        default:
            Logo_Led_Effect_Solid();
            break;
    }
}

// Process Logo LED keycodes - call from process_record_user
// Returns true if keycode was handled (should return false from process_record_user)
bool process_logo_led_keycodes(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOGO_TOG:
            if (!record->event.pressed) {
                Keyboard_Info.Logo_On_Off = !Keyboard_Info.Logo_On_Off;
                Save_Flash_Set();
            }
            return true;
        case LOGO_MOD:
            if (!record->event.pressed) {
                Keyboard_Info.Logo_Mode++;
                if (Keyboard_Info.Logo_Mode > 9) {
                    Keyboard_Info.Logo_Mode = 0;
                }
                Save_Flash_Set();
            }
            return true;
        case LOGO_RMOD:
            if (!record->event.pressed) {
                if (Keyboard_Info.Logo_Mode == 0) {
                    Keyboard_Info.Logo_Mode = 9;
                } else {
                    Keyboard_Info.Logo_Mode--;
                }
                Save_Flash_Set();
            }
            return true;
        case LOGO_HUI:
            if (!record->event.pressed) {
                Keyboard_Info.Logo_Hue += 8;
                Save_Flash_Set();
            }
            return true;
        case LOGO_HUD:
            if (!record->event.pressed) {
                Keyboard_Info.Logo_Hue -= 8;
                Save_Flash_Set();
            }
            return true;
        case LOGO_SAI:
            if (!record->event.pressed) {
                if (Keyboard_Info.Logo_Saturation <= 247) {
                    Keyboard_Info.Logo_Saturation += 8;
                } else {
                    Keyboard_Info.Logo_Saturation = 255;
                }
                Save_Flash_Set();
            }
            return true;
        case LOGO_SAD:
            if (!record->event.pressed) {
                if (Keyboard_Info.Logo_Saturation >= 8) {
                    Keyboard_Info.Logo_Saturation -= 8;
                } else {
                    Keyboard_Info.Logo_Saturation = 0;
                }
                Save_Flash_Set();
            }
            return true;
        case LOGO_VAI:
            if (!record->event.pressed) {
                if (Keyboard_Info.Logo_Brightness <= 247) {
                    Keyboard_Info.Logo_Brightness += 8;
                } else {
                    Keyboard_Info.Logo_Brightness = 255;
                }
                Save_Flash_Set();
            }
            return true;
        case LOGO_VAD:
            if (!record->event.pressed) {
                if (Keyboard_Info.Logo_Brightness >= 8) {
                    Keyboard_Info.Logo_Brightness -= 8;
                } else {
                    Keyboard_Info.Logo_Brightness = 0;
                }
                Save_Flash_Set();
            }
            return true;
        case LOGO_SPI:
            if (!record->event.pressed) {
                if (Keyboard_Info.Logo_Speed < 4) {
                    Keyboard_Info.Logo_Speed++;
                }
                Save_Flash_Set();
            }
            return true;
        case LOGO_SPD:
            if (!record->event.pressed) {
                if (Keyboard_Info.Logo_Speed > 0) {
                    Keyboard_Info.Logo_Speed--;
                }
                Save_Flash_Set();
            }
            return true;
        default:
            return false; // Not a logo LED keycode
    }
}

// VIA custom handler for Logo LED settings (channel 2 - rgblight channel)
void via_logo_led_command(uint8_t *data, uint8_t length) {
    // data[0] is the command ID
    // data[1] is the channel ID (2 = rgblight for logo LED)
    // data[2] is the value ID
    // data[3+] is the value data
    
    uint8_t *command_id = &(data[0]);
    uint8_t *channel_id = &(data[1]);
    uint8_t *value_id   = &(data[2]);
    uint8_t *value_data = &(data[3]);
    
    // Only handle channel 2 (rgblight/logo LED)
    if (*channel_id != 2) {
        return;
    }
    
    switch (*command_id) {
        case 0x07: // id_custom_set_value
            switch (*value_id) {
                case 1: // brightness
                    Keyboard_Info.Logo_Brightness = value_data[0];
                    Save_Flash_Set();
                    break;
                case 2: // effect
                    Keyboard_Info.Logo_Mode = value_data[0];
                    Keyboard_Info.Logo_On_Off = (value_data[0] > 0) ? 1 : 0;
                    Save_Flash_Set();
                    break;
                case 3: // effect speed
                    Keyboard_Info.Logo_Speed = value_data[0];
                    Save_Flash_Set();
                    break;
                case 4: // color (HSV)
                    Keyboard_Info.Logo_Hue = value_data[0];
                    Keyboard_Info.Logo_Saturation = value_data[1];
                    Save_Flash_Set();
                    break;
            }
            break;
        case 0x08: // id_custom_get_value
            switch (*value_id) {
                case 1: // brightness
                    value_data[0] = Keyboard_Info.Logo_Brightness;
                    break;
                case 2: // effect
                    value_data[0] = Keyboard_Info.Logo_On_Off ? Keyboard_Info.Logo_Mode : 0;
                    break;
                case 3: // effect speed
                    value_data[0] = Keyboard_Info.Logo_Speed;
                    break;
                case 4: // color (HSV)
                    value_data[0] = Keyboard_Info.Logo_Hue;
                    value_data[1] = Keyboard_Info.Logo_Saturation;
                    break;
            }
            break;
        case 0x09: // id_custom_save
            Save_Flash_Set();
            break;
    }
}

#endif // LOGO_LED_ENABLE
