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
# KLOR split keyboard

KLOR is 42 keys column-staggered split keyboard made by @geigeigeist. It supports a per key RGB matrix, encoders, OLED displays, haptic feedback, audio, a Pixart Paw3204 trackball and four different layouts, through brake off parts.
It's schematics are based on the Sofle, while the layout is based on the Yacc46.

You can use this command to compile the firmware
`qmk compile -kb klor -km default`

and this command if you want to compile the firmware for a RP2040 based MCU
`qmk compile -kb klor/2040 -km default`