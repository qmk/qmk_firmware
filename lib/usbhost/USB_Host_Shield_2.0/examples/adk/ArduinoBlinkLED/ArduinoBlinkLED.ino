// The source for the Android application can be found at the following link: https://github.com/Lauszus/ArduinoBlinkLED
// The code for the Android application is heavily based on this guide: http://allaboutee.com/2011/12/31/arduino-adk-board-blink-an-led-with-your-phone-code-and-explanation/ by Miguel
#include <adk.h>

//
// CAUTION! WARNING! ATTENTION! VORSICHT! ADVARSEL! ¡CUIDADO! ВНИМАНИЕ!
//
// Pin 13 is occupied by the SCK pin on various Arduino boards,
// including Uno, Duemilanove, etc., so use a different pin for those boards.
//
// CAUTION! WARNING! ATTENTION! VORSICHT! ADVARSEL! ¡CUIDADO! ВНИМАНИЕ!
//
#if defined(LED_BUILTIN)
#define LED LED_BUILTIN // Use built in LED
#else
#define LED 9 // Set to something here that makes sense for your board.
#endif


// Satisfy IDE, which only needs to see the include statment in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
ADK adk(&Usb, "TKJElectronics", // Manufacturer Name
              "ArduinoBlinkLED", // Model Name
              "Example sketch for the USB Host Shield", // Description (user-visible string)
              "1.0", // Version
              "http://www.tkjelectronics.dk/uploads/ArduinoBlinkLED.apk", // URL (web page to visit if no installed apps support the accessory)
              "123456789"); // Serial Number (optional)

uint32_t timer;
bool connected;

void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print("\r\nOSCOKIRQ failed to assert");
    while (1); // halt
  }
  pinMode(LED, OUTPUT);
  Serial.print("\r\nArduino Blink LED Started");
}

void loop() {
  Usb.Task();

  if (adk.isReady()) {
    if (!connected) {
      connected = true;
      Serial.print(F("\r\nConnected to accessory"));
    }

    uint8_t msg[1];
    uint16_t len = sizeof(msg);
    uint8_t rcode = adk.RcvData(&len, msg);
    if (rcode && rcode != hrNAK) {
      Serial.print(F("\r\nData rcv: "));
      Serial.print(rcode, HEX);
    } else if (len > 0) {
      Serial.print(F("\r\nData Packet: "));
      Serial.print(msg[0]);
      digitalWrite(LED, msg[0] ? HIGH : LOW);
    }

    if (millis() - timer >= 1000) { // Send data every 1s
      timer = millis();
      rcode = adk.SndData(sizeof(timer), (uint8_t*)&timer);
      if (rcode && rcode != hrNAK) {
        Serial.print(F("\r\nData send: "));
        Serial.print(rcode, HEX);
      } else if (rcode != hrNAK) {
        Serial.print(F("\r\nTimer: "));
        Serial.print(timer);
      }
    }
  } else {
    if (connected) {
      connected = false;
      Serial.print(F("\r\nDisconnected from accessory"));
      digitalWrite(LED, LOW);
    }
  }
}
