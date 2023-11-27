#include QMK_KEYBOARD_H

#define _MAIN 0
#define _FN 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	/* Keymap __MAIN: Default Layer  
	*  ,--------------------------------.
	*  | .------.   |-----|-----|-----| |  
	*  | |      |	|Play |VolUp| Fn  | |
	*  | | Pro  |	|-----|-----|-----| |
	*  | | Micro|   --------------------|
	*  | |      |	|-----|-----|-----| |
	*  | '------'	|Prev |VolD	|Next | |
	*  |  |||||| 	|-----|-----|-----| |
	*  '--------------------------------'
	*/
  [_MAIN] = LAYOUT( 
    KC_MPLY,  KC_VOLU,  MO(1),
    KC_MPRV,  KC_VOLD,  KC_MNXT
  ),
	/* Keymap __FN: Second Layer   
	*  ,--------------------------------.
	*  | .------.   |-----|-----|-----| |  
	*  | |      |	|Calc |PgUp |TRANS| |
	*  | | Pro  |	|-----|-----|-----| |
	*  | | Micro|   --------------------|
	*  | |      |	|-----|-----|-----| |
	*  | '------'	|MyPC | PgD	|QK_BOOT| |
	*  |  |||||| 	|-----|-----|-----| |
	*  '--------------------------------'
	*/
  
  [_FN] = LAYOUT( 
    KC_CALC, KC_PGUP, _______,
    KC_MYCM, KC_PGDN, QK_BOOT
  )
};
