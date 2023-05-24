#if !defined(__HIDJOYSTICKRPTPARSER_H__)
#define __HIDJOYSTICKRPTPARSER_H__

#include <hid.h>

struct GamePadEventData
{
  union { //axes and hut switch
    uint32_t axes;
    struct {
      uint32_t x : 10;
      uint32_t y : 10;
      uint32_t hat : 4;
      uint32_t twist : 8;      
    };
  };
  uint8_t buttons_a;
  uint8_t slider;
  uint8_t buttons_b;
};

class JoystickEvents
{
public:
	virtual void OnGamePadChanged(const GamePadEventData *evt);
};

#define RPT_GAMEPAD_LEN	sizeof(GamePadEventData)/sizeof(uint8_t)

class JoystickReportParser : public HIDReportParser
{
	JoystickEvents		*joyEvents;

  uint8_t oldPad[RPT_GAMEPAD_LEN];

public:
	JoystickReportParser(JoystickEvents *evt);

	virtual void Parse(HID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
};

#endif // __HIDJOYSTICKRPTPARSER_H__
