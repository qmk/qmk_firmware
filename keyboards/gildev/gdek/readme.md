# GDEK

![GDEK](https://i.imgur.com/7DprpLD.jpeg)

![GDEK Default Layout](https://i.imgur.com/aqDqtBy.png)

*A simple but complete split ergo, great for beginners!*

* Keyboard Maintainer: [GilDev](https://github.com/GilDev)
* PCB sources: https://github.com/GilDev/gdek
* More information and documentation: https://gildev.dev/gdek

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb gildev/gdek -km default

Flashing example for this keyboard:

    qmk flash -kb gildev/gdek -km default

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at the top left for the left half or top right for the right half and plug in the keyboard in the same half.
* **Physical reset button**: Short the B pads on the back of the PCB and briefly short the R pads or replug the keyboard. Alternatively, quickly short the R pads twice while the keyboard is plugged in.
* **Keycode in layout**: Hold the key mapped to `QK_REBOOT` on the plugged in half.
