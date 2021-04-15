#include "id-b3.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef OLED_DRIVER_ENABLE

#ifdef WPM_ENABLE
	//#include "wpm_oled.c"
	#include "wpm_cat.c"
	char wpm_str[10];
#endif

extern uint8_t is_master;

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
		//case _WARHAMMER:
          //  oled_write_ln_P(PSTR(OLED_RENDER_LAYOUT_WARHAMMER), false);
            //break;
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
	//render_keylogger_status();
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
		//render_wpm_graph();
		render_anim();
        oled_set_cursor(0,6);
        sprintf(wpm_str, "       WPM: %03d", get_current_wpm());
        oled_write(wpm_str, false);
		
		#endif
        //render_custom_image();
		//oled_scroll_left();
    }
}
#endif