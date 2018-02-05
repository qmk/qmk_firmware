/* Digital Scale Output. Written for Stamps.com Model 510  */
/* 5lb Digital Scale; any HID scale with Usage page 0x8d should work */

#include <hid.h>
#include <hiduniversal.h>
#include <usbhub.h>

#include "scale_rptparser.h"

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB                                             Usb;
USBHub                                          Hub(&Usb);
HIDUniversal                                    Hid(&Usb);
Max_LCD                                       LCD(&Usb);
ScaleEvents                                  ScaleEvents(&LCD);
ScaleReportParser                            Scale(&ScaleEvents);

void setup()
{
  Serial.begin( 115200 );
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  Serial.println("Start");

  if (Usb.Init() == -1)
      Serial.println("OSC did not start.");

    // set up the LCD's number of rows and columns:
    LCD.begin(16, 2);
    LCD.clear();
    LCD.home();
    LCD.setCursor(0,0);
    LCD.write('R');

  delay( 200 );

  if (!Hid.SetReportParser(0, &Scale))
      ErrorMessage<uint8_t>(PSTR("SetReportParser"), 1  );
}

void loop()
{
    Usb.Task();
}

