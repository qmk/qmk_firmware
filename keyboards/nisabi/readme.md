# NISABI

![NISABI](https://i.imgur.com/REPLACE_ME.png)

This document provides QMK-specific information for the NISABI split compact keyboard by Raiju Inc.

**Maintainer:** [RaijuInc](https://github.com/RaijuInc)

---

## Highlights

- Split keyboard with serial transport
- EEPROM-based handedness support (`EE_HANDS`)

---

## References

- Official manual: https://nisabi.raiju.jp/ (keymaps, notices)
- QMK keyboard definition: [keyboards/nisabi/keyboard.json](keyboards/nisabi/keyboard.json)
- Build and EEPROM settings: [keyboards/nisabi/config.h](keyboards/nisabi/config.h)

---

## Build

After setting up the QMK build environment, build the default keymap:

```bash
make nisabi:default
```

To build a different keymap, replace `default` with the keymap name.

---

## Flash

Enter the bootloader and flash the firmware. Examples:

```bash
make nisabi:default:flash
# or using qmk flash with a board-specific bootloader
qmk flash -kb nisabi -km default -bl avrdude-split-right
```

See the Bootloader section below for ways to enter the bootloader.

---

## Keymaps & Layout

Default keymaps are stored under `keyboards/nisabi/keymaps/`. Example keymaps are published on the product site: https://nisabi.raiju.jp/keymaps

Layout metadata (rows, columns, and matrix coordinates) is maintained in [keyboards/nisabi/keyboard.json](keyboards/nisabi/keyboard.json). Ensure every layout entry includes a `matrix` coordinate; missing or incorrect coordinates will shift key outputs.

---

## Bootloader

Ways to enter the bootloader:

- Hold the Bootmagic key assigned in `keyboard.json` while plugging in the keyboard
- Press the physical reset button or short the reset pads on the PCB
- Use the `QK_BOOT` keycode in your layout

Note: Right-hand Bootmagic row/column values must use global matrix indices (for this keyboard the right half maps to global rows `5`–`9`). Using a local-right index will generate a warning.

---

## EEPROM / EE_HANDS

Handedness is stored in EEPROM (`EE_HANDS`). `EE_HANDS` remains defined in `keyboards/nisabi/config.h`. To force handedness or reset EEPROM, follow the split keyboard EEPROM procedures in the QMK documentation.

---

## Troubleshooting

- If keys send the wrong keycodes, verify the `matrix` coordinates in [keyboards/nisabi/keyboard.json](keyboards/nisabi/keyboard.json) match the PCB wiring. A missing position in the layout will shift subsequent keys.
- If you see Bootmagic warnings about row ranges, convert the local-right row to the global row index and update `split.bootmagic.matrix` accordingly.

---

## Notices & Warranty

Refer to the official site for safety notices, warranty, and other product information: https://nisabi.raiju.jp/notice

---

## License

Firmware in this folder follows the repository license files at the project root (LICENSE, license_GPLv2.md, license_GPLv3.md).

---

For questions or bug reports, please open an issue on the GitHub repository.

