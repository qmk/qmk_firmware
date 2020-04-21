# 2x5keypad

![2x5keypad](http://jmcameron.net/2x5keypad-small.jpg)

This Keypad has 2 rows x 5 columns of keys. It has the top/default layer that
has a few handy navigation keys as well as one dedicated key to cycle through
the layers. The second layer has some media keys. The third and fourth layers
are currently undefined (although I may use them for inserting accented French
characters). The keypad also includes three LEDs that show which layer is
active (no lit LEDs means the default layer).

Keyboard Maintainer: [Jonathan Cameron](https://github.com/jmcameron)  

Hardware:
  * Key switch holes cut in blank piece of copper-clad project board
  * Uses Kailh Box White switches with relegendable keycaps
  * Chassis is three layers of wood
  * Handwired
  * Uses a Pro Micro
  * Includes a reset switch accessible by a hole on the bottom

Make example for this keyboard (after setting up your build environment):

    make handwired/2x5keyapd:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
