#ifndef PARSER_H
#define PARSER_H

#include "hid.h"

class KBDReportParser : public HIDReportParser
{
public:
	virtual void Parse(HID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
};

#endif
