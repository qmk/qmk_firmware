# Yugo-M

![Yugo-M](https://raw.githubusercontent.com/tomic1785/Yugo-M-controller-project/master/Pictures/rev_09b.jpg)

A drop-in replacement controller PCB for IBM Model M keyboards, based on the STM32 MCU. [More info on the Yugo-M project repository](https://github.com/tomic1785/Yugo-M-controller-project)

* Keyboard Maintainer: [Nidzo Tomic](https://github.com/tomic1785)
* Hardware Supported: Yugo-M PCB
    * Rev 0.9b
    * Rev 1.1b
* Hardware Availability: [Check out the project repository](https://github.com/tomic1785/Yugo-M-controller-project)

Make example for this keyboard (after setting up your build environment):

    make ibm/model_m/yugo_m:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).



Note regarding 2022 matrix update:

The original author's firmware did not make several lesser-used membrane/matrix positions available to the controller. These are useful for JIS users and/or if you simply want to create a more unique layout. I've added all of the unused membrane positions to the firmware, except for an extremely seldom used one that sits in the left side of the space bar on some later membranes (I would have added it if I knew its matrix position, but I haven't mapped that out yet). The default mappings for these additional keys follow JIS conventions, except for the extra key on the bottom right corner of the numpad (lower half of vertical 2u Enter), which I've mapped to the LGUI key a.k.a. left Windows/Command key for now. Remap as you wish!

- an_achronism, February 2022
