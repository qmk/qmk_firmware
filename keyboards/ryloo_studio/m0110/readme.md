# RYLOO STUDIO "HELLO" M0110

![RYLOO STUDIO "HELLO" M0110](https://i.imgur.com/CpKGhRl.jpeg)

* Keyboard Maintainer: [G14D](https://github.com/HumphreyKwok), [newtonapple](https://github.com/newtonapple)
* Hardware Supported: M0110 PCB
* Hardware Availability: [M0110](https://drop.com/buy/ryloo-studio-hello-m0110-mechanical-keyboard-kit)

Make example for this keyboard (after setting up your build environment):

    make ryloo_studio/m0110:default

Flashing example for this keyboard:

    make ryloo_studio/m0110:default:flash

Putting the Keyboard in Bootloader Mode:

The shipped PCB did not come with a reset button.  To put the PCB in bootloader mode: locate the 2 `RESET` pins in the back of the PCB and short them with a conductive wire or tweezer.

![Ryloo Studio M0110 PCB RESET pins location](https://i.imgur.com/QJWmpqF.jpeg)


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
