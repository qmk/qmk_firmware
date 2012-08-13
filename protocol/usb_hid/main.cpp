#include <util/delay.h>
#include <Arduino.h>
#include "Usb.h"
#include "hid.h"
#include "hidboot.h"
#include "parser.h"


USB     Usb;
HIDBoot<HID_PROTOCOL_KEYBOARD>    kbd(&Usb);
KBDReportParser Prs;

void usb_disable()
{
    USBCON &= ~(1<<VBUSTI);
    UDIEN = 0;
    USBINT = 0;
    UDINT = 0;
    UDCON |= (1<<DETACH);
    USBCON &= ~(1<<USBE);
    PLLCSR = 0;
    UHWCON &= ~(1<<UVREGE);
    USBCON &= ~(1<<OTGPADE);
}

void setup()
{
    usb_disable();

    // RX LED for debug
    DDRB |= (1<<0);

    Serial.begin( 115200 );
    while (!Serial) ;

    delay( 1000 );

    Serial.println("Start");

    if (Usb.Init() == -1) {
        Serial.println("OSC did not start.");
    }
      
    delay( 200 );
  
    kbd.SetReportParser(0, (HIDReportParser*)&Prs);
}

void loop()
{
    Usb.Task();
}

int main(void)
{
    // arduino/wiring.c(Timer initialize)
    init();

    setup();
    
    for (;;) {
        loop();
    }
        
    return 0;
}
