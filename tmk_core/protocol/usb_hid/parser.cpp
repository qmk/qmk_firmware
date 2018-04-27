#include "parser.h"
#include "usb_hid.h"

#include "debug.h"


void KBDReportParser::Parse(HID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf)
{
    ::memcpy(&report, buf, sizeof(report_keyboard_t));
    time_stamp = millis();

    dprintf("input %d:  %02X %02X", hid->GetAddress(), report.mods, report.reserved);
    for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
        dprintf(" %02X", report.keys[i]);
    }
    dprint("\r\n");
}
