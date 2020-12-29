#pragma once

#define PRODUCT      Adelais
#define DESCRIPTION  Team.Mechlovin Adelais

#define MATRIX_ROW_PINS { B1, A0, C13, A1, A2}
#define MATRIX_COL_PINS { A10, A9, A8, B15, B14, B13, B12, B11, B10, B8, B4, B5, B3, C14, A15 }
#define UNUSED_PINS

#define BACKLIGHT_PIN B0
#define BACKLIGHT_BREATHING
#define BACKLIGHT_PWM_DRIVER PWMD3
#define BACKLIGHT_PWM_CHANNEL 3

#define RGB_DI_PIN A7
#define RGBLED_NUM 23
#define RGBLIGHT_LIMIT_VAL 255
#define RGBLIGHT_ANIMATIONS
