# EM.8

The Ergonomic Modified 8 is a tented ergonomic keyboard and the successor to the EM.7, designed by Syryan and Lx3.The default PCB supports hotswap and the layout options are limited to split or regular backpsace, as well as regular or stepped caps lock.

* Keyboard maintainer: [ebastler](https://github.com/ebastler)
* Hardware supported: Lin EM.8
* Hardware availability: Groupbuy. More infos on [the Linworks Discord](https://discord.gg/UC8gTdVnsj)

Make example for this keyboard (after setting up your build environment):

    make linworks/em8:default

Flash example for this keyboard:

    make linworks/em8:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).


## How to enter the bootloader
* **Bootmagic reset**: Hold down the key `ESC` key and plug in the keyboard (Top left most switch). On older firmware revisions, `~` (top left most switch of the alpha cluster) may be needed instead.
* **Physical reset button**: Briefly press the button on the back of the PCB