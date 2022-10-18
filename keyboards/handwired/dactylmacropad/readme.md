# DactylMacropad

[Glamour shot](https://preview.redd.it/95khc8oywfu91.jpg?width=4896&format=pjpg&auto=webp&s=edf64608b3a32af4117e52c6274f435260b25648)

*A short description of the keyboard/project*

* Keyboard Maintainer: [bwprobably](https://github.com/bwprobably)
* Hardware Supported: ProMicro (Atmega32U4), EC11 Rotary Encoder
* Hardware Availability: [Example Encoder](https://www.amazon.com/dp/B07D3DF8TK/ref=sspa_dk_detail_3?psc=1&pd_rd_i=B07D3DF8TK&pd_rd_w=UTDPr&content-id=amzn1.sym.88097cb9-5064-44ef-891b-abfacbc1c44b&pf_rd_p=88097cb9-5064-44ef-891b-abfacbc1c44b&pf_rd_r=E2VGNYFE6MSTPS43HPW8&pd_rd_wg=OqrIj&pd_rd_r=4574f140-495a-4c55-aee1-1873bb55c1dd&s=industrial&sp_csd=d2lkZ2V0TmFtZT1zcF9kZXRhaWw)
[ProMicro](https://www.amazon.com/HiLetgo-Atmega32U4-Bootloadered-Development-Microcontroller/dp/B01MTU9GOB/ref=sr_1_4?crid=2YWTO4R56JPDN&keywords=pro+micro&qid=1666109727&qu=eyJxc2MiOiI0LjMwIiwicXNhIjoiNC4wNyIsInFzcCI6IjMuOTgifQ%3D%3D&sprefix=pro+micro%2Caps%2C173&sr=8-4)

Make example for this keyboard (after setting up your build environment):

    make default:default

Flashing example for this keyboard:

    make default:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
