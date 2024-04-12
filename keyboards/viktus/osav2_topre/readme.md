# OSAv2 Topre

![osav2_topre](https://i.imgur.com/WTRrpQFh.png)

-   Keyboard Maintainer: BlindAssassin111
-   Hardware Supported: OSAv2 Topre PCBs
-   Hardware Availability: Viktus Design LLC

Make example for this keyboard (after setting up your build environment):

    make viktus/osav2_topre:default

Flashing example for this keyboard:

    make viktus/osav2_topre:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

Here are the instructions to add to the README on how users can modify the actuation levels of each key:

## Modifying Key Actuation Levels

The actuation level of each key on the OSAv2 Topre keyboard is determined by two values: `DEFAULT_RESET_PT` and `DEFAULT_ACTUATION_PT`. These values are specified in the `ec.h` file.

By default, all keys use these values. However, you can customize the actuation levels for specific keys by modifying the `key_level_configs` array in the `ec.c` file.

All available key positions on the OSAv2 matrix are defined with friendly names in the `key_positions.c` file. You can refer to these names when specifying the keys you want to customize.

To change the actuation level of a specific key, add an entry to the `key_level_configs` array in the following format:

```c
const KeyConfig key_level_configs[] = {
    {&KEY_POSITION_NAME, {reset_pt, actuation_pt}},
    // ...
};
```

Replace `KEY_POSITION_NAME` with the name of the key position you want to customize (e.g., `KEY_014_KC_BSLS`), and set the desired `reset_pt` and `actuation_pt` values.

For example, to customize the actuation levels for the split backspace left 1U key, you would add the following entry:

```c
const KeyConfig key_level_configs[] = {
    {&KEY_014_KC_BSLS, {48, 53}}, // Custom levels for (SPLIT_BACKSPACE_LEFT_1U)
    // ...
};
```

You can add multiple entries to the `key_level_configs` array to customize the actuation levels for different keys. By modifying the `key_level_configs` array, you can fine-tune the actuation levels of specific keys to suit your preferences.