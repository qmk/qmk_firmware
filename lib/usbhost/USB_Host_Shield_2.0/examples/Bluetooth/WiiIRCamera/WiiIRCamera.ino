/*
Example sketch for the Wii libary showing the IR camera functionality. This example
is for the Bluetooth Wii library developed for the USB shield from Circuits@Home

Created by Allan Glover and Kristian Lauszus.
Contact Kristian:  http://blog.tkjelectronics.dk/ or send an email at kristianl@tkjelectronics.com.
Contact Allan at adglover9.81@gmail.com

To test the Wiimote IR camera, you will need access to an IR source. Sunlight will work but is not ideal.
The simpleist solution is to use the Wii sensor bar, i.e. emitter bar, supplied by the Wii system.
Otherwise, wire up a IR LED yourself.
*/

#include <Wii.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

#ifndef WIICAMERA // Used to check if WIICAMERA is defined
#error "Please set ENABLE_WII_IR_CAMERA to 1 in settings.h"
#endif

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
WII Wii(&Btd, PAIR); // This will start an inquiry and then pair with your Wiimote - you only have to do this once
//WII Wii(&Btd); // After the Wiimote pairs once with the line of code above, you can simply create the instance like so and re upload and then press any button on the Wiimote

bool printAngle;
uint8_t printObjects;

void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nWiimote Bluetooth Library Started"));
}

void loop() {
  Usb.Task();
  if (Wii.wiimoteConnected) {
    if (Wii.getButtonClick(HOME)) { // You can use getButtonPress to see if the button is held down
      Serial.print(F("\r\nHOME"));
      Wii.disconnect();
    }
    else {
      if (Wii.getButtonClick(ONE))
        Wii.IRinitialize(); // Run the initialisation sequence
      if (Wii.getButtonClick(MINUS) || Wii.getButtonClick(PLUS)) {
        if (!Wii.isIRCameraEnabled())
          Serial.print(F("\r\nEnable IR camera first"));
        else {
          if (Wii.getButtonPress(MINUS)) { // getButtonClick will only return true once
            if (printObjects > 0)
              printObjects--;
          }
          else {
            if (printObjects < 4)
              printObjects++;
          }
          Serial.print(F("\r\nTracking "));
          Serial.print(printObjects);
          Serial.print(F(" objects"));
        }
      }
      if (Wii.getButtonClick(A)) {
        printAngle = !printAngle;
        Serial.print(F("\r\nA"));
      }
      if (Wii.getButtonClick(B)) {
        Serial.print(F("\r\nBattery level: "));
        Serial.print(Wii.getBatteryLevel()); // You can get the battery level as well
      }
    }
    if (printObjects > 0) {
      if (Wii.getIRx1() != 0x3FF || Wii.getIRy1() != 0x3FF || Wii.getIRs1() != 0) { // Only print if the IR camera is actually seeing something
        Serial.print(F("\r\nx1: "));
        Serial.print(Wii.getIRx1());
        Serial.print(F("\ty1: "));
        Serial.print(Wii.getIRy1());
        Serial.print(F("\ts1:"));
        Serial.print(Wii.getIRs1());
      }
      if (printObjects > 1) {
        if (Wii.getIRx2() != 0x3FF || Wii.getIRy2() != 0x3FF || Wii.getIRs2() != 0) {
          Serial.print(F("\r\nx2: "));
          Serial.print(Wii.getIRx2());
          Serial.print(F("\ty2: "));
          Serial.print(Wii.getIRy2());
          Serial.print(F("\ts2:"));
          Serial.print(Wii.getIRs2());
        }
        if (printObjects > 2) {
          if (Wii.getIRx3() != 0x3FF || Wii.getIRy3() != 0x3FF || Wii.getIRs3() != 0) {
            Serial.print(F("\r\nx3: "));
            Serial.print(Wii.getIRx3());
            Serial.print(F("\ty3: "));
            Serial.print(Wii.getIRy3());
            Serial.print(F("\ts3:"));
            Serial.print(Wii.getIRs3());
          }
          if (printObjects > 3) {
            if (Wii.getIRx4() != 0x3FF || Wii.getIRy4() != 0x3FF || Wii.getIRs4() != 0) {
              Serial.print(F("\r\nx4: "));
              Serial.print(Wii.getIRx4());
              Serial.print(F("\ty4: "));
              Serial.print(Wii.getIRy4());
              Serial.print(F("\ts4:"));
              Serial.print(Wii.getIRs4());
            }
          }
        }
      }
    }
    if (printAngle) { // There is no extension bytes available, so the MotionPlus or Nunchuck can't be read
      Serial.print(F("\r\nPitch: "));
      Serial.print(Wii.getPitch());
      Serial.print(F("\tRoll: "));
      Serial.print(Wii.getRoll());
    }
  }
}
