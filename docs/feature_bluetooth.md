# Bluetooth

This feature allows you to integrate into a Bluetooth module to create a Bluetooth keyboard for wireless operation.

## Supported Modules

Currently on the following modules are supported:

| Board                                                              | Module based on     |  Bluetooth Protocol         | Connection Type | rules.mk                        |Bluetooth Chip  |
|--------------------------------------------------------------------|---------------------|-----------------------------|-----------------|---------------------------------|----------------|
|[Sparkfun BlueSMiRF Silver](https://www.sparkfun.com/products/12577)|Roving Networks RN-42|Bluetooth 2.1 *"Classic"*    |UART             |`BLUETOOTH_DRIVER = rn42`        |RN42<sup>1</sup>|
|[Bluefruit LE SPI Friend](https://www.adafruit.com/product/2633)    |Raytac MDBT40-256RV3 |Bluetooth 4.1 BLE<sup>2</sup>|SPI              |`BLUETOOTH_DRIVER = bluefruit_le`|nRF51822        |

> <sup>1</sup> RN42 based are modules mostly retired or EOL as the BT2.1 spec is deprecated and withdrawn as of July 2020.
>
> <sup>2</sup> BLE is needed to connect to iOS devices.

Not supported yet, but possible:

* [Bluefruit LE UART Friend](https://www.adafruit.com/product/2479).
* HC-05, HC-06 and HC-08 modules.
* Modules based on Nordic nRF51*, nRF52* and nRF53* SoC's - however in most cases one will also need to develop firmware for those modules.

> **NOTE:** QMK does not currently support MCU sleep modes, and this may impact the longevity of battery based builds.

## Driver configuration

### Adafruit BLE SPI Friend

To enable support for the Adafruit Bluefruit LE SPI Friend, add this to your `rules.mk` file:

```make
NKRO_ENABLE      = no           # ** Required
BLUETOOTH_ENABLE = yes
BLUETOOTH_DRIVER = bluefruit_le
```

> ** This module does not support [N-Key Rollover (NKRO)](reference_glossary.md#n-key-rollover-nkro);

The Adafruit Bluefruit SPI Friend is a module based on the MDBT30 module with embedded Nordic nRF51822 chip, and is flashed with Adafruit's custom firmware.  
This firmware uses AT Command sets over Adafruit's [SDEP](https://learn.adafruit.com/introducing-the-adafruit-bluefruit-spi-breakout/sdep-spi-data-transport) data transfer protocol.

#### SPI Configuration

QMK’s `spi_master` must already be correctly configured for the platform you’re building for.
In addition, you will also need to define the following items in `config.h``:

| Variable               | Description                               | Default |
|------------------------|-------------------------------------------|---------|
| `BLUEFRUIT_LE_RST_PIN` | Used to perform a reset on initialization | D4      |
| `BLUEFRUIT_LE_CS_PIN`  | SPI SS/CI "Chip Select" pin               | B4      |
| `BLUEFRUIT_LE_IRQ_PIN` | Module Interrupt Request pin              | E6      |

> Defaults are based on the [Adafruit Feather 32u4 Bluefruit](https://learn.adafruit.com/adafruit-feather-32u4-bluefruit-le/overview).

## Keycodes

The following keycodes will allow you change the output selector for the keyboard.
This allows for switching between USB and Bluetooth on keyboards that support both.

| Key                 | Aliases | Description                                              |
|---------------------|---------|----------------------------------------------------------|
|`QK_OUTPUT_AUTO`     |`OU_AUTO`|Automatically switch between USB and Bluetooth *(Default)*|
|`QK_OUTPUT_USB`      |`OU_USB` |USB only                                                  |
|`QK_OUTPUT_BLUETOOTH`|`OU_BT`  |Bluetooth only                                            |

## Output Interface Selection

The above keycodes will in turn call the output selector API to direct all key, mouse, consumer, and system output events to the selected interface:

```c
send_output_t set_send_output(send_output_t send_output);
send_output_t get_send_output(void);
```

The *`send_output`* variable should be one of:

```c
enum send_output_t {
    SEND_OUTPUT_AUTO,      // Selection is USB if USB cable connected, else is Bluetooth is Bluetooth is connected. (Default)
    SEND_OUTPUT_NONE,      // No output is sent.
    SEND_OUTPUT_USB,       // Output is always USB.
    SEND_OUTPUT_BLUETOOTH, // Output is always Bluetooth.
    SEND_OUTPUT_BOTH       // Output is sent to both USb and Bluetooth (used for testing).
};
```

You can change the initial state with the following define in the `config.h` file:

```c
#define SEND_OUTPUT_DEFAULT SEND_OUTPUT_AUTO
```

Vendor and keymap code can also use the keyboard-level and user-level (to either perform ancillary functions on the setting, or override the setting) by creating the following functions in the `kb_name.c` or the `keymap.c` files:

```c
send_output_t set_send_output_kb(send_output_t send_output);   // kb-level function usually in the `kb_name.c file`.  Should also call `set_send_output_user`.
send_output_t set_send_output_user(send_output_t send_output); // user-level function usually in `keymap.c` file.
```

## Bluetooth Driver API

### Custom Bluetooth Driver

You can create your own Bluetooth driver (or for that matter, any alternate output interface) with the `bluetooth_driver` variable, and the `bluetooth_driver_t` struct.

Then, to enable a custom Bluetooth driver add this to your `rules.mk` file:

```make
BLUETOOTH_ENABLE = yes
BLUETOOTH_DRIVER = custom
```

#### Example

You can create your own Bluetooth driver by creating compliant functions and referencing these with within the `bluetooth_driver` variable.

In your `kb_name.c` file, create that variable as such:

```c
const bluetooth_driver_t bluetooth_driver = {
    .init          = xyz_bt_init,
    .task          = xyz_bt_task,          // Optional
    .is_connected  = xyz_bt_is_connected,  // Optional
    .send_keyboard = xyz_bt_send_keyboard,
    .send_mouse    = xyz_bt_send_mouse,
    .send_consumer = xyz_bt_send_consumer,
    .send_system   = xyz_bt_send_system,   // Optional
};
```

> * Members `init`, `send_keyboard`, `send_mouse` and `send_consumer` must be provided.
> * Members `task`, `is_connected` and `send_system` are optional and may be set to `NULL`.


Then code for the following functions:

```c
/* Initialize the Bluetooth system. */
void xyz_bt_init(void) {}

/* Perform housekeeping tasks. Called every loop. (Optional) */
void xyz_bt_task(void) {}

/* Detects if BT is connected, also used by `SEND_OUTPUT_AUTO`. (Optional) */
bool xyz_bt_is_connected(void) {}

/* Send a keyboard report. */
void xyz_bt_send_keyboard(report_keyboard_t *report) {}

/* Send a mouse report. */
void xyz_bt_send_mouse(report_mouse_t *report) {}

/* Send a consumer usage. */
void xyz_bt_send_consumer(uint16_t usage) {}

/* Send a system usage. (Optional) */
void xyz_bt_send_system(uint16_t usage) {}
```
