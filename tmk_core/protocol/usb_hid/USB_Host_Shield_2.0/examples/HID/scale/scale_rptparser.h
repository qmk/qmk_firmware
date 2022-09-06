#if !defined(__SCALERPTPARSER_H__)
#define __SCALERPTPARSER_H__

#include <max_LCD.h>
#include <hid.h>

/* Scale status constants */
#define REPORT_FAULT 0x01
#define ZEROED 0x02
#define WEIGHING 0x03
#define WEIGHT_VALID 0x04
#define WEIGHT_NEGATIVE 0x05
#define OVERWEIGHT 0x06
#define CALIBRATE_ME 0x07
#define ZERO_ME 0x08

/* input data report */
struct ScaleEventData
{
  uint8_t reportID;	//must be 3
  uint8_t status;
  uint8_t unit;
  int8_t exp;			//scale factor for the weight
  uint16_t weight;	//
};

class ScaleEvents
{

	Max_LCD*	pLcd;

	void LcdPrint( const char* str );

public:

	ScaleEvents( Max_LCD* pLCD );

	virtual void OnScaleChanged(const ScaleEventData *evt);
};

#define RPT_SCALE_LEN	sizeof(ScaleEventData)/sizeof(uint8_t)

class ScaleReportParser : public HIDReportParser
{
	ScaleEvents		*scaleEvents;

  uint8_t oldScale[RPT_SCALE_LEN];

public:
	ScaleReportParser(ScaleEvents *evt);

	virtual void Parse(HID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
};

#endif // __SCALERPTPARSER_H__
