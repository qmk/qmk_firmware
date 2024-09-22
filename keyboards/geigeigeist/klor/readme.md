```text
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

# KLOR split keyboard

KLOR is 42 keys column-staggered split keyboard made by @geigeigeist. It supports a per key RGB matrix, encoders, OLED displays, haptic feedback, audio, a Pixart Paw3204 trackball and four different layouts, through brake off parts.
It's schematics are based on the Sofle, while the layout is based on the Yacc46.

Make example for this keyboard (after setting up your build environment):

```text
make geigeigeist/klor/<layout>:default
```

where `<layout>` is one of `polydactyl`, `konrad`, `yubitsume`, `saegewerk`

Flashing example for this keyboard:

```text
make geigeigeist/klor/<layout>:default:flash
```

Note: This code is a modernized take on @geigeigeist's original KLOR code. The original is not currently compatible with modern QMK. @geigeigeist's repo can be found [here](https://github.com/GEIGEIGEIST/qmk-config-klor)

Improvements

- Put as much configuration as possible in `.json` files to align with future QMK Firmware objectives
- KLOR is now Pro-Micro RP2040 native as there are many cost-effective and easy to obtain variants available and eliminates firmware size constraints
- Only has RGB Matrix

## Bootloader

Enter the bootloader in two ways:

- **Keycode in layout**: Press the key mapped to `QK_BOOTLOADER` if it is configured.
- **Physical reset button**: Quick double-tap on the reset button soldered on the PCB.
