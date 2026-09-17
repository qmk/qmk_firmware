# DIP Switches

DIP switches are supported by adding this to your `rules.mk`:

    DIP_SWITCH_ENABLE = yes

and this to your `config.h`:

```c
// Connects each switch in the dip switch to the GPIO pin of the MCU
#define DIP_SWITCH_PINS { B14, A15, A10, B9 }
// For split keyboards, you can separately define the right side pins
#define DIP_SWITCH_PINS_RIGHT { ... }
```

or

```c
// Connect each switch in the DIP switch to an unused intersections in the key matrix.
#define DIP_SWITCH_MATRIX_GRID { {0,6}, {1,6}, {2,6} } // List of row and col pairs
```

## DIP Switch map {#dip-switch-map}

DIP Switch mapping may be added to your `keymap.c`, which replicates the normal keyswitch functionality, but with dip switches. Add this to your keymap's `rules.mk`:

```make
DIP_SWITCH_MAP_ENABLE = yes
```

Your `keymap.c` will then need a dip switch mapping defined (for two dip switches):

```c
#if defined(DIP_SWITCH_MAP_ENABLE)
const uint16_t PROGMEM dip_switch_map[NUM_DIP_SWITCHES][NUM_DIP_STATES] = {
    DIP_SWITCH_OFF_ON(DF(0), DF(1)),
    DIP_SWITCH_OFF_ON(EC_NORM, EC_SWAP)
};
#endif
```

::: tip
This should only be enabled at the keymap level.
:::

## Callbacks

The callback functions can be inserted into your `<keyboard>.c`:

```c
bool dip_switch_update_kb(uint8_t index, bool active) { 
    if (!dip_switch_update_user(index, active)) { return false; }
    return true;
}
```


or `keymap.c`:

```c
bool dip_switch_update_user(uint8_t index, bool active) { 
    switch (index) {
        case 0:
            if(active) { audio_on(); } else { audio_off(); }
            break;
        case 1:
            if(active) { clicky_on(); } else { clicky_off(); }
            break;
        case 2:
            if(active) { music_on(); } else { music_off(); }
            break;
        case 3:
            if (active) {
                #ifdef AUDIO_ENABLE
                    PLAY_SONG(plover_song);
                #endif
                layer_on(_PLOVER);
            } else {
                #ifdef AUDIO_ENABLE
                    PLAY_SONG(plover_gb_song);
                #endif
                layer_off(_PLOVER);
            }
            break;
    }
    return true;
}
```

Additionally, we support bit mask functions which allow for more complex handling. 


```c
bool dip_switch_update_mask_kb(uint32_t state) { 
    if (!dip_switch_update_mask_user(state)) { return false; }
    return true;
}
```


or `keymap.c`:

```c
bool dip_switch_update_mask_user(uint32_t state) { 
    if (state & (1UL<<0) && state & (1UL<<1)) {
        layer_on(_ADJUST); // C on esc
    } else {
        layer_off(_ADJUST);
    }
    if (state & (1UL<<0)) {
        layer_on(_TEST_A); // A on ESC
    } else {
        layer_off(_TEST_A);
    }
    if (state & (1UL<<1)) {
        layer_on(_TEST_B); // B on esc
    } else {
        layer_off(_TEST_B);
    }
    return true;
}
```

## Hardware

### Connects each switch in the dip switch to the GPIO pin of the MCU

One side of the DIP switch should be wired directly to the pin on the MCU, and the other side to ground.  It should not matter which side is connected to which, as it should be functionally the same. 

### Connect each switch in the DIP switch to an unused intersections in the key matrix.

As with the keyswitch, a diode and DIP switch connect the ROW line to the COL line.
