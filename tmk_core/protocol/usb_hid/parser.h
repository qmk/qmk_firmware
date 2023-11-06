#pragma once

#include "hid.h"
#include "report.h"

class KBDReportParser : public HIDReportParser
{
public:
    report_keyboard_t report;
    uint16_t time_stamp;
    virtual void Parse(HID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
};
