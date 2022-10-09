## Droxx's ANSI style keymap for the KBD67 REV 2 PCB

* An ANSI keymap layout made by Alex for the KBD67 Rev 2
* This keymap features two layers using basic Fn alternate keys on the second layer as well as lighting control

![KBD67Rev2 Layout](https://i.imgur.com/DPSMhIX.png)

### Layer 0 (_DRXXMAIN)

The base QWERTY layer

* Basic qwerty key layout with nothing other than an Fn key
* Fn on the bottom row activates layer 1

### Layer 1 (_DRXXFN)

The function layer

* Backspace will trigger KC_DEL until I find the KC_HOME key less useful.
* Pressing T will toggle the keyboard underglow feature on and off.
* Keys Q and E are used to change the underglow style of the keyboard.
* Keys W and S modify the brightness of the underglow.
* Keys A and D change the speed of the LED RGB animation.

~~When Fn is held on layer 0, the arrow keys become a control surface for the LED baclighting~~
~~The up arrow is used to cycle backlight modes, down arrow for toggling the backlight on or off,~~
~~and the right and left for increasing and decreasing the brightness respectively.~~[^note]
* X is used to disable the GUI key and C is used to enable the GUI key.

[^note]: I don't have in-switch LEDs installed?
