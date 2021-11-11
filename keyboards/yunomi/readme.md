# yunomi

![yunomi](https://raw.githubusercontent.com/google/mozc-devices/master/mozc-yunomi/images/device.jpg)

![yunomi-bottom](https://i.imgur.com/HXzKYRY.jpg)

*A QMK port of the mozc-yunomi firmware. The [mozc-yunomi](https://github.com/google/mozc-devices/tree/master/mozc-yunomi) is an open-source keyboard by Google.*

* Keyboard Maintainer: [Austin Wang](https://github.com/Dafondo)
* Hardware Supported: [mozc-yunomi](https://github.com/google/mozc-devices/tree/master/mozc-yunomi)
* Hardware Availability: [mozc-yunomi](https://github.com/google/mozc-devices/tree/master/mozc-yunomi)

Make example for this keyboard (after setting up your build environment):

    make yunomi:default

Flashing example for this keyboard:

    make yunomi:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader
Enter the bootloader by briefly bridging the ground and reset pins on the bottom of the base PCB. If you're using the Arduino Leonardo bootloader, you may need to quickly bridge two times.
