# Battery Driver

This driver provides support for directly sampling battery level.

## Usage

To use this driver, add the following to your `rules.mk`:

```make
BATTERY_DRIVER_REQUIRED = yes
```

::::info Note
This is already configured for you if you are using the [Battery](../features/battery) feature.
::::

## Driver Configuration {#driver-configuration}

Driver selection can be configured in `rules.mk` as `BATTERY_DRIVER`. Valid values are `adc`, `vendor`, or `custom`. See below for information on individual drivers.

### ADC Driver {#adc-driver}

The default configuration assumes the battery is connected to a ADC capable pin through a voltage divider.

```make
BATTERY_DRIVER = adc
```

The following `#define`s apply only to the `adc` driver:

|Define                           |Default       |Description                                                   |
|---------------------------------|--------------|--------------------------------------------------------------|
|`BATTERY_ADC_PIN`                |*Not defined* |The GPIO pin connected to the voltage divider.                |
|`BATTERY_ADC_REF_VOLTAGE_MV`     |`3300`        |The ADC reverence voltage, in millivolts.                     |
|`BATTERY_ADC_VOLTAGE_DIVIDER_R1` |`100`         |The voltage divider resistance, in kOhm. Set to 0 to disable. |
|`BATTERY_ADC_VOLTAGE_DIVIDER_R2` |`100`         |The voltage divider resistance, in kOhm. Set to 0 to disable. |
|`BATTERY_ADC_RESOLUTION`         |`10`          |The ADC resolution configured for the ADC Driver.             |

### Custom Driver {#custom-driver}

A custom driver is expected to implement the following interface:

```c
void battery_driver_init(void) {
    // Perform any initialisation here
}

uint8_t battery_driver_sample_percent(void) {
    // Read and return current state here
    return value;
}
```
