/* Arduino terminal for PL2303 USB to serial converter and DealeXtreme GPRS modem. */
/* USB support */
#include <usbhub.h>
/* CDC support */
#include <cdcacm.h>
#include <cdcprolific.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

class PLAsyncOper : public CDCAsyncOper
{
public:
    uint8_t OnInit(ACM *pacm);
};

uint8_t PLAsyncOper::OnInit(ACM *pacm)
{
    uint8_t rcode;

    // Set DTR = 1
    rcode = pacm->SetControlLineState(1);

    if (rcode)
    {
        ErrorMessage<uint8_t>(PSTR("SetControlLineState"), rcode);
        return rcode;
    }

    LINE_CODING	lc;
    //lc.dwDTERate	= 9600;
    lc.dwDTERate = 115200;
    lc.bCharFormat	= 0;
    lc.bParityType	= 0;
    lc.bDataBits	= 8;

    rcode = pacm->SetLineCoding(&lc);

    if (rcode)
        ErrorMessage<uint8_t>(PSTR("SetLineCoding"), rcode);

    return rcode;
}
USB     Usb;
//USBHub     Hub(&Usb);
PLAsyncOper  AsyncOper;
PL2303       Pl(&Usb, &AsyncOper);

void setup()
{
  Serial.begin( 115200 );
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  Serial.println("Start");

  if (Usb.Init() == -1)
      Serial.println("OSCOKIRQ failed to assert");

  delay( 200 );
}

void loop()
{
    Usb.Task();

    if( Usb.getUsbTaskState() == USB_STATE_RUNNING )
    {
       uint8_t rcode;

       /* reading the keyboard */
       if(Serial.available()) {
         uint8_t data= Serial.read();

         /* sending to the phone */
         rcode = Pl.SndData(1, &data);
         if (rcode)
            ErrorMessage<uint8_t>(PSTR("SndData"), rcode);
       }//if(Serial.available()...

        /* reading the converter */
        /* buffer size must be greater or equal to max.packet size */
        /* it it set to 64 (largest possible max.packet size) here, can be tuned down
        for particular endpoint */
        uint8_t  buf[64];
        uint16_t rcvd = 64;
        rcode = Pl.RcvData(&rcvd, buf);
         if (rcode && rcode != hrNAK)
           ErrorMessage<uint8_t>(PSTR("Ret"), rcode);

           if( rcvd ) { //more than zero bytes received
             for(uint16_t i=0; i < rcvd; i++ ) {
               Serial.print((char)buf[i]); //printing on the screen
             }
           }//if( rcvd ...
    }//if( Usb.getUsbTaskState() == USB_STATE_RUNNING..
}

