# Model H - A USB capable PCB for the IBM Model M keyboard

![modelh](https://i.imgur.com/4ymGdkM.jpg)

This conversion kit allows you to replace your IBM Model M's original internal controller board with a modern USB board. This aims to match the footprint of the original controller and plugs into the original keyboard matrix, but exposes a USB port through the original SDL connector.

* Keyboard Maintainer: [John Hawthorn](https://github.com/jhawthorn)
* Hardware Supported: IBM Model M
* Hardware Availability: [www.modelh.club](www.modelh.club)
* How to [build your own controller](https://github.com/jberclaz/modelh)

Make example for this keyboard (after setting up your build environment):

    make ibm/model_m/modelh:default

Flashing example for this keyboard:

    make ibm/model_m/modelh:default:flash

For IBM Wheelwriter 10/15/1000 modules (ISO), you can try the `wheelwriter_1x_iso` keymap:

    make ibm/model_m/modelh:wheelwriter_1x_iso

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
