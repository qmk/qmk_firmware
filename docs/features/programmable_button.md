# Programmable Button {#programmable-button}

Programmable Buttons are keys that have no predefined meaning. This means they can be processed on the host side by custom software without the operating system trying to interpret them.

The keycodes are emitted according to the HID Telephony Device page (`0x0B`), Programmable Button usage (`0x09`). On Linux (> 5.14) they are handled automatically and translated to `KEY_MACRO#` keycodes (up to `KEY_MACRO30`).

::: tip
Currently there is no known support in Windows or macOS. It may be possible to write a custom HID driver to receive these usages, but this is out of the scope of the QMK documentation.
:::

## Usage {#usage}

Add the following to your `rules.mk`:

```make
PROGRAMMABLE_BUTTON_ENABLE = yes
```

## Keycodes {#keycodes}

|Key                        |Aliases|Description           |
|---------------------------|-------|----------------------|
|`QK_PROGRAMMABLE_BUTTON_1` |`PB_1` |Programmable button 1 |
|`QK_PROGRAMMABLE_BUTTON_2` |`PB_2` |Programmable button 2 |
|`QK_PROGRAMMABLE_BUTTON_3` |`PB_3` |Programmable button 3 |
|`QK_PROGRAMMABLE_BUTTON_4` |`PB_4` |Programmable button 4 |
|`QK_PROGRAMMABLE_BUTTON_5` |`PB_5` |Programmable button 5 |
|`QK_PROGRAMMABLE_BUTTON_6` |`PB_6` |Programmable button 6 |
|`QK_PROGRAMMABLE_BUTTON_7` |`PB_7` |Programmable button 7 |
|`QK_PROGRAMMABLE_BUTTON_8` |`PB_8` |Programmable button 8 |
|`QK_PROGRAMMABLE_BUTTON_9` |`PB_9` |Programmable button 9 |
|`QK_PROGRAMMABLE_BUTTON_10`|`PB_10`|Programmable button 10|
|`QK_PROGRAMMABLE_BUTTON_11`|`PB_11`|Programmable button 11|
|`QK_PROGRAMMABLE_BUTTON_12`|`PB_12`|Programmable button 12|
|`QK_PROGRAMMABLE_BUTTON_13`|`PB_13`|Programmable button 13|
|`QK_PROGRAMMABLE_BUTTON_14`|`PB_14`|Programmable button 14|
|`QK_PROGRAMMABLE_BUTTON_15`|`PB_15`|Programmable button 15|
|`QK_PROGRAMMABLE_BUTTON_16`|`PB_16`|Programmable button 16|
|`QK_PROGRAMMABLE_BUTTON_17`|`PB_17`|Programmable button 17|
|`QK_PROGRAMMABLE_BUTTON_18`|`PB_18`|Programmable button 18|
|`QK_PROGRAMMABLE_BUTTON_19`|`PB_19`|Programmable button 19|
|`QK_PROGRAMMABLE_BUTTON_20`|`PB_20`|Programmable button 20|
|`QK_PROGRAMMABLE_BUTTON_21`|`PB_21`|Programmable button 21|
|`QK_PROGRAMMABLE_BUTTON_22`|`PB_22`|Programmable button 22|
|`QK_PROGRAMMABLE_BUTTON_23`|`PB_23`|Programmable button 23|
|`QK_PROGRAMMABLE_BUTTON_24`|`PB_24`|Programmable button 24|
|`QK_PROGRAMMABLE_BUTTON_25`|`PB_25`|Programmable button 25|
|`QK_PROGRAMMABLE_BUTTON_26`|`PB_26`|Programmable button 26|
|`QK_PROGRAMMABLE_BUTTON_27`|`PB_27`|Programmable button 27|
|`QK_PROGRAMMABLE_BUTTON_28`|`PB_28`|Programmable button 28|
|`QK_PROGRAMMABLE_BUTTON_29`|`PB_29`|Programmable button 29|
|`QK_PROGRAMMABLE_BUTTON_30`|`PB_30`|Programmable button 30|
|`QK_PROGRAMMABLE_BUTTON_31`|`PB_31`|Programmable button 31|
|`QK_PROGRAMMABLE_BUTTON_32`|`PB_32`|Programmable button 32|

## API {#api}

### `void programmable_button_clear(void)` {#api-programmable-button-clear}

Clear the programmable button report.

---

### `void programmable_button_add(uint8_t index)` {#api-programmable-button-add}

Set the state of a button.

#### Arguments {#api-programmable-button-add-arguments}

 - `uint8_t index`  
   The index of the button to press, from 0 to 31.

---

### `void programmable_button_remove(uint8_t index)` {#api-programmable-button-remove}

Reset the state of a button.

#### Arguments {#api-programmable-button-remove-arguments}

 - `uint8_t index`  
   The index of the button to release, from 0 to 31.

---

### `void programmable_button_register(uint8_t index)` {#api-programmable-button-register}

Set the state of a button, and flush the report.

#### Arguments {#api-programmable-button-register-arguments}

 - `uint8_t index`  
   The index of the button to press, from 0 to 31.

---

### `void programmable_button_unregister(uint8_t index)` {#api-programmable-button-unregister}

Reset the state of a button, and flush the report.

#### Arguments {#api-programmable-button-unregister-arguments}

 - `uint8_t index`  
   The index of the button to release, from 0 to 31.

---

### `bool programmable_button_is_on(uint8_t index)` {#api-programmable-button-is-on}

Get the state of a button.

#### Arguments {#api-programmable-button-is-on-arguments}

 - `uint8_t index`  
   The index of the button to check, from 0 to 31.

#### Return Value {#api-programmable-button-is-on-return}

`true` if the button is pressed.

---

### `void programmable_button_flush(void)` {#api-programmable-button-flush}

Send the programmable button report to the host.

---

### `uint32_t programmable_button_get_report(void)` {#api-programmable-button-get-report}

Get the programmable button report.

#### Return Value {#api-programmable-button-get-report-return}

The bitmask of programmable button states.

---

### `void programmable_button_set_report(uint32_t report)` {#api-programmable-button-set-report}

Set the programmable button report.

#### Arguments {#api-programmable-button-set-report-arguments}

 - `uint32_t report`  
   A bitmask of programmable button states.
