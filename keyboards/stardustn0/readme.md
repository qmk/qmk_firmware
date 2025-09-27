# stardustn0

![stardustn0](https://imgur.com/a/OtCh0fQ)

This project is a custom-built split ergonomic mechanical keyboard, using two Raspberry Pi Pico microcontrollers.

* Keyboard Maintainer: [navidyt](https://github.com/navidyt)
* Hardware SupportedRaspberry Pi Pico, MX switches, Gateron hot-swap sockets, 1N4148 diodes, generic USB-C breakout board

Make example for this keyboard (after setting up your build environment):

    make stardustn0:default

Flashing example for this keyboard:

    make stardustn0:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Entering the bootloader:

* **Physical reset button**: Briefly press the  reset button on the pico while connecting it to the USB-C to enter the flash mode



This keyboard is using a custom PCB, which the design files will be provided in my github.
However, it might need some minor tweaking to suit your version of the project.

The case is 3D printed, and the files will be provided in my github.
The switch cutouts are slightly larger than the MX standards, as the 3D printer I had was printing them slightly smaller than expected, so to address that issue the cutouts are larger than usual.

To connect the two halves, it is using a USB-C to USB-C cable.
The connectors on the PCB design use a USB-C breakout board that I could get my hands on. Change the pinout according to your own parts.

I used a single M3 screw and an M3 nut to assemble the keyboard and the PCB. This was put on the center screw hole.
To connect the two halves of the case, I used M3 screws. I didn’t use threaded inserts on the lower case. However, I encourage you to do so (might need minor tweaking on the 3D design).

This keyboard is VIA supported.
The keymap is fine, however, I encourage you to go to the VIA website and update it yourself to your favorite layout.
The VIA file is provided in my github, and you can use it by enabling the design tab and dragging the VIA file into the design tab.
After pairing the keyboard, it should do the trick.
(I will be adding the keyboard to VIA repository for auto detection in the future.)

Note: there is this issue I’m encountering while using the keyboard, where after a system reboot it won’t work unless you disconnect and connect it again to the system.
I couldn’t find any solution to this, as I think it is a QMK-related problem.
