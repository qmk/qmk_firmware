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
            print("Up:	Bell On\n");
            print("Down:	Bell Off\n");
            print("Left:	Click On\n");
            print("Right:	Click Off\n");
            print("PgUp:	LED all On\n");
            print("PgDown:	LED all On\n");
            print("Insert:	Layout\n");
            print("Delete:	Reset\n");
            return false;
        case KC_DEL:
            print("Reset\n");
            serial_send(0x01);
            break;
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
        case KC_PGUP:
            print("LED all on\n");
            serial_send(0x0E);
            serial_send(0xFF);
            break;
        case KC_PGDOWN:
            print("LED all off\n");
            serial_send(0x0E);
            serial_send(0x00);
            break;
        case KC_INSERT:
            print("layout\n");
            serial_send(0x0F);
            break;
        default:
            return false;
    }
    return true;
}
