# Dip Switches

Dip switches are supported by adding this to your `rules.mk`:

    DIP_SWITCH_ENABLE = yes

and this to your `config.h`:

```c
#define NUMBER_OF_DIP_SWITCHES 4
#define DIP_SWITCH_PINS { B14, A15, A10, B9 }
```


## Callbacks

The callback functions can be inserted into your `<keyboard>.c`:

```c
void dip_switch_update_kb(uint8_t index, bool active) { 
    dip_switch_update_user(index, active); 
}
```


or `keymap.c`:

```c
void dip_switch_update_user(uint8_t index, bool active) { 
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
}
```


## Hardware

For the dip switches, one side should be wired directly to the pin on the MCU, and the other side to ground.  It should not matter which side is connected to which, as it should be functionally the same. 
