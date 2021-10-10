#include "le3dp_rptparser.h"

JoystickReportParser::JoystickReportParser(JoystickEvents *evt) :
	joyEvents(evt)
{}

void JoystickReportParser::Parse(HID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf)
{
	bool match = true;

	// Checking if there are changes in report since the method was last called
	for (uint8_t i=0; i<RPT_GAMEPAD_LEN; i++) {
		if( buf[i] != oldPad[i] ) {
			match = false;
			break;
		}
  }
  	// Calling Game Pad event handler
	if (!match && joyEvents) {
		joyEvents->OnGamePadChanged((const GamePadEventData*)buf);

		for (uint8_t i=0; i<RPT_GAMEPAD_LEN; i++) oldPad[i] = buf[i];
	}
}

void JoystickEvents::OnGamePadChanged(const GamePadEventData *evt)
{
	Serial.print("X: ");
	PrintHex<uint16_t>(evt->x, 0x80);
	Serial.print(" Y: ");
	PrintHex<uint16_t>(evt->y, 0x80);
	Serial.print(" Hat Switch: ");
	PrintHex<uint8_t>(evt->hat, 0x80);
	Serial.print(" Twist: ");
	PrintHex<uint8_t>(evt->twist, 0x80);
	Serial.print(" Slider: ");
	PrintHex<uint8_t>(evt->slider, 0x80);
  Serial.print(" Buttons A: ");
	PrintHex<uint8_t>(evt->buttons_a, 0x80);
	Serial.print(" Buttons B: ");
	PrintHex<uint8_t>(evt->buttons_b, 0x80);
	Serial.println("");
}
