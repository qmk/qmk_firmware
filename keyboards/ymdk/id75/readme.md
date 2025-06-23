# Idobao x YMDK ID75

![Idobao x YMDK ID75](https://i.imgur.com/bhVfzrzh.jpg)

A 75-key, 5-row ortholinear keyboard with per-key and underglow RGB LEDs.

* Keyboard Maintainer: [The QMK Community](https://github.com/qmk)
* Hardware Supported: [Idobao x YMDK ID75](https://www.aliexpress.com/item/3256804537842097.html). **This is not the same PCB as `idobao/id75` or `ymdk/ymd75`.**
  This keyboard has had multiple PCB revisions, some of which may not work with the firmware in this repository. **Check your PCB before flashing.**
  * `f103`: (Geehy APM32F103CBT6, uf2boot)
* Hardware Availability: [YMDK](https://ymdkey.com/products/id75-75-keys-ortholinear-layout-qmk-anodized-aluminum-case-plate-hot-swappable-hot-swap-type-c-pcb-mechanical-keyboard-kit), [AliExpress (YMDK Store)](https://www.aliexpress.com/item/2255800125183974.html), [Amazon](https://www.amazon.com/Ortholinear-Anodized-Aluminum-hot-swappable-Mechanical/dp/B07ZQ8CD88)

Make example for this keyboard (after setting up your build environment):

    make ymdk/id75/f103:default

Flashing example for this keyboard:

    make ymdk/id75/f103:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard. This will also clear the emulated EEPROM, so it is a good first step if the keyboard is misbehaving.
* **Physical reset button**: Press the button on the back of the PCB twice in quick succession.
* **Keycode in layout**: Press the key mapped to `QK_BOOT`. In the pre-supplied keymaps it is on the second layer, in the bottom-right corner.

After entering the bootloader through one of the three methods above, the keyboard will appear as a USB mass storage device. If the CLI is unable to find this device, the compiled `.uf2` file can be manually copied to it. The keyboard will reboot on completion with the new firmware loaded.
- `f103`: The volume name is `MT.KEY`.
