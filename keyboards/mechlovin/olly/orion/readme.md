# Olly Orion

![Olly Orion](https://i.imgur.com/midAJSplh.jpeg)

The Olly Orion is designed as a drop-in replacement PCB for the Duck Orion V2; V2.5 and V3 TKL custom keyboards. 

* Keyboard Maintainer: [Mechlovin' Studio](https://github.com/mechlovin)
* Hardware Supported: Olly Orion, APM32F103.
* Hardware Availability: [Mechlovin' Studio](https://mechlovin.studio), [GB](https://www.reddit.com/r/mechmarket/comments/z1i5g3/gb_mechlovin_olly_orion_octagon_duck_orion/).

Make example for this keyboard (after setting up your build environment):

    make mechlovin/olly/orion:default

Flashing example for this keyboard:

    make mechlovin/olly/orion/default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

**Reset Key:** 3 ways to put the IF87.5 into bootloader:
- By keycode: Tap RESET keycode.
- By bootmagic: hold ESC key while plugging in.
- By hardware: Push reset button on bottom of the PCB while the PCB is plugged in.