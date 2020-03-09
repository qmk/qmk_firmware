# Compose Onboard

You may already know the concept of composing from linux, sometimes also called multi key. Composing allows to map a sequence of keystrokes to press different keys, insert a character, or perform any preconfigured action. For example this is often used to write foreign or unicode characters. This features allows you to define such mappings directly on the keyboard. For example, you can create a mapping to write the character `→` by tapping `-` followed by `>` after pressing the compose key.

This is similar to how the [Leader Key](feature_leader_key.md) works. However, while the Leader Key is time-based, compose doesn't have any time constraints.

To use this feature, set one of your keys to `KC_COMPOSE_ONBOARD`, which you can then use to start a compose sequence. Also don't forget to enable the compose onboard feature as described in "Adding Compose Onboard Support in the `rules.mk`".

Imagine the example mapping from above (`-` `>` → `→`). After pressing `KC_COMPOSE_ONBOARD` any key press will be captured (i.e. not written on the computer). We can now type `-` and `>`, which will result in the character `→` being sent to the computer instead. Composing stops by finishing a sequence (e.g. `-` `>`), typing a key for which no further mapping matches (`f`, or `-` `a`), or by pressing the abort key (which defaults to the compose key itself). In those cases no output will be generated.


```c
COMPOSE_ONBOARD_DICTIONARY(
    // quantum keyboard
    COMPOSE_ONBOARD_MAPPING(
        COMPOSE_ONBOARD_INPUT(KC_Q, KC_M, KC_K),
        COMPOSE_ONBOARD_ACTION(
            KC_Q, KC_U, KC_A, KC_N, KC_T, KC_U, KC_M,
            KC_SPC, KC_K, KC_E, KC_Y, KC_B, KC_O, KC_A, KC_R, KC_D
        )
    )
    // →
    COMPOSE_ONBOARD_MAPPING(
        COMPOSE_ONBOARD_INPUT(KC_MINS, KC_GT),
        {
            unicode_input_start();
            register_hex(0x2192);
            unicode_input_finish();
        }
    )
    // shrug
    COMPOSE_ONBOARD_MAPPING(
        COMPOSE_ONBOARD_INPUT(KC_S, KC_H, KC_R, KC_U, KC_G),
        {
            unicode_input_start();
            register_hex(0xaf);
            register_hex(0x5c);
            register_hex(0x5f);
            register_hex(0x28);
            register_hex(0x30c4);
            register_hex(0x29);
            register_hex(0x5f);
            register_hex(0x2f);
            register_hex(0xaf);
            unicode_input_finish();
        }
    )
)
```

* `COMPOSE_ONBOARD_DICTIONARY` starts the list of all mappings
* `COMPOSE_ONBOARD_MAPPING` defines a mapping from an input key sequence to an action
    * the first argument is the input key sequence
    * the second argument is the action
* `COMPOSE_ONBOARD_INPUT` is used to define the key sequence needed to be typed to trigger the action
* `COMPOSE_ONBOARD_ACTION` can be used to define a key sequence to be typed if the input sequence has been typed

The action can also be a code block containing any C code. This can be used like in the above example to write a unicode character, or to run any arbitrary code similar to a predefined macro.

## Adding Compose Onboard Support in the `rules.mk`

To add support for Compose Onboard you simply need to add a single line to your keymap's `rules.mk`:

```make
COMPOSE_ONBOARD_ENABLE = yes
```

## Configuring the Abort Key

