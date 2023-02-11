#include QMK_KEYBOARD_H
#include "uart.h"

bool sun_bell = false;
bool sun_click = false;


bool command_extra(uint8_t code)
{
    switch (code) {
        case KC_H:
        case KC_SLASH: /* ? */
            print("\n\n----- Sun converter Help -----\n");
            print("Home:        Toggle Bell\n");
            print("End:         Toggle Click\n");
            print("PgUp:        LED all On\n");
            print("PgDown:      LED all Off\n");
            print("Insert:      Layout\n");
            print("Delete:      Reset\n");
            return false;
        case KC_DEL:
            print("Reset\n");
            uart_write(0x01);
            break;
        case KC_HOME:
	    sun_bell = !sun_bell;
	    if (sun_bell) {
                print("Bell On\n");
	        uart_write(0x02);
	    } else {
	        print("Bell Off\n");
	        uart_write(0x03);
	    }
            break;
        case KC_END:
	    sun_click = !sun_click;
	    if (sun_click) {
	        print("Click On\n");
		uart_write(0x0A);
	    } else {
	        print("Click Off\n");
                uart_write(0x0B);
	    }
	    break;
        case KC_PGUP:
            print("LED all on\n");
            uart_write(0x0E);
            uart_write(0xFF);
            break;
        case KC_PGDN:
            print("LED all off\n");
            uart_write(0x0E);
            uart_write(0x00);
            break;
        case KC_INSERT:
            print("layout\n");
            uart_write(0x0F);
            break;
        default:
            xprintf("Unknown extra command: %02X\n", code);
            return false;
    }
    return true;
}
