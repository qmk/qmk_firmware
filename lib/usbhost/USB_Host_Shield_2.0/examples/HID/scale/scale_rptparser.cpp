/* Parser for standard HID scale (usage page 0x8d) data input report (ID 3) */ 
#include "scale_rptparser.h"

const char* UNITS[13] = {
    "units",        // unknown unit
    "mg",           // milligram
    "g",            // gram
    "kg",           // kilogram
    "cd",           // carat
    "taels",        // lian
    "gr",           // grain
    "dwt",          // pennyweight
    "tonnes",       // metric tons
    "tons",         // avoir ton
    "ozt",          // troy ounce
    "oz",           // ounce
    "lbs"           // pound
};

ScaleReportParser::ScaleReportParser(ScaleEvents *evt) :
	scaleEvents(evt)
{}

void ScaleReportParser::Parse(HID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf)
{
	bool match = true;

	// Checking if there are changes in report since the method was last called
	for (uint8_t i=0; i<RPT_SCALE_LEN; i++) {
		if( buf[i] != oldScale[i] ) {
			match = false;
			break;
		}
  }
  	// Calling Game Pad event handler
	if (!match && scaleEvents) {
		scaleEvents->OnScaleChanged((const ScaleEventData*)buf);

		for (uint8_t i=0; i<RPT_SCALE_LEN; i++) oldScale[i] = buf[i];
	}
}

ScaleEvents::ScaleEvents( Max_LCD* pLCD ) :
	
	pLcd( pLCD )

{}

void ScaleEvents::LcdPrint( const char* str )
{
	
	while( *str ) {
		
		pLcd->write(	*str++ );
		
	}
}

void ScaleEvents::OnScaleChanged(const ScaleEventData *evt)
{
	
	pLcd->clear();
  pLcd->home();
  pLcd->setCursor(0,0);
	
	if( evt->reportID != 3 ) {
		
		const char inv_report[]="Invalid report!";
		
		Serial.println(inv_report);
		LcdPrint(inv_report);
		
		return;
		
	}//if( evt->reportID != 3...
	
	switch( evt->status ) {
		
		case REPORT_FAULT: 
			Serial.println(F("Report fault"));
			break;
			
		case ZEROED:
			Serial.println(F("Scale zero set"));
			break;
			
		case WEIGHING: {
			
			const char progress[] = "Weighing...";
			Serial.println(progress);
			LcdPrint(progress);
			break;
		}
		
		case WEIGHT_VALID: {
			
			char buf[10];
      double weight = evt->weight * pow( 10, evt->exp );
      
      	
                        
      	Serial.print(F("Weight: "));
				Serial.print( weight );
				Serial.print(F(" "));
				Serial.println( UNITS[ evt->unit ]);
				
				LcdPrint("Weight: ");
				dtostrf( weight, 4, 2, buf );
				LcdPrint( buf ); 
				LcdPrint( UNITS[ evt->unit ]);
			
			break;
			
		}//case WEIGHT_VALID...
			
		case WEIGHT_NEGATIVE: {
			
			const char negweight[] = "Negative weight";
			Serial.println(negweight);
			LcdPrint(negweight);
			break;
		}
			
		case OVERWEIGHT: {
		
			const char overweight[] = "Max.weight reached";
			Serial.println(overweight);
			LcdPrint( overweight );
			break;
		}
		
		case CALIBRATE_ME:
			
			Serial.println(F("Scale calibration required"));
			break;
			
		case ZERO_ME:
			
			Serial.println(F("Scale zeroing required"));
			break;
			
		default:
			
			Serial.print(F("Undefined status code: "));
			Serial.println( evt->status );
			break;	
			
	}//switch( evt->status...

}
