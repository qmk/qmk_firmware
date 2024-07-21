# nuovotaka/freeadrs32_knob/rev1

![nuovotaka/freeadrs32_knob/rev1](https://imgur.com/a/w6D2VXD)

| Name            | Description                                   |
| :-------------- | :-------------------------------------------- |
| Freeadrs32_knob | Left-handed keyboard with 32 keys and 3 knobs |

-   Keyboard Maintainer: [Takahiro Natsume](https://github.com/nuovotaka)
-   Hardware Supported: ProMicro like footprint
-   Hardware Availability: See [nuovotaka shop](https://nuovotaka-kbd.stores.jp/)

## How to build

1. Check out this repository.

```
git clone https://github.com/nuovotaka/FreeAdrs32.git freeadrs32
```

2. Check out [qmk/qmk_firmware](https://github.com/qmk/qmk_firmware/) repository in another place.

```
git clone https://github.com/qmk/qmk_firmware.git --depth 1 --recurse-submodules --shallow-submodules -b 0.25.17 qmk
```

Currently Freeadrs32_knob firmwares are verified to compile with QMK 0.25.17

3. Create a symbolic link to this freeadrs32/ directory from [qmk/qmk_firmware]'s `keyboards`/ directory.

```
$ ls
freeadrs32/ qmk/

$ cd qmk/keyboards


$ ln -s ../../freeadrs32/FreeAdrs32_knob/qmk_firmware/keyboards/nuovotaka nuovotaka
$ ls nuovotaka/
freeadrs32_knob/  lib/
$ cd ..
```

4. `make` your Freeadrs32_knob firmware.

```
# Build Freeadrs32_knob firmware with "default" keymap
$ make SKIP_GIT=yes nuovotaka/freeadrs32_knob/rev1:default
```

5. Flashing firmware.

```
$ make nuovotaka/freeadrs32_knob/rev1:default:flash
```

There are three keymaps provided at least:

-   via - Standard version with [Remap](https://remap-keys.app/) to change keymap
-   test - Easy-to-use version for checking operation at build time
-   default - Base version for creating your own customized firmware

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

-   **Bootmagic reset**: Hold down the key at (0,1) in the matrix (usually the top left key or Escape) and plug in the keyboard
-   **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
-   **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
