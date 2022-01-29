# Tractyl Manuform (6x7) with a right side trackball

It's a Tractyl Manuform with an integrated thumb based trackball, using the pmw3360 optical sensor.

-   Keyboard Maintainer: [Drashna Jael're](https://github.com/drashna)
-   Hardware Supported: [Elite C (2x)](https://keeb.io/products/elite-c-low-profile-version-usb-c-pro-micro-replacement-atmega32u4), [PMW3360 Optical Sensor](https://www.tindie.com/products/jkicklighter/pmw3360-motion-sensor/)

Make example for this keyboard (after setting up your build environment):

    make handwired/tractyl_manuform/6x7_right/elite_c:default

Flashing example for this keyboard:

    make handwired/tractyl_manuform/6x7_right/elite_c:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

# Wiring

Figuring out the wiring was not simple for me as a newb, here is what I found works:

| PMW3360 Pin | Elite C Pin | Note        |
| ----------- | ----------- | ----------- |
| SC          | B1 (SLCK)   |             |
| MI (MISO)   | B3 (MISO)   |             |
| MO (MOSI)   | B2 (MOSI)   |             |
| SS          | B6          | configured by the PMW3360_CS_PIN parameter in config.h |
| GD          | GND         |             |
| VI          | VCC         |             |

The MT pin on the PMW3360 does not need to be hooked up.

The RS (Reset) pin on the PMW3360 can be connected to the reset pin on the Elite C if you have a reset button hooked up to the Elite C as well.

# Other considerations

Fitting all this on an Elite C doesn't leave room for much else. You may want to consider a WeAct Blackpill Controller, which has more pins and performance. If you want LEDs or large features like autocorrection you will want a more powerful controller than the Elite C.
