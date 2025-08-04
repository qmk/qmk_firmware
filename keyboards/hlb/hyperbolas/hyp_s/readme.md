# Hyperbolas

![hyperbolas](https://mint-tomato-83b.notion.site/image/attachment%3A80a8f4b8-9c85-41f6-8fe5-5ce0d04d3ee3%3A4k_2025v6_Hyperbolas16.jpg?table=block&id=2303f3e3-ee19-8076-9b95-e92cb368dec3&spaceId=41a0dc7a-fdbe-4a75-8b60-e3a45cfce97f&width=2000&userId=&cache=v2)

TKL project from HLB with 8K pcb layout compatibility.

* Keyboard Maintainer: [H3lli0n](https://github.com/H3lli0n)
* Hardware Supported: HLB Hyperbolas

Make example for this keyboard (after setting up your build environment):

    make hlb/hyperbolas/hyp-s:default

Flashing example for this keyboard:

    make hlb/hyperbolas/hyp-s:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard.
* **Physical reset button**: Press 2 times the physical reset button.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available.
