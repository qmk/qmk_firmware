# Zeno Ergo 60%

![zeno](https://imgur.com/bO9qHCuh.png)

The following is the QMK Firmware for the Zeno 60% Ergo - 8 Degree ergo 60 designed in Dubai, UAE.

The PCB features:
* QMK & VIA compatibility
* Pre-configured Space-FN

---

* Keyboard Maintainer: [paulgali](https://github.com/paulgali)
* Hardware Supported: ZenoPCB for the Zeno Ergo 60%
* Hardware Availability: https://sandkeys.me 

Make example for this keyboard (after setting up your build environment):

    make skme/zeno:default

Flashing example for this keyboard:

    make skme/zeno:default:flash


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader Enter the bootloader in 3 ways: 
* **Bootmagic reset**: Hold down the key ESC key and plug in the keyboard (Top Left most switch)
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the B key on layer 1 which is mapped to `RESET`
