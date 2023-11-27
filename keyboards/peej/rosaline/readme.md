# Rosaline

## Through-hole 40% keyboard PCB for 60% cases

![Rosaline Staggered](https://raw.githubusercontent.com/peej/rosaline-keyboard/a40d60e95ee69630db0ea53d97c59b9e5db4851f/images/pcb-staggered-render.jpg)

40% staggered or 4x15 ortholinear PCB for 60% tray mount cases with only through hole components.

* Keyboard Maintainer: [Paul James](https://github.com/peej)
* Hardware Supported: ATMEGA328p with vusb [PCB](https://github.com/peej/rosaline-keyboard)

Make example for this keyboard (after setting up your build environment):

    make peej/rosaline/staggered:default  # for staggered PCBs
    make peej/rosaline/ortho:default      # for ortholinear PCBs

## Bootloader

Use usbasploader in [hsgw's repository](https://github.com/hsgw/USBaspLoader/tree/plaid).

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
