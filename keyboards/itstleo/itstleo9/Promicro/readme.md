# itstleo/handwired/it9_32u4

This is my first handwire macropad project call itstleo9 or it9, using orthor 3x3 layout powered with 2 MCU are promicro ATmega32u4 and RasberryPi RP2040 for simple flash using QMK Toolbox and Drag&Drop file. Supported for Via and Vial keymap.

* Keyboard Maintainer: [Its TLeo](https://github.com/Its TLeo)
* Hardware Supported: Promicro ATmega32u4
* Hardware Availability: [Promicro](https://aliexpress.com/item/32888212119.html?spm=a2g0o.productlist.main.3.6e5ef70cdBVEF7&algo_pvid=fe4ec051-4a64-4e5d-810f-9984bfe852eb&aem_p4p_detail=2023070605140211214266150364960004273054&algo_exp_id=fe4ec051-4a64-4e5d-810f-9984bfe852eb-1&pdp_npi=3%40dis%21VND%21110929%2189788.0%21%21%214.67%21%21%402102160416886456429678477d07bc%2112000029855280287%21sea%21VN%210&curPageLogUid=FnJUdcJPhdXf&search_p4p_id=2023070605140211214266150364960004273054_2)

Make example for this keyboard (after setting up your build environment):

    make itstleo/handwired/it9_32u4:default

Flashing example for this keyboard:

    make itstleo/handwired/it9_32u4:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).  Dont know how to make a handwire keyboard, check it out [SkottoKeebs handwire tutorial](https://www.youtube.com/watch?v=hjml-K-pV4E&pp=ygUTaGFuZHdpcmUgYSBtYWNyb3BhZA%3D%3D)

## Matrix pin

*    **cols** :     D1  ,  D0   ,  D4
*    **rows** :     F4  ,  F5   ,  F6

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
