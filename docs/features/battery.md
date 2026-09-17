# Battery

This feature provides the high level abstraction for sampling battery level.

## Usage

To use this driver, add the following to your `rules.mk`:

```make
BATTERY_ENABLE = yes
```

## Basic Configuration {#basic-configuration}

Add the following to your `config.h`:

|Define                    |Default |Description                                       |
|--------------------------|--------|--------------------------------------------------|
|`BATTERY_SAMPLE_INTERVAL` |`30000` |The time between battery samples in milliseconds. |

## Driver Configuration {#driver-configuration}

See the [Battery Driver](../drivers/battery) documentation for more information.

## Functions

### `uint8_t battery_get_percent(void)` {#api-battery-get-percent}

Sample battery level.

#### Return Value {#api-battery-get-percent-return}

The battery percentage, in the range 0-100.

## Callbacks

### `void battery_percent_changed_user(uint8_t level)` {#api-battery-percent-changed-user}

User hook called when battery level changed.

### Arguments {#api-battery-percent-changed-user-arguments}

 - `uint8_t level`  
   The battery percentage, in the range 0-100.

---

### `void battery_percent_changed_kb(uint8_t level)` {#api-battery-percent-changed-kb}

Keyboard hook called when battery level changed.

### Arguments {#api-battery-percent-changed-kb-arguments}

 - `uint8_t level`  
   The battery percentage, in the range 0-100.
