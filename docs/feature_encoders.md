# Encoders

Basic encoders are supported by adding this to your `rules.mk`:

```make
ENCODER_ENABLE = yes
```

and this to your `config.h`:

```c
#define ENCODERS_PAD_A { B12 }
#define ENCODERS_PAD_B { B13 }
```

Each PAD_A/B variable defines an array so multiple encoders can be defined, e.g.:

```c
#define ENCODERS_PAD_A { encoder1a, encoder2a }
#define ENCODERS_PAD_B { encoder1b, encoder2b }
```

If your encoder's clockwise directions are incorrect, you can swap the A & B pad definitions.  They can also be flipped with a define:

```c
#define ENCODER_DIRECTION_FLIP
```

Additionally, the resolution, which defines how many pulses the encoder registers between each detent, can be defined with:

```c
#define ENCODER_RESOLUTION 4
```

It can also be defined per-encoder, by instead defining:

```c
#define ENCODER_RESOLUTIONS { 4, 2 }
```

For 4× encoders you also can assign default position if encoder skips pulses when it changes direction. For example, if your encoder send high level on both pins by default, define this:

```c
#define ENCODER_DEFAULT_POS 0x3
```

## Split Keyboards

If you are using different pinouts for the encoders on each half of a split keyboard, you can define the pinout (and optionally, resolutions) for the right half like this:

```c
#define ENCODERS_PAD_A_RIGHT { encoder1a, encoder2a }
#define ENCODERS_PAD_B_RIGHT { encoder1b, encoder2b }
#define ENCODER_RESOLUTIONS_RIGHT { 2, 4 }
```

?> Note: When using Encoders with split keyboards, it assumes that you have double the number of encoders. If not all encoders are populated, then you may need to skip indexes. 

## Mapping Encoder Functions to the Keymap

By enabling this config, you can place the keycodes for the encoders directly in the keymap itself.  If you have extra spots in your matrix (eg, not populated), you can use those locations.  To enable this you need to add a define that lists the row and column location to use. 

```c
#define ENCODER_KEYMAPPING { { 4, 0 }, { 4, 1 } }, { { 5, 0 }, { 5, 1 } }
```

This tells it to use row 4, column 0 for counter clockwise, row 4 column 1 for clockwise, and then row 5 column 0 and 1 for the second encoder.  

This works with most keycodes.  Tap-Hold keys may not work well for this, nor will special keys, like tap dances.  However, this will work with quantum keycodes, as well as custom macros. 

Additionally, this will explicitly disable callback functionality if defined, and solely handle the encoders through the keymap. Alternatievly, you can add `#define ENCODER_PROCESS_CALLBACKS` to allow the callbacks to continue working.  And returning false in the callbacks will prevent it from handling the encoder keymap configuration.

?> Note: With Split Keyboards, you will want to define all of the possible positions. Meaning you should have double the number of encoder locations as you have "pads" defined for the encoder.

?> Note: When adding support for this, you may want to consider adding an additional layout for those that don't wish to use this functionality.

## Callbacks

The callback functions can be inserted into your `<keyboard>.c`:

```c
bool encoder_update_kb(uint8_t index, bool clockwise) {
    return encoder_update_user(index, clockwise);
}
```

or `keymap.c`:

```c
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    }
    return false;
}
```

!> If you return `true`, this will allow the keyboard level code to run, as well.  Returning `false` will override the keyboard level code.  Depending on how the keyboard level function is set up. 

## Hardware

The A an B lines of the encoders should be wired directly to the MCU, and the C/common lines should be wired to ground.

## Multiple Encoders

Multiple encoders may share pins so long as each encoder has a distinct pair of pins. 

For example you can support two encoders using only 3 pins like this
```
#define ENCODERS_PAD_A { B1, B1 }
#define ENCODERS_PAD_B { B2, B3 }
```

You could even support three encoders using only three pins (one per encoder) however in this configuration, rotating two encoders which share pins simultaneously will often generate incorrect output. For example:
```
#define ENCODERS_PAD_A { B1, B1, B2 }
#define ENCODERS_PAD_B { B2, B3, B3 }
```
Here rotating Encoder 0 `B1 B2` and Encoder 1 `B1 B3` could be interpreted as rotating Encoder 2 `B2 B3` or `B3 B2` depending on the timing. This may still be a useful configuration depending on your use case 
