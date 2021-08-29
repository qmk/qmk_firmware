# KeyHive Sofle

Based on the [original Sofle](../../sofle), this variant brings per-key RGB to an alredy great keyboard. The bottom row was also slightly adjusted.

-   Keyboard Maintainer: [KeyHive](https://github.com/keyhive/)
-   Hardware Availability: [PCB kits](https://keyhive.xyz/shop/sofle)

## Flashing

```sh
# for pro micro-based builds
qmk flash -kb keyhive/sofle -km default

# for Elite C or dfu bootloader builds
qmk flash -kb keyhive/sofle -km default -bl dfu
```

See also the [via keymap README](./keymaps/via/readme.md).

Disconnect the first half, connect the second one and repeat the process.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
