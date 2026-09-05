# cocot46plus

![cocot46plus_photo15](https://i.imgur.com/yCvbMgo.jpeg)


cocot46plus is a column-staggered keyboard with 46 keys, a 34mm-trackball and a rotary encoder.

- Keyboard Maintainer: [markstos](https://github.com/markstos)
- Hardware Supported: cocot46plus PCB, SparkFun Pro Micro - RP2040
- Hardware Availability: [Yushakobo.jp](https://shop.yushakobo.jp/en/products/6955)

Detailed information is available from the links below:  

 - [JP](https://www.notion.so/aki27/cocot46plus-55775bf44a664dae9d6ca342e79e8312) 
 - [EN](https://aki27.notion.site/cocot46plus-Introduction-e6261b0a5ce045f8a0d8535a74844929)

## Build Guides 

 - [JP](https://github.com/aki27kbd/cocot46plus/blob/main/doc/buildguide.md) 
 - [EN](https://github.com/aki27kbd/cocot46plus/blob/main/doc/v1/buildguide_en.md)

### Special keycodes

Value    | Keycode   |Description
---------|-----------|-----------
`0x5DA7` | `CPI_SW`  |Switch CPI. Low for precision, high for large movements.
`0x5DA8` | `SCRL_SW` |Switch scroll divider. Larger value equals smaller scroll motion
`0x5DA9` | `ROT_R15` |Rotate sensor coordinate by 15 degrees clockwise
`0x5DAA` | `ROT_L15` |Rotate sensor coordinate by 15 degrees counterclockwise
`0x5DAB` | `SCRL_MO` |Enable scroll mode while being pressed
`0x5DAC` | `SCRL_TO` |Toggle scroll mode. Once pushed, mouse mode and scroll mode are switched.
`0x5DAD` | `SCRL_IN` |Invert scroll direction

# VIA Support

 * [aki27 provides VIA JSON files](https://github.com/aki27kbd/cocot46plus/tree/main/firmware)


### Gallery

![cocot46plus_photo12](https://i.imgur.com/hPOB98H.jpeg)
![cocot46plus_photo14](https://i.imgur.com/HrtI9w1.jpeg)
![cocot46plus_photo05](https://i.imgur.com/LOcxHIV.jpeg)
![cocot46plus_photo02](https://i.imgur.com/b5O9tKq.jpeg)
![cocot46plus_photo10](https://i.imgur.com/gDx5e64.jpeg)
