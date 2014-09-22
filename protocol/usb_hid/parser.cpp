#include "parser.h"
#include "usb_hid.h"

#include "debug.h"


report_keyboard_t usb_hid_keyboard_report;
uint16_t usb_hid_time_stamp;


void KBDReportParser::Parse(HID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf)
{
    ::memcpy(&usb_hid_keyboard_report, buf, sizeof(report_keyboard_t));
    usb_hid_time_stamp = millis();

    debug("KBDReport: ");
    debug_hex(usb_hid_keyboard_report.mods);
    debug(" --");
    for (uint8_t i = 0; i < 6; i++) {
        debug(" ");
        debug_hex(usb_hid_keyboard_report.keys[i]);
    }
    debug("\r\n");
}
