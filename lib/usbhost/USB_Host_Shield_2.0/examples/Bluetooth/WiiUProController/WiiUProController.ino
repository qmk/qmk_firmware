/*
 Example sketch for the Wiimote Bluetooth library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or
 send me an e-mail:  kristianl@tkjelectronics.com
 */

#include <Wii.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
WII Wii(&Btd, PAIR); // This will start an inquiry and then pair with your Wiimote - you only have to do this once
//WII Wii(&Btd); // After that you can simply create the instance like so and then press any button on the Wiimote

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
  if (Wii.wiiUProControllerConnected) {
    if (Wii.getButtonClick(HOME)) { // You can use getButtonPress to see if the button is held down
      Serial.print(F("\r\nHome"));
      Wii.disconnect();
    }
    else {
      if (Wii.getButtonClick(LEFT)) {
        Wii.setLedOff();
        Wii.setLedOn(LED1);
        Serial.print(F("\r\nLeft"));
      }
      if (Wii.getButtonClick(RIGHT)) {
        Wii.setLedOff();
        Wii.setLedOn(LED3);
        Serial.print(F("\r\nRight"));
      }
      if (Wii.getButtonClick(DOWN)) {
        Wii.setLedOff();
        Wii.setLedOn(LED4);
        Serial.print(F("\r\nDown"));
      }
      if (Wii.getButtonClick(UP)) {
        Wii.setLedOff();
        Wii.setLedOn(LED2);
        Serial.print(F("\r\nUp"));
      }

      if (Wii.getButtonClick(PLUS))
        Serial.print(F("\r\nPlus"));
      if (Wii.getButtonClick(MINUS))
        Serial.print(F("\r\nMinus"));

      if (Wii.getButtonClick(A))
        Serial.print(F("\r\nA"));
      if (Wii.getButtonClick(B)) {
        Wii.setRumbleToggle();
        Serial.print(F("\r\nB"));
      }
      if (Wii.getButtonClick(X))
        Serial.print(F("\r\nX"));
      if (Wii.getButtonClick(Y))
        Serial.print(F("\r\nY"));

      if (Wii.getButtonClick(L))
        Serial.print(F("\r\nL"));
      if (Wii.getButtonClick(R))
        Serial.print(F("\r\nR"));
      if (Wii.getButtonClick(ZL))
        Serial.print(F("\r\nZL"));
      if (Wii.getButtonClick(ZR))
        Serial.print(F("\r\nZR"));
      if (Wii.getButtonClick(L3))
        Serial.print(F("\r\nL3"));
      if (Wii.getButtonClick(R3))
        Serial.print(F("\r\nR3"));
    }
    if (Wii.getAnalogHat(LeftHatX) > 2200 || Wii.getAnalogHat(LeftHatX) < 1800 || Wii.getAnalogHat(LeftHatY) > 2200 || Wii.getAnalogHat(LeftHatY) < 1800 || Wii.getAnalogHat(RightHatX) > 2200 ||  Wii.getAnalogHat(RightHatX) < 1800 || Wii.getAnalogHat(RightHatY) > 2200 || Wii.getAnalogHat(RightHatY) < 1800) {
      Serial.print(F("\r\nLeftHatX: "));
      Serial.print(Wii.getAnalogHat(LeftHatX));
      Serial.print(F("\tLeftHatY: "));
      Serial.print(Wii.getAnalogHat(LeftHatY));
      Serial.print(F("\tRightHatX: "));
      Serial.print(Wii.getAnalogHat(RightHatX));
      Serial.print(F("\tRightHatY: "));
      Serial.print(Wii.getAnalogHat(RightHatY));
    }
  }
}
