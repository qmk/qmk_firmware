

# Ploopy Trackball Nano

![Ploopyco Trackball Nano](https://www.ploopy.co/uploads/b/113cb4122f867acc306a72a2741c5237a9b1d0db13abfe4e8e394cd466c4a311/_MG_7710_1614037372.jpg)

It's a DIY, QMK Powered Trackball...Nano!

* Maintainer: [PloopyCo](https://github.com/ploopyco)
* Key contributors: [Drashna Jael're](https://github.com/drashna/), [Germ](https://github.com/germ/)
* Hardware Supported: ATMega32u4 16MHz(5v)  
* Hardware Availability: [Store](https://ploopy.co/nano-trackball), [GitHub](https://github.com/ploopyco/nano-trackball)

Make example for this trackball (after setting up your build environment):

    make ploopyco/trackball_nano/rev1_001:default:flash
    make ploopyco/trackball_nano/rev1_001:via:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Hardware Reset Button

The Ploopy Nano has a handy bootloader reset mechanism: two via pins on the board, designated by the reference designator `MCU.J.X BOOTLOADER`. If you stick an uninsulated paperclip or a pair of metal tweezers into both holes and plug in the Nano, it will start in bootloader mode.

## Revisions

Occasionally, new revisions of the PCB will be released. Every board comes with a designator that looks something like `R1.001`.

Match the firmware that you flash onto the board with the designator on the board.

# Customzing your Ploopy Nano Trackball

You can change the DPI/CPI or speed of the trackball by calling `adns_set_cpi` at any time. Additionally, there is a `DPI_CONFIG` macro that will cycle through an array of options for the DPI.  This is set to 375, 750, and 1375, but can be changed. 750 is the default. 

To configure/set your own array, there are two defines to use, `PLOOPY_DPI_OPTIONS` to set the array, and `PLOOPY_DPI_DEFAULT`. 

```c
#define PLOOPY_DPI_OPTIONS { CPI375, CPI750, CPI1375}
#define PLOOPY_DPI_DEFAULT 1
```

The `PLOOPY_DPI_OPTIONS` array sets the values that you want to be able to cycle through, and the order they are in.  The "default" define lets the firmware know which of these options is the default and should be loaded by default.

The `DPI_CONFIG` macro will cycle through the values in the array, each time you hit it.  It stores this value in persistent memory, so it will load it the next time the device powers up.

## Fuse settings

When flashing the bootloader, use the following fuse settings:

| Fuse     | Setting     |
|----------|-------------|
| Low      | `0x5E`      |
| High     | `0x99`      |
| Extended | `0xC3`      |