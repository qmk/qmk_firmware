#include "parser.h"
#include "usb_hid.h"

#include "debug.h"


report_keyboard_t usb_hid_keyboard_report;
uint16_t usb_hid_time_stamp;


void KBDReportParser::Parse(HID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf)
{
    bool is_error = false;
    report_keyboard_t *report = (report_keyboard_t *)buf;

    dprintf("keyboard input:  %02X %02X", report->mods, report->reserved);
    for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
        if (IS_ERROR(report->keys[i])) {
            is_error = true;
        }
        dprintf(" %02X", report->keys[i]);
    }
    dprint("\r\n");

    // ignore error and not send report to computer
    if (is_error) {
        dprint("Error usage! \r\n");
        return;
    }

    ::memcpy(&usb_hid_keyboard_report, buf, sizeof(report_keyboard_t));
    usb_hid_time_stamp = millis();
}
