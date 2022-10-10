# Programmable Button :id=programmable-button

Programmable Buttons are keys that have no predefined meaning. This means they can be processed on the host side by custom software without the operating system trying to interpret them.

The keycodes are emitted according to the HID Telephony Device page (`0x0B`), Programmable Button usage (`0x07`). On Linux (> 5.14) they are handled automatically and translated to `KEY_MACRO#` keycodes (up to `KEY_MACRO30`).

?> Currently there is no known support in Windows or macOS. It may be possible to write a custom HID driver to receive these usages, but this is out of the scope of the QMK documentation.

## Usage :id=usage

Add the following to your `rules.mk`:

```make
PROGRAMMABLE_BUTTON_ENABLE = yes
```

## Keycodes :id=keycodes

|Key                     |Aliases|Description           |
|------------------------|-------|----------------------|
|`PROGRAMMABLE_BUTTON_1` |`PB_1` |Programmable button 1 |
|`PROGRAMMABLE_BUTTON_2` |`PB_2` |Programmable button 2 |
|`PROGRAMMABLE_BUTTON_3` |`PB_3` |Programmable button 3 |
|`PROGRAMMABLE_BUTTON_4` |`PB_4` |Programmable button 4 |
|`PROGRAMMABLE_BUTTON_5` |`PB_5` |Programmable button 5 |
|`PROGRAMMABLE_BUTTON_6` |`PB_6` |Programmable button 6 |
|`PROGRAMMABLE_BUTTON_7` |`PB_7` |Programmable button 7 |
|`PROGRAMMABLE_BUTTON_8` |`PB_8` |Programmable button 8 |
|`PROGRAMMABLE_BUTTON_9` |`PB_9` |Programmable button 9 |
|`PROGRAMMABLE_BUTTON_10`|`PB_10`|Programmable button 10|
|`PROGRAMMABLE_BUTTON_11`|`PB_11`|Programmable button 11|
|`PROGRAMMABLE_BUTTON_12`|`PB_12`|Programmable button 12|
|`PROGRAMMABLE_BUTTON_13`|`PB_13`|Programmable button 13|
|`PROGRAMMABLE_BUTTON_14`|`PB_14`|Programmable button 14|
|`PROGRAMMABLE_BUTTON_15`|`PB_15`|Programmable button 15|
|`PROGRAMMABLE_BUTTON_16`|`PB_16`|Programmable button 16|
|`PROGRAMMABLE_BUTTON_17`|`PB_17`|Programmable button 17|
|`PROGRAMMABLE_BUTTON_18`|`PB_18`|Programmable button 18|
|`PROGRAMMABLE_BUTTON_19`|`PB_19`|Programmable button 19|
|`PROGRAMMABLE_BUTTON_20`|`PB_20`|Programmable button 20|
|`PROGRAMMABLE_BUTTON_21`|`PB_21`|Programmable button 21|
|`PROGRAMMABLE_BUTTON_22`|`PB_22`|Programmable button 22|
|`PROGRAMMABLE_BUTTON_23`|`PB_23`|Programmable button 23|
|`PROGRAMMABLE_BUTTON_24`|`PB_24`|Programmable button 24|
|`PROGRAMMABLE_BUTTON_25`|`PB_25`|Programmable button 25|
|`PROGRAMMABLE_BUTTON_26`|`PB_26`|Programmable button 26|
|`PROGRAMMABLE_BUTTON_27`|`PB_27`|Programmable button 27|
|`PROGRAMMABLE_BUTTON_28`|`PB_28`|Programmable button 28|
|`PROGRAMMABLE_BUTTON_29`|`PB_29`|Programmable button 29|
|`PROGRAMMABLE_BUTTON_30`|`PB_30`|Programmable button 30|
|`PROGRAMMABLE_BUTTON_31`|`PB_31`|Programmable button 31|
|`PROGRAMMABLE_BUTTON_32`|`PB_32`|Programmable button 32|

## API :id=api

### `void programmable_button_clear(void)` :id=api-programmable-button-clear

Clear the programmable button report.

---

### `void programmable_button_add(uint8_t index)` :id=api-programmable-button-add

Set the state of a button.

#### Arguments :id=api-programmable-button-add-arguments

 - `uint8_t index`  
   The index of the button to press, from 0 to 31.

---

### `void programmable_button_remove(uint8_t index)` :id=api-programmable-button-remove

Reset the state of a button.

#### Arguments :id=api-programmable-button-remove-arguments

 - `uint8_t index`  
   The index of the button to release, from 0 to 31.

---

### `void programmable_button_register(uint8_t index)` :id=api-programmable-button-register

Set the state of a button, and flush the report.

#### Arguments :id=api-programmable-button-register-arguments

 - `uint8_t index`  
   The index of the button to press, from 0 to 31.

---

### `void programmable_button_unregister(uint8_t index)` :id=api-programmable-button-unregister

Reset the state of a button, and flush the report.

#### Arguments :id=api-programmable-button-unregister-arguments

 - `uint8_t index`  
   The index of the button to release, from 0 to 31.

---

### `bool programmable_button_is_on(uint8_t index)` :id=api-programmable-button-is-on

Get the state of a button.

#### Arguments :id=api-programmable-button-is-on-arguments

 - `uint8_t index`  
   The index of the button to check, from 0 to 31.

#### Return Value :id=api-programmable-button-is-on-return

`true` if the button is pressed.

---

### `void programmable_button_flush(void)` :id=api-programmable-button-flush

Send the programmable button report to the host.

---

### `uint32_t programmable_button_get_report(void)` :id=api-programmable-button-get-report

Get the programmable button report.

#### Return Value :id=api-programmable-button-get-report-return

The bitmask of programmable button states.

---

### `void programmable_button_set_report(uint32_t report)` :id=api-programmable-button-set-report

Set the programmable button report.

#### Arguments :id=api-programmable-button-set-report-arguments

 - `uint32_t report`  
   A bitmask of programmable button states.
