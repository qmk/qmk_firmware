## Programmable Button

Programmable button is a feature that can be used to send keys that have no
predefined meaning.
This means they can be processed on the host side by custom software without
colliding without the operating system trying to interpret these keys.

### Enabling Programmable Button support

To enable Programmable Button, add the following line to your keymap’s `rules.mk`:

```c
PROGRAMMABLE_BUTTON_ENABLE = yes
```

### Mapping

In your keymap you can use the following keycodes to map key presses to Programmable Buttons:

|Key                       |Description                                                     |
|--------------------------|----------------------|
|`KC_PROGRAMMABLE_BUTTON1` |Programmable button 1 |
|`KC_PROGRAMMABLE_BUTTON2` |Programmable button 2 |
|`KC_PROGRAMMABLE_BUTTON3` |Programmable button 3 |
|`KC_PROGRAMMABLE_BUTTON4` |Programmable button 4 |
|`KC_PROGRAMMABLE_BUTTON5` |Programmable button 5 |
|`KC_PROGRAMMABLE_BUTTON6` |Programmable button 6 |
|`KC_PROGRAMMABLE_BUTTON7` |Programmable button 7 |
|`KC_PROGRAMMABLE_BUTTON8` |Programmable button 8 |
|`KC_PROGRAMMABLE_BUTTON9` |Programmable button 9 |
|`KC_PROGRAMMABLE_BUTTON10`|Programmable button 10|
|`KC_PROGRAMMABLE_BUTTON11`|Programmable button 11|
|`KC_PROGRAMMABLE_BUTTON12`|Programmable button 12|
|`KC_PROGRAMMABLE_BUTTON13`|Programmable button 13|
|`KC_PROGRAMMABLE_BUTTON14`|Programmable button 14|
|`KC_PROGRAMMABLE_BUTTON15`|Programmable button 15|
|`KC_PROGRAMMABLE_BUTTON16`|Programmable button 16|
|`KC_PROGRAMMABLE_BUTTON17`|Programmable button 17|
|`KC_PROGRAMMABLE_BUTTON18`|Programmable button 18|
|`KC_PROGRAMMABLE_BUTTON19`|Programmable button 19|
|`KC_PROGRAMMABLE_BUTTON20`|Programmable button 20|
|`KC_PROGRAMMABLE_BUTTON21`|Programmable button 21|
|`KC_PROGRAMMABLE_BUTTON22`|Programmable button 22|
|`KC_PROGRAMMABLE_BUTTON23`|Programmable button 23|
|`KC_PROGRAMMABLE_BUTTON24`|Programmable button 24|
|`KC_PROGRAMMABLE_BUTTON25`|Programmable button 25|
|`KC_PROGRAMMABLE_BUTTON26`|Programmable button 26|
|`KC_PROGRAMMABLE_BUTTON27`|Programmable button 27|
|`KC_PROGRAMMABLE_BUTTON28`|Programmable button 28|
|`KC_PROGRAMMABLE_BUTTON29`|Programmable button 29|
|`KC_PROGRAMMABLE_BUTTON30`|Programmable button 30|
|`KC_PROGRAMMABLE_BUTTON31`|Programmable button 31|
|`KC_PROGRAMMABLE_BUTTON32`|Programmable button 32|

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
