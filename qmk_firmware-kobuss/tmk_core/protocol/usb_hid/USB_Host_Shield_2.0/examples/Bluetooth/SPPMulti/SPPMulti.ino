/*
 Example sketch for the RFCOMM/SPP Bluetooth library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or
 send me an e-mail:  kristianl@tkjelectronics.com
 */

#include <SPP.h>
#include <usbhub.h>

// Satisfy IDE, which only needs to see the include statment in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so

const uint8_t length = 2; // Set the number of instances here
SPP *SerialBT[length]; // We will use this pointer to store the instances, you can easily make it larger if you like, but it will use a lot of RAM!

bool firstMessage[length] = { true }; // Set all to true

void setup() {
  for (uint8_t i = 0; i < length; i++)
    SerialBT[i] = new SPP(&Btd); // This will set the name to the default: "Arduino" and the pin to "0000" for all connections

  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // Halt
  }
  Serial.print(F("\r\nSPP Bluetooth Library Started"));
}

void loop() {
  Usb.Task(); // The SPP data is actually not send until this is called, one could call SerialBT.send() directly as well

  for (uint8_t i = 0; i < length; i++) {
    if (SerialBT[i]->connected) {
      if (firstMessage[i]) {
        firstMessage[i] = false;
        SerialBT[i]->println(F("Hello from Arduino")); // Send welcome message
      }
      if (SerialBT[i]->available())
        Serial.write(SerialBT[i]->read());
    }
    else
      firstMessage[i] = true;
  }

  // Set the connection you want to send to using the first character
  // For instance "0Hello World" would send "Hello World" to connection 0
  if (Serial.available()) {
    delay(10); // Wait for the rest of the data to arrive
    uint8_t id = Serial.read() - '0'; // Convert from ASCII
    if (id < length && SerialBT[id]->connected) { // Make sure that the id is valid and make sure that a device is actually connected
      while (Serial.available()) // Check if data is available
        SerialBT[id]->write(Serial.read()); // Send the data
    }
  }
}
