# null/st110r2

null ST110r2 is a custom PCB/keyboard project that supports multiple layouts and is built on top of the Filco and the clones alike.

![st110r2_zoom](https://s3.amazonaws.com/null-src/images/posts/nkbm-st110r2/NKBM-ST110r21-both1.png)
![st110r2_full](https://s3.amazonaws.com/null-src/images/posts/nkbm-st110r2/NKBM-ST110r21-both3.png)

* Keyboard Maintainer: [user176176](https://github.com/user176176)
* Hardware Supported: [null] 最高タイプ (SaikouType) NKBM-ST110r2.x keyboard PCBs with Teensy 2.0++.
* Hardware Availability: [NKBM-ST110r2 - null-src.com](https://null-src.com/posts/nkbm-st110r2/post.php)

Make example for this keyboard (after setting up your build environment):

    make null/st110r2:default

Flashing example for this keyboard:

    make null/st110r2:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the reset button on Teensy
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

![st110r2_pcb](https://s3.amazonaws.com/null-src/images/posts/nkbm-st110r2/NKBM-ST110r2_PCB.jpg)
![st110r2_build](https://s3.amazonaws.com/null-src/images/posts/nkbm-st110r2/NKBM-ST110r2.1_rosewill_top.jpg)
