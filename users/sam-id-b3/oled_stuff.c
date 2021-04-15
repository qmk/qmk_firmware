#include "sam-id-b3.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef OLED_DRIVER_ENABLE

#ifdef WPM_ENABLE
	#include "wpm_oled.c"
#endif

extern uint8_t is_master;

/* KEYLOGGER BEGIN ---------------
											*/
#ifndef KEYLOGGER_LENGTH
	#define KEYLOGGER_LENGTH ((int)(OLED_DISPLAY_HEIGHT / OLED_FONT_WIDTH))
#endif

//keylogger
static char     keylog_str[KEYLOGGER_LENGTH + 1] = {"\n"};

// clang-format off
static const char PROGMEM code_to_name[0xFF] = {
//   0    1    2    3    4    5    6    7    8    9    A    B    c    D    E    F
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',  // 0x
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2',  // 1x
    '3', '4', '5', '6', '7', '8', '9', '0',  20,  19,  27,  26,  22, '-', '=', '[',  // 2x
    ']','\\', '#', ';','\'', '`', ',', '.', '/', 128, ' ', ' ', ' ', ' ', ' ', ' ',  // 3x
    ' ', ' ', ' ', ' ', ' ', ' ', 'P', 'S', ' ', ' ', ' ', ' ',  16, ' ', ' ', ' ',  // 4x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 5x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 6x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 7x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 8x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 9x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ax
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Bx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Cx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Dx
    'C', 'S', 'A', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ex
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '        // Fx
};
// clang-format on
void add_keylog(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) || (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) {
        keycode = keycode & 0xFF;
    } else if (keycode > 0xFF) {
        keycode = 0;
    }

    for (uint8_t i = (KEYLOGGER_LENGTH - 1); i > 0; --i) {
        keylog_str[i] = keylog_str[i - 1];
    }

    if (keycode < (sizeof(code_to_name) / sizeof(char))) {
        keylog_str[0] = pgm_read_byte(&code_to_name[keycode]);
    }
}

bool process_record_user_oled(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        add_keylog(keycode);
    }
    return true;
}

void render_keylogger_status(void) {
    oled_write_P(PSTR(OLED_RENDER_KEYLOGGER), false);
	
    oled_write(keylog_str, false);
}

// KEYLOGGER END
//
//


// STATUS BEGIN
//
//

void render_mod_status(uint8_t modifiers) {
    oled_write_P(PSTR(OLED_RENDER_MODS_NAME), false);
	
	if (modifiers & MOD_MASK_SHIFT){oled_write_P(shift_key, false);}
	if (modifiers & MOD_MASK_CTRL){oled_write_P(ctrl_key, false);}
	if (modifiers & MOD_MASK_ALT){oled_write_P(alt_key, false);}
	if (modifiers & MOD_MASK_GUI){oled_write_P(win_key, false);}
	oled_advance_page(true);
}

static void render_status(void) {
    // QMK Logo and version information
    oled_write_P(logo, false);
	oled_advance_page(true);
	oled_advance_page(true);
    //oled_write_P(PSTR("         Coolio\n\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR(OLED_RENDER_LAYOUT_NAME), false);
    switch (get_highest_layer(layer_state)) {
        case _COLEMAK:
            oled_write_ln_P(PSTR(OLED_RENDER_LAYOUT_COLEMAK), false);
            break;
        case _SYMNUM:
            oled_write_ln_P(PSTR(OLED_RENDER_LAYOUT_SYMNUM), false);
            break;
        case _SHORTCUT:
            oled_write_ln_P(PSTR(OLED_RENDER_LAYOUT_SHORTCUT), false);
            break;
		case _GAMING:
            oled_write_ln_P(PSTR(OLED_RENDER_LAYOUT_GAMING), false);
            break;
		case _NAVIGATION:
            oled_write_ln_P(PSTR(OLED_RENDER_LAYOUT_NAVIGATION), false);
            break;
		#ifdef DICE_ROLLER_ENABLE
		case _RPG:
            oled_write_ln_P(PSTR(OLED_RENDER_LAYOUT_RPG), false);
            break;
		#endif
		case _QWERTY:
            oled_write_ln_P(PSTR(OLED_RENDER_LAYOUT_QWERTY), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
	oled_write_P(PSTR(OLED_RENDER_LOCK_NAME), false);
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
	oled_advance_page(true);
	render_mod_status(get_mods() | get_oneshot_mods());
	render_keylogger_status();
}

//
//
// STATUS END

// DICE ROLLER BEGIN
//
//
/*
#ifdef DICE_ROLLER_ENABLE
char* roll_dice(int num){
	// roll d20
	static char roll_str[14];
	uint8_t roll20 = (rand() % num) + 1;
	sprintf(roll_str, "Roll d%d: %d", num, roll20);
	return roll_str;
}

void oled_dice(int num){
	if(!is_keyboard_master()){
		oled_set_cursor(0,4);
		oled_write("-=: ", false);
		oled_write(roll_dice(num), false);
		oled_write(" :=-", false);
	}
}
#endif
*/
//
//
// DICE ROLLER END

void oled_task_user(void) {
    if (is_keyboard_master()) {
		render_status();
    } else {
		
		#ifdef WPM_ENABLE
		render_wpm_graph();
		#endif
        //render_custom_image();
		//oled_scroll_left();
    }
}
#endif