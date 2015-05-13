/**/
/* A sketch demonstrating data exchange between two USB devices - a HID barcode scanner and ADK-compatible Android phone */
/**/
#include <adk.h>
#include <hidboot.h>
#include <usbhub.h>

// Satisfy IDE, which only needs to see the include statment in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
USBHub Hub1(&Usb);
USBHub Hub2(&Usb);
HIDBoot<HID_PROTOCOL_KEYBOARD> Keyboard(&Usb);

ADK adk(&Usb,"Circuits@Home, ltd.",
            "USB Host Shield",
            "Arduino Terminal for Android",
            "1.0",
            "http://www.circuitsathome.com",
            "0000000000000001");


class KbdRptParser : public KeyboardReportParser
{

protected:
	void OnKeyDown	(uint8_t mod, uint8_t key);
	void OnKeyPressed(uint8_t key);
};

void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key)
{
    uint8_t c = OemToAscii(mod, key);

    if (c)
        OnKeyPressed(c);
}

/* what to do when symbol arrives */
void KbdRptParser::OnKeyPressed(uint8_t key)
{
const char* new_line = "\n";
uint8_t rcode;
uint8_t keylcl;

 if( adk.isReady() == false ) {
   return;
 }

  keylcl = key;

  if( keylcl == 0x13 ) {
    rcode = adk.SndData( strlen( new_line ), (uint8_t *)new_line );
  }
  else {
    rcode = adk.SndData( 1, &keylcl );
  }

  Serial.print((char) keylcl );
  Serial.print(" : ");
  Serial.println( keylcl, HEX );
};

KbdRptParser Prs;

void setup()
{
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  Serial.println("\r\nADK demo start");

  if (Usb.Init() == -1) {
    Serial.println("OSCOKIRQ failed to assert");
    while(1); //halt
  }//if (Usb.Init() == -1...

  Keyboard.SetReportParser(0, (HIDReportParser*)&Prs);

  delay( 200 );
}

void loop()
{
  Usb.Task();
}
