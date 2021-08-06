# Lime Keyboard

![LimeKeyboard version 1](https://www.simonepellegrino.com/)

Lime is 6×4+6 keys column-staggered split keyboard. Based on Sofle with a hint of Lily58, Corne and Helix keyboards.

Build guide and a build log not available yet

* Keyboard Maintainer: [HellSingCoder](https://www.simonepellegrino.com/) [GitHub: HellSingCoder](https://github.com/HellSingCoder)  
* Hardware Supported: LimeKeyboard PCB, ProMicro  
* Hardware Availability: [PCB & Case Data](https://github.com/HellSingCoder/LimeKeyboard)

Make example for this keyboard (after setting up your build environment):

    make lime:default
    
        or
        
    qmk compile -kb lime -km default
    qmk flash -kb lime -km default

Flash the default keymap: 

    make lime:default:avrdude

Press reset button on he keyboard when asked.

Disconnect the first half, connect the second one and repeat the process.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
