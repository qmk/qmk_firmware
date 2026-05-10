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

## Charging State {#charging-state}

When a charger driver is configured (see [Charger Driver Configuration](../drivers/battery#charger-driver-configuration)), the framework also tracks the charging state and emits change notifications.

### `battery_charging_state_t` {#charging-state-enum}

|Value                       |Description                                                |
|----------------------------|-----------------------------------------------------------|
|`BATTERY_CHARGING_UNKNOWN`  |State not yet determined or no charger driver configured.  |
|`BATTERY_NOT_CHARGING`      |Cable is not connected.                                    |
|`BATTERY_CHARGING`          |Cable is connected and battery is charging.                |
|`BATTERY_FULL`              |Cable is connected and battery is fully charged.           |

### `battery_charging_state_t battery_get_charging_state(void)` {#api-battery-get-charging-state}

Read current charging state.

#### Return Value {#api-battery-get-charging-state-return}

The current charging state. Returns `BATTERY_CHARGING_UNKNOWN` when no charger driver is configured.

### `void battery_charging_state_changed_user(battery_charging_state_t state)` {#api-battery-charging-state-changed-user}

User hook called when charging state changed.

#### Arguments {#api-battery-charging-state-changed-user-arguments}

 - `battery_charging_state_t state`  
   The new charging state.

---

### `void battery_charging_state_changed_kb(battery_charging_state_t state)` {#api-battery-charging-state-changed-kb}

Keyboard hook called when charging state changed.

#### Arguments {#api-battery-charging-state-changed-kb-arguments}

 - `battery_charging_state_t state`  
   The new charging state.
