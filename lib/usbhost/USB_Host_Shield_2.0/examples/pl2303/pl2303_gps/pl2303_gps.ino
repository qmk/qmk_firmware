/* USB Host to PL2303-based USB GPS unit interface */
/* Navibee GM720 receiver - Sirf Star III */
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

class PLAsyncOper : public CDCAsyncOper {
public:
        uint8_t OnInit(ACM *pacm);
};

uint8_t PLAsyncOper::OnInit(ACM *pacm) {
        uint8_t rcode;

        // Set DTR = 1
        rcode = pacm->SetControlLineState(1);

        if(rcode) {
                ErrorMessage<uint8_t>(PSTR("SetControlLineState"), rcode);
                return rcode;
        }

        LINE_CODING lc;
        lc.dwDTERate = 4800; //default serial speed of GPS unit
        lc.bCharFormat = 0;
        lc.bParityType = 0;
        lc.bDataBits = 8;

        rcode = pacm->SetLineCoding(&lc);

        if(rcode)
                ErrorMessage<uint8_t>(PSTR("SetLineCoding"), rcode);

        return rcode;
}

USB Usb;
USBHub Hub(&Usb);
PLAsyncOper AsyncOper;
PL2303 Pl(&Usb, &AsyncOper);
uint32_t read_delay;
#define READ_DELAY 100

void setup() {
        Serial.begin(115200);
#if !defined(__MIPSEL__)
        while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
        Serial.println("Start");

        if(Usb.Init() == -1)
                Serial.println("OSCOKIRQ failed to assert");

        delay(200);
}

void loop() {
        uint8_t rcode;
        uint8_t buf[64]; //serial buffer equals Max.packet size of bulk-IN endpoint
        uint16_t rcvd = 64;

        Usb.Task();

        if(Pl.isReady()) {
                /* reading the GPS */
                if((long)(millis() - read_delay) >= 0L) {
                        read_delay += READ_DELAY;
                        rcode = Pl.RcvData(&rcvd, buf);
                        if(rcode && rcode != hrNAK)
                                ErrorMessage<uint8_t>(PSTR("Ret"), rcode);
                        if(rcvd) { //more than zero bytes received
                                for(uint16_t i = 0; i < rcvd; i++) {
                                        Serial.print((char)buf[i]); //printing on the screen
                                }//for( uint16_t i=0; i < rcvd; i++...
                        }//if( rcvd
                }//if( read_delay > millis()...
        }//if( Usb.getUsbTaskState() == USB_STATE_RUNNING..
}


