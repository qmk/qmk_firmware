# MutePad

![MutePad Repo](https://github.com/JoshwJB/MutePad)

*A short description of the keyboard/project*

* Keyboard Maintainer: [JoshwJB](https://github.com/JoshwJB)
* Hardware Supported: ProMicro
* Hardware Availability: [MutePad Repo](https://github.com/JoshwJB/MutePad)

Make example for this keyboard (after setting up your build environment):

    make mutepad:default

Flashing example for this keyboard:

    make mutepad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly short the ground and reset on the ProMicro
