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

[keycodes_programmable_buttons.md](./keycodes_programmable_buttons.md ':include')

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
