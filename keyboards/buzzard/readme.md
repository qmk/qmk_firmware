# Buzzard

![Buzzard Keyboard](https://raw.githubusercontent.com/crehmann/Buzzard/main/Pictures/build_guide_final.jpg)

Buzzard is a 40 keys ergonomic split keyboard. The layout is inspired by the [Architeuthis dux](https://github.com/tapioki/cephalopoda/tree/main/Architeuthis%20dux) with pinky, ring, index, and inner columns splayed at 15, 5, 0, -5, -5 degrees. However, it as two additional pinky keys and a modified thumb cluster.

* Keyboard Maintainer: [crehmann](https://github.com/crehmann)  
* Hardware Supported: Pro Micro 5V/16MHz and compatible.
* Hardware Availability: https://github.com/crehmann/Buzzard

## Some Features:

- Integrated TrackPoint reset circuit and two possible positions to mount a TrackPoint to the bottom of the PCB. Either between the two inner columns or between the index and middle finger columns
- Mounting option for a linear actuator ([HapticBuzz from pimoroni](https://shop.pimoroni.com/products/drv2605l-linear-actuator-haptic-breakout))
- I2C interface for an OLED display
- Wireless Ready (however, without TrackPoint / linear actuator support):
  - Battery switch / connector
  - Option to use a battery friendly Sharp memory display instead of an OLED display
- Choc-spaced

## Building the Firmware

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb buzzard -km  default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

A build guide for the Buzzard keyboard can be found at [https://github.com/crehmann/Buzzard](https://github.com/crehmann/Buzzard)