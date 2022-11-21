/*
 Example sketch for the PS3 Bluetooth library - developed by Kristian Lauszus
 This example show how one can use multiple controllers with the library
 For more information visit my blog: http://blog.tkjelectronics.dk/ or
 send me an e-mail:  kristianl@tkjelectronics.com
 */

#include <PS3BT.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
PS3BT *PS3[2]; // We will use this pointer to store the two instance, you can easily make it larger if you like, but it will use a lot of RAM!
const uint8_t length = sizeof(PS3) / sizeof(PS3[0]); // Get the lenght of the array
bool printAngle[length];
bool oldControllerState[length];

void setup() {
  for (uint8_t i = 0; i < length; i++) {
    PS3[i] = new PS3BT(&Btd); // Create the instances
    PS3[i]->attachOnInit(onInit); // onInit() is called upon a new connection - you can call the function whatever you like
  }

  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
}
void loop() {
  Usb.Task();

  for (uint8_t i = 0; i < length; i++) {
    if (PS3[i]->PS3Connected || PS3[i]->PS3NavigationConnected) {
      if (PS3[i]->getAnalogHat(LeftHatX) > 137 || PS3[i]->getAnalogHat(LeftHatX) < 117 || PS3[i]->getAnalogHat(LeftHatY) > 137 || PS3[i]->getAnalogHat(LeftHatY) < 117 || PS3[i]->getAnalogHat(RightHatX) > 137 || PS3[i]->getAnalogHat(RightHatX) < 117 || PS3[i]->getAnalogHat(RightHatY) > 137 || PS3[i]->getAnalogHat(RightHatY) < 117) {
        Serial.print(F("\r\nLeftHatX: "));
        Serial.print(PS3[i]->getAnalogHat(LeftHatX));
        Serial.print(F("\tLeftHatY: "));
        Serial.print(PS3[i]->getAnalogHat(LeftHatY));
        if (PS3[i]->PS3Connected) { // The Navigation controller only have one joystick
          Serial.print(F("\tRightHatX: "));
          Serial.print(PS3[i]->getAnalogHat(RightHatX));
          Serial.print(F("\tRightHatY: "));
          Serial.print(PS3[i]->getAnalogHat(RightHatY));
        }
      }
      //Analog button values can be read from almost all buttons
      if (PS3[i]->getAnalogButton(L2) || PS3[i]->getAnalogButton(R2)) {
        Serial.print(F("\r\nL2: "));
        Serial.print(PS3[i]->getAnalogButton(L2));
        if (PS3[i]->PS3Connected) {
          Serial.print(F("\tR2: "));
          Serial.print(PS3[i]->getAnalogButton(R2));
        }
      }
      if (PS3[i]->getButtonClick(PS)) {
        Serial.print(F("\r\nPS"));
        PS3[i]->disconnect();
        oldControllerState[i] = false; // Reset value
      }
      else {
        if (PS3[i]->getButtonClick(TRIANGLE))
          Serial.print(F("\r\nTraingle"));
        if (PS3[i]->getButtonClick(CIRCLE))
          Serial.print(F("\r\nCircle"));
        if (PS3[i]->getButtonClick(CROSS))
          Serial.print(F("\r\nCross"));
        if (PS3[i]->getButtonClick(SQUARE))
          Serial.print(F("\r\nSquare"));

        if (PS3[i]->getButtonClick(UP)) {
          Serial.print(F("\r\nUp"));
          if (PS3[i]->PS3Connected) {
            PS3[i]->setLedOff();
            PS3[i]->setLedOn(LED4);
          }
        }
        if (PS3[i]->getButtonClick(RIGHT)) {
          Serial.print(F("\r\nRight"));
          if (PS3[i]->PS3Connected) {
            PS3[i]->setLedOff();
            PS3[i]->setLedOn(LED1);
          }
        }
        if (PS3[i]->getButtonClick(DOWN)) {
          Serial.print(F("\r\nDown"));
          if (PS3[i]->PS3Connected) {
            PS3[i]->setLedOff();
            PS3[i]->setLedOn(LED2);
          }
        }
        if (PS3[i]->getButtonClick(LEFT)) {
          Serial.print(F("\r\nLeft"));
          if (PS3[i]->PS3Connected) {
            PS3[i]->setLedOff();
            PS3[i]->setLedOn(LED3);
          }
        }

        if (PS3[i]->getButtonClick(L1))
          Serial.print(F("\r\nL1"));
        if (PS3[i]->getButtonClick(L3))
          Serial.print(F("\r\nL3"));
        if (PS3[i]->getButtonClick(R1))
          Serial.print(F("\r\nR1"));
        if (PS3[i]->getButtonClick(R3))
          Serial.print(F("\r\nR3"));

        if (PS3[i]->getButtonClick(SELECT)) {
          Serial.print(F("\r\nSelect - "));
          PS3[i]->printStatusString();
        }
        if (PS3[i]->getButtonClick(START)) {
          Serial.print(F("\r\nStart"));
          printAngle[i] = !printAngle[i];
        }
      }
      if (printAngle[i]) {
        Serial.print(F("\r\nPitch: "));
        Serial.print(PS3[i]->getAngle(Pitch));
        Serial.print(F("\tRoll: "));
        Serial.print(PS3[i]->getAngle(Roll));
      }
    }
    /* I have removed the PS3 Move code as an Uno will run out of RAM if it's included */
    //else if(PS3[i]->PS3MoveConnected) {
  }
}

void onInit() {
  for (uint8_t i = 0; i < length; i++) {
    if ((PS3[i]->PS3Connected || PS3[i]->PS3NavigationConnected) && !oldControllerState[i]) {
      oldControllerState[i] = true; // Used to check which is the new controller
      PS3[i]->setLedOn((LEDEnum)(i + 1)); // Cast directly to LEDEnum - see: "controllerEnums.h"
    }
  }
}
