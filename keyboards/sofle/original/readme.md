# Sofle Keyboard

![SofleKeyboard version 1](https://raw.githubusercontent.com/josefadamcik/SofleKeyboard/master/Images/IMG_20200126_114622.jpg)

Sofle is 6×4+5 keys column-staggered split keyboard. Based on Lily58, Corne and Helix keyboards.

More details about the keyboard on my blog: [Let me introduce you SofleKeyboard - a split keyboard based on Lily58 and Crkbd](https://josef-adamcik.cz/electronics/let-me-introduce-you-sofle-keyboard-split-keyboard-based-on-lily58.html)

The build guide is available on Github. There is a [common section](https://josefadamcik.github.io/SofleKeyboard/build_guide.html) and a section specific to the [original variant](https://josefadamcik.github.io/SofleKeyboard/build_guide.html).

An (outdated) build log is available here: [SofleKeyboard build log/guide](https://josef-adamcik.cz/electronics/soflekeyboard-build-log-and-build-guide.html)

* Keyboard Maintainer: [Josef Adamcik](https://josef-adamcik.cz) [Twitter:@josefadamcik](https://twitter.com/josefadamcik)  
* Hardware Supported: SofleKeyboard PCB, ProMicro  
* Hardware Availability: [PCB & Case Data](https://github.com/josefadamcik/SofleKeyboard)

Compilation example for this keyboard (after setting up your build environment):

    qmk compile -kb sofle/original -km default

Flash the default keymap: 

    qmk flash -kb sofle/original -km default

Press reset button on the keyboard when asked.

Disconnect the first half, connect the second one and repeat the process.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
