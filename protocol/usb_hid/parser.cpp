#include "parser.h"
#include "leonardo_led.h"
#include "debug.h"

void KBDReportParser::Parse(HID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf)
{
    LED_TX_TOGGLE;
    debug("KBDReport: ");
    for (uint8_t i = 0; i < len; i++) {
        debug_hex(buf[i]);
        debug(" ");
    }
    debug("\r\n");
}
