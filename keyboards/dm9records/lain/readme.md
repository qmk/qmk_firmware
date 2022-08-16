# lain

![lain](https://i.imgur.com/V0mR1Bgh.jpg)

Ergonomic 40% keyboard.

serial exprement lain themed.    
licensed under #lainttl (https://www.nbcuni.co.jp/rondorobe/anime/lain/ttl/)

* Keyboard Maintainer: [Takuya Urakawa @hsgw](https://github.com/hsgw), https://5z6p.com
* Hardware Supported: onboard MCU.
* Hardware Availability: Group buy. (https://5z6p.com/products/lain/)

Make example for this keyboard (after setting up your build environment):

    make dm9records/lain:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Note
### PCB revision

If your pcb is not Rev.1, you should use the firmware in below repository.   
https://github.com/hsgw/qmk_firmware/tree/lain/keyboards/dm9records/lain

### Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `RESET` if it is available
