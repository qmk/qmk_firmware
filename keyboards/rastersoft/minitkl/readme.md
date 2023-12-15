# MiniTKL

![MiniTKL](https://images2.imgbox.com/53/28/YxGS3GJT_o.png)

A compact TenKeyLess keyboard.

* Keyboard maintainer: [Sergio Costas](https://github.com/rastersoft)
* Hardware supported: ISO version. ANSI will be added in a future.
* Hardware Availability: it's a build-yourself keyboard.

Make example for this keyboard (after setting up your build environment):

    make rastersoft/minitkl:default

Flashing example for this keyboard:

    make rastersoft/minitkl:default:flash

![PCB](https://images2.imgbox.com/84/b3/GnPfMO94_o.png)

![Result](https://images2.imgbox.com/78/90/rM5iLSdx_o.jpg)

The default layout is ISO. Replace 'default' with 'ansi' for ANSI layout, or 'hybrid' for the ANSI/ISO hybrid layout.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead

More info: [gitlab.com/rastersoft/full-ten-keyless](https://gitlab.com/rastersoft/full-ten-keyless)
