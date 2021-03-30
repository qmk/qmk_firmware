# eek!

![eek](https://i.imgur.com/34O3xKWl.jpg)

The eek! is a 36 key per key RGB keyboard with a 90 degree split layout suited for travel and typing close to the body. It uses a Pro Micro or an Elite C and can be soldered low profile using castilated pads. The PCB can be flipped so that the silk is on top and the USB plugin can face to the right or left. The keyboard is compatible with MX, Alps, and Choc style switches. It can use SMD or through hole diodes. The per key RGB LEDs used in the build are the SK6812 Mini E (these can also be flipped). The eek! can be used without a case if you choose for a very low profile keyboard.

When flashing the eek! with the bat side up follow the second example below and use: make eek/silk_up:default

![eek_bat](https://i.imgur.com/YrOqmft.jpeg)

* Keyboard Maintainer: [klackygears](https://github.com/klackygears)
* Hardware Supported: The eek! PCBs, Pro Micro supported, Low Profile Elite-C supported
* Hardware Availability: [Case Data & firmware](https://github.com/klackygears/eek_doc)

Make example for this keyboard (after setting up your build environment):

    make eek:default
    make eek/silk_up:default

Flashing example for this keyboard:

    make eek:default:flash
    make eek/silk_up:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
