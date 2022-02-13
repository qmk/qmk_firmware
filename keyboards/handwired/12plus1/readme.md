# 12plus 1 (Macropad)
Created 2021 by Sono-Gomorrha using kbfirmware.com and https://noroadsleft.github.io/kbf_qmk_converter/
This is essentially an interpretation of the macropad designed by Ryan Bates as presented here: http://www.retrobuiltgames.com/the-build-page/macro-keyboard-v2-0
As I did however wanted to make somthing with QMK and high shipping was in the way of ordering his PCB to Europe, I basically took the keylayout, designed a 3D printed case around it and handwired the whole thing together

There are two keymaps here. The default one serves as an example with som basics. The other one labeled drg is a variation I made for the game Deep Rock Galactic, essentially adding a layer for the game, mostly consisting of text macros to save time on typing.

* Keyboard Maintainer: [Sono-Gomorrha](https://github.com/Sono-Gomorrha)
* Hardware Supported: all the usual micro controllers, e.g. Pro Micro ATmega32U4, Teensy 2.0 
* Hardware Availability: [see 12plus1-Macropad for STL files](https://github.com/Sono-Gomorrha/12plus1-Macropad)

Example for this keyboard (after setting up your build environment):

    qmk compile -kb handwired/12plus1 -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
