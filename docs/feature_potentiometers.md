# Potentiometers

Add this to your `rules.mk`:

```make
POTENTIOMETER_ENABLE = yes
```

and this to your `config.h`:

```c
#define POTENTIOMETER_PINS { B0 }
```

## Callbacks

The callback functions can be inserted into your `<keyboard>.c`:

```c
bool potentiometer_update_kb(uint8_t index, uint16_t value) {
    if (!potentiometer_update_user(index, value)) {
        midi_send_cc(&midi_device, 2, 0x3E, 0x7F + value);
    }
    return true;
}
```

or `keymap.c`:

```c
bool potentiometer_update_user(uint8_t index, uint16_t value) {
    midi_send_cc(&midi_device, 2, 0x3E, 0x7F + value);
    return false;
}
```
