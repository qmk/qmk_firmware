# M0110(A) keyboard converter

This is a port of the original M0110 converter from TMK to QMK. The original converter was designed to work with **ATmega32U2** and **ATmega32U4** based microcontrollers to convert Apple M0110/M0110A keyboards and M0120 numpads to USB. This port has been tested to be compatible with the [**Adafruit Feather 32U4 BLE**](https://learn.adafruit.com/adafruit-feather-32u4-bluefruit-le).


## Enabling Bluetooth for the Adafruit Feather 32U4 BLE

Simply add `BLUETOOTH = AdafruitBLE` to your `rules.mk` file. This enables code specifically for the Adafruit Feather 32U4 BLE. If enabled, the device will use the `PRODUCT` value from `config.h` for the device name displayed by the Feather on host devices. You can simply change these values to change the device name.


## Pins

This port utilizes the same pins that the TMK converter used. `PD1` is used for `CLOCK` and `PD0` is used for the `DATA` from the keyboard. These pins can be changed in `config.h`.


## Other important hardware notes from the original TMK converter Readme:
>### Hardware
>--------
>You can buy preassembled [TMK converter] or make yourown with AVR dev board like PJRC [Teensy].
>
>Port of the MCU `PD1` is assigned to `CLOCK` line and `PD0` to `DATA` by default, you can change pin configuration with editing `config.h`.
>
>[![M0110 Converter](http://i.imgur.com/yEp2eRim.jpg)](http://i.imgur.com/yEp2eRi.jpg)
>
>#### 4P4C phone handset cable
>Note that original cable used with Mac is **straight** while phone handset cable is **crossover**.
>
><http://en.wikipedia.org/wiki/Modular_connector#4P4C>
>
>[Teensy]: http://www.pjrc.com/teensy/
>[TMK converter]: https://geekhack.org/index.php?topic=72052.0
>
>
>#### Socket Pinout
>- <http://pinouts.ru/Inputs/MacKeyboard_pinout.shtml>
>
>![Jack fig](http://www.kbdbabel.org/conn/kbd_connector_macplus.png)
>
>
>#### Pull-up Resistor
>You may need pull-up resistors on signal lines(`CLOCK`, `DATA`) in particular when you have long or coiled cable. **1k-10k Ohm** will be OK >for this purpose. In that case the converter may not read signal from keyboard correctly without pull-up resistors.
>

[**View the original TMK converter Readme**](https://github.com/tmk/tmk_keyboard/tree/master/converter/m0110_usb)\
[**View the original TMK converter Repository**](https://github.com/tmk/tmk_keyboard/tree/master/converter/m0110_usb)


## QMK Port Changelog

- 2018/08/01 - Original Release

