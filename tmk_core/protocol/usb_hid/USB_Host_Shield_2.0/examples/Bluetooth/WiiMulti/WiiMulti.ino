/*
 Example sketch for the Wiimote Bluetooth library - developed by Kristian Lauszus
 This example show how one can use multiple controllers with the library
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
WII *Wii[2]; // We will use this pointer to store the two instance, you can easily make it larger if you like, but it will use a lot of RAM!
const uint8_t length = sizeof(Wii) / sizeof(Wii[0]); // Get the lenght of the array
bool printAngle[length];
bool oldControllerState[length];

void setup() {
  for (uint8_t i = 0; i < length; i++) {
    Wii[i] = new WII(&Btd); // You will have to pair each controller with the dongle before you can define the instances like so, just add PAIR as the second argument
    Wii[i]->attachOnInit(onInit); // onInit() is called upon a new connection - you can call the function whatever you like
  }

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

  for (uint8_t i = 0; i < length; i++) {
    if (Wii[i]->wiimoteConnected) {
      if (Wii[i]->getButtonClick(HOME)) { // You can use getButtonPress to see if the button is held down
        Serial.print(F("\r\nHOME"));
        Wii[i]->disconnect();
        oldControllerState[i] = false; // Reset value
      }
      else {
        if (Wii[i]->getButtonClick(LEFT)) {
          Wii[i]->setLedOff();
          Wii[i]->setLedOn(LED1);
          Serial.print(F("\r\nLeft"));
        }
        if (Wii[i]->getButtonClick(RIGHT)) {
          Wii[i]->setLedOff();
          Wii[i]->setLedOn(LED3);
          Serial.print(F("\r\nRight"));
        }
        if (Wii[i]->getButtonClick(DOWN)) {
          Wii[i]->setLedOff();
          Wii[i]->setLedOn(LED4);
          Serial.print(F("\r\nDown"));
        }
        if (Wii[i]->getButtonClick(UP)) {
          Wii[i]->setLedOff();
          Wii[i]->setLedOn(LED2);
          Serial.print(F("\r\nUp"));
        }

        if (Wii[i]->getButtonClick(PLUS))
          Serial.print(F("\r\nPlus"));
        if (Wii[i]->getButtonClick(MINUS))
          Serial.print(F("\r\nMinus"));

        if (Wii[i]->getButtonClick(ONE))
          Serial.print(F("\r\nOne"));
        if (Wii[i]->getButtonClick(TWO))
          Serial.print(F("\r\nTwo"));

        if (Wii[i]->getButtonClick(A)) {
          printAngle[i] = !printAngle[i];
          Serial.print(F("\r\nA"));
        }
        if (Wii[i]->getButtonClick(B)) {
          Wii[i]->setRumbleToggle();
          Serial.print(F("\r\nB"));
        }
      }
      if (printAngle[i]) {
        Serial.print(F("\r\nPitch: "));
        Serial.print(Wii[i]->getPitch());
        Serial.print(F("\tRoll: "));
        Serial.print(Wii[i]->getRoll());
        if (Wii[i]->motionPlusConnected) {
          Serial.print(F("\tYaw: "));
          Serial.print(Wii[i]->getYaw());
        }
        if (Wii[i]->nunchuckConnected) {
          Serial.print(F("\tNunchuck Pitch: "));
          Serial.print(Wii[i]->getNunchuckPitch());
          Serial.print(F("\tNunchuck Roll: "));
          Serial.print(Wii[i]->getNunchuckRoll());
        }
      }
    }
    if (Wii[i]->nunchuckConnected) {
      if (Wii[i]->getButtonClick(Z))
        Serial.print(F("\r\nZ"));
      if (Wii[i]->getButtonClick(C))
        Serial.print(F("\r\nC"));
      if (Wii[i]->getAnalogHat(HatX) > 137 ||  Wii[i]->getAnalogHat(HatX) < 117 || Wii[i]->getAnalogHat(HatY) > 137 || Wii[i]->getAnalogHat(HatY) < 117) {
        Serial.print(F("\r\nHatX: "));
        Serial.print(Wii[i]->getAnalogHat(HatX));
        Serial.print(F("\tHatY: "));
        Serial.print(Wii[i]->getAnalogHat(HatY));
      }
    }
  }
}

void onInit() {
  for (uint8_t i = 0; i < length; i++) {
    if (Wii[i]->wiimoteConnected && !oldControllerState[i]) {
      oldControllerState[i] = true; // Used to check which is the new controller
      Wii[i]->setLedOn((LEDEnum)(i + 1)); // Cast directly to LEDEnum - see: "controllerEnums.h"
    }
  }
}
