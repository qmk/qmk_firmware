#include "parser.h"
#include "usb_hid.h"

#include "debug.h"


void KBDReportParser::Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf)
{

    dprintf("input %d:  %02X %02X", hid->GetAddress(), report.mods, report.reserved);
    for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
        dprintf(" %02X", report.keys[i]);
    }
    dprint("\r\n");

    // Rollover error
    // Cherry: 0101010101010101
    // https://geekhack.org/index.php?topic=69169.msg2638223#msg2638223
    // Apple:  0000010101010101
    // https://geekhack.org/index.php?topic=69169.msg2760969#msg2760969
    if (buf[2] == 0x01) {
       dprintf("Rollover error: ignored\r\n");
       return;
    }

    ::memcpy(&report, buf, sizeof(report_keyboard_t));
    time_stamp = millis();
}
