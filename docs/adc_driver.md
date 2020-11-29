# ADC Driver

QMK can leverage the Analog-to-Digital Converter (ADC) on supported MCUs to measure voltages on certain pins. This can be useful for implementing things such as battery level indicators for Bluetooth keyboards, or volume controls using a potentiometer, as opposed to a [rotary encoder](feature_encoders.md).

This driver currently supports both AVR and a limited selection of ARM devices. The values returned are 10-bit integers (0-1023) mapped between 0V and VCC (usually 5V or 3.3V for AVR, 3.3V only for ARM), however on ARM there is more flexibility in control of operation through `#define`s if you need more precision.

## Usage

To use this driver, add the following to your `rules.mk`:

```make
SRC += analog.c
```

Then place this include at the top of your code:

```c
#include "analog.h"
```

## Channels

### AVR

|Channel|AT90USB64/128|ATmega16/32U4|ATmega32A|ATmega328/P|
|-------|-------------|-------------|---------|----------|
|0      |`F0`         |`F0`         |`A0`     |`C0`      |
|1      |`F1`         |`F1`         |`A1`     |`C1`      |
|2      |`F2`         |             |`A2`     |`C2`      |
|3      |`F3`         |             |`A3`     |`C3`      |
|4      |`F4`         |`F4`         |`A4`     |`C4`      |
|5      |`F5`         |`F5`         |`A5`     |`C5`      |
|6      |`F6`         |`F6`         |`A6`     |*         |
|7      |`F7`         |`F7`         |`A7`     |*         |
|8      |             |`D4`         |         |          |
|9      |             |`D6`         |         |          |
|10     |             |`D7`         |         |          |
|11     |             |`B4`         |         |          |
|12     |             |`B5`         |         |          |
|13     |             |`B6`         |         |          |

<sup>\* The ATmega328/P possesses two extra ADC channels; however, they are not present on the DIP pinout, and are not shared with GPIO pins. You can use `adc_read()` directly to gain access to these.</sup>

### ARM

Note that some of these pins are doubled-up on ADCs with the same channel. This is because the pins can be used for either ADC.

Also note that the F0 and F3 use different numbering schemes. The F0 has a single ADC and the channels are 0-based, whereas the F3 has 4 ADCs and the channels are 1 based. This is because the F0 uses the `ADCv1` implementation of the ADC, whereas the F3 uses the `ADCv3` implementation.

|ADC|Channel|STM32F0XX|STM32F3XX|
|---|-------|---------|---------|
|1  |0      |`A0`     |         |
|1  |1      |`A1`     |`A0`     |
|1  |2      |`A2`     |`A1`     |
|1  |3      |`A3`     |`A2`     |
|1  |4      |`A4`     |`A3`     |
|1  |5      |`A5`     |`F4`     |
|1  |6      |`A6`     |`C0`     |
|1  |7      |`A7`     |`C1`     |
|1  |8      |`B0`     |`C2`     |
|1  |9      |`B1`     |`C3`     |
|1  |10     |`C0`     |`F2`     |
|1  |11     |`C1`     |         |
|1  |12     |`C2`     |         |
|1  |13     |`C3`     |         |
|1  |14     |`C4`     |         |
|1  |15     |`C5`     |         |
|1  |16     |         |         |
|2  |1      |         |`A4`     |
|2  |2      |         |`A5`     |
|2  |3      |         |`A6`     |
|2  |4      |         |`A7`     |
|2  |5      |         |`C4`     |
|2  |6      |         |`C0`     |
|2  |7      |         |`C1`     |
|2  |8      |         |`C2`     |
|2  |9      |         |`C3`     |
|2  |10     |         |`F2`     |
|2  |11     |         |`C5`     |
|2  |12     |         |`B2`     |
|2  |13     |         |         |
|2  |14     |         |         |
|2  |15     |         |         |
|2  |16     |         |         |
|3  |1      |         |`B1`     |
|3  |2      |         |`E9`     |
|3  |3      |         |`E13`    |
|3  |4      |         |         |
|3  |5      |         |         |
|3  |6      |         |`E8`     |
|3  |7      |         |`D10`    |
|3  |8      |         |`D11`    |
|3  |9      |         |`D12`    |
|3  |10     |         |`D13`    |
|3  |11     |         |`D14`    |
|3  |12     |         |`B0`     |
|3  |13     |         |`E7`     |
|3  |14     |         |`E10`    |
|3  |15     |         |`E11`    |
|3  |16     |         |`E12`    |
|4  |1      |         |`E14`    |
|4  |2      |         |`B12`    |
|4  |3      |         |`B13`    |
|4  |4      |         |`B14`    |
|4  |5      |         |`B15`    |
|4  |6      |         |`E8`     |
|4  |7      |         |`D10`    |
|4  |8      |         |`D11`    |
|4  |9      |         |`D12`    |
|4  |10     |         |`D13`    |
|4  |11     |         |`D14`    |
|4  |12     |         |`D8`     |
|4  |13     |         |`D9`     |
|4  |14     |         |         |
|4  |15     |         |         |
|4  |16     |         |         |

