# RGB Matrix Lighting :id=rgb-matrix-lighting

This feature allows you to use RGB LED matrices driven by external drivers. It hooks into the RGBLIGHT system so you can use the same keycodes as RGBLIGHT to control it.

If you want to use single color LED's you should use the [LED Matrix Subsystem](feature_led_matrix.md) instead.

## Driver configuration :id=driver-configuration
---
### IS31FL3731 :id=is31fl3731

There is basic support for addressable RGB matrix lighting with the I2C IS31FL3731 RGB controller. To enable it, add this to your `rules.mk`:

```make
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = is31fl3731
```

You can use between 1 and 4 IS31FL3731 IC's. Do not specify `DRIVER_ADDR_<N>` defines for IC's that are not present on your keyboard. You can define the following items in `config.h`:

| Variable | Description | Default |
|----------|-------------|---------|
| `ISSI_TIMEOUT` | (Optional) How long to wait for i2c messages, in milliseconds | 100 |
| `ISSI_PERSISTENCE` | (Optional) Retry failed messages this many times | 0 |
| `ISSI_3731_DEGHOST` | (Optional) Set this define to enable de-ghosting by halving Vcc during blanking time | |
| `DRIVER_COUNT` | (Required) How many RGB driver IC's are present | |
| `RGB_MATRIX_LED_COUNT` | (Required) How many RGB lights are present across all drivers | |
| `DRIVER_ADDR_1` | (Required) Address for the first RGB driver | |
| `DRIVER_ADDR_2` | (Optional) Address for the second RGB driver | |
| `DRIVER_ADDR_3` | (Optional) Address for the third RGB driver | |
| `DRIVER_ADDR_4` | (Optional) Address for the fourth RGB driver | |

Here is an example using 2 drivers.

```c
// This is a 7-bit address, that gets left-shifted and bit 0
// set to 0 for write, 1 for read (as per I2C protocol)
// The address will vary depending on your wiring:
// 0b1110100 AD <-> GND
// 0b1110111 AD <-> VCC
// 0b1110101 AD <-> SCL
// 0b1110110 AD <-> SDA
#define DRIVER_ADDR_1 0b1110100
#define DRIVER_ADDR_2 0b1110110

#define DRIVER_COUNT 2
#define DRIVER_1_LED_TOTAL 25
#define DRIVER_2_LED_TOTAL 24
#define RGB_MATRIX_LED_COUNT (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)
```

!> Note the parentheses, this is so when `RGB_MATRIX_LED_COUNT` is used in code and expanded, the values are added together before any additional math is applied to them. As an example, `rand() % (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)` will give very different results than `rand() % DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL`.

For split keyboards using `RGB_MATRIX_SPLIT` with an LED driver, you can either have the same driver address or different driver addresses. If using different addresses, use `DRIVER_ADDR_1` for one and `DRIVER_ADDR_2` for the other one. Then, in `g_is31_leds`, fill out the correct driver index (0 or 1). If using one address, use `DRIVER_ADDR_1` for both, and use index 0 for `g_is31_leds`.

Define these arrays listing all the LEDs in your `<keyboard>.c`:

```c
const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, C1_3,  C2_3,  C3_3},
    ....
}
```

