# ADC Driver

QMK can read analog values on certain pins. For AVR MCUs, these values are 10-bit (0-1023) and mapped between 0V and VCC (5V or 3.3V). This can be useful for implementing things like volume controls or battery level indicators.

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

|Channel|AT90USB64/128|ATmega16/32U4|ATmega32A|ATmega328P|
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

\* The ATmega328P possesses two extra ADC channels; however, they are not present on the DIP pinout, and are not shared with GPIO pins.

## Functions

|Function                    |Description                                                                                                        |
|----------------------------|-------------------------------------------------------------------------------------------------------------------|
|`analogReference(mode)`     |Sets the analog voltage reference source. Must be one of `ADC_REF_EXTERNAL`, `ADC_REF_POWER` or `ADC_REF_INTERNAL`.|
|`analogRead(pin)`           |Reads the value from the specified Arduino pin, eg. `4` for ADC6 on the ATmega32U4.                                |
|`analogReadPin(pin)`        |Reads the value from the specified QMK pin, eg. `F6` for ADC6 on the ATmega32U4.                                   |
|`pinToMux(pin)`             |Translates a given QMK pin to a mux value. **Note that the default `0` is also a valid value.**                    |
|`adc_read(mux)`             |Reads the value from the ADC according to the specified mux. See your MCU's datasheet for more information.        |
