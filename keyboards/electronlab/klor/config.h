/*
Copyright 2024 ElectronLab

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

#define I2C1_SCL_PIN GP3
#define I2C1_SDA_PIN GP2

#ifdef OLED_ENABLE
# define OLED_DISPLAY_128X64
# define SPLIT_OLED_ENABLE
# define OLED_FONT_H  "./lib/glcdfont.c"
#endif

#ifdef AUDIO_ENABLE
#define AUDIO_PWM_DRIVER PWMD4
#define AUDIO_PWM_CHANNEL RP2040_PWM_CHANNEL_B
#define AUDIO_STATE_TIMER GPTD4
#define AUDIO_PIN GP9
#define AUDIO_DAC_SAMPLE_MAX 4095U
#define AUDIO_VOICE_DEFAULT butts_fader
# define STARTUP_SONG SONG(W__NOTE(_DS0), W__NOTE(_DS1), H__NOTE(_DS2), H__NOTE(_DS3), Q__NOTE(_DS4), Q__NOTE(_DS5), E__NOTE(_DS6), E__NOTE(_DS7), S__NOTE(_DS8), Q__NOTE(_GS0))
# define GOODBYE_SONG SONG(H__NOTE(_DS4), H__NOTE(_DS3), W__NOTE(_DS1))
# define DEFAULT_LAYER_SONGS \
        { SONG(QWERTY_SOUND), SONG(COLEMAK_SOUND) }
#endif

#ifdef HAPTIC_ENABLE
#define DRV2605L_FB_ERM_LRA 1
#define DRV2605L_FB_BRAKEFACTOR 3
#define DRV2605L_FB_LOOPGAIN 1
#define DRV2605L_RATED_VOLTAGE 2
#define DRV2605L_V_PEAK 2.8
#define DRV2605L_V_RMS 2.0 
#define DRV2605L_F_LRA 150
#define DRV2605L_DRV_GREETING alert_750ms
#define DRV2605L_DEFAULT_MODE 4
#endif

#ifdef POINTING_DEVICE_ENABLE
# define POINTING_DEVICE_SCLK_PIN GP3
# define POINTING_DEVICE_SDIO_PIN GP2
# define POINTING_DEVICE_AUTO_MOUSE_ENABLE
# define AUTO_MOUSE_DELAY 300
#endif
