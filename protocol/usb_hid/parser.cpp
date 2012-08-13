#include "parser.h"

void KBDReportParser::Parse(HID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf)
{
    PORTB ^= (1<<0);
/*
    Serial.print("KBDReport: ");
    for (uint8_t i = 0; i < len; i++) {
        PrintHex<uint8_t>(buf[i]);
        Serial.print(" ");
    }
    Serial.print("\r\n");
*/
    //PORTC &= ~(1<<7);
}
