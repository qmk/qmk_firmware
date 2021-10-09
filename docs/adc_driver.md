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

Also note that the F0 and F3 use different numbering schemes. The F0 has a single ADC and the channels are 0-indexed, whereas the F3 has 4 ADCs and the channels are 1-indexed. This is because the F0 uses the `ADCv1` implementation of the ADC, whereas the F3 uses the `ADCv3` implementation.

|ADC|Channel|STM32F0xx|STM32F1xx|STM32F3xx|STM32F4xx|
|---|-------|---------|---------|---------|---------|
|1  |0      |`A0`     |`A0`     |         |`A0`     |
|1  |1      |`A1`     |`A1`     |`A0`     |`A1`     |
|1  |2      |`A2`     |`A2`     |`A1`     |`A2`     |
|1  |3      |`A3`     |`A3`     |`A2`     |`A3`     |
|1  |4      |`A4`     |`A4`     |`A3`     |`A4`     |
|1  |5      |`A5`     |`A5`     |`F4`     |`A5`     |
|1  |6      |`A6`     |`A6`     |`C0`     |`A6`     |
|1  |7      |`A7`     |`A7`     |`C1`     |`A7`     |
|1  |8      |`B0`     |`B0`     |`C2`     |`B0`     |
|1  |9      |`B1`     |`B1`     |`C3`     |`B1`     |
|1  |10     |`C0`     |`C0`     |`F2`     |`C0`     |
|1  |11     |`C1`     |`C1`     |         |`C1`     |
|1  |12     |`C2`     |`C2`     |         |`C2`     |
|1  |13     |`C3`     |`C3`     |         |`C3`     |
|1  |14     |`C4`     |`C4`     |         |`C4`     |
|1  |15     |`C5`     |`C5`     |         |`C5`     |
|1  |16     |         |         |         |         |
|2  |0      |         |`A0`¹    |         |`A0`²    |
|2  |1      |         |`A1`¹    |`A4`     |`A1`²    |
|2  |2      |         |`A2`¹    |`A5`     |`A2`²    |
|2  |3      |         |`A3`¹    |`A6`     |`A3`²    |
|2  |4      |         |`A4`¹    |`A7`     |`A4`²    |
|2  |5      |         |`A5`¹    |`C4`     |`A5`²    |
|2  |6      |         |`A6`¹    |`C0`     |`A6`²    |
|2  |7      |         |`A7`¹    |`C1`     |`A7`²    |
|2  |8      |         |`B0`¹    |`C2`     |`B0`²    |
|2  |9      |         |`B1`¹    |`C3`     |`B1`²    |
|2  |10     |         |`C0`¹    |`F2`     |`C0`²    |
|2  |11     |         |`C1`¹    |`C5`     |`C1`²    |
|2  |12     |         |`C2`¹    |`B2`     |`C2`²    |
|2  |13     |         |`C3`¹    |         |`C3`²    |
|2  |14     |         |`C4`¹    |         |`C4`²    |
|2  |15     |         |`C5`¹    |         |`C5`²    |
|2  |16     |         |         |         |         |
|3  |0      |         |`A0`¹    |         |`A0`²    |
|3  |1      |         |`A1`¹    |`B1`     |`A1`²    |
|3  |2      |         |`A2`¹    |`E9`     |`A2`²    |
|3  |3      |         |`A3`¹    |`E13`    |`A3`²    |
|3  |4      |         |`F6`¹    |         |`F6`²    |
|3  |5      |         |`F7`¹    |`B13`    |`F7`²    |
|3  |6      |         |`F8`¹    |`E8`     |`F8`²    |
|3  |7      |         |`F9`¹    |`D10`    |`F9`²    |
|3  |8      |         |`F10`¹   |`D11`    |`F10`²   |
|3  |9      |         |         |`D12`    |`F3`²    |
|3  |10     |         |`C0`¹    |`D13`    |`C0`²    |
|3  |11     |         |`C1`¹    |`D14`    |`C1`²    |
|3  |12     |         |`C2`¹    |`B0`     |`C2`²    |
|3  |13     |         |`C3`¹    |`E7`     |`C3`²    |
|3  |14     |         |         |`E10`    |`F4`²    |
|3  |15     |         |         |`E11`    |`F5`²    |
|3  |16     |         |         |`E12`    |         |
|4  |1      |         |         |`E14`    |         |
|4  |2      |         |         |`E15`    |         |
|4  |3      |         |         |`B12`    |         |
|4  |4      |         |         |`B14`    |         |
|4  |5      |         |         |`B15`    |         |
|4  |6      |         |         |`E8`     |         |
|4  |7      |         |         |`D10`    |         |
|4  |8      |         |         |`D11`    |         |
|4  |9      |         |         |`D12`    |         |
|4  |10     |         |         |`D13`    |         |
|4  |11     |         |         |`D14`    |         |
|4  |12     |         |         |`D8`     |         |
|4  |13     |         |         |`D9`     |         |
|4  |14     |         |         |         |         |
|4  |15     |         |         |         |         |
|4  |16     |         |         |         |         |

