# Drashna's Blackpill Tractyl Manuform (5x6) with a right side trackball

* VBUS mod, using PB10
* Split Hand Pin, using PC14
* Full Duplex Serial/USART using PA3 and PA4 on USART2
* PWM Audio using PB1 and TIM3 and GPT on TIM4
* PWM RGB using PA1 TIM5
* pmw3360 sensor sharing PA5-PA7 on SPI1, with B0 as CS pin
* 8KB SPI EEPROM chip sharing PA5-PA7 on SPI1 with PA4 as CS pin
* Encoder using PA10 and PA12
* SSD1306 OLED display (128x64) using PB8-PB9 on I2C1

* Keyboard Maintainer: [Drashna Jael're](https://github.com/drashna)
* Hardware Supported: [Design files](https://gitlab.com/keyboards1/dm_r_track/-/tree/master/boolean), [WeAct BlackPill (F411)](https://github.com/WeActTC/MiniSTM32F4x1), [PMW3360 Optical Sensor](https://www.tindie.com/products/jkicklighter/pmw3360-motion-sensor/)

Make example for this keyboard (after setting up your build environment):

    make handwired/tractyl_manuform/5x6_right/f411:default

Flashing example for this keyboard:

    make handwired/tractyl_manuform/5x6_right/f411:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
