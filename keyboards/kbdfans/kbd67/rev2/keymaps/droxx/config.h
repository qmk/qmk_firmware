/* 
Copyright 2022 Alex K

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

/* USB Device descriptor parameter */
#undef VENDOR_ID
#undef MANUFACTURER
#undef PRODUCT

#define VENDOR_ID       0xAF88
#define PRODUCT_ID      0x6067
#define DEVICE_VER      0x0002
#define MANUFACTURER    Droxx-FurFuzz
#define PRODUCT         Carbon v2 4rk

/* force N key rollover even on startup regardless of EEPROM setting */
#define FORCE_NKRO

/* USB polling rate */
#define USB_POLLING_INTERVAL_MS 1

/* turn off RGB when computer sleeps. already on config */
#ifdef RGB_DI_PIN
#define RGBLIGHT_SLEEP
#endif
