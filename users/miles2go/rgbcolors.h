#pragma once


// Babble modes
#define COLOR_MS 		0x27, 0x00, 0x88 // light blue
#define COLOR_MAC 		0x20, 0x20, 0x20 // grey
#define COLOR_LINUX 	0x00, 0x00, 0x00 // black
#define COLOR_EMACS 	0x00, 0x00, 0x00
#define COLOR_VI 		0x00, 0x60, 0x00
#define COLOR_READMUX 	0x50, 0x13, 0x13 // green screen
#define COLOR_CHROMEOS 	0x82, 0xa4, 0xd0 // google yellows
#define COLOR_KITTY 	0x40, 0x20, 0x90 // rosey

// layers
#define COLOR_QWERTY 	0x00, 0x40, 0x00  //light green
#define COLOR_CDH 		0x00, 0x00, 0x50 //blue
#define COLOR_SYM 		0x40, 0x00, 0x00 // cyan
#define COLOR_MOV 		0x60, 0x00, 0x60  //red
#define COLOR_DMOV 		0x60, 0x60, 0x00  //orange
#define COLOR_NUM 		0xFF, 0x00, 0xFF //purply

/// I'm sure there's a clever C preprocessor way to do this
// Instead I just pipe through sed
//  sed -e 's/\(0x..\),\([^\,]*\),.*\(0x..\)/\2,\1,\3/' -e 's/COLOR_/GRB_/' users/miles2go/rgbcolors.h  

#define RGBLIGHT_OFF 0x00,0x00,0x00

// Babble modes
#define GRB_MS 		0x00,0x27,0x88 // light blue
#define GRB_MAC 		0x20,0x20,0x20 // grey
#define GRB_LINUX 	0x00,0x00,0x00 // black
#define GRB_EMACS 	0x00,0x00,0x00
#define GRB_VI 		0x60,0x00,0x00
#define GRB_READMUX 	0x13,0x50,0x13 // green screen
#define GRB_CHROMEOS 	0xa4,0x82,0xd0 // google yellows
#define GRB_KITTY 	0x20,0x40,0x90 // rosey

// layers
#define GRB_QWERTY 	0x40,0x00,0x00  //light green
#define GRB_CDH 		0x00,0x00,0x50 //blue
#define GRB_SYM 		0x00,0x40,0x00 // cyan
#define GRB_MOV 		0x00,0x60,0x60  //red
#define GRB_DMOV 		0x60,0x60,0x00  //orange
#define GRB_NUM 		0x00,0xFF,0xFF //purply

/* These should be done in local keyboard config instead of centrally. 
 * The settings really aren't consistent between boards
*/ 
#ifdef LED_IS_GRB
#define RGBLIGHT_COLOR_MS  GRB_MS
#define RGBLIGHT_COLOR_MAC  GRB_MAC
#define RGBLIGHT_COLOR_LINUX GRB_LINUX
#define RGBLIGHT_COLOR_EMACS GRB_EMACS
#define RGBLIGHT_COLOR_VI GRB_VI
#define RGBLIGHT_COLOR_READMUX GRB_READMUX
#define RGBLIGHT_COLOR_CHROMEOS GRB_CHROMEOS
#define RGBLIGHT_COLOR_KITTY GRB_KITTY

#define RGBLIGHT_COLOR_LAYER_1 GRB_CDH
#define RGBLIGHT_COLOR_LAYER_0 GRB_QWERTY
#define RGBLIGHT_COLOR_LAYER_2 GRB_SYM
#define RGBLIGHT_COLOR_LAYER_3 GRB_MOV
#define RGBLIGHT_COLOR_LAYER_4 GRB_DMOV
#define RGBLIGHT_COLOR_LAYER_5 GRB_NUM

#else

#define RGBLIGHT_COLOR_MS COLOR_MS
#define RGBLIGHT_COLOR_MAC COLOR_MAC
#define RGBLIGHT_COLOR_LINUX COLOR_LINUX
#define RGBLIGHT_COLOR_EMACS COLOR_EMACS
#define RGBLIGHT_COLOR_VI COLOR_VI
#define RGBLIGHT_COLOR_READMUX COLOR_READMUX
#define RGBLIGHT_COLOR_CHROMEOS COLOR_CHROMEOS
#define RGBLIGHT_COLOR_KITTY COLOR_KITTY

#define RGBLIGHT_COLOR_LAYER_1 COLOR_CDH
#define RGBLIGHT_COLOR_LAYER_0 COLOR_QWERTY
#define RGBLIGHT_COLOR_LAYER_2 COLOR_SYM	
#define RGBLIGHT_COLOR_LAYER_3 COLOR_MOV
#define RGBLIGHT_COLOR_LAYER_4 COLOR_DMOV
#define RGBLIGHT_COLOR_LAYER_5 COLOR_NUM

#endif

