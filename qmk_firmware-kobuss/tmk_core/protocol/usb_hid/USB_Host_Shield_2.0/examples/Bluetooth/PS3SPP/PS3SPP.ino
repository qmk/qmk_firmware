/*
 Example sketch for the Bluetooth library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or
 send me an e-mail:  kristianl@tkjelectronics.com

 This example show how one can combine all the difference Bluetooth services in one single code.
 Note:
 You will need a Arduino Mega 1280/2560 to run this sketch,
 as a normal Arduino (Uno, Duemilanove etc.) doesn't have enough SRAM and FLASH
 */

#include <PS3BT.h>
#include <SPP.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so

/* You can create the instances of the bluetooth services in two ways */
SPP SerialBT(&Btd); // This will set the name to the defaults: "Arduino" and the pin to "0000"
//SPP SerialBTBT(&Btd,"Lauszus's Arduino","0000"); // You can also set the name and pin like so
PS3BT PS3(&Btd); // This will just create the instance
//PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

bool firstMessage = true;
String output = ""; // We will store the data in this string

void setup() {
  Serial.begin(115200); // This wil lprint the debugging from the libraries
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nBluetooth Library Started"));
  output.reserve(200); // Reserve 200 bytes for the output string
}
void loop() {
  Usb.Task(); // The SPP data is actually not send until this is called, one could call SerialBT.send() directly as well

  if (SerialBT.connected) {
    if (firstMessage) {
      firstMessage = false;
      SerialBT.println(F("Hello from Arduino")); // Send welcome message
    }
    if (Serial.available())
      SerialBT.write(Serial.read());
    if (SerialBT.available())
      Serial.write(SerialBT.read());
  }
  else
    firstMessage = true;

  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
    output = ""; // Reset output string
    if (PS3.getAnalogHat(LeftHatX) > 137 || PS3.getAnalogHat(LeftHatX) < 117 || PS3.getAnalogHat(LeftHatY) > 137 || PS3.getAnalogHat(LeftHatY) < 117 || PS3.getAnalogHat(RightHatX) > 137 || PS3.getAnalogHat(RightHatX) < 117 || PS3.getAnalogHat(RightHatY) > 137 || PS3.getAnalogHat(RightHatY) < 117) {
      output += "LeftHatX: ";
      output += PS3.getAnalogHat(LeftHatX);
      output += "\tLeftHatY: ";
      output += PS3.getAnalogHat(LeftHatY);
      if (PS3.PS3Connected) { // The Navigation controller only have one joystick
        output += "\tRightHatX: ";
        output += PS3.getAnalogHat(RightHatX);
        output += "\tRightHatY: ";
        output += PS3.getAnalogHat(RightHatY);
      }
    }
    //Analog button values can be read from almost all buttons
    if (PS3.getAnalogButton(L2) || PS3.getAnalogButton(R2)) {
      if (output != "")
        output += "\r\n";
      output += "L2: ";
      output += PS3.getAnalogButton(L2);
      if (PS3.PS3Connected) {
        output += "\tR2: ";
        output += PS3.getAnalogButton(R2);
      }
    }
    if (output != "") {
      Serial.println(output);
      if (SerialBT.connected)
        SerialBT.println(output);
      output = ""; // Reset output string
    }
    if (PS3.getButtonClick(PS)) {
      output += " - PS";
      PS3.disconnect();
    }
    else {
      if (PS3.getButtonClick(TRIANGLE))
        output += " - Traingle";
      if (PS3.getButtonClick(CIRCLE))
        output += " - Circle";
      if (PS3.getButtonClick(CROSS))
        output += " - Cross";
      if (PS3.getButtonClick(SQUARE))
        output += " - Square";

      if (PS3.getButtonClick(UP)) {
        output += " - Up";
        if (PS3.PS3Connected) {
          PS3.setLedOff();
          PS3.setLedOn(LED4);
        }
      }
      if (PS3.getButtonClick(RIGHT)) {
        output += " - Right";
        if (PS3.PS3Connected) {
          PS3.setLedOff();
          PS3.setLedOn(LED1);
        }
      }
      if (PS3.getButtonClick(DOWN)) {
        output += " - Down";
        if (PS3.PS3Connected) {
          PS3.setLedOff();
          PS3.setLedOn(LED2);
        }
      }
      if (PS3.getButtonClick(LEFT)) {
        output += " - Left";
        if (PS3.PS3Connected) {
          PS3.setLedOff();
          PS3.setLedOn(LED3);
        }
      }

      if (PS3.getButtonClick(L1))
        output += " - L1";
      if (PS3.getButtonClick(L3))
        output += " - L3";
      if (PS3.getButtonClick(R1))
        output += " - R1";
      if (PS3.getButtonClick(R3))
        output += " - R3";

      if (PS3.getButtonClick(SELECT)) {
        output += " - Select";
      }
      if (PS3.getButtonClick(START))
        output += " - Start";

      if (output != "") {
        String string = "PS3 Controller" + output;
        Serial.println(string);
        if (SerialBT.connected)
          SerialBT.println(string);
      }
    }
    delay(10);
  }
}
