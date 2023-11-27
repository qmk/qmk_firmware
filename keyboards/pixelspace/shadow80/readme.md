# Shadow80

![shadow80](https://imgur.com/XLjjdMzh.jpg)
An 80%/TenKeyLess sized keyboard with 74 RGB.
Before enabling the maximum brightness of RGB lights, please confirm whether the USB device power supply supports it.
This PCB about two versions ： hotswap and  solder.

* Keyboard Maintainer: [PixelSpace](https://github.com/PixelSpaceStudio)
* Hardware Supported: shadow80
* Hardware Availability: [PixelSpace](https://github.com/PixelSpaceStudio)

Make example for this keyboard (after setting up your build environment):

    make shadow80:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

- **Bootmagic reset**: Hold down the key at (0,0)(always "ESC") in the matrix (usually the top left key which is Escape in this keyboard) and plug in the keyboard
- **Keycode in layout**: Press the key mapped to `QK_BOOT` 


/*
 *              ┌───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┐ ┌───┬───┬───┐
 *              │00 ││01 │02 │03 │04 ││05 │06 │07 │08 ││09 │0A │0B │0C ││0D │ │0E │0F │0G │
 *              └───┘└───┴───┴───┴───┘└───┴───┴───┴───┘└───┴───┴───┴───┘└───┘ └───┴───┴───┘
 *              ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐ ┌───┬───┬───┐      ┌───────┐
 *              │10 │11 │12 │13 │14 │15 │16 │17 │18 │19 │1A │1B │1C │3C │1D │ │1E │1F │1G │      │1D     │ 2u Backspace
 *              ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤ ├───┼───┼───┤      └─┬─────┤
 *              │20   │21 │22 │23 │24 │25 │26 │27 │28 │29 │2A │2B │2C │2D   │ │2E │2F │2G │        │     │
 *  2.25u       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘     ┌──┴┐3D  │ ISO Enter
 *  LShift      │30    │31 │32 │33 │34 │35 │36 │37 │38 │39 │3A │3B │3D      │                   │2D │    │
 * ┌────────┐   ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤     ┌───┐       ┌─┴───┴────┤
 * │40      │   │40  │41 │42 │43 │44 │45 │46 │47 │48 │49 │4A │4B │4C    │4D │     │4F │       │4C        │ 2.75u RShift
 * └────────┘   ├────┴┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬───┬─┴───┤ ┌───┼───┼───┐   └──────────┘
 *              │50   │51 │52   │56                         │5B   │5C │5D   │ │5E │5F │5G │
 *              └─────┴───┴─────┴───────────────────────────┴─────┴───┴─────┘ └───┴───┴───┘
 *              ┌────┬────┬────┬────────────────────────┬────┬────┬────┬────┐ 
 *              │50  │51  │52  │56                      │5A  │5B  │5C  │ 5D |  6.25u Spacebar
 *              └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 **/
