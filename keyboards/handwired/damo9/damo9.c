#include "quantum.h"
#include "damo9.h"
//#include "ssd1306.h"

// void display_text(const char *text) {
//     oled_clear();
//     oled_set_cursor(0,1);
//     oled_write_ln_P(text, false);
// }    

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_90;
}

// bool oled_task_user(void) {
//     display_text("Hello from damo9!");
//     return false;

//     // if (is_keyboard_master()) {
//     //     render_status();
//     // } else {
//     //     render_logo();
//     // }
//     // return false;
// }

void render_status(void) {
    // Add the following to init_quantum:
    // if (!is_keyboard_master()) {
    //     oled_init(OLED_ROTATION_180);
    // }

    // Clear the display
    oled_clear();
    
    // Add custom text
    oled_write_P(PSTR("Layer: "), false);
    
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("Media\n"), false);
            break;
        case 1:
            oled_write_P(PSTR("Lolz1\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("Lolz2\n"), false);
            break;
        default:
            oled_write_P(PSTR("Unknown\n"), false);
    }        
}

void render_logo(void) {

    oled_clear();

    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}
