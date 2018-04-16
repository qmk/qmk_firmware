#include <adk.h>
#include <usbhub.h>

// Satisfy IDE, which only needs to see the include statment in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
//USBHub     Hub(&Usb);

ADK adk(&Usb,"Circuits@Home, ltd.",
            "USB Host Shield",
            "Arduino Terminal for Android",
            "1.0",
            "http://www.circuitsathome.com",
            "0000000000000001");

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
}

void loop()
{
  uint8_t rcode;
  uint8_t msg[64] = { 0x00 };
  const char* recv = "Received: ";

   Usb.Task();

   if( adk.isReady() == false ) {
     return;
   }
   uint16_t len = 64;

   rcode = adk.RcvData(&len, msg);
   if( rcode & ( rcode != hrNAK )) {
     USBTRACE2("Data rcv. :", rcode );
   }
   if(len > 0) {
     USBTRACE("\r\nData Packet.");

    for( uint8_t i = 0; i < len; i++ ) {
      Serial.print((char)msg[i]);
    }
    /* sending back what was received */
    rcode = adk.SndData( strlen( recv ), (uint8_t *)recv );
    rcode = adk.SndData( strlen(( char * )msg ), msg );

   }//if( len > 0 )...

   delay( 1000 );
}

