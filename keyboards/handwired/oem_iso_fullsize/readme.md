# oem_iso_fullsize

![top view](https://i.imgur.com/Pm5Vz1P.jpg)

I handwired a Gamdias 7 Colors that had a dead PCB and manage to revive it with a teensy

* Keyboard Maintainer: [Andres Teare](https://github.com/andresteare)
* Hardware Supported: Teensy++ 2.0
* Hardware Availability: got the teensy from aliexpress
Make example for this keyboard (after setting up your build environment):

    make handwired/oem_iso_fullsize:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

I didn't manage to make backlighting to work properly, because it looks like I need a LED driver, but if you have this keyboard and already have an LED driver, here are the respective resistor you need to wire to the teensy 
*Row 0, resistor R132, Pin A1
*Row 1, R131, Pin B5
*Row 2, R130, Pin E4
*Row 3, R129, Pin A2
*Row 4, R128, Pin E5
*Row 5, R127, Pin A7

These line are specifically to my pinout so it's probably not essencial for you
#define DIODE_DIRECTION ROW2COL
#define LED_CAPS_LOCK_PIN C7
#define LED_SCROLL_LOCK_PIN A3
#define LED_NUM_LOCK_PIN C6
#define BACKLIGHT_PINS { B5, E5, E4, A7, A1, A2 }
#define BACKLIGHT_LEVELS 1