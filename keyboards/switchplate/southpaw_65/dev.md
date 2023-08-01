# Southpaw Extended 65%

Development docs covering the following:
- Kimera core
- RGB
- Backlight

## Kimera core
![Kimera core](https://gd2.alicdn.com/imgextra/i4/159916802/TB2qsIgdrJkpuFjy1zcXXa5FFXa_!!159916802.jpg)

What little available info that was available for the qmk port
- atmega32u4 16Mhz
- board seems to have a 6Mhz crystal 
- 2x PCA9555 I2C IO expander

Links:
- [Schematic, BOM, Gerbers](/kairyu/kimera/blob/master/kimera_core)
- [Original firmware](https://github.com/kairyu/tmk_keyboard_custom/tree/master/keyboard/kimera)

```c
/*
Kimera_core_v1.0 Components

             U1 (atmega32u4)
           ,----------------.
      TX --| TX0(PD3)   RAW |--
      RX --| RX1(PD2)   GND |--
         --| GND      RESET |-- RST
         --| GND        VCC |--
     SDA --| 2(PD1) (PF4)A3 |--
     SCL --| 3(PD0) (PF5)A2 |--
   (INT) --| 4(PD4) (PF6)A1 |--
         --| 5(PC6) (PF7)A0 |--
         --| 6(PD7) (PB1)15 |-- SCK
    LED2 --| 7(PE6) (PB3)14 |-- MISO
    LED1 --| 8(PB4) (PB2)16 |-- MOSI
    LED3 --| 9(PB5) (PB6)10 |-- LED4
          `----------------'

         IC1 (PCA9555)                  IC2 (PCA9555)
         ,----------.                   ,----------.
   SDA --| SDA  P00 |-- P1        SDA --| SDA  P00 |-- P17
   SCL --| SCL  P01 |-- P2        SCL --| SCL  P01 |-- P18
   INT --| INT  P02 |-- P3        INT --| INT  P02 |-- P19
         |      P03 |-- P4              |      P03 |-- P20
   GND --| A0   P04 |-- P5        VCC --| A0   P04 |-- P21
   SJ1 --| A1   P05 |-- P6        SJ1 --| A1   P05 |-- P22
   SJ2 --| A2   P06 |-- P7        SJ2 --| A2   P06 |-- P23
         |      P07 |-- P8              |      P07 |-- P24
         |          |                   |          |
         |      P10 |-- P9              |      P10 |-- P25
         |      P11 |-- P10             |      P11 |-- P26
         |      P12 |-- P11             |      P12 |-- P27
         |      P13 |-- P12             |      P13 |-- P28
         |      P14 |-- P13             |      P14 |-- P29
         |      P15 |-- P14             |      P15 |-- P30
         |      P16 |-- P15             |      P16 |-- P31
         |      P17 |-- P16             |      P17 |-- P32
         `----------'                   `----------'
*/

```

### Bootloader
Default bootloader is `atmel-dfu`.
Reboot to bootloader via magnetic switch next to icsp header.
Flash using regular dfu methods.

### Southpaw Extended 65 pin mappings
Taken from [kimera-config.json](https://github.com/kairyu/tkg/blob/master/keyboard/config/kimera-config.json)

	"row_mapping": [ 2, 3, 4, 5, 6 ],
	"col_mapping": [ 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 ],

# RGB
- PIN C7
- Number of RGB LED 7

# Backlight
- PIN B5

# Capslock
- PIN B6

# Numlock
- PIN C6

## Assumptions
### Pin/Port mappings
- All cols are on the same IC
- All rows are on the same IC and port
- Pins mapped sequentially
- Each port only does row or column not a mixture of both
  - No need to have complex port config
  - 

| ROW index | Kimera Pin | PCA9555           |
| ----------|------------|-------------------|
| 0         | 2          | IC1 Port 0  pin 1 |
| 1         | 3          | IC1 Port 0  pin 2 |
| 2         | 4          | IC1 Port 0  pin 3 |
| 3         | 5          | IC1 Port 0  pin 4 |
| 4         | 6          | IC1 Port 0  pin 5 |

- Safe enough to assume `row_index == pin`


| COL index | Kimera Pin | PCA9555           |
| ----------|------------|-------------------|
| 0         | 13         | IC1 Port 1  pin 4 |
| 1         | 14         | IC1 Port 1  pin 5 |
| 2         | 15         | IC1 Port 1  pin 6 |
| 3         | 16         | IC1 Port 1  pin 7 |
| 4         | 17         | IC2 Port 0  pin 0 |
| 5         | 18         | IC2 Port 0  pin 1 |
| 6         | 19         | IC2 Port 0  pin 2 |
| 7         | 20         | IC2 Port 0  pin 3 |
| 8         | 21         | IC2 Port 0  pin 4 |
| 9         | 22         | IC2 Port 0  pin 5 |
| 10        | 23         | IC2 Port 0  pin 6 |
| 11        | 24         | IC2 Port 0  pin 7 |
| 12        | 25         | IC2 Port 1  pin 0 |
| 13        | 26         | IC2 Port 1  pin 1 |
| 14        | 27         | IC2 Port 1  pin 2 |
| 15        | 28         | IC2 Port 1  pin 3 |
| 16        | 29         | IC2 Port 1  pin 4 |
| 17        | 30         | IC2 Port 1  pin 5 |
| 18        | 31         | IC2 Port 1  pin 6 |

- Need to read both ICs and corresponding port to compile the correct column data
- All pins are mapped sequentially
- maps to the usual practice of reading matrix columns
- Needs uint32_t to read 19 columns of data

## Notes
[pca9555 datasheet](https://www.ti.com/lit/ds/symlink/pca9555.pdf)

- Other Kimera based boards with non sequential pin mappings, pins mapped across ICs, or mixed row/col configs will need more complicated `pin -> i2c_addr,port,pin` logic as well as rather more complex pin functions.

## Return to stock firmware
To return back to stock TMK firmware, use [programming guide provided by Reconsiderit](https://geekhack.org/index.php?topic=92344.msg2625784#msg2625784)
