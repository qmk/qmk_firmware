# LZ ST with VIA support.

* Keyboard Maintainer: [MajorKoos](https://github.com/MajorKoos)
* Hardware Supported: LZ ST, atmega32
* There are stability issues with QMK versions > 0.10.54, perhaps related to VUSB and the additional endpoint added in 0.11?
* Compiled 10.54 version of the firmware along with the VIA JSON files is [here](https://github.com/MajorKoos/KBDParts/tree/master/Firmware/l3-qmk-10.54)

## Hardware information

Controller: Atmega32a

    PA  [0:7]   col[0:7]
    PB  [0:7]   col[8:15]
    PC  [0]     SCL
        [1]     SDA
        [2:6]   row[0:6]
    PD  [0]     USB D+- level shifter(high 3.3v, low 5v)
        [1]     PS2 pull-up for CLK
        [2]     CLK[D+]
        [3]     DATA[D-]
        [4:7]   col[16:19]

        signal direction : row -> col
        
        
## Building the firmware
Make example for this keyboard (after setting up your build environment):

    make leeku/lz_st:default


To place your keyboard into DFU mode either
*   Hold down the ` key while plugging in the USB
*   Hold down ` while issuing the RESET QMK keycode from your keyboard


Flashing example for this keyboard ([after setting up the bootloadHID flashing environment](https://docs.qmk.fm/#/flashing_bootloadhid))

    make leeku/lz_st:default:flash


To reset the PCB to [L3 and JigOn](https://github.com/MajorKoos/KBDParts/tree/master/Firmware) put your PCB into DFU mode and run

    bootloadhid_l3.exe -r l3.hex


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
