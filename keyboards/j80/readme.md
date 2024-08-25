# J80

JER PLANT - J80 (JER-A06) Round 2
The J80 is a OG Cherry style(no plate) custom 80% kit.
It is characterized by the fact that the hoisting PCB has no steel plate and can fully reflect the elasticity of the linear shaft. Tested by the buyer, its feel and typing sound are different from other custom keyboards and are satisfactory. It has a simple and elegant original cherry-like shape, the author's original intention is to start from the touching feel, let everyone have a comfortable tapping experience. The light stick module in the upper right corner is detachable, it could be switches (3 keys) or the light stick module. When using light stick module, PrtScr Scrolllock and Pause are achieved by pressing FN+ Insert / Home / Page Up.

* Keyboard Maintainer: [oeywil](https://github.com/oeywil)
* Hardware Supported: J80 PCB (atmega32a)
* Hardware Availability: [J80 R2 GB](https://geekhack.org/index.php?topic=101401.0)

Make example for this keyboard (after setting up your build environment):

    make j80:default

Flashing example for this keyboard:

    make j80:default:flash

**Reset Key**: Hold down the key located at *TOP RIGHT*, commonly programmed as *PAUSE* while plugging in the keyboard. The key definition for the reset key is k6D. Bootmagic Lite is enabled so holding down Escape while plugging in the keyboard will also jump to bootloader, after QMK is flashed.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