Where `Cx_y` is the location of the LED in the matrix defined by [the datasheet](https://www.issi.com/WW/pdf/31FL3731.pdf) and the header file `drivers/led/issi/is31fl3731.h`. The `driver` is the index of the driver you defined in your `config.h` (`0`, `1`, `2`, or `3`).

---
### IS31FL3733 :id=is31fl3733

There is basic support for addressable RGB matrix lighting with the I2C IS31FL3733 RGB controller. To enable it, add this to your `rules.mk`:

```make
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = is31fl3733
```

You can use between 1 and 4 IS31FL3733 IC's. Do not specify `DRIVER_ADDR_<N>` defines for IC's that are not present on your keyboard. You can define the following items in `config.h`:

| Variable | Description | Default |
|----------|-------------|---------|
| `ISSI_TIMEOUT` | (Optional) How long to wait for i2c messages, in milliseconds | 100 |
| `ISSI_PERSISTENCE` | (Optional) Retry failed messages this many times | 0 |
| `ISSI_PWM_FREQUENCY` | (Optional) PWM Frequency Setting - IS31FL3733B only | 0 |
| `ISSI_GLOBALCURRENT` | (Optional) Configuration for the Global Current Register | 0xFF |
| `ISSI_SWPULLUP` | (Optional) Set the value of the SWx lines on-chip de-ghosting resistors | PUR_0R (Disabled) |
| `ISSI_CSPULLUP` | (Optional) Set the value of the CSx lines on-chip de-ghosting resistors | PUR_0R (Disabled) |
| `DRIVER_COUNT` | (Required) How many RGB driver IC's are present | |
| `RGB_MATRIX_LED_COUNT` | (Required) How many RGB lights are present across all drivers | |
| `DRIVER_ADDR_1` | (Required) Address for the first RGB driver | |
| `DRIVER_ADDR_2` | (Optional) Address for the second RGB driver | |
| `DRIVER_ADDR_3` | (Optional) Address for the third RGB driver | |
| `DRIVER_ADDR_4` | (Optional) Address for the fourth RGB driver | |
| `DRIVER_SYNC_1` | (Optional) Sync configuration for the first RGB driver | 0 |
| `DRIVER_SYNC_2` | (Optional) Sync configuration for the second RGB driver | 0 |
| `DRIVER_SYNC_3` | (Optional) Sync configuration for the third RGB driver | 0 |
| `DRIVER_SYNC_4` | (Optional) Sync configuration for the fourth RGB driver | 0 |

The IS31FL3733 IC's have on-chip resistors that can be enabled to allow for de-ghosting of the RGB matrix. By default these resistors are not enabled (`ISSI_SWPULLUP`/`ISSI_CSPULLUP` are given the value of`PUR_0R`), the values that can be set to enable de-ghosting are as follows:

| `ISSI_SWPULLUP/ISSI_CSPULLUP` | Description |
|----------------------|-------------|
| `PUR_0R` | (default) Do not use the on-chip resistors/enable de-ghosting |
| `PUR_05KR` | The 0.5k Ohm resistor used during blanking period (t_NOL) |
| `PUR_3KR` | The 3k Ohm resistor used at all times |
| `PUR_4KR` | The 4k Ohm resistor used at all times |
| `PUR_8KR` | The 8k Ohm resistor used at all times |
| `PUR_16KR` | The 16k Ohm resistor used at all times |
| `PUR_32KR` | The 32k Ohm resistor used during blanking period (t_NOL) |

Here is an example using 2 drivers.

```c
// This is a 7-bit address, that gets left-shifted and bit 0
// set to 0 for write, 1 for read (as per I2C protocol)
// The address will vary depending on your wiring:
// 00 <-> GND
// 01 <-> SCL
// 10 <-> SDA
// 11 <-> VCC
// ADDR1 represents A1:A0 of the 7-bit address.
// ADDR2 represents A3:A2 of the 7-bit address.
// The result is: 0b101(ADDR2)(ADDR1)
#define DRIVER_ADDR_1 0b1010000
#define DRIVER_ADDR_2 0b1010011

#define DRIVER_COUNT 2
#define DRIVER_1_LED_TOTAL 58
#define DRIVER_2_LED_TOTAL 10
#define RGB_MATRIX_LED_COUNT (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)
```

!> Note the parentheses, this is so when `RGB_MATRIX_LED_COUNT` is used in code and expanded, the values are added together before any additional math is applied to them. As an example, `rand() % (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)` will give very different results than `rand() % DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL`.

Currently only 4 drivers are supported, but it would be trivial to support all 8 combinations.

Define these arrays listing all the LEDs in your `<keyboard>.c`:

```c
const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, B_1,    A_1,    C_1},
    ....
}
```

Where `X_Y` is the location of the LED in the matrix defined by [the datasheet](https://www.issi.com/WW/pdf/31FL3733.pdf) and the header file `drivers/led/issi/is31fl3733.h`. The `driver` is the index of the driver you defined in your `config.h` (`0`, `1`, `2`, or `3` for now).

---
### IS31FL3736 :id=is31fl3736

There is basic support for addressable RGB matrix lighting with the I2C IS31FL3736 RGB controller. To enable it, add this to your `rules.mk`:

```make
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = is31fl3736
```
You can use between 1 and 4 IS31FL3736 IC's. Do not specify `DRIVER_ADDR_<N>` defines for IC's that are not present on your keyboard.

Configure the hardware via your `config.h`:

| Variable | Description | Default |
|----------|-------------|---------|
| `ISSI_TIMEOUT` | (Optional) How long to wait for i2c messages, in milliseconds | 100 |
| `ISSI_PERSISTENCE` | (Optional) Retry failed messages this many times | 0 |
| `ISSI_PWM_FREQUENCY` | (Optional) PWM Frequency Setting - IS31FL3736B only | 0 |
| `ISSI_GLOBALCURRENT` | (Optional) Configuration for the Global Current Register | 0xFF |
| `ISSI_SWPULLUP` | (Optional) Set the value of the SWx lines on-chip de-ghosting resistors | PUR_0R (Disabled) |
| `ISSI_CSPULLUP` | (Optional) Set the value of the CSx lines on-chip de-ghosting resistors | PUR_0R (Disabled) |
| `DRIVER_COUNT` | (Required) How many RGB driver IC's are present | |
| `RGB_MATRIX_LED_COUNT` | (Required) How many RGB lights are present across all drivers | |
| `DRIVER_ADDR_1` | (Required) Address for the first RGB driver | |
| `DRIVER_ADDR_2` | (Optional) Address for the second RGB driver | |
| `DRIVER_ADDR_3` | (Optional) Address for the third RGB driver | |
| `DRIVER_ADDR_4` | (Optional) Address for the fourth RGB driver | |

The IS31FL3736 IC's have on-chip resistors that can be enabled to allow for de-ghosting of the RGB matrix. By default these resistors are not enabled (`ISSI_SWPULLUP`/`ISSI_CSPULLUP` are given the value of`PUR_0R`), the values that can be set to enable de-ghosting are as follows:

| `ISSI_SWPULLUP/ISSI_CSPULLUP` | Description |
|----------------------|-------------|
| `PUR_0R` | (default) Do not use the on-chip resistors/enable de-ghosting |
| `PUR_05KR` | The 0.5k Ohm resistor used during blanking period (t_NOL) |
| `PUR_1KR` | The 1k Ohm resistor used during blanking period (t_NOL) |
| `PUR_2KR` | The 2k Ohm resistor used during blanking period (t_NOL) |
| `PUR_4KR` | The 4k Ohm resistor used during blanking period (t_NOL) |
| `PUR_8KR` | The 8k Ohm resistor during blanking period (t_NOL) |
| `PUR_16KR` | The 16k Ohm resistor during blanking period (t_NOL) |
| `PUR_32KR` | The 32k Ohm resistor used during blanking period (t_NOL) |

Here is an example using 2 drivers.

```c
// This is a 7-bit address, that gets left-shifted and bit 0
// set to 0 for write, 1 for read (as per I2C protocol)
// The address will vary depending on your wiring:
// 0000 <-> GND
// 0101 <-> SCL
// 1010 <-> SDA
// 1111 <-> VCC
// ADDR represents A3:A0 of the 7-bit address.
// The result is: 0b101(ADDR)
#define DRIVER_ADDR_1 0b1010000
#define DRIVER_ADDR_2 0b1010001

#define DRIVER_COUNT 2
#define DRIVER_1_LED_TOTAL 30
#define DRIVER_2_LED_TOTAL 32
#define RGB_MATRIX_LED_COUNT (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)
```
!> Note the parentheses, this is so when `RGB_MATRIX_LED_COUNT` is used in code and expanded, the values are added together before any additional math is applied to them. As an example, `rand() % (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)` will give very different results than `rand() % DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL`.

Define these arrays listing all the LEDs in your `<keyboard>.c`:

```c
const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, B_1,    A_1,    C_1},
    ....
}
```
### IS31FL3737 :id=is31fl3737

There is basic support for addressable RGB matrix lighting with the I2C IS31FL3737 RGB controller. To enable it, add this to your `rules.mk`:

```make
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = is31fl3737
```
You can use between 1 and 4 IS31FL3737 IC's. Do not specify `DRIVER_ADDR_<N>` defines for IC's that are not present on your keyboard.

Configure the hardware via your `config.h`:

| Variable | Description | Default |
|----------|-------------|---------|
| `ISSI_TIMEOUT` | (Optional) How long to wait for i2c messages, in milliseconds | 100 |
| `ISSI_PERSISTENCE` | (Optional) Retry failed messages this many times | 0 |
| `ISSI_PWM_FREQUENCY` | (Optional) PWM Frequency Setting - IS31FL3737B only | 0 |
| `ISSI_GLOBALCURRENT` | (Optional) Configuration for the Global Current Register | 0xFF |
| `ISSI_SWPULLUP` | (Optional) Set the value of the SWx lines on-chip de-ghosting resistors | PUR_0R (Disabled) |
| `ISSI_CSPULLUP` | (Optional) Set the value of the CSx lines on-chip de-ghosting resistors | PUR_0R (Disabled) |
| `DRIVER_COUNT` | (Required) How many RGB driver IC's are present | |
| `RGB_MATRIX_LED_COUNT` | (Required) How many RGB lights are present across all drivers | |
| `DRIVER_ADDR_1` | (Required) Address for the first RGB driver | |
| `DRIVER_ADDR_2` | (Optional) Address for the second RGB driver | |
| `DRIVER_ADDR_3` | (Optional) Address for the third RGB driver | |
| `DRIVER_ADDR_4` | (Optional) Address for the fourth RGB driver | |

The IS31FL3737 IC's have on-chip resistors that can be enabled to allow for de-ghosting of the RGB matrix. By default these resistors are not enabled (`ISSI_SWPULLUP`/`ISSI_CSPULLUP` are given the value of`PUR_0R`), the values that can be set to enable de-ghosting are as follows:

| `ISSI_SWPULLUP/ISSI_CSPULLUP` | Description |
|----------------------|-------------|
| `PUR_0R` | (default) Do not use the on-chip resistors/enable de-ghosting |
| `PUR_05KR` | The 0.5k Ohm resistor used during blanking period (t_NOL) |
| `PUR_1KR` | The 1k Ohm resistor used during blanking period (t_NOL) |
| `PUR_2KR` | The 2k Ohm resistor used during blanking period (t_NOL) |
| `PUR_4KR` | The 4k Ohm resistor used during blanking period (t_NOL) |
| `PUR_8KR` | The 8k Ohm resistor during blanking period (t_NOL) |
| `PUR_16KR` | The 16k Ohm resistor during blanking period (t_NOL) |
| `PUR_32KR` | The 32k Ohm resistor used during blanking period (t_NOL) |

Here is an example using 2 drivers.

```c
// This is a 7-bit address, that gets left-shifted and bit 0
// set to 0 for write, 1 for read (as per I2C protocol)
// The address will vary depending on your wiring:
// 0000 <-> GND
// 0101 <-> SCL
// 1010 <-> SDA
// 1111 <-> VCC
// ADDR represents A3:A0 of the 7-bit address.
// The result is: 0b101(ADDR)
#define DRIVER_ADDR_1 0b1010000
#define DRIVER_ADDR_2 0b1010001

#define DRIVER_COUNT 2
#define DRIVER_1_LED_TOTAL 30
#define DRIVER_2_LED_TOTAL 36
#define RGB_MATRIX_LED_COUNT (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)
```
!> Note the parentheses, this is so when `RGB_MATRIX_LED_COUNT` is used in code and expanded, the values are added together before any additional math is applied to them. As an example, `rand() % (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)` will give very different results than `rand() % DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL`.

Define these arrays listing all the LEDs in your `<keyboard>.c`:

```c
const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, B_1,    A_1,    C_1},
    ....
}
```

Where `X_Y` is the location of the LED in the matrix defined by [the datasheet](https://www.issi.com/WW/pdf/31FL3737.pdf) and the header file `drivers/led/issi/is31fl3737.h`. The `driver` is the index of the driver you defined in your `config.h` (Only `0`, `1`, `2`, or `3` for now).

---
### IS31FLCOMMON :id=is31flcommon

There is basic support for addressable RGB matrix lighting with a selection of I2C ISSI Lumissil RGB controllers through a shared common driver. To enable it, add this to your `rules.mk`:

```makefile
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = <driver name>
```

Where `<driver name>` is the applicable LED driver chip as below

| Driver Name | Data Sheet | Capability |
|-------------|------------|------------|
| `IS31FL3742A` | [datasheet](https://www.lumissil.com/assets/pdf/core/IS31FL3742A_DS.pdf) | 60 RGB, 30x6 Matrix |
| `IS31FL3743A` | [datasheet](https://www.lumissil.com/assets/pdf/core/IS31FL3743A_DS.pdf) | 66 RGB, 18x11 Matrix |
| `IS31FL3745` | [datasheet](https://www.lumissil.com/assets/pdf/core/IS31FL3745_DS.pdf) | 48 RGB, 18x8 Matrix |
| `IS31FL3746A` | [datasheet](https://www.lumissil.com/assets/pdf/core/IS31FL3746A_DS.pdf) | 24 RGB, 18x4 Matrix |

You can use between 1 and 4 IC's. Do not specify `DRIVER_ADDR_<N>` define for IC's if not present on your keyboard. The `DRIVER_ADDR_1` default assumes that all Address pins on the controller have been connected to GND. Drivers that have SYNC functionality have the default settings to disable if 1 driver. If more than 1 drivers then `DRIVER_ADDR_1` will be set to Master and the remaining ones set to Slave.

Configure the hardware via your `config.h`:

| Variable | Description | Default |
|----------|-------------|---------|
| `ISSI_TIMEOUT` | (Optional) How long to wait for i2c messages, in milliseconds | 100 |
| `ISSI_PERSISTENCE` | (Optional) Retry failed messages this many times | 0 |
| `DRIVER_COUNT` | (Required) How many RGB driver IC's are present | |
| `RGB_MATRIX_LED_COUNT` | (Required) How many RGB lights are present across all drivers | |
| `DRIVER_ADDR_1` | (Optional) Address for the first RGB driver | |
| `DRIVER_ADDR_<N>` | (Required) Address for the additional RGB drivers | |
| `ISSI_SSR_<N>` | (Optional) Configuration for the Spread Spectrum Register | |
| `ISSI_CONFIGURATION` | (Optional) Configuration for the Configuration Register | |
| `ISSI_GLOBALCURRENT` | (Optional) Configuration for the Global Current Register | 0xFF |
| `ISSI_PULLDOWNUP` | (Optional) Configuration for the Pull Up & Pull Down Register | |
| `ISSI_TEMP` | (Optional) Configuration for the Temperature Register | |
| `ISSI_PWM_ENABLE` | (Optional) Configuration for the PWM Enable Register | |
| `ISSI_PWM_SET` | (Optional) Configuration for the PWM Setting Register | |
| `ISSI_SCAL_RED` | (Optional) Configuration for the RED LEDs in Scaling Registers | 0xFF |
| `ISSI_SCAL_BLUE` | (Optional) Configuration for the BLUE LEDs in Scaling Registers | 0xFF |
| `ISSI_SCAL_GREEN` | (Optional) Configuration for the GREEN LEDs in Scaling Registers | 0xFF |
| `ISSI_MANUAL_SCALING` | (Optional) If you wish to configure the Scaling Registers manually | |


Defaults

| Variable | IS31FL3742A | IS31FL3743A | IS31FL3745 | IS31FL3746 |
|----------|-------------|-------------|------------|------------|
| `DRIVER_ADDR_1` | 0b0110000 | 0b0100000 | 0b0100000 | 0b1100000 |
| `ISSI_SSR_1` | 0x00 | 0x00 / 0x60 | 0x00 / 0xC0 | 0x00 |
| `ISSI_SSR_<2-4>` | 0x00 | 0x40 | 0x80 | 0x00 |
| `ISSI_CONFIGURATION` | 0x31 | 0x01 | 0x31 | 0x01 |
| `ISSI_PULLDOWNUP` | 0x55 | 0x33 | 0x33 | 0x33 |
| `ISSI_TEMP` | N/A | 0x00 | 0x00 | 0x00 |
| `ISSI_PWM_ENABLE` | N/A | N/A | N/A | 0x00 |
| `ISSI_PWM_SET` | 0x00 | N/A | N/A | 0x00 |

Here is an example using 2 drivers.

```c
#define DRIVER_ADDR_2 0b0100001

#define DRIVER_COUNT 2
#define DRIVER_1_LED_TOTAL 66
#define DRIVER_2_LED_TOTAL 42
#define RGB_MATRIX_LED_COUNT (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)
```

!> Note the parentheses, this is so when `RGB_MATRIX_LED_COUNT` is used in code and expanded, the values are added together before any additional math is applied to them. As an example, `rand() % (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)` will give very different results than `rand() % DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL`.

Currently only 4 drivers are supported, but it would be trivial to support for more. Note that using a combination of different drivers is not supported. All drivers must be of the same model.

Define these arrays listing all the LEDs in your `<keyboard>.c`:

```c
const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |        G location
 *   |  |        |        B location
 *   |  |        |        | */
    {0, CS1_SW1, CS2_SW1, CS3_SW1},
    ....
}
```

Where `CSx_SWx` is the location of the LED in the matrix defined by the datasheet. The `driver` is the index of the driver you defined in your `config.h` (`0`, `1`, `2`, or `3` for now).

`ISSI_MANUAL_SCALING` is used to override the Scaling for individual LED's. By default they will be set as per `ISSI_SCAL_<colour>`. In `config.h` set how many LED's you want to manually set scaling for.
Eg `#define ISSI_MANUAL_SCALING 3`

Then Define the array listing all the LEDs you want to override in your `<keyboard>.c`:

```c
const is31_led PROGMEM g_is31_scaling[ISSI_MANUAL_SCALING] = {
 *   LED Index
 *   |  R scaling
 *   |  |    G scaling
 *   |  |    |    B scaling
 *   |  |    |    | */
    {5, 120, 155, 167},
    {9, 120, 155, 167},
    ....
}
```

Where LED Index is the position of the LED in the `g_is31_leds` array. The `scaling` value between 0 and 255 to be written to the Scaling Register.

---

### WS2812 :id=ws2812

There is basic support for addressable RGB matrix lighting with a WS2811/WS2812{a,b,c} addressable LED strand. To enable it, add this to your `rules.mk`:

```make
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = ws2812
```

Configure the hardware via your `config.h`:

```c
// The pin connected to the data pin of the LEDs
#define WS2812_DI_PIN D7
// The number of LEDs connected
#define RGB_MATRIX_LED_COUNT 70
```

?> There are additional configuration options for ARM controllers that offer increased performance over the default bitbang driver. Please see [WS2812 Driver](ws2812_driver.md) for more information.

---

### APA102 :id=apa102

There is basic support for APA102 based addressable LED strands. To enable it, add this to your `rules.mk`:

```make
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = apa102
```

Configure the hardware via your `config.h`:

```c
// The pin connected to the data pin of the LEDs
#define APA102_DI_PIN D7
// The pin connected to the clock pin of the LEDs
#define APA102_CI_PIN D6
// The number of LEDs connected
#define RGB_MATRIX_LED_COUNT 70
```

---
### AW20216S :id=aw20216s
There is basic support for addressable RGB matrix lighting with the SPI AW20216S RGB controller. To enable it, add this to your `rules.mk`:

```make
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = aw20216s
```

You can use up to 2 AW20216S IC's. Do not specify `DRIVER_<N>_xxx` defines for IC's that are not present on your keyboard. You can define the following items in `config.h`:

| Variable | Description | Default |
|----------|-------------|---------|
| `AW20216S_DRIVER_1_CS` | (Required) MCU pin connected to first RGB driver chip select line  | B13 |
| `AW20216S_DRIVER_2_CS` | (Optional) MCU pin connected to second RGB driver chip select line  | |
| `AW20216S_DRIVER_1_EN` | (Required) MCU pin connected to first RGB driver hardware enable line  | C13 |
| `AW20216S_DRIVER_2_EN` | (Optional) MCU pin connected to second RGB driver hardware enable line  | |
| `DRIVER_1_LED_TOTAL` | (Required) How many RGB lights are connected to first RGB driver  | |
| `DRIVER_2_LED_TOTAL` | (Optional) How many RGB lights are connected to second RGB driver  | |
| `AW20216S_DRIVER_COUNT` | (Required) How many RGB driver IC's are present | |
| `RGB_MATRIX_LED_COUNT` | (Required) How many RGB lights are present across all drivers | |
| `AW20216S_SCALING_MAX` | (Optional) LED current scaling value (0-255, higher values mean LED is brighter at full PWM) | 150 |
| `AW20216S_GLOBAL_CURRENT_MAX` | (Optional) Driver global current limit (0-255, higher values means the driver may consume more power) | 150 |
| `AW20216S_SPI_MODE` | (Optional) Mode for SPI communication (0-3, defines polarity and phase of the clock) | 3 |
| `AW20216S_SPI_DIVISOR` | (Optional) Clock divisor for SPI communication (powers of 2, smaller numbers means faster communication, should not be less than 4) | 4 |

Here is an example using 2 drivers.

```c
#define AW20216S_DRIVER_1_CS B13
#define AW20216S_DRIVER_2_CS B14
// Hardware enable lines may be connected to the same pin
#define AW20216S_DRIVER_1_EN C13
#define AW20216S_DRIVER_2_EN C13

#define AW20216S_DRIVER_COUNT 2
#define DRIVER_1_LED_TOTAL 66
#define DRIVER_2_LED_TOTAL 32
#define RGB_MATRIX_LED_COUNT (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)
```

!> Note the parentheses, this is so when `RGB_MATRIX_LED_COUNT` is used in code and expanded, the values are added together before any additional math is applied to them. As an example, `rand() % (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)` will give very different results than `rand() % DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL`.

Define these arrays listing all the LEDs in your `<keyboard>.c`:

```c
const aw20216s_led PROGMEM g_aw20216s_leds[RGB_MATRIX_LED_COUNT] = {
/* Each AW20216S channel is controlled by a register at some offset between 0x00
 * and 0xD7 inclusive.
 * See drivers/led/aw20216s.h for the mapping between register offsets and
 * driver pin locations.
 *    driver
 *    |  R location
 *    |  |        G location
 *    |  |        |        B location
 *    |  |        |        | */
    { 0, CS1_SW1, CS2_SW1, CS3_SW1 },
    { 0, CS4_SW1, CS5_SW1, CS6_SW1 },
    { 0, CS7_SW1, CS8_SW1, CS9_SW1 },
    { 0, CS10_SW1, CS11_SW1, CS12_SW1 },
    { 0, CS13_SW1, CS14_SW1, CS15_SW1 },
    ...
    { 1, CS1_SW1, CS2_SW1, CS3_SW1 },
    { 1, CS13_SW1, CS14_SW1, CS15_SW1 },
    { 1, CS16_SW1, CS17_SW1, CS18_SW1 },
    { 1, CS4_SW2, CS5_SW2, CS6_SW2 },
    ...
};
```

---

## Common Configuration :id=common-configuration

From this point forward the configuration is the same for all the drivers. The `led_config_t` struct provides a key electrical matrix to led index lookup table, what the physical position of each LED is on the board, and what type of key or usage the LED if the LED represents. Here is a brief example:

```c
led_config_t g_led_config = { {
  // Key Matrix to LED Index
  {   5, NO_LED, NO_LED,   0 },
  { NO_LED, NO_LED, NO_LED, NO_LED },
  {   4, NO_LED, NO_LED,   1 },
  {   3, NO_LED, NO_LED,   2 }
}, {
  // LED Index to Physical Position
  { 188,  16 }, { 187,  48 }, { 149,  64 }, { 112,  64 }, {  37,  48 }, {  38,  16 }
}, {
  // LED Index to Flag
  1, 4, 4, 4, 4, 1
} };
```

The first part, `// Key Matrix to LED Index`, tells the system what key this LED represents by using the key's electrical matrix row & col. The second part, `// LED Index to Physical Position` represents the LED's physical `{ x, y }` position on the keyboard. The default expected range of values for `{ x, y }` is the inclusive range `{ 0..224, 0..64 }`. This default expected range is due to effects that calculate the center of the keyboard for their animations. The easiest way to calculate these positions is imagine your keyboard is a grid, and the top left of the keyboard represents `{ x, y }` coordinate `{ 0, 0 }` and the bottom right of your keyboard represents `{ 224, 64 }`. Using this as a basis, you can use the following formula to calculate the physical position:

```c
x = 224 / (NUMBER_OF_COLS - 1) * COL_POSITION
y =  64 / (NUMBER_OF_ROWS - 1) * ROW_POSITION
```

Where NUMBER_OF_COLS, NUMBER_OF_ROWS, COL_POSITION, & ROW_POSITION are all based on the physical layout of your keyboard, not the electrical layout.

As mentioned earlier, the center of the keyboard by default is expected to be `{ 112, 32 }`, but this can be changed if you want to more accurately calculate the LED's physical `{ x, y }` positions. Keyboard designers can implement `#define RGB_MATRIX_CENTER { 112, 32 }` in their config.h file with the new center point of the keyboard, or where they want it to be allowing more possibilities for the `{ x, y }` values. Do note that the maximum value for x or y is 255, and the recommended maximum is 224 as this gives animations runoff room before they reset.

`// LED Index to Flag` is a bitmask, whether or not a certain LEDs is of a certain type. It is recommended that LEDs are set to only 1 type.

## Flags :id=flags

|Define                      |Value |Description                                      |
|----------------------------|------|-------------------------------------------------|
|`HAS_FLAGS(bits, flags)`    |*n/a* |Evaluates to `true` if `bits` has all `flags` set|
|`HAS_ANY_FLAGS(bits, flags)`|*n/a* |Evaluates to `true` if `bits` has any `flags` set|
|`LED_FLAG_NONE`             |`0x00`|If this LED has no flags                         |
|`LED_FLAG_ALL`              |`0xFF`|If this LED has all flags                        |
|`LED_FLAG_MODIFIER`         |`0x01`|If the LED is on a modifier key                  |
|`LED_FLAG_UNDERGLOW`        |`0x02`|If the LED is for underglow                      |
|`LED_FLAG_KEYLIGHT`         |`0x04`|If the LED is for key backlight                  |
|`LED_FLAG_INDICATOR`        |`0x08`|If the LED is for keyboard state indication      |

## Keycodes :id=keycodes

All RGB keycodes are currently shared with the RGBLIGHT system:

|Key                |Aliases   |Description                                                                           |
|-------------------|----------|--------------------------------------------------------------------------------------|
|`RGB_TOG`          |          |Toggle RGB lighting on or off                                                         |
|`RGB_MODE_FORWARD` |`RGB_MOD` |Cycle through modes, reverse direction when Shift is held                             |
|`RGB_MODE_REVERSE` |`RGB_RMOD`|Cycle through modes in reverse, forward direction when Shift is held                  |
|`RGB_HUI`          |          |Increase hue, decrease hue when Shift is held                                         |
|`RGB_HUD`          |          |Decrease hue, increase hue when Shift is held                                         |
|`RGB_SAI`          |          |Increase saturation, decrease saturation when Shift is held                           |
|`RGB_SAD`          |          |Decrease saturation, increase saturation when Shift is held                           |
|`RGB_VAI`          |          |Increase value (brightness), decrease value when Shift is held                        |
|`RGB_VAD`          |          |Decrease value (brightness), increase value when Shift is held                        |
|`RGB_SPI`          |          |Increase effect speed (does not support eeprom yet), decrease speed when Shift is held|
|`RGB_SPD`          |          |Decrease effect speed (does not support eeprom yet), increase speed when Shift is held|
|`RGB_MODE_PLAIN`   |`RGB_M_P` |Static (no animation) mode                                                            |
|`RGB_MODE_BREATHE` |`RGB_M_B` |Breathing animation mode                                                              |
|`RGB_MODE_RAINBOW` |`RGB_M_R` |Full gradient scrolling left to right (uses the `RGB_MATRIX_CYCLE_LEFT_RIGHT` mode)   |
|`RGB_MODE_SWIRL`   |`RGB_M_SW`|Full gradient spinning pinwheel around center of keyboard (uses `RGB_MATRIX_CYCLE_PINWHEEL` mode) |

* `RGB_MODE_*` keycodes will generally work, but not all of the modes are currently mapped to the correct effects for the RGB Matrix system.

`RGB_MODE_PLAIN`, `RGB_MODE_BREATHE`, `RGB_MODE_RAINBOW`, and `RGB_MODE_SWIRL` are the only ones that are mapped properly. The rest don't have a direct equivalent, and are not mapped.

?> `RGB_*` keycodes cannot be used with functions like `tap_code16(RGB_HUD)` as they're not USB HID keycodes. If you wish to replicate similar behaviour in custom code within your firmware (e.g. inside `encoder_update_user()` or `process_record_user()`), the equivalent [RGB functions](#functions) should be used instead.


!> By default, if you have both the [RGB Light](feature_rgblight.md) and the RGB Matrix feature enabled, these keycodes will work for both features, at the same time. You can disable the keycode functionality by defining the `*_DISABLE_KEYCODES` option for the specific feature.

## RGB Matrix Effects :id=rgb-matrix-effects

All effects have been configured to support current configuration values (Hue, Saturation, Value, & Speed) unless otherwise noted below. These are the effects that are currently available:

```c
enum rgb_matrix_effects {
    RGB_MATRIX_NONE = 0,
    RGB_MATRIX_SOLID_COLOR = 1,     // Static single hue, no speed support
    RGB_MATRIX_ALPHAS_MODS,         // Static dual hue, speed is hue for secondary hue
    RGB_MATRIX_GRADIENT_UP_DOWN,    // Static gradient top to bottom, speed controls how much gradient changes
    RGB_MATRIX_GRADIENT_LEFT_RIGHT,    // Static gradient left to right, speed controls how much gradient changes
    RGB_MATRIX_BREATHING,           // Single hue brightness cycling animation
    RGB_MATRIX_BAND_SAT,        // Single hue band fading saturation scrolling left to right
    RGB_MATRIX_BAND_VAL,        // Single hue band fading brightness scrolling left to right
    RGB_MATRIX_BAND_PINWHEEL_SAT,   // Single hue 3 blade spinning pinwheel fades saturation
    RGB_MATRIX_BAND_PINWHEEL_VAL,   // Single hue 3 blade spinning pinwheel fades brightness
    RGB_MATRIX_BAND_SPIRAL_SAT,     // Single hue spinning spiral fades saturation
    RGB_MATRIX_BAND_SPIRAL_VAL,     // Single hue spinning spiral fades brightness
    RGB_MATRIX_CYCLE_ALL,           // Full keyboard solid hue cycling through full gradient
    RGB_MATRIX_CYCLE_LEFT_RIGHT,    // Full gradient scrolling left to right
    RGB_MATRIX_CYCLE_UP_DOWN,       // Full gradient scrolling top to bottom
    RGB_MATRIX_CYCLE_OUT_IN,        // Full gradient scrolling out to in
    RGB_MATRIX_CYCLE_OUT_IN_DUAL,   // Full dual gradients scrolling out to in
    RGB_MATRIX_RAINBOW_MOVING_CHEVRON,  // Full gradient Chevron shapped scrolling left to right
    RGB_MATRIX_CYCLE_PINWHEEL,      // Full gradient spinning pinwheel around center of keyboard
    RGB_MATRIX_CYCLE_SPIRAL,        // Full gradient spinning spiral around center of keyboard
    RGB_MATRIX_DUAL_BEACON,         // Full gradient spinning around center of keyboard
    RGB_MATRIX_RAINBOW_BEACON,      // Full tighter gradient spinning around center of keyboard
    RGB_MATRIX_RAINBOW_PINWHEELS,   // Full dual gradients spinning two halfs of keyboard
    RGB_MATRIX_RAINDROPS,           // Randomly changes a single key's hue
    RGB_MATRIX_JELLYBEAN_RAINDROPS, // Randomly changes a single key's hue and saturation
    RGB_MATRIX_HUE_BREATHING,       // Hue shifts up a slight ammount at the same time, then shifts back
    RGB_MATRIX_HUE_PENDULUM,        // Hue shifts up a slight ammount in a wave to the right, then back to the left
    RGB_MATRIX_HUE_WAVE,            // Hue shifts up a slight ammount and then back down in a wave to the right
    RGB_MATRIX_PIXEL_FRACTAL,       // Single hue fractal filled keys pulsing horizontally out to edges
    RGB_MATRIX_PIXEL_FLOW,          // Pulsing RGB flow along LED wiring with random hues
    RGB_MATRIX_PIXEL_RAIN,          // Randomly light keys with random hues
    RGB_MATRIX_TYPING_HEATMAP,      // How hot is your WPM!
    RGB_MATRIX_DIGITAL_RAIN,        // That famous computer simulation
    RGB_MATRIX_SOLID_REACTIVE_SIMPLE,   // Pulses keys hit to hue & value then fades value out
    RGB_MATRIX_SOLID_REACTIVE,      // Static single hue, pulses keys hit to shifted hue then fades to current hue
    RGB_MATRIX_SOLID_REACTIVE_WIDE       // Hue & value pulse near a single key hit then fades value out
    RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE  // Hue & value pulse near multiple key hits then fades value out
    RGB_MATRIX_SOLID_REACTIVE_CROSS      // Hue & value pulse the same column and row of a single key hit then fades value out
    RGB_MATRIX_SOLID_REACTIVE_MULTICROSS // Hue & value pulse the same column and row of multiple key hits then fades value out
    RGB_MATRIX_SOLID_REACTIVE_NEXUS      // Hue & value pulse away on the same column and row of a single key hit then fades value out
    RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS // Hue & value pulse away on the same column and row of multiple key hits then fades value out
    RGB_MATRIX_SPLASH,              // Full gradient & value pulse away from a single key hit then fades value out
    RGB_MATRIX_MULTISPLASH,         // Full gradient & value pulse away from multiple key hits then fades value out
    RGB_MATRIX_SOLID_SPLASH,        // Hue & value pulse away from a single key hit then fades value out
    RGB_MATRIX_SOLID_MULTISPLASH,   // Hue & value pulse away from multiple key hits then fades value out
    RGB_MATRIX_EFFECT_MAX
};
```

You can enable a single effect by defining `ENABLE_[EFFECT_NAME]` in your `config.h`:


|Define                                                |Description                                   |
|------------------------------------------------------|----------------------------------------------|
|`#define ENABLE_RGB_MATRIX_ALPHAS_MODS`               |Enables `RGB_MATRIX_ALPHAS_MODS`              |
|`#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN`          |Enables `RGB_MATRIX_GRADIENT_UP_DOWN`         |
|`#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT`       |Enables `RGB_MATRIX_GRADIENT_LEFT_RIGHT`      |
|`#define ENABLE_RGB_MATRIX_BREATHING`                 |Enables `RGB_MATRIX_BREATHING`                |
|`#define ENABLE_RGB_MATRIX_BAND_SAT`                  |Enables `RGB_MATRIX_BAND_SAT`                 |
|`#define ENABLE_RGB_MATRIX_BAND_VAL`                  |Enables `RGB_MATRIX_BAND_VAL`                 |
|`#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT`         |Enables `RGB_MATRIX_BAND_PINWHEEL_SAT`        |
|`#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL`         |Enables `RGB_MATRIX_BAND_PINWHEEL_VAL`        |
|`#define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT`           |Enables `RGB_MATRIX_BAND_SPIRAL_SAT`          |
|`#define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL`           |Enables `RGB_MATRIX_BAND_SPIRAL_VAL`          |
|`#define ENABLE_RGB_MATRIX_CYCLE_ALL`                 |Enables `RGB_MATRIX_CYCLE_ALL`                |
|`#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT`          |Enables `RGB_MATRIX_CYCLE_LEFT_RIGHT`         |
|`#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN`             |Enables `RGB_MATRIX_CYCLE_UP_DOWN`            |
|`#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON`    |Enables `RGB_MATRIX_RAINBOW_MOVING_CHEVRON`   |
|`#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN`              |Enables `RGB_MATRIX_CYCLE_OUT_IN`             |
|`#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL`         |Enables `RGB_MATRIX_CYCLE_OUT_IN_DUAL`        |
|`#define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL`            |Enables `RGB_MATRIX_CYCLE_PINWHEEL`           |
|`#define ENABLE_RGB_MATRIX_CYCLE_SPIRAL`              |Enables `RGB_MATRIX_CYCLE_SPIRAL`             |
|`#define ENABLE_RGB_MATRIX_DUAL_BEACON`               |Enables `RGB_MATRIX_DUAL_BEACON`              |
|`#define ENABLE_RGB_MATRIX_RAINBOW_BEACON`            |Enables `RGB_MATRIX_RAINBOW_BEACON`           |
|`#define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS`         |Enables `RGB_MATRIX_RAINBOW_PINWHEELS`        |
|`#define ENABLE_RGB_MATRIX_RAINDROPS`                 |Enables `RGB_MATRIX_RAINDROPS`                |
|`#define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS`       |Enables `RGB_MATRIX_JELLYBEAN_RAINDROPS`      |
|`#define ENABLE_RGB_MATRIX_HUE_BREATHING`             |Enables `RGB_MATRIX_HUE_BREATHING`            |
|`#define ENABLE_RGB_MATRIX_HUE_PENDULUM`              |Enables `RGB_MATRIX_HUE_PENDULUM`             |
|`#define ENABLE_RGB_MATRIX_HUE_WAVE`                  |Enables `RGB_MATRIX_HUE_WAVE `                |
|`#define ENABLE_RGB_MATRIX_PIXEL_FRACTAL`             |Enables `RGB_MATRIX_PIXEL_FRACTAL`            |
|`#define ENABLE_RGB_MATRIX_PIXEL_FLOW`                |Enables `RGB_MATRIX_PIXEL_FLOW`               |
|`#define ENABLE_RGB_MATRIX_PIXEL_RAIN`                |Enables `RGB_MATRIX_PIXEL_RAIN`               |

|Framebuffer Defines                                   |Description                                   |
|------------------------------------------------------|----------------------------------------------|
|`#define ENABLE_RGB_MATRIX_TYPING_HEATMAP`            |Enables `RGB_MATRIX_TYPING_HEATMAP`           |
|`#define ENABLE_RGB_MATRIX_DIGITAL_RAIN`              |Enables `RGB_MATRIX_DIGITAL_RAIN`             |

?> These modes introduce additional logic that can increase firmware size.

|Reactive Defines                                    |Description                                   |
|------------------------------------------------------|----------------------------------------------|
|`#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE`     |Enables `RGB_MATRIX_SOLID_REACTIVE_SIMPLE`    |
|`#define ENABLE_RGB_MATRIX_SOLID_REACTIVE`            |Enables `RGB_MATRIX_SOLID_REACTIVE`           |
|`#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE`       |Enables `RGB_MATRIX_SOLID_REACTIVE_WIDE`      |
|`#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE`  |Enables `RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE` |
|`#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS`      |Enables `RGB_MATRIX_SOLID_REACTIVE_CROSS`     |
|`#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS` |Enables `RGB_MATRIX_SOLID_REACTIVE_MULTICROSS`|
|`#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS`      |Enables `RGB_MATRIX_SOLID_REACTIVE_NEXUS`     |
|`#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS` |Enables `RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS`|
|`#define ENABLE_RGB_MATRIX_SPLASH`                    |Enables `RGB_MATRIX_SPLASH`                   |
|`#define ENABLE_RGB_MATRIX_MULTISPLASH`               |Enables `RGB_MATRIX_MULTISPLASH`              |
|`#define ENABLE_RGB_MATRIX_SOLID_SPLASH`              |Enables `RGB_MATRIX_SOLID_SPLASH`             |
|`#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH`         |Enables `RGB_MATRIX_SOLID_MULTISPLASH`        |

?> These modes introduce additional logic that can increase firmware size.


### RGB Matrix Effect Typing Heatmap :id=rgb-matrix-effect-typing-heatmap

This effect will color the RGB matrix according to a heatmap of recently pressed keys. Whenever a key is pressed its "temperature" increases as well as that of its neighboring keys. The temperature of each key is then decreased automatically every 25 milliseconds by default.

In order to change the delay of temperature decrease define `RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS`:

```c
#define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 50
```

As heatmap uses the physical position of the leds set in the g_led_config, you may need to tweak the following options to get the best effect for your keyboard. Note the size of this grid is `224x64`.

Limit the distance the effect spreads to surrounding keys. 

```c
#define RGB_MATRIX_TYPING_HEATMAP_SPREAD 40
```

Limit how hot surrounding keys get from each press.

```c
#define RGB_MATRIX_TYPING_HEATMAP_AREA_LIMIT 16
```

Remove the spread effect entirely.

```c
#define RGB_MATRIX_TYPING_HEATMAP_SLIM
```

It's also possible to adjust the tempo of *heating up*. It's defined as the number of shades that are
increased on the [HSV scale](https://en.wikipedia.org/wiki/HSL_and_HSV). Decreasing this value increases
the number of keystrokes needed to fully heat up the key.

```c
#define RGB_MATRIX_TYPING_HEATMAP_INCREASE_STEP 32
```

### RGB Matrix Effect Solid Reactive :id=rgb-matrix-effect-solid-reactive

Solid reactive effects will pulse RGB light on key presses with user configurable hues. To enable gradient mode that will automatically change reactive color, add the following define:

```c
#define RGB_MATRIX_SOLID_REACTIVE_GRADIENT_MODE
```

Gradient mode will loop through the color wheel hues over time and its duration can be controlled with the effect speed keycodes (`RGB_SPI`/`RGB_SPD`).

## Custom RGB Matrix Effects :id=custom-rgb-matrix-effects

By setting `RGB_MATRIX_CUSTOM_USER = yes` in `rules.mk`, new effects can be defined directly from your keymap or userspace, without having to edit any QMK core files. To declare new effects, create a `rgb_matrix_user.inc` file in the user keymap directory or userspace folder.

?> Hardware maintainers who want to limit custom effects to a specific keyboard can create a `rgb_matrix_kb.inc` file in the root of the keyboard directory, and add `RGB_MATRIX_CUSTOM_KB = yes` to the keyboard level `rules.mk`.

To use custom effects in your code, simply prepend `RGB_MATRIX_CUSTOM_` to the effect name specified in `RGB_MATRIX_EFFECT()`. For example, an effect declared as `RGB_MATRIX_EFFECT(my_cool_effect)` would be referenced with:

```c
rgb_matrix_mode(RGB_MATRIX_CUSTOM_my_cool_effect);
```

```c
// !!! DO NOT ADD #pragma once !!! //

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(my_cool_effect)
RGB_MATRIX_EFFECT(my_cool_effect2)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// e.g: A simple effect, self-contained within a single method
static bool my_cool_effect(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (uint8_t i = led_min; i < led_max; i++) {
    rgb_matrix_set_color(i, 0xff, 0xff, 0x00);
  }
  return rgb_matrix_check_finished_leds(led_max);
}

// e.g: A more complex effect, relying on external methods and state, with
// dedicated init and run methods
static uint8_t some_global_state;
static void my_cool_effect2_complex_init(effect_params_t* params) {
  some_global_state = 1;
}
static bool my_cool_effect2_complex_run(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (uint8_t i = led_min; i < led_max; i++) {
    rgb_matrix_set_color(i, 0xff, some_global_state++, 0xff);
  }
  return rgb_matrix_check_finished_leds(led_max);
}
static bool my_cool_effect2(effect_params_t* params) {
  if (params->init) my_cool_effect2_complex_init(params);
  return my_cool_effect2_complex_run(params);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
```

For inspiration and examples, check out the built-in effects under `quantum/rgb_matrix/animations/`.


## Colors :id=colors

These are shorthands to popular colors. The `RGB` ones can be passed to the `setrgb` functions, while the `HSV` ones to the `sethsv` functions.

|RGB                  |HSV                  |
|---------------------|---------------------|
|`RGB_AZURE`          |`HSV_AZURE`          |
|`RGB_BLACK`/`RGB_OFF`|`HSV_BLACK`/`HSV_OFF`|
|`RGB_BLUE`           |`HSV_BLUE`           |
|`RGB_CHARTREUSE`     |`HSV_CHARTREUSE`     |
|`RGB_CORAL`          |`HSV_CORAL`          |
|`RGB_CYAN`           |`HSV_CYAN`           |
|`RGB_GOLD`           |`HSV_GOLD`           |
|`RGB_GOLDENROD`      |`HSV_GOLDENROD`      |
|`RGB_GREEN`          |`HSV_GREEN`          |
|`RGB_MAGENTA`        |`HSV_MAGENTA`        |
|`RGB_ORANGE`         |`HSV_ORANGE`         |
|`RGB_PINK`           |`HSV_PINK`           |
|`RGB_PURPLE`         |`HSV_PURPLE`         |
|`RGB_RED`            |`HSV_RED`            |
|`RGB_SPRINGGREEN`    |`HSV_SPRINGGREEN`    |
|`RGB_TEAL`           |`HSV_TEAL`           |
|`RGB_TURQUOISE`      |`HSV_TURQUOISE`      |
|`RGB_WHITE`          |`HSV_WHITE`          |
|`RGB_YELLOW`         |`HSV_YELLOW`         |

These are defined in [`color.h`](https://github.com/qmk/qmk_firmware/blob/master/quantum/color.h). Feel free to add to this list!


## Additional `config.h` Options :id=additional-configh-options

```c
#define RGB_MATRIX_KEYRELEASES // reactive effects respond to keyreleases (instead of keypresses)
#define RGB_MATRIX_TIMEOUT 0 // number of milliseconds to wait until rgb automatically turns off
#define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended
#define RGB_MATRIX_LED_PROCESS_LIMIT (RGB_MATRIX_LED_COUNT + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
#define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200 // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CYCLE_LEFT_RIGHT // Sets the default mode, if none has been set
#define RGB_MATRIX_DEFAULT_HUE 0 // Sets the default hue value, if none has been set
#define RGB_MATRIX_DEFAULT_SAT 255 // Sets the default saturation value, if none has been set
#define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS // Sets the default brightness value, if none has been set
#define RGB_MATRIX_DEFAULT_SPD 127 // Sets the default animation speed, if none has been set
#define RGB_MATRIX_DISABLE_KEYCODES // disables control of rgb matrix by keycodes (must use code functions to control the feature)
#define RGB_MATRIX_SPLIT { X, Y } 	// (Optional) For split keyboards, the number of LEDs connected on each half. X = left, Y = Right.
                              		// If reactive effects are enabled, you also will want to enable SPLIT_TRANSPORT_MIRROR
#define RGB_TRIGGER_ON_KEYDOWN      // Triggers RGB keypress events on key down. This makes RGB control feel more responsive. This may cause RGB to not function properly on some boards
```

## EEPROM storage :id=eeprom-storage

The EEPROM for it is currently shared with the LED Matrix system (it's generally assumed only one feature would be used at a time).

## Functions :id=functions

### Direct Operation :id=direct-operation
|Function                                    |Description  |
|--------------------------------------------|-------------|
|`rgb_matrix_set_color_all(r, g, b)`         |Set all of the LEDs to the given RGB value, where `r`/`g`/`b` are between 0 and 255 (not written to EEPROM) |
|`rgb_matrix_set_color(index, r, g, b)`      |Set a single LED to the given RGB value, where `r`/`g`/`b` are between 0 and 255, and `index` is between 0 and `RGB_MATRIX_LED_COUNT` (not written to EEPROM) |

### Disable/Enable Effects :id=disable-enable-effects
|Function                                    |Description  |
|--------------------------------------------|-------------|
|`rgb_matrix_toggle()`                       |Toggle effect range LEDs between on and off |
|`rgb_matrix_toggle_noeeprom()`              |Toggle effect range LEDs between on and off (not written to EEPROM) |
|`rgb_matrix_enable()`                       |Turn effect range LEDs on, based on their previous state |
|`rgb_matrix_enable_noeeprom()`              |Turn effect range LEDs on, based on their previous state (not written to EEPROM) |
|`rgb_matrix_disable()`                      |Turn effect range LEDs off, based on their previous state |
|`rgb_matrix_disable_noeeprom()`             |Turn effect range LEDs off, based on their previous state (not written to EEPROM) |

### Change Effect Mode :id=change-effect-mode
|Function                                    |Description  |
|--------------------------------------------|-------------|
|`rgb_matrix_mode(mode)`                     |Set the mode, if RGB animations are enabled |
|`rgb_matrix_mode_noeeprom(mode)`            |Set the mode, if RGB animations are enabled (not written to EEPROM) |
|`rgb_matrix_step()`                         |Change the mode to the next RGB animation in the list of enabled RGB animations |
|`rgb_matrix_step_noeeprom()`                |Change the mode to the next RGB animation in the list of enabled RGB animations (not written to EEPROM) |
|`rgb_matrix_step_reverse()`                 |Change the mode to the previous RGB animation in the list of enabled RGB animations |
|`rgb_matrix_step_reverse_noeeprom()`        |Change the mode to the previous RGB animation in the list of enabled RGB animations (not written to EEPROM) |
|`rgb_matrix_increase_speed()`               |Increase the speed of the animations |
|`rgb_matrix_increase_speed_noeeprom()`      |Increase the speed of the animations (not written to EEPROM) |
|`rgb_matrix_decrease_speed()`               |Decrease the speed of the animations |
|`rgb_matrix_decrease_speed_noeeprom()`      |Decrease the speed of the animations (not written to EEPROM) |
|`rgb_matrix_set_speed(speed)`               |Set the speed of the animations to the given value where `speed` is between 0 and 255 |
|`rgb_matrix_set_speed_noeeprom(speed)`      |Set the speed of the animations to the given value where `speed` is between 0 and 255 (not written to EEPROM) |
|`rgb_matrix_reload_from_eeprom()`           |Reload the effect configuration (enabled, mode and color) from EEPROM |

### Change Color :id=change-color
|Function                                    |Description  |
|--------------------------------------------|-------------|
|`rgb_matrix_increase_hue()`                 |Increase the hue for effect range LEDs. This wraps around at maximum hue |
|`rgb_matrix_increase_hue_noeeprom()`        |Increase the hue for effect range LEDs. This wraps around at maximum hue (not written to EEPROM) |
|`rgb_matrix_decrease_hue()`                 |Decrease the hue for effect range LEDs. This wraps around at minimum hue |
|`rgb_matrix_decrease_hue_noeeprom()`        |Decrease the hue for effect range LEDs. This wraps around at minimum hue (not written to EEPROM) |
|`rgb_matrix_increase_sat()`                 |Increase the saturation for effect range LEDs. This wraps around at maximum saturation |
|`rgb_matrix_increase_sat_noeeprom()`        |Increase the saturation for effect range LEDs. This wraps around at maximum saturation (not written to EEPROM) |
|`rgb_matrix_decrease_sat()`                 |Decrease the saturation for effect range LEDs. This wraps around at minimum saturation |
|`rgb_matrix_decrease_sat_noeeprom()`        |Decrease the saturation for effect range LEDs. This wraps around at minimum saturation (not written to EEPROM) |
|`rgb_matrix_increase_val()`                 |Increase the value for effect range LEDs. This wraps around at maximum value |
|`rgb_matrix_increase_val_noeeprom()`        |Increase the value for effect range LEDs. This wraps around at maximum value (not written to EEPROM) |
|`rgb_matrix_decrease_val()`                 |Decrease the value for effect range LEDs. This wraps around at minimum value |
|`rgb_matrix_decrease_val_noeeprom()`        |Decrease the value for effect range LEDs. This wraps around at minimum value (not written to EEPROM) |
|`rgb_matrix_sethsv(h, s, v)`                |Set LEDs to the given HSV value where `h`/`s`/`v` are between 0 and 255 |
|`rgb_matrix_sethsv_noeeprom(h, s, v)`       |Set LEDs to the given HSV value where `h`/`s`/`v` are between 0 and 255 (not written to EEPROM) |

### Query Current Status :id=query-current-status
|Function                         |Description                |
|---------------------------------|---------------------------|
|`rgb_matrix_is_enabled()`        |Gets current on/off status |
|`rgb_matrix_get_mode()`          |Gets current mode          |
|`rgb_matrix_get_hue()`           |Gets current hue           |
|`rgb_matrix_get_sat()`           |Gets current sat           |
|`rgb_matrix_get_val()`           |Gets current val           |
|`rgb_matrix_get_hsv()`           |Gets hue, sat, and val and returns a [`HSV` structure](https://github.com/qmk/qmk_firmware/blob/7ba6456c0b2e041bb9f97dbed265c5b8b4b12192/quantum/color.h#L56-L61)|
|`rgb_matrix_get_speed()`         |Gets current speed         |
|`rgb_matrix_get_suspend_state()` |Gets current suspend state |

## Callbacks :id=callbacks

### Indicators :id=indicators

If you want to set custom indicators, such as an LED for Caps Lock, or layer indication, then you can use the `rgb_matrix_indicators_kb` function on the keyboard level source file, or `rgb_matrix_indicators_user` function in the user `keymap.c`.
```c
bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    rgb_matrix_set_color(index, red, green, blue);
    return true;
}
```

In addition, there are the advanced indicator functions.  These are aimed at those with heavily customized displays, where rendering every LED per cycle is expensive.  Such as some of the "drashna" layouts.  This includes a special macro to help make this easier to use: `RGB_MATRIX_INDICATOR_SET_COLOR(i, r, g, b)`.

```c
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    RGB_MATRIX_INDICATOR_SET_COLOR(index, red, green, blue);
    return false;
}
```

### Indicator Examples :id=indicator-examples

Caps Lock indicator on alphanumeric flagged keys:
```c
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        for (uint8_t i = led_min; i < led_max; i++) {
            if (g_led_config.flags[i] & LED_FLAG_KEYLIGHT) {
                rgb_matrix_set_color(i, RGB_RED);
            }
        }
    }
    return false;
}
```

Layer indicator on all keys:
```c
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = led_min; i < led_max; i++) {
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case 2:
                rgb_matrix_set_color(i, RGB_BLUE);
                break;
            case 1:
                rgb_matrix_set_color(i, RGB_YELLOW);
                break;
            default:
                break;
        }
    }
    return false;
}
```

Layer indicator only on keys with configured keycodes:
```c
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (get_highest_layer(layer_state) > 0) {
        uint8_t layer = get_highest_layer(layer_state);

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if (index >= led_min && index < led_max && index != NO_LED &&
                keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                    rgb_matrix_set_color(index, RGB_GREEN);
                }
            }
        }
    }
    return false;
}
```

?> Split keyboards will require layer state data syncing with `#define SPLIT_LAYER_STATE_ENABLE`. See [Data Sync Options](feature_split_keyboard?id=data-sync-options) for more details.

#### Examples :id=indicator-examples

This example sets the modifiers to be a specific color based on the layer state.  You can use a switch case here, instead, if you would like.  This uses HSV and then converts to RGB, because this allows the brightness to be limited (important when using the WS2812 driver).

```c
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    HSV hsv = {0, 255, 255};

    if (layer_state_is(layer_state, 2)) {
        hsv = {130, 255, 255};
    } else {
        hsv = {30, 255, 255};
    }

    if (hsv.v > rgb_matrix_get_val()) {
        hsv.v = rgb_matrix_get_val();
    }
    RGB rgb = hsv_to_rgb(hsv);

    for (uint8_t i = led_min; i < led_max; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], 0x01)) { // 0x01 == LED_FLAG_MODIFIER
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
    return false;
}
```

If you want to indicate a Host LED status (caps lock, num lock, etc), you can use something like this to light up the caps lock key:

```c
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(5, 255, 255, 255); // assuming caps lock is at led #5
    } else {
        RGB_MATRIX_INDICATOR_SET_COLOR(5, 0, 0, 0);
    }
    return false;
}
```

?> RGB indicators on split keyboards will require state information synced to the slave half (e.g. `#define SPLIT_LAYER_STATE_ENABLE`). See [data sync options](feature_split_keyboard.md#data-sync-options) for more details.

#### Indicators without RGB Matrix Effect

If you want to just use RGB indicators without RGB matrix effect, it is not possible to disable the latter because toggling RGB off will disable everything. You can workaround it with solid effect and colors off using this init function:
```c
void keyboard_post_init_user(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
}
```
