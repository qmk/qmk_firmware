Iris
====

A split ergo 4x6 keyboard with 3 or 4 thumb keys made and sold by Keebio. [More info at Keebio](https://keeb.io).

Keyboard Maintainer: [Bakingpy/nooges](https://github.com/nooges)  
Hardware Supported: Pro Micro, ATmega32u4  
Hardware Availability: [Keebio](https://keeb.io)  

Make example for this keyboard (after setting up your build environment):

    make keebio/iris/rev6:default

Example of flashing this keyboard:

    make keebio/iris/rev6:default:flash

See [build environment setup](https://docs.qmk.fm/#/newbs_getting_started) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

A build guide for this keyboard can be found here: [Iris Build Guide](https://docs.keeb.io/iris-rev6-build-guide)

## Iris Rev. 6 Notes

The Iris Rev. 6 and Rev. 6.1 PCBs are nearly identical and have the same firmware (`rev6`) pre-flashed to them that has VIA support enabled. However this stock firmware does not support for Lighting controls in VIA.

To enable Lighting controls in VIA, you will need the `rev6a` firmware. See [Enabling Iris Rev. 6 VIA RGB Controls](https://docs.keeb.io/iris-rev6-rgb-via) for more details.

Both the Rev. 6 and Rev. 6.1 PCBs are compatible with the `rev6a` firmware.
