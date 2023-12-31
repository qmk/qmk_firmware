# EC Pro X JIS

![EC Pro X JIS PCB](https://i.imgur.com/yJdPOcbh.png)

Open source replacement PCB kit for the HHKB Pro 2 and Pro 3 keyboards using the JIS case.

* Keyboard Maintainer: [cipulot](https://github.com/cipulot)
* Hardware Supported: EC Pro X JP PCB
* Hardware Availability: [EC Pro X](https://github.com/cipulot/EC-Pro-X)

Make example for this keyboard (after setting up your build environment):

    make cipulot/ec_prox/jis:default

Flashing example for this keyboard:

    make cipulot/ec_prox/jis:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical Boot0 pins**: Short the Boot0 pins on the back of the PCB while plugging in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
