# ake160886
Big Keyboard

First thing you want to do is take off the case, unscrew the daughterboard, and remove the ribbon of wires connecting the daughterboard from the main PCB.
The daughterboard isn't used from this point on. All pictures are of the top part of the main PCB that was hidden by the daughterboard and the teensy.

Jumpers on the motherboard
Pin0 is on the far left. I don't know what the last 4 holes on the right are used for.

![Jumpers on the motherboard](https://i.imgur.com/iwAAsR8.jpg)

Pin 12 (grey wire) should actually be soldered in to the VCC hole opposite the USB connector. Also, pins 13-15 are just for the built in LEDs, so you'll want to go through a 220 ohm or 470 ohm resistor so they don't burn out the corresponding diodes.

![Pinout of Teensy](https://i.imgur.com/eO2G1nD.png)

![Teensy as seen from GND side](https://i.imgur.com/4Dmncby.jpg)

![Teensy as seen from VCC side](https://i.imgur.com/m8e5wii.jpg)

https://imgur.com/gallery/vZbpR2K

From there it's a matter of flashing QMK on to the teensy and you're good to go!
