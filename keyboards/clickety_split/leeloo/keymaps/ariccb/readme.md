# Clickety Split | Leeloo

![Leeloo](https://cdn.shopify.com/s/files/1/0599/3460/5491/files/Leeloo-rev1.0-w.jpg?v=1646798726)

Keyboard Designer: [clicketysplit.ca](https://clicketysplit.ca)
GitHub: [ClicketySplit](https://github.com/ClicketySplit)
Hardware Supported: Pro Micro, Elite-C, nice!nano v2

Albeit, there is no doubt where Leeloo's heritage is derived from—Lily58, and Corne.  It is not a copy-paste-modify implementation.

Leeloo has been designed from scratch; everything from the schematic to its PCB footprints, and column stagger. There are some subtle differences that may not be apparent; however, its subtle changes enable an interesting future.

Features:
* 4x6x5m Split Keyboard
* Support for MX/Box or Low Profile Choc switches.
* 90% of the switches are socketed; with the exception to the rotary encoder positions—6 positions require soldering.
* Support for 128x32 OLED Displays.
* The option to select one of three positions for an EC11 rotary encoder on each half.
* Support for Alps Alpine Micro Switch
* Support for 3.7v 301230 LiPo Battery

# Building Your Firmware
QMK Firmware: [Quantum Mechanical Keyboard Firmware](https://docs.qmk.fm/#/)
Setup: [Setting Up Your QMK Environment](https://docs.qmk.fm/#/newbs_getting_started)
Customization: [Building Your First Firmware](https://docs.qmk.fm/#/newbs_building_firmware)
Flashing Firmware: [Flashing Your Keyboard](https://docs.qmk.fm/#/newbs_flashing)

Build commands for the default keymap of Leeloo with Pro Micros:

    qmk flash -kb clickety_split/leeloo/rev1 -km default -bl avrdude-split-left
    qmk flash -kb clickety_split/leeloo/rev1 -km default -bl avrdude-split-right


Build commands for the default keymap of Leeloo with Elite-Cs:

    * Open rules.mk and edit the following lines:
        * Add a '#' in front of: BOOTLOADER = caterina
        * Remove the '#' in front of: #BOOTLOADER = atmel-dfu
    * Save rules.mk

    qmk flash -kb clickety_split/leeloo/rev1 -km default -bl dfu-split-left
    qmk flash -kb clickety_split/leeloo/rev1 -km default -bl dfu-split-right


# Support
If you have any questions with regards to Leeloo, please [Contact Us](https://clicketysplit.ca/pages/contact-us).

Clickety Split
For the love of split keyboards.
