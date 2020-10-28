# Little Alby

Little Alby is a keyboard library using QMK used to create Arduino based keyboards.

## Keyboard Layouts

[Mute:](keyboards/littlealby/mute)
A single button layout that can be used as a mute audio keyboard shortcut for popular video conferencing programs e.g. [Zoom](keyboards/littlealby/mute/keymaps/zoom/readme.md), [Microsoft teams](keyboards/littlealby/mute/keymaps/ms_teams/readme.md), [Google meet](keyboards/littlealby/mute/keymaps/g_meet/readme.md) 


## Arduino Micro pinout
![ARDUINO MICRO pinout](https://content.arduino.cc/assets/Pinout-Micro_latest.png)

Keyboard Maintainer: [albybarber](https://github.com/albybarber)

Keyboard Maintainers spirit guide : [Olivia](https://github.com/olivia)

Hardware:
* [ARDUINO MICRO - 5v](https://store.arduino.cc/usa/arduino-micro) or [Pro Micro - 5V/16MHz](https://www.sparkfun.com/products/12640)

## Building Code
Make example for this keyboard (after setting up your build environment):

    make littlealby/mute:default
    
    // Builds for specific programs 
    make littlealby/mute:zoom
    make littlealby/mute:ms_teams
    make littlealby/mute:g_meet

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Credits
+ [2% Milk by spaceman - heavly inspired by](https://github.com/qmk/qmk_firmware/tree/master/keyboards/spaceman/2_milk)
