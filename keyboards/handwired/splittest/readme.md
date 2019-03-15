Split Tester
============

A two-switch tester built using two Pro Micros, mainly intended to test RGB on split keyboards. Seen here: https://www.instagram.com/p/BvCPNzynwrV/

Keyboard Maintainer: [Bakingpy/nooges](https://github.com/nooges)  
Hardware Supported: Pro Micro   

Make example for this keyboard (after setting up your build environment):

    make handwired/splittest:default

Example of flashing this keyboard:

    make handwired/splittest:default:avrdude

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

Wiring
------
- Add switches to both Pro Micros across B3 and B6 pins
- Add pull-up resistor to left side between VCC and F6
- Add pull-down resistors to right side between GND and F6
- Connect the following pins on both sides together: D0, D1, GND, VCC
- Add I2C 4.7kOhm resistors between D0 and VCC, and D1 and VCC
- Wire Di of RGB strip for each half to D2
