# Encoders

Basic encoders are supported by adding this to your `rules.mk`:

    ENCODER_ENABLE = yes

and this to your `config.h`:

    #define ENCODERS_PAD_A { B12 }
    #define ENCODERS_PAD_B { B13 }

Each PAD_A/B variable defines an array so multiple encoders can be defined, e.g.:

    #define ENCODERS_PAD_A { encoder1a, encoder2a }
    #define ENCODERS_PAD_B { encoder1b, encoder2b }

If your encoder's clockwise directions are incorrect, you can swap the A & B pad definitions.

Additionally, the resolution can be specified in the same file (the default & suggested is 4):

    #define ENCODER_RESOLUTION 4

## Split Keyboards

If you are using different pinouts for the encoders on each half of a split keyboard, you can define the pinout for the right half like this:

```c
#define ENCODERS_PAD_A_RIGHT { encoder1a, encoder2a }
#define ENCODERS_PAD_B_RIGHT { encoder1b, encoder2b }
```

## Callbacks

The callback functions can be inserted into your `<keyboard>.c`:

    void encoder_update_kb(uint8_t index, bool clockwise) {
        encoder_update_user(index, clockwise);
    }

or `keymap.c`:

    void encoder_update_user(uint8_t index, bool clockwise) {
      if (index == 0) { /* First encoder */
        if (clockwise) {
          tap_code(KC_PGDN);
        } else {
          tap_code(KC_PGUP);
        }
      } else if (index == 1) { /* Second encoder */  
        if (clockwise) {
          tap_code(KC_UP);
        } else {
          tap_code(KC_DOWN);
        }
      }
    }

## Hardware

The A an B lines of the encoders should be wired directly to the MCU, and the C/common lines should be wired to ground.

## Encoder matrix

You can also wire the C/common line through a diode (arrow towards the row) to each of the rows (or reading pin) in your matrix, and use as many encoders as you have rows (multiplied by the number of A/B lines you have hooked up). To do this, you can add this line to your `config.h` with all of the pins you use:

```c
#define ENCODERS_PAD_C { encoder1c, encoder2c }
```