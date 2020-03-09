# Kira 80/TKL

![kira80](https://i.imgur.com/QnGKnaml.jpg)
![kira80pcb](https://i.imgur.com/wrEZhg5l.jpg)

Custom TKL keyboard designed and made by Thesiscamper and EVE

* Keyboard Maintainer: [elmo-space](https://github.com/elmo-space)
* Hardware Supported: Kira 80 PCB made by EVE
* Hardware Availability: limited [Group Buy](https://geekhack.org/index.php?topic=96381.0) finished

Make example for this keyboard (after setting up your build environment):

    make kira80:default

Flashing example for this keyboard ([after setting up the bootloadHID flashing environment](https://docs.qmk.fm/#/flashing_bootloadhid))

    make kira80:default:flash

**Reset Key:** Hold down the key located at `K102`, commonly programmed as 'Pause' while plugging in the keyboard.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Hardware Information

Controller: ATmega32A

### Pinout:

|Pin|Use||Pin|Use
|-|-|-|-|-|
|A1|Column 0||B1|Row 0|
|A2|Column 1||B2|Row 1|
|A3|Column 2||B3|Row 2|
|A4|Column 3||B5|Row 3|
|A5|Column 4||B6|Row 4|
|A6|Column 5||B7|Row 5|
|A7|Column 6||B0|Row 6|
|C7|Column 7|
|C6|Column 8||D1|Capslock LED|
|C5|Column 9||D6|Scrolllock LED|
|C4|Column 10||D4|Backlight|
|C3|Column 11|
|A0|Column 12||D2|USB D+|
|C2|Column 13||D3|USB D-|
|D7|Column 14|

### Layout matrix:

![matrix](https://i.imgur.com/FqjTNQS.png)
