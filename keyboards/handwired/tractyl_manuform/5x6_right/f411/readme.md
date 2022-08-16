# Drashna's Blackpill Tractyl Manuform (5x6) with a right side trackball

* System Timer on TIM5
* VBUS mod, using PB10 -- does work, but not on my tractyl... bad soldering probably
* Split Hand Pin, using PC14
* Full Duplex Serial/USART using PA2 and PA3 on USART2
* PWM Audio using PB1 and TIM3 and GPT on TIM4
* PWM WS2812 RGB using PA1 TIM2
* 8KB SPI EEPROM chip sharing PA5-PA7 on SPI1 with PA4 as CS pin
* pmw3360 sensor sharing PA5-PA7 on SPI1, with B0 as CS pin
* Encoder using PA13 and PA14
* SSD1306 OLED display (128x64) using PB8-PB9 on I2C1
* Pull-up resistor (22k) on PA10 to fix reset issue.
* Pull-up resistor (5.1k) on PA1 for WS2812 LED support, and wire it's VCC to the 5V pin.
* Pins PA9 is meant for VBUS sense, and has an internal pulldown resistor. A 5.1k pullup resistor can work (but should be avoided)
* Pins PA11 and A12 are not useable because they're used for USB connection, and can't be shared. 
* Pin PB2 is used by BOOT1, and is unusable

## Keyboard Info

* Keyboard Maintainer: [Drashna Jael're](https://github.com/drashna)
* Hardware Supported: [Design files](https://gitlab.com/keyboards1/dm_r_track/-/tree/master/boolean), [WeAct BlackPill (F411)](https://github.com/WeActTC/MiniSTM32F4x1), [PMW3360 Optical Sensor](https://www.tindie.com/products/jkicklighter/pmw3360-motion-sensor/)

Make example for this keyboard (after setting up your build environment):

    make handwired/tractyl_manuform/5x6_right/f411:default

Flashing example for this keyboard:

    make handwired/tractyl_manuform/5x6_right/f411:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader 

* **Bootmagic reset**: Hold down the top right key on the right side, or the top left key on the left side while plugging in.
* **Physical reset button**: Briefly press the "USER" button on the BlackPill
* **Keycode in layout**: Press the key mapped to `RESET`.
