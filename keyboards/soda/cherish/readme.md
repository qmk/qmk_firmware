# CHERISH-75

A customizable 75%  keyboard, support both HOTSWAP and SOLDER.

* Keyboard Maintainer: [gezhaoyou](https://github.com/gezhaoyou)
* Hardware Supported: [gezhaoyou](https://github.com/gezhaoyou)
* Hardware Availability: [Cherish-75](https://github.com/gezhaoyou/Cherish-75)

Make example for this keyboard (after setting up your build environment):

**default**:

```shell
qmk compile -kb soda/cherish -km default
```

**via:**

```shell
qmk compile -kb soda/cherish -km via
```

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the button: [boot] first, then press button: [reset]  on the back of the PCB
* **Keycode in layout**: Press the key mapped to `RESET` if it is available

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
