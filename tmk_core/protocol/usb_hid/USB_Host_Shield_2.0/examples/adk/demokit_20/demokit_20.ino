#include <adk.h>
#include <usbhub.h>

// Satisfy IDE, which only needs to see the include statment in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
USBHub hub0(&Usb);
USBHub hub1(&Usb);
ADK adk(&Usb,"Google, Inc.",
            "DemoKit",
            "DemoKit Arduino Board",
            "1.0",
            "http://www.android.com",
            "0000000012345678");
uint8_t  b, b1;


#define  LED1_RED       3
#define  BUTTON1        2

void init_buttons()
{
	pinMode(BUTTON1, INPUT);

	// enable the internal pullups
	digitalWrite(BUTTON1, HIGH);
}

void init_leds()
{
	digitalWrite(LED1_RED, 0);

	pinMode(LED1_RED, OUTPUT);
}

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


	init_leds();
	init_buttons();
	b1 = digitalRead(BUTTON1);
}

void loop()
{
  uint8_t rcode;
  uint8_t msg[3] = { 0x00 };
   Usb.Task();

   if( adk.isReady() == false ) {
     analogWrite(LED1_RED, 255);
     return;
   }
   uint16_t len = sizeof(msg);

   rcode = adk.RcvData(&len, msg);
   if( rcode ) {
     USBTRACE2("Data rcv. :", rcode );
   }
   if(len > 0) {
     USBTRACE("\r\nData Packet.");
    // assumes only one command per packet
    if (msg[0] == 0x2) {
      switch( msg[1] ) {
        case 0:
          analogWrite(LED1_RED, 255 - msg[2]);
          break;
      }//switch( msg[1]...
    }//if (msg[0] == 0x2...
   }//if( len > 0...

   msg[0] = 0x1;

   b = digitalRead(BUTTON1);
   if (b != b1) {
     USBTRACE("\r\nButton state changed");
     msg[1] = 0;
     msg[2] = b ? 0 : 1;
     rcode = adk.SndData( 3, msg );
     if( rcode ) {
       USBTRACE2("Button send: ", rcode );
     }
     b1 = b;
    }//if (b != b1...


      delay( 10 );
}
