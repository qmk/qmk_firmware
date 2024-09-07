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


// ┌─────────────────────────────────────────────────┐
// │ p i n   c o n f i g                             │
// └─────────────────────────────────────────────────┘ 

#define I2C1_SCL_PIN GP3
#define I2C1_SDA_PIN GP2

// ┌─────────────────────────────────────────────────┐
// │ k e y   m a t r i x                             │
// └─────────────────────────────────────────────────┘ 

//#define MATRIX_ROW_PINS { GP5, GP6, GP7, GP8 }
//#define MATRIX_COL_PINS { GP27, GP26, GP22, GP20, GP23, GP21 }
//#define DIODE_DIRECTION COL2ROW
#define MATRIX_ROWS 8
#define MATRIX_COLS 6
#define DEBOUNCE 5


// ┌─────────────────────────────────────────────────┐
// │ s p l i t   c o m m u n i c a t i o n           │
// └─────────────────────────────────────────────────┘ 

#define USE_SERIAL
#define SERIAL_USE_MULTI_TRANSACTION
#define SPLIT_USB_DETECT

//Half Duplex communication
#define SERIAL_USART_TX_PIN GP1     // USART TX pin

//Full Duplex communication
//#define SERIAL_USART_TX_PIN GP4     // USART TX pin
//#define SERIAL_USART_RX_PIN GP1     // USART RX pin
//#define SERIAL_USART_FULL_DUPLEX
//#define SERIAL_USART_PIN_SWAP

// ┌─────────────────────────────────────────────────┐
// │ e n c o d e r s                                 │
// └─────────────────────────────────────────────────┘ 

//#define ENCODERS_PAD_A       { GP28 }
//#define ENCODERS_PAD_B       { GP29 }
//#define ENCODERS_PAD_A_RIGHT { GP29 }
//#define ENCODERS_PAD_B_RIGHT { GP28 }
#define ENCODER_RESOLUTION { 2 }
#define ENCODER_RESOLUTIONS_RIGHT { 2 }


// ┌─────────────────────────────────────────────────┐
// │ o l e d s                                       │
// └─────────────────────────────────────────────────┘

#ifdef OLED_ENABLE
#    define OLED_DISPLAY_128X64
#    define SPLIT_OLED_ENABLE
#    define OLED_FONT_H  "./lib/glcdfont.c"
#endif


// ┌─────────────────────────────────────────────────┐
// │ r g b   l e d s                                 │
// └─────────────────────────────────────────────────┘ 

//#define WS2812_DI_PIN GP0
#define RGBLED_NUM 42
#define RGBLED_SPLIT { 21, 21 }
#define RGB_MATRIX_LED_COUNT RGBLED_NUM

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_BREATHING
#    define SPLIT_TRANSPORT_MIRROR true
#    define DRIVER_LED_TOTAL 42 // Number of LEDs
#    define RGB_MATRIX_SPLIT { 21, 21 }
#    define RGB_MATRIX_TIMEOUT 120000
#    define RGB_MATRIX_SLEEP
#    define RGB_MATRIX_LED_FLUSH_LIMIT 16
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255
#    define RGB_MATRIX_STARTUP_HUE 299
#    define RGB_MATRIX_DEFAULT_ON true
#    define RGB_MATRIX_DEFAULT_SAT 255
#    define RGB_MATRIX_DEFAULT_SPD 127
#    define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
#    define RGB_DISABLE_WHEN_USB_SUSPENDED
#    define RGB_MATRIX_KEYPRESSES
#endif 


// ┌─────────────────────────────────────────────────┐
// │ a u d i o                                       │
// └─────────────────────────────────────────────────┘

#define AUDIO_PWM_DRIVER PWMD4
#define AUDIO_PWM_CHANNEL RP2040_PWM_CHANNEL_B
#define AUDIO_STATE_TIMER GPTD4
#define AUDIO_PIN GP9
#define AUDIO_VOICES
#define AUDIO_DAC_SAMPLE_MAX 4095U
#define AUDIO_VOICE_DEFAULT butts_fader

#ifdef AUDIO_ENABLE     
#    define KLOR_SOUND W__NOTE(_DS0), W__NOTE(_DS1), H__NOTE(_DS2), H__NOTE(_DS3), Q__NOTE(_DS4), Q__NOTE(_DS5), E__NOTE(_DS6), E__NOTE(_DS7), S__NOTE(_DS8), Q__NOTE(_GS0)
#    define STARTUP_SONG SONG(KLOR_SOUND)
#    define BYE_SOUND H__NOTE(_DS4), H__NOTE(_DS3), W__NOTE(_DS1)
#    define GOODBYE_SONG SONG(BYE_SOUND)
#    define DEFAULT_LAYER_SONGS \
        { SONG(QWERTY_SOUND), SONG(COLEMAK_SOUND) }
#endif 


// ┌─────────────────────────────────────────────────┐
// │ h a p t i c   f e e d b a c k                   │
// └─────────────────────────────────────────────────┘ 

#ifdef HAPTIC_ENABLE
#    define FB_ERM_LRA 1
#    define FB_BRAKEFACTOR 3 // For 1x:0, 2x:1, 3x:2, 4x:3, 6x:4, 8x:5, 16x:6, Disable Braking:7 
#    define FB_LOOPGAIN 1 // For  Low:0, Medium:1, High:2, Very High:3 
#    define RATED_VOLTAGE 2
#    define V_PEAK 2.8
#    define V_RMS 2.0 
#    define F_LRA 150 // resonance freq 
#    define DRV_GREETING       alert_750ms
#    define SPLIT_HAPTIC_ENABLE
#    define DRV2605L_DEFAULT_MODE 4
#endif


// ┌─────────────────────────────────────────────────┐
// │ t r a c k b a l l                               │
// └─────────────────────────────────────────────────┘ 

#ifdef POINTING_DEVICE_ENABLE
#    define PAW3204_SCLK_PIN GP3
#    define PAW3204_SDIO_PIN GP2
#    define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#    define AUTO_MOUSE_DELAY 300
#endif
