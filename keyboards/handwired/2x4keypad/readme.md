# 2x4keypad

![2x4keypad](http://jmcameron.net/2x5keypad-small.jpg)


This Keypad has 2 rows x 4 columns of keys. Derived from Jonathan Cameron's 2x5.
It has the top/default layer that has a few handy navigation keys as well as one dedicated key to cycle through
the layers. The second layer has some media keys. The third and fourth layers
are currently undefined (although I may use them for inserting accented French
characters). The keypad also includes three LEDs that show which layer is
active (no lit LEDs means the default layer).

Keyboard Maintainer: [Kuba Tyszko](https://github.com/kubatyszko)  

Hardware:
  * 3d-Printed enclosure, STL here: https://www.thingiverse.com/thing:4671269
  * Handwired
  * Uses a Teensy

Make example for this keyboard (after setting up your build environment):

    make handwired/2x4keyapd:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