<sup>¹ As of ChibiOS 20.3.4, the ADC driver for STM32F1xx devices supports only ADC1, therefore any configurations involving ADC2 or ADC3 cannot actually be used. In particular, pins `F6`…`F10`, which are present at least on some STM32F103x[C-G] devices, cannot be used as ADC inputs because of this driver limitation.</sup>

<sup>² Not all STM32F4xx devices have ADC2 and/or ADC3, therefore some configurations shown in this table may be unavailable; in particular, pins `F4`…`F10` cannot be used as ADC inputs on devices which do not have ADC3. Check the device datasheet to confirm which pin functions are supported.</sup>

## Functions

### AVR

|Function                    |Description                                                                                                        |
|----------------------------|-------------------------------------------------------------------------------------------------------------------|
|`analogReference(mode)`     |Sets the analog voltage reference source. Must be one of `ADC_REF_EXTERNAL`, `ADC_REF_POWER` or `ADC_REF_INTERNAL`.|
|`analogReadPin(pin)`        |Reads the value from the specified pin, eg. `F6` for ADC6 on the ATmega32U4.                                       |
|`pinToMux(pin)`             |Translates a given pin to a mux value. If an unsupported pin is given, returns the mux value for "0V (GND)".       |
|`adc_read(mux)`             |Reads the value from the ADC according to the specified mux. See your MCU's datasheet for more information.        |

### ARM

|Function                    |Description                                                                                                                                                                                                                                                                                           |
|----------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|`analogReadPin(pin)`        |Reads the value from the specified pin, eg. `A0` for channel 0 on the STM32F0 and ADC1 channel 1 on the STM32F3. Note that if a pin can be used for multiple ADCs, it will pick the lower numbered ADC for this function. eg. `C0` will be channel 6 of ADC 1 when it could be used for ADC 2 as well.|
|`analogReadPinAdc(pin, adc)`|Reads the value from the specified pin and ADC, eg. `C0, 1` will read from channel 6, ADC 2 instead of ADC 1. Note that the ADCs are 0-indexed for this function.                                                                                                                                     |
|`pinToMux(pin)`             |Translates a given pin to a channel and ADC combination. If an unsupported pin is given, returns the mux value for "0V (GND)".                                                                                                                                                                        |
|`adc_read(mux)`             |Reads the value from the ADC according to the specified pin and ADC combination. See your MCU's datasheet for more information.                                                                                                                                                                       |

## Configuration

## ARM

The ARM implementation of the ADC has a few additional options that you can override in your own keyboards and keymaps to change how it operates. Please consult the corresponding `hal_adc_lld.h` in ChibiOS for your specific microcontroller for further documentation on your available options.

|`#define`            |Type  |Default                                       |Description                                                                                                                                                                                                 |
|---------------------|------|----------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|`ADC_CIRCULAR_BUFFER`|`bool`|`false`                                       |If `true`, then the implementation will use a circular buffer.                                                                                                                                              |
|`ADC_NUM_CHANNELS`   |`int` |`1`                                           |Sets the number of channels that will be scanned as part of an ADC operation. The current implementation only supports `1`.                                                                                 |
|`ADC_BUFFER_DEPTH`   |`int` |`2`                                           |Sets the depth of each result. Since we are only getting a 10-bit result by default, we set this to 2 bytes so we can contain our one value. This could be set to 1 if you opt for an 8-bit or lower result.|
|`ADC_SAMPLING_RATE`  |`int` |`ADC_SMPR_SMP_1P5`                            |Sets the sampling rate of the ADC. By default, it is set to the fastest setting.                                                                                                                            |
|`ADC_RESOLUTION`     |`int` |`ADC_CFGR1_RES_10BIT` or `ADC_CFGR_RES_10BITS`|The resolution of your result. We choose 10 bit by default, but you can opt for 12, 10, 8, or 6 bit. Different MCUs use slightly different names for the resolution constants.                              |
