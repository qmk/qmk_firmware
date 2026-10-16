# DEBROGLIE RK0313S3

![top](https://i.imgur.com/jRL9Zd0.jpeg)

![bottom](https://i.imgur.com/lka7clx.jpeg)

![pcb_top](https://i.imgur.com/6khwxYB.jpeg)

![pcb_bottom](https://i.imgur.com/1D1msSV.jpeg)

A 3 key APM32F072 macropad with SK6812MINI-E LEDs.

* Keyboard Maintainer: [Zeranoe](https://github.com/Zeranoe)
* Hardware Supported: DEBROGLIE RK0313S3
* Hardware Availability: Hudson River Trading conference booth

Make example for this keyboard (after setting up your build environment):

    make debroglie/rk0313s:default
	
Flashing example for this keyboard:

	make debroglie/rk0313s:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader:

* **Bootmagic reset**: Hold down the left key and plug in the keyboard

## Serial Wire Debug

SWD is available on the unpopulated programming header with the mapping:

| RK0313S3 | SWD    |
|----------|--------|
| GND      | GND    |
| CLK      | SWDIO  |
| DIO      | SWCLK  |
| VOC      | VTref  |
| INO      | nRESET |
