# Battery Driver

This driver provides support for sampling battery level.

## Usage

To use this driver, add the following to your `rules.mk`:

```make
BATTERY_DRIVER_REQUIRED = yes
```

## Basic Configuration {#basic-configuration}

Add the following to your `config.h`:

|Define                    |Default |Description                                       |
|--------------------------|--------|--------------------------------------------------|
|`BATTERY_SAMPLE_INTERVAL` |`30000` |The time between battery samples in milliseconds. |

## Driver Configuration {#driver-configuration}

Driver selection can be configured in `rules.mk` as `BATTERY_DRIVER`. Valid values are `adc` (default), `vendor`, or `custom`. See below for information on individual drivers.

### ADC Driver {#adc-driver}

This is the default battery driver. The default configuration assumes the battery is connected to a ADC capable pin through a voltage divider.

```make
BATTERY_DRIVER = adc
```

The following `#define`s apply only to the `adc` driver:

|Define                       |Default       |Description                                                   |
|-----------------------------|--------------|--------------------------------------------------------------|
|`BATTERY_PIN`                |*Not defined* |The GPIO pin connected to the voltage divider.                |
|`BATTERY_REF_VOLTAGE_MV`     |`3300`        |The ADC reverence voltage, in millivolts.                     |
|`BATTERY_VOLTAGE_DIVIDER_R1` |`100000`      |The voltage divider resistance, in kOhm. Set to 0 to disable. |
|`BATTERY_VOLTAGE_DIVIDER_R1` |`100000`      |The voltage divider resistance, in kOhm. Set to 0 to disable. |
|`BATTERY_ADC_RESOLUTION`     |`10`          |The ADC resolution configured for the ADC Driver.             |

## Functions

### `uint8_t battery_get_percent(void)` {#api-battery-get-percent}

Sample battery level.

#### Return Value {#api-battery-get-percent-return}

The battery percentage, in the range 0-100.
