

# Electronlab KLOR split keyboard

```
█         █    █            ▄▄▄▀▀▀▀▀▀▄▄▄        █▀▀▀▀▀▀▀▀▀▀█
█        █     █          ▄▀            ▀▄      █          █
█       █      █        ▄▀                ▀▄    █          █
█      █       █        █                  █    █          █
█     █        █       █                    █   █          █
█    █         █       █                    █   █▄▄▄▄▄▄▄▄▄▄█
█   █ █        █       █                    █   █      █
█  █   █       █        █                  █    █       █
█ █     █      █        ▀▄                ▄▀    █        █
██       █     █          ▀▄            ▄▀      █         █
█         █    █▄▄▄▄▄▄▄▄    ▀▀▀▄▄▄▄▄▄▀▀▀        █          █
```

KLOR is 42 keys column-staggered split keyboard originaly made by @geigeigeist and forked by Lefuneste83 from Electronlab. It supports a per key RGB matrix, encoders, OLED displays, haptic feedback, audio, a Pixart Paw3204 trackball and four different layouts, through brake off parts.
It's schematics are based on the Sofle, while the layout is based on the Yacc46.

* Keyboard Maintainer: [Lefuneste83](https://github.com/Lefuneste83)
* Hardware Supported: KLOR PCB from 1.3 onward
* Hardware Availability: https://github.com/Lefuneste83/KLOR/tree/main/PCB

Make example for this keyboard (after setting up your build environment):

    make electronlab/klor:default

Flashing example for this keyboard:

    make electronlab/klor:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,1) in the matrix for the left side and (4,1) in the matrix for the right side (usually the top left and top right) and plug in the keyboard half to USB
* **Physical reset button**: Briefly press the button on the side of the PCB. A rapid double press will resart the keyboard half in bootloader mode.
* **Keycode in layout**: Press the key mapped to `QK_BOOT`
