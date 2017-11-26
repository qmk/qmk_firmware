#ifndef KEYMAP_RUSSIAN_H
#define KEYMAP_RUSSIAN_H

#include "keymap.h"

// Normal Chracters      // reg   SHIFT
#define RU_A     KC_F    // а and А
#define RU_BE    KC_COMM // б and Б
#define RU_VE    KC_D    // в and В
#define RU_GHE   KC_U    // г and Г
#define RU_DE    KC_L    // д and Д
#define RU_IE    KC_T    // е and Е
#define RU_IO    KC_GRV  // ё and Ё
#define RU_ZHE   KC_SCLN // ж and Ж
#define RU_ZE    KC_P    // з and З
#define RU_I     KC_B    // и and И
#define RU_SRT_I KC_Q    // й and Й
#define RU_KA    KC_R    // к and К
#define RU_EL    KC_K    // л and Л
#define RU_EM    KC_V    // м and М
#define RU_EN    KC_Y    // н and Н
#define RU_O     KC_J    // о and О
#define RU_PE    KC_G    // п and П
#define RU_ER    KC_H    // р and Р
#define RU_ES    KC_C    // с and С
#define RU_TE    KC_N    // т and Т
#define RU_U     KC_E    // у and У
#define RU_EF    KC_A    // ф and Ф
#define RU_HA    KC_LBRC // х and Х
#define RU_TSE   KC_W    // ц and Ц
#define RU_CHE   KC_X    // ч and Ч
#define RU_SHA   KC_I    // ш and Ш
#define RU_SHCHA KC_O    // щ and Щ
#define RU_HSIGN KC_RBRC // ъ and Ъ
#define RU_YERU  KC_S    // ы and Ы
#define RU_SSIGN KC_M    // ь and Ь
#define RU_E     KC_QUOT // э and Э
#define RU_YU    KC_DOT  // ю and Ю
#define RU_YA    KC_Z    // я and Я

#define RU_1     KC_1    // 1 and !
#define RU_2     KC_2    // 2 and "
#define RU_3     KC_3    // 3 and №
#define RU_4     KC_4    // 4 and ;
#define RU_5     KC_5    // 5 and %
#define RU_6     KC_6    // 6 and :
#define RU_7     KC_7    // 7 and ?
#define RU_8     KC_8    // 8 and *
#define RU_9     KC_9    // 9 and (
#define RU_0     KC_0    // 0 and )

#define RU_MINS  KC_MINS // - and _
#define RU_EQL   KC_EQL  // = and +
#define RU_BSLS  KC_BSLS // \ and /
#define RU_DOT   KC_SLSH // . and ,

// Shifted Chracters
#define RU_EXLM LSFT(RU_1) // !
#define RU_DQUT LSFT(RU_2) // "
#define RU_NMRO LSFT(RU_3) // №
#define RU_SCLN LSFT(RU_4) // ;
#define RU_PERC LSFT(RU_5) // %
#define RU_COLN LSFT(RU_6) // :
#define RU_QUES LSFT(RU_7) // ?
#define RU_ASTR LSFT(RU_8) // *
#define RU_LPRN LSFT(RU_9) // (
#define RU_RPRN LSFT(RU_0) // )

#define RU_UNDR LSFT(RU_MINS) // _
#define RU_PLUS LSFT(RU_EQL)  // +
#define RU_SLSH LSFT(RU_BSLS) // /
#define RU_COMM LSFT(RU_DOT)  // ,

// Alt Gr-ed characters
#define RU_RUBL RALT(RU_8) // ₽

#endif
