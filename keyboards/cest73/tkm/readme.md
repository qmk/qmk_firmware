# Ten Key Mirrored - 2021

![TKM-2021](https://imgur.com/AlvRk1zh.jpg)

Another take on left side numpad and this time mirrored too for the ever more spacious mouse playground.

* Keyboard Maintainer: cest73 (aka fire-h0und)
* Hardware Supported: TKM-2021 (multiple layouts and switch options including ALPS, ISO and BAE)
* Hardware Availability: https://geekhack.org/index.php?topic=110499


Make example for this keyboard (after setting up your build environment):

    qmk compile -kb cest73/tkm -km default

As the board uses Teensy 2.0 as a daughter board, to bring the board into flash mode is it sufficient to press the button present on the Teensy.

[TKM-2021 PCB](https://geekhack.org/index.php?action=dlattach;topic=110499.0;attach=268641;image)

Despite many hours gazing over the schematics there was a nasty error on the first batch: namely the 6 and 7 columns got swapped in the design process. Luckily it was trivial to fix in the firmware section (see the comments in the layout file(s)).

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
