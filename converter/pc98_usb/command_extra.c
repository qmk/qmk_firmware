#include "stdbool.h"
#include "stdint.h"
#include "keycode.h"
#include "serial.h"
#include "print.h"
#include "command.h"

bool command_extra(uint8_t code)
{
    switch (code) {
        case KC_H:
        case KC_SLASH: /* ? */
            print("\n\n----- Sun converter Help -----\n");
            print("UP:	Bell On\n");
            print("DOWN:	Bell Off\n");
            print("LEFT:	Click On\n");
            print("RIGHT:	Click Off\n");
            return false;
        case KC_UP:
            print("Bell On\n");
            serial_send(0x02);
            break;
        case KC_DOWN:
            print("Bell Off\n");
            serial_send(0x03);
            break;
        case KC_LEFT:
            print("Click On\n");
            serial_send(0x0A);
            break;
        case KC_RIGHT:
            print("Click Off\n");
            serial_send(0x0B);
            break;
        case KC_NUMLOCK:
            print("layout\n");
            serial_send(0x0F);
            break;
        default:
            return false;
    }
    return true;
}
