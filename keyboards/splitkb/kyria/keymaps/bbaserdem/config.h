/*
Copyright 2019 Batuhan Başerdem <baserdem.batuhan@gmail.com> @bbaserdem
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

// Kyria specific
#ifdef KEYBOARD_kyria_rev1
    // Split definition; use the following to flash;
    //  pro-micro:      avrdude-split-left/right
    //  elite-c:        dfu-split-left/right
    #define ENCODER_DIRECTION_FLIP
    #define EE_HANDS

    #ifdef OLED_DRIVER_ENABLE
    #define OLED_DISPLAY_128X64
    #endif

    #ifdef RGBLIGHT_ENABLE
        #ifdef RGBLIGHT_LEFT_BEG
        #undef RGBLIGHT_LEFT_BEG
        #endif
        #define RGBLIGHT_LEFT_BEG 0

        #ifdef RGBLIGHT_LEFT_NUM
        #undef RGBLIGHT_LEFT_NUM
        #endif
        #define RGBLIGHT_LEFT_NUM 10

        #ifdef RGBLIGHT_RIGHT_BEG
        #undef RGBLIGHT_RIGHT_BEG
        #endif
        #define RGBLIGHT_RIGHT_BEG 10

        #ifdef RGBLIGHT_RIGHT_NUM
        #undef RGBLIGHT_RIGHT_NUM
        #endif
        #define RGBLIGHT_RIGHT_NUM 10
    #endif

    // If you are using an Elite C rev3 on the slave side, uncomment the lines below:
    // #define SPLIT_USB_DETECT
    // #define NO_USB_STARTUP_CHECK
#endif
