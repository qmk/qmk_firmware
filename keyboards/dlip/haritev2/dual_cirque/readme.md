# Harite v2 (Cirque trackpad version)

5 way switch directional keyboard

![Harite-v2](https://i.imgur.com/v8kUtL3.jpeg)

* Keyboard Maintainer: [Dane Lipscombe](https://github.com/dlip)
* Hardware Supported: Harite v2 (Cirque trackpad version)
* Hardware Availability: <https://github.com/dlip/harite-v2>

Make example for this keyboard (after setting up your build environment):

```bash
make dlip/haritev2/dual_cirque:default
```

Flashing example for this keyboard:

```bash
# For the left half...
make dlip/haritev2/dual_cirque:default:uf2-split-left
# or the qmk cli equivalent:
qmk flash -kb dlip/haritev2/dual_cirque --keymap default -bl uf2-split-left

# For the right half...
make dlip/haritev2/dual_cirque:default:uf2-split-right
# or the qmk cli equivalent:
qmk flash -kb dlip/haritev2/dual_cirque --keymap default -bl uf2-split-right
```

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
