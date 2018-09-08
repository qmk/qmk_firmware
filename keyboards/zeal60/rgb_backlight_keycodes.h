
#ifndef RGB_BACKLIGHT_KEYCODES_H
#define RGB_BACKLIGHT_KEYCODES_H

// This is hardcoded at 0x5F00 so it's well after keycode value SAFE_RANGE
enum backlight_keycodes {
	BR_INC = 0x5F00,	// backlight brightness increase
	BR_DEC, 			// backlight brightness decrease
	EF_INC, 			// backlight effect increase
	EF_DEC,  			// backlight effect decrease
	ES_INC,
	ES_DEC,
	H1_INC,
	H1_DEC,
	S1_INC,
	S1_DEC,
	H2_INC,
	H2_DEC,
	S2_INC,
	S2_DEC
};

#endif // RGB_BACKLIGHT_KEYCODES_H
