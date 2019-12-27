#include <cdcftdi.h>
#include <usbhub.h>

#include "pgmstrings.h"

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

class FTDIAsync : public FTDIAsyncOper
{
public:
    uint8_t OnInit(FTDI *pftdi);
};

uint8_t FTDIAsync::OnInit(FTDI *pftdi)
{
    uint8_t rcode = 0;

    rcode = pftdi->SetBaudRate(115200);

    if (rcode)
    {
        ErrorMessage<uint8_t>(PSTR("SetBaudRate"), rcode);
        return rcode;
    }
    rcode = pftdi->SetFlowControl(FTDI_SIO_DISABLE_FLOW_CTRL);

    if (rcode)
        ErrorMessage<uint8_t>(PSTR("SetFlowControl"), rcode);

    return rcode;
}

USB              Usb;
//USBHub         Hub(&Usb);
FTDIAsync        FtdiAsync;
FTDI             Ftdi(&Usb, &FtdiAsync);

uint32_t next_time;

void setup()
{
  Serial.begin( 115200 );
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  Serial.println("Start");

  if (Usb.Init() == -1)
      Serial.println("OSC did not start.");

  delay( 200 );

  next_time = millis() + 5000;
}

void loop()
{
    Usb.Task();

    if( Usb.getUsbTaskState() == USB_STATE_RUNNING )
    {
        uint8_t  rcode;
        char strbuf[] = "DEADBEEF";
        //char strbuf[] = "The quick brown fox jumps over the lazy dog";
        //char strbuf[] = "This string contains 61 character to demonstrate FTDI buffers"; //add one symbol to it to see some garbage
        Serial.print(".");

        rcode = Ftdi.SndData(strlen(strbuf), (uint8_t*)strbuf);

	if (rcode)
            ErrorMessage<uint8_t>(PSTR("SndData"), rcode);

        delay(50);

        uint8_t  buf[64];

        for (uint8_t i=0; i<64; i++)
            buf[i] = 0;

        uint16_t rcvd = 64;
        rcode = Ftdi.RcvData(&rcvd, buf);

        if (rcode && rcode != hrNAK)
            ErrorMessage<uint8_t>(PSTR("Ret"), rcode);

        // The device reserves the first two bytes of data
        //   to contain the current values of the modem and line status registers.
        if (rcvd > 2)
            Serial.print((char*)(buf+2));

        delay(10);
    }
}

