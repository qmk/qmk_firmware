# Gravity-45

![green_keys/gravity_45](https://i.imgur.com/FTyC65h.jpeg)

Gravity-45 is a 45-key integrated keyboard.  
It uses the Waveshare RP2040-Zero MCU.  
Keyswitch sockets are used for easy keyswitch replacement.  
The tight PCB outline lines allow for easy case design.

---

Gravity-45 は 45キーの一体型のキーボードだ。  
MCUにはWaveshare RP2040-Zeroを採用している。  
キースイッチソケットを使用するためキースイッチの交換が容易に行える。  
PCBの外形線がタイトなので、ケースの設計が容易だ。  

* Keyboard Maintainer: [takashicompany](https://github.com/takashicompany)
* Hardware Supported: PCB, Waveshare RP2040-Zero
* Hardware Availability: [GreenKeys](https://green-keys.info/)

Make example for this keyboard (after setting up your build environment):

    make green_keys/gravity_45:default

Flashing example for this keyboard:

    make green_keys/gravity_45:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
