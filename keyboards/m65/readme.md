# M65

![M65](https://i.imgur.com/gXuecush.jpg)

A  (13x5) ortholinear keyboard that can be hand wired or using a pcb.

* Keyboard Maintainer: [Alin Elena](https://gitlab.com/drFaustroll)
* Hardware Supported: custom pcb [see](https://gitlab.com/drFaustroll/m65) STM/APM32F103C8T6, aka Black Pill
* Hardware Availability: [custom how to](https://alin.elena.space/blog/keeblego/)


Make example for this keyboard (after setting up your build environment):

    make m65/rev1:default

Flashing example for this keyboard:

    make m65/rev1:default:flash

To enter flashing mode, press Lower+Raise+R.

Alternative boards, one can use weact GD32F303CCT6 which is pin compatible by making the firmware

   make m65/rev2:default

Flashing example for this keyboard:

    make m65/rev2:default:flash

To enter flashing mode, press KEY button and power the keyboard.

uk and dk variants are in place too if one pleases.


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
