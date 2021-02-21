/* Copyright 2021 4EBOOT 
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
#pragma once
#define VENDOR_ID 0x1234
#define PRODUCT_ID 0x1234
#define DEVICE_VER 0
#define MANUFACTURER 4EBOOT
#define PRODUCT Lotus58
#define MATRIX_ROWS 10
#define MATRIX_COLS 6
#define MATRIX_ROW_PINS { C6, D7, E6, B4, B5}
#define MATRIX_COL_PINS {F6, F7, B1, B3, B2, B6}
#define DIODE_DIRECTION COL2ROW
#define TAPPING_TERM 100
#define DEBOUNCE 5
#define RGB_DI_PIN D3
#define RGBLED_NUM 58
#define RGBLED_SPLIT {29, 29}
#define ENCODERS_PAD_A { F5 }
#define ENCODERS_PAD_B { F4 }
#define ENCODER_RESOLUTION 2
#define TAP_CODE_DELAY 10
#define USE_SERIAL
#define SERIAL_USE_MULTI_TRANSACTION
#define SOFT_SERIAL_PIN D2
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
