/*
Copyright 2022 GEIST <@geigeigeist>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// Most configuration will be found in info.json

// ┌─────────────────────────────────────────────────┐
// │ g e n e r a l                                   │
// └─────────────────────────────────────────────────┘

#define MASTER_LEFT
#define NO_ACTION_ONESHOT

// ┌─────────────────────────────────────────────────┐
// │ o l e d s                                       │
// └─────────────────────────────────────────────────┘

#if defined(OLED_ENABLE)
#define OLED_DISPLAY_128X64
#define OLED_FONT_H  "./lib/glcdfont.c"
#endif //OLED_ENABLE

// ┌─────────────────────────────────────────────────┐
// │ a u d i o                                       │
// └─────────────────────────────────────────────────┘

#define AUDIO_PIN GP9
#define AUDIO_DAC_SAMPLE_MAX 4095U
#define AUDIO_VOICE_DEFAULT butts_fader

#define AUDIO_PWM_DRIVER PWMD4
#define AUDIO_PWM_CHANNEL RP2040_PWM_CHANNEL_B
#define AUDIO_STATE_TIMER GPTD4

#if defined(AUDIO_ENABLE)
#define KLOR_SOUND W__NOTE(_DS0), W__NOTE(_DS1), H__NOTE(_DS2), H__NOTE(_DS3), Q__NOTE(_DS4), Q__NOTE(_DS5), E__NOTE(_DS6), E__NOTE(_DS7), S__NOTE(_DS8), Q__NOTE(_GS0)
#define BYE_SOUND H__NOTE(_DS4), H__NOTE(_DS3), W__NOTE(_DS1)

#define STARTUP_SONG SONG(KLOR_SOUND)
#define GOODBYE_SONG SONG(BYE_SOUND)
#define DEFAULT_LAYER_SONGS  { SONG(QWERTY_SOUND), SONG(COLEMAK_SOUND) }
#endif // AUDIO_ENABLE

// ┌─────────────────────────────────────────────────┐
// │ h a p t i c   f e e d b a c k                   │
// └─────────────────────────────────────────────────┘

#if defined(HAPTIC_ENABLE) && defined(HAPTIC_DRV2605L)
#define DRV2605L_FB_ERM_LRA 1
#define DRV2605L_FB_BRAKEFACTOR 3 // For 1x:0, 2x:1, 3x:2, 4x:3, 6x:4, 8x:5, 16x:6, Disable Braking:7
#define DRV2605L_FB_LOOPGAIN 1 // For  Low:0, Medium:1, High:2, Very High:3
#define DRV2605L_RATED_VOLTAGE 2
#define DRV2605L_V_PEAK 2.8
#define DRV2605L_V_RMS 2.0
#define DRV2605L_F_LRA 150 // resonance freq
#define DRV2605L_GREETING DRV2605L_EFFECT_750_MS_ALERT_100
#define DRV2605L_DEFAULT_MODE DRV2605L_EFFECT_STRONG_CLICK_30
#endif // HAPTIC_ENABLE && HAPTIC_DRV2605L

// ┌─────────────────────────────────────────────────┐
// │ t r a c k b a l l                               │
// └─────────────────────────────────────────────────┘

#if defined(POINTING_DEVICE_ENABLE)
#define PAW3204_SCLK_PIN D0
#define PAW3204_SDIO_PIN D1
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_DELAY 300
#endif //0POINTING_DEVICE_ENABLE
