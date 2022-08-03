#include <cdc_XR21B1411.h>

// Satisfy IDE, which only needs to see the include statment in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

class ACMAsyncOper : public CDCAsyncOper
{
public:
    uint8_t OnInit(ACM *pacm);
};

uint8_t ACMAsyncOper::OnInit(ACM *pacm)
{
    uint8_t rcode;
    // Set DTR = 1 RTS=1
    rcode = pacm->SetControlLineState(3);

    if (rcode)
    {
        ErrorMessage<uint8_t>(PSTR("SetControlLineState"), rcode);
        return rcode;
    }

    LINE_CODING	lc;
    lc.dwDTERate	= 115200;
    lc.bCharFormat	= 0;
    lc.bParityType	= 0;
    lc.bDataBits	= 8;

    rcode = pacm->SetLineCoding(&lc);

    if (rcode)
        ErrorMessage<uint8_t>(PSTR("SetLineCoding"), rcode);

    return rcode;
}

USB     Usb;
ACMAsyncOper  AsyncOper;
XR21B1411     Acm(&Usb, &AsyncOper);

void setup() {
        Serial.begin( 115200 );
#if !defined(__MIPSEL__)
        while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
        Serial.println("\r\n\r\nStart");

        if (Usb.Init() == -1) Serial.println("OSCOKIRQ failed to assert");
}

void loop() {
        Usb.Task();
        if( Acm.isReady()) {
                uint8_t rcode;
                uint8_t  buf[1];
                uint16_t rcvd = 1;

                /* read keyboard */
                if(Serial.available()) {
                         uint8_t data = Serial.read();
                         /* send */
                         rcode = Acm.SndData(1, &data);
                         if (rcode)
                                 ErrorMessage<uint8_t>(PSTR("SndData"), rcode);
                 }
                
                /* read XR serial */
                rcode = Acm.RcvData(&rcvd, buf);
                if (rcode && rcode != hrNAK)
                        ErrorMessage<uint8_t>(PSTR("Ret"), rcode);

                if( rcvd ) { //more than zero bytes received
                        for(uint16_t i=0; i < rcvd; i++ ) {
                                Serial.print((char)buf[i]);
                        }
                }
        }
}