The abort key can be used while in the middle of a sequence to abort composing. It defaults to the compose key itself. If you press the compose key to start a compose sequence, but want to abort halfway through, you can press the compose key (i.e. the configured abort key). (Or you could just continue with a key which doesn't have any mapping.)

```c
#define COMPOSE_ONBOARD_ABORT KC_COMPOSE_ONBOARD
```

## Configuring the Maximum Input Length

While performing a compose sequence, the pressed keys are recorded. The maximum number of keys recorded should match the longest input of any compose mapping (but can be larger). By default, the number of recorded keys is configured to be `5`. However, if you want to have an input sequence longer than that, you need to adjust that number.

```c
#define COMPOSE_ONBOARD_LEN 5
```

Notice that compilation will fail with "Number of keys in Compose Onboard input keystroke is too long. Consider increasing COMPOSE_ONBOARD_LEN" if you define an input which is longer than the configured `COMPOSE_ONBOARD_LEN`.

## Customization - Hooks

There are some functions which you can define, which will be called during composing.

* `void compose_onboard_start(void)` is called when the compose key is pressed and can for example be used to light up an LED to indicate that you are within a compose sequence.
* `void compose_onboard_end(void)` is called when composing is done, either by having been aborted or finished successfully. It can for example be used to turn off the composing LED again.

## Customization - Custom Dictionary

The macros used above to define the dictionary define a function, which is called for the mapping procedure. For fine-grained control, you can manually define that function instead of using the macros.

The mapping function has the signature `bool compose_onboard_mapping(uint16_t* sequence, uint8_t len)`. That function is called whenever a new key is pressed, after it has been added to the sequence array.

* `uint16_t* sequence`: a pointer to an array of recorded keys like `KC_MINS`
* `uint8_t len`: current length of that array


To get a feeling for that function, this is an example of the macros and their resulting function definition.

```c
COMPOSE_ONBOARD_DICTIONARY(
    // quantum keyboard
    COMPOSE_ONBOARD_MAPPING(
        COMPOSE_ONBOARD_INPUT(KC_Q, KC_M, KC_K),
        COMPOSE_ONBOARD_ACTION(
            KC_Q, KC_U, KC_A, KC_N, KC_T, KC_U, KC_M,
            KC_SPC, KC_K, KC_E, KC_Y, KC_B, KC_O, KC_A, KC_R, KC_D
        )
    )
    // →
    COMPOSE_ONBOARD_MAPPING(
        COMPOSE_ONBOARD_INPUT(KC_MINS, KC_GT),
        {
            unicode_input_start();
            register_hex(0x2192);
            unicode_input_finish();
        }
    )
)
```

The above macros get converted to the following code.

```c
bool compose_onboard_mapping(uint16_t* sequence, uint8_t sequence_len) {
    bool partial_match = false;
    {
        uint16_t input[] = {KC_Q, KC_M, KC_K};
        _Static_assert((sizeof(input) / sizeof(input[0])) <= COMPOSE_ONBOARD_LEN, "Number of keys in Compose Onboard input keystroke is too long. Consider increasing COMPOSE_ONBOARD_LEN");
        uint8_t input_len = (sizeof(input) / sizeof(input[0]));
        int res = compose_onboard_compare_input(input, input_len, sequence, sequence_len);
        if (res == -1) {
            uint16_t actions[] = {
                KC_Q, KC_U, KC_A, KC_N, KC_T, KC_U, KC_M,
                KC_SPC, KC_K, KC_E, KC_Y, KC_B, KC_O, KC_A, KC_R, KC_D
            };
            for (int i = 0; i < (sizeof(actions) / sizeof(actions[0])); i++) {
                register_code16(actions[i]);
                unregister_code16(actions[i]);
            }
            return false;
        }
        partial_match |= res;
    }
    {
        uint16_t input[] = {KC_MINS, KC_GT};
        _Static_assert((sizeof(input) / sizeof(input[0])) <= 5, "Number of keys in Compose Onboard input keystroke is too long. Consider increasing COMPOSE_ONBOARD_LEN");
        uint8_t input_len = (sizeof(input) / sizeof(input[0]));
        int res = compose_onboard_compare_input(input, input_len, sequence, sequence_len);
        if (res == -1) {
            {
                unicode_input_start();
                register_hex(0x2192);
                unicode_input_finish();
            }
return false;
        }
        partial_match |= res;
    }
    return partial_match;
}
```

That code uses the helper function `int compose_onboard_compare_input(uint16_t* input, uint8_t input_len, uint16_t* seq, uint8_t seq_len)`. That function compares the compose mapping input to the sequence so far. Its return values are counter-intuitive for binary size reasons. It returns -1 on a full match (the input matched completely and the action can be performed), 0 on no match (it's never possible in the current sequence to get this input), and 1 on a partial match (the recorded sequence so far matches the beginning of the mapping input, but the mapping input still has some keys left).

