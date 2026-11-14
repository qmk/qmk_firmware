# MonacoKeys MK60MX

60% MX keyboard PCB from [MonacoKeys](https://monacokeys.de) by [quark-works](https://github.com/quark-works), Bakeneko60 and GH60 compatible, with per-key RGB and underglow.

![monacokeys/mk60mx](https://monacokeys.de/cdn/shop/files/mk60mx-0.jpg)

* Keyboard Maintainer: [MonacoKeys](https://github.com/monacokeys)
* Hardware Supported: MK60MX (RP2040)
* Hardware Availability: [MonacoKeys](https://monacokeys.de/en/products/mk60mx-60-mechanical-keyboard-pcb)

Make example for this keyboard (after setting up your build environment):

    make monacokeys/mk60mx:default

Flashing example for this keyboard:

    make monacokeys/mk60mx:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Lighting

The 71 key LEDs and 16 underglow LEDs run as one RGB Matrix. Fn with Z, X, C and V toggles it, steps to the next effect, and lowers or raises brightness.

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard. This also clears the EEPROM.
* **Boot button**: Hold the BOOT button on the PCB while plugging in the keyboard. There's no reset button.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` (Fn+right Ctrl in the default keymap)
