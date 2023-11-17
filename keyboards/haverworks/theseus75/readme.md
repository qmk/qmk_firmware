# haverworks Theseus75
![Theseus Render](https://i.imgur.com/yzCfVSth.png)

The Theseus 75 is a 75% row-stagger split keyboard with a macro column + encoder on both sides. It features one USB-C dual role port per side, and USB hubs, that allow the unused port to turn into a USB-C 2.0 High-Speed host port to connect flash drives, cell phones and similar. Up to 5V 1.5A current are offered, depending on negotiations with the host.

* Keyboard Maintainer: [ebastler](https://github.com/ebastler)
* Hardware Supported: Haverworks Theseus75 r1 PCBs (Hotswap and solder)
* Hardware Availability: Groupbuy

How to enter the Bootloader:
* Follow instructions on the PCB (Hold Boot/Flash button for approx. 1s)
* Bootmagic reset, left half: Hold the first key to the right of the encoder while plugging the board in
* Bootmagic reset, right half: Hold the first key to the left of the encoder while plugging the board in

Make example for this keyboard (after setting up your build environment):

    qmk compile haverworks/theseus75:default

Flash example for this keyboard (after setting up your build environment):

    qmk flash haverworks/theseus75:default


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).