## Functions

### AVR

|Function                    |Description                                                                                                        |
|----------------------------|-------------------------------------------------------------------------------------------------------------------|
|`analogReference(mode)`     |Sets the analog voltage reference source. Must be one of `ADC_REF_EXTERNAL`, `ADC_REF_POWER` or `ADC_REF_INTERNAL`.|
|`analogRead(pin)`           |Reads the value from the specified Arduino pin, eg. `4` for ADC6 on the ATmega32U4.                                |
|`analogReadPin(pin)`        |Reads the value from the specified QMK pin, eg. `F6` for ADC6 on the ATmega32U4.                                   |
|`pinToMux(pin)`             |Translates a given QMK pin to a mux value. If an unsupported pin is given, returns the mux value for "0V (GND)".   |
|`adc_read(mux)`             |Reads the value from the ADC according to the specified mux. See your MCU's datasheet for more information.        |

### ARM

Note that care was taken to match all of the functions used for AVR devices, however complications in the ARM platform prevent that from always being possible. For example, the `STM32` chips do not have assigned Arduino pins. We could use the default pin numbers, but those numbers change based on the package type of the device. For this reason, please specify your target pins with their identifiers (`A0`, `F3`, etc.). Also note that there are some variants of functions that accept the target ADC for the pin. Some pins can be used for multiple ADCs, and this specified can help you pick which ADC will be used to interact with that pin.

|Function                    |Description                                                                                                         |
|----------------------------|--------------------------------------------------------------------------------------------------------------------|
|`analogReadPin(pin)`        |Reads the value from the specified QMK pin, eg. `A0` for channel 0 on the STM32F0 and ADC1 channel 1 on the STM32F3. Note that if a pin can be used for multiple ADCs, it will pick the lower numbered ADC for this function. eg. `C0` will be channel 6 of ADC 1 when it could be used for ADC 2 as well.|
|`analogReadPinAdc(pin, adc)`|Reads the value from the specified QMK pin and ADC, eg. `C0, 1` will read from channel 6, ADC 2 instead of ADC 1. Note that the ADCs are 0-indexed for this function.|
|`pinToMux(pin)`             |Translates a given QMK pin to a channel and ADC combination. If an unsupported pin is given, returns the mux value for "0V (GND)".|
|`adc_read(mux)`             |Reads the value from the ADC according to the specified pin and adc combination. See your MCU's datasheet for more information.|

## Configuration

## ARM

The ARM implementation of the ADC has a few additional options that you can override in your own keyboards and keymaps to change how it operates.

|`#define`          |Type  |Default              |Description|
|-------------------|------|---------------------|-----------|
|ADC_CIRCULAR_BUFFER|`bool`|`false`              |If `TRUE`, then the implementation will use a circular buffer.|
|ADC_NUM_CHANNELS   |`int` |`1`                  |Sets the number of channels that will be scanned as part of an ADC operation. The current implementation only supports `1`.|
|ADC_BUFFER_DEPTH   |`int` |`2`                  |Sets the depth of each result. Since we are only getting a 12-bit result by default, we set this to `2` bytes so we can contain our one value. This could be set to 1 if you opt for a 8-bit or lower result.|
|ADC_SAMPLING_RATE  |`int` |`ADC_SMPR_SMP_1P5`   |Sets the sampling rate of the ADC. By default, it is set to the fastest setting. Please consult the corresponding `hal_adc_lld.h` in ChibiOS for your specific microcontroller for further documentation on your available options.|
|ADC_RESOLUTION     |`int` |`ADC_CFGR1_RES_12BIT`|The resolution of your result. We choose 12 bit by default, but you can opt for 12, 10, 8, or 6 bit. Please consult the corresponding `hal_adc_lld.h` in ChibiOS for your specific microcontroller for further documentation on your available options.|
