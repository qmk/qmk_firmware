## Programmable Button

Programmable button is a feature that can be used to send keys that have no
predefined meaning.
This means they can be processed on the host side by custom software without
colliding without the operating system trying to interpret these keys.

The keycodes are emitted according to the HID usage
"Telephony Device Page" (0x0B), "Programmable button usage" (0x07).
On Linux (> 5.14) they are handled automatically and translated to `KEY_MACRO#`
keycodes.
(Up to `KEY_MACRO30`)

### Enabling Programmable Button support

To enable Programmable Button, add the following line to your keymap’s `rules.mk`:

```c
PROGRAMMABLE_BUTTON_ENABLE = yes
```

### Mapping

In your keymap you can use the following keycodes to map key presses to Programmable Buttons:

|Key                     |Description                                                     |
|------------------------|----------------------|
|`PROGRAMMABLE_BUTTON_1` |Programmable button 1 |
|`PROGRAMMABLE_BUTTON_2` |Programmable button 2 |
|`PROGRAMMABLE_BUTTON_3` |Programmable button 3 |
|`PROGRAMMABLE_BUTTON_4` |Programmable button 4 |
|`PROGRAMMABLE_BUTTON_5` |Programmable button 5 |
|`PROGRAMMABLE_BUTTON_6` |Programmable button 6 |
|`PROGRAMMABLE_BUTTON_7` |Programmable button 7 |
|`PROGRAMMABLE_BUTTON_8` |Programmable button 8 |
|`PROGRAMMABLE_BUTTON_9` |Programmable button 9 |
|`PROGRAMMABLE_BUTTON_10`|Programmable button 10|
|`PROGRAMMABLE_BUTTON_11`|Programmable button 11|
|`PROGRAMMABLE_BUTTON_12`|Programmable button 12|
|`PROGRAMMABLE_BUTTON_13`|Programmable button 13|
|`PROGRAMMABLE_BUTTON_14`|Programmable button 14|
|`PROGRAMMABLE_BUTTON_15`|Programmable button 15|
|`PROGRAMMABLE_BUTTON_16`|Programmable button 16|
|`PROGRAMMABLE_BUTTON_17`|Programmable button 17|
|`PROGRAMMABLE_BUTTON_18`|Programmable button 18|
|`PROGRAMMABLE_BUTTON_19`|Programmable button 19|
|`PROGRAMMABLE_BUTTON_20`|Programmable button 20|
|`PROGRAMMABLE_BUTTON_21`|Programmable button 21|
|`PROGRAMMABLE_BUTTON_22`|Programmable button 22|
|`PROGRAMMABLE_BUTTON_23`|Programmable button 23|
|`PROGRAMMABLE_BUTTON_24`|Programmable button 24|
|`PROGRAMMABLE_BUTTON_25`|Programmable button 25|
|`PROGRAMMABLE_BUTTON_26`|Programmable button 26|
|`PROGRAMMABLE_BUTTON_27`|Programmable button 27|
|`PROGRAMMABLE_BUTTON_28`|Programmable button 28|
|`PROGRAMMABLE_BUTTON_29`|Programmable button 29|
|`PROGRAMMABLE_BUTTON_30`|Programmable button 30|
|`PROGRAMMABLE_BUTTON_31`|Programmable button 31|
|`PROGRAMMABLE_BUTTON_32`|Programmable button 32|
|`PB_1` to `PB_32`       |Aliases for keymaps   |

### API

You can also use a dedicated API defined in `programmable_button.h` to interact with this feature:

```
void programmable_button_clear(void);
void programmable_button_send(void);
void programmable_button_on(uint8_t code);
void programmable_button_off(uint8_t code);
bool programmable_button_is_on(uint8_t code);
uint32_t programmable_button_get_report(void);
void programmable_button_set_report(uint32_t report);
```
