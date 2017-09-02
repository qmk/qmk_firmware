#ifndef ZEAL_KEYCODE_H
#define ZEAL_KEYCODE_H

#define KC_EENULL 0xFFFF // TODO: move to enum quantum_keycodes

// Can't use SAFE_RANGE here, it might change if someone adds
// new values to enum quantum_keycodes.
// Need to keep checking 0x5F00 is still in the safe range.
enum zeal60_keycodes {
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
	S2_DEC,
	FN_MO13,
	FN_MO23
};

// Zeal60 specific "action functions"
// These are only valid IDs in action_function()
// Use FN_TT13, FN_TT23, etc. in keymaps
enum zeal60_action_functions {
	TRIPLE_TAP_1_3 = 0x31,
	TRIPLE_TAP_2_3 = 0x32
};

// Bitwise OR the above with 0x0F00 to use in F(x) macro
// This reserves the top 256 of the 4096 range of F(x) keycodes,
// leaving the rest for use in fn_actions[] or actions in EEPROM.
#define FN_TT13 F((0x0F00|TRIPLE_TAP_1_3))
#define FN_TT23 F((0x0F00|TRIPLE_TAP_2_3))

#define TG_NKRO             MAGIC_TOGGLE_NKRO

#endif // ZEAL_KEYCODE_H
