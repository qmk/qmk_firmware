# Mitosis

![Mitosis](https://i.imgur.com/JTzXTCD.jpg)

A wireless split compact keyboard.

Keyboard Maintainer: [@reversebias](https://github.com/reversebias)  
Hardware Supported: Mitosis PCB  
Hardware Availability: See the [Mitosis keyboard announcement and discussion](https://www.reddit.com/r/MechanicalKeyboards/comments/66588f/wireless_split_qmk_mitosis/)

Make example for this keyboard (after setting up your build environment):

    make mitosis:default

See [build environment setup](https://docs.qmk.fm/build_environment_setup.html) then the [make instructions](https://docs.qmk.fm/make_instructions.html) for more information.

## Notes

Some circuit board manufacturers including [DirtyPCBs](https://dirtypcbs.com/) and [PCBWay](https://www.pcbway.com/) offer a steeply discounted "prototyping" rate for a small quantity of identical circuit boards less than 100x100mm in size. The Mitosis was designed to take advantage of this, so that individuals might affordably manufacture their own without waiting for a group-buy.

These configuration files were based off the Atreus keyboard. It assumes a Pro Micro is being used, however retains the 'make upload' feature from the Atreus branch.

This keyboard uses a completely different 'matrix scan' system than most other keyboards supported by QMK. Here, QMK runs in a Pro Micro on a receiver module, and communicates only with an nRF51822 microcontroller module that in turn does wireless communication. The nRF51822 maintains a matrix of keystates received from the same microcontrollers on each of the keyboard halves. The matrix.c file contains the code to make the Pro Micro poll the external wireless microcontroller for the key matrix. As long as this file is not changed, all other QMK features are supported.

[Mitosis keyboard build log](https://imgur.com/a/mwTFj), including many photos and notes about the assembly process.

[Mitosis keyboard hardware design files](https://github.com/reversebias/mitosis-hardware), including PCB schematics and manufacturing files, parts list, and a laser-cutting template for the neoprene base.

[Mitosis keyboard wireless firmware](https://github.com/reversebias/mitosis) for the Nordic microcontrollers.
