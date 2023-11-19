# User Space Code for Paul Ewing

This folder contains my user space code.

## Key Repeater

I've implemented a key repeater utility in [./key_repeater.h](./key_repeater.h)
and [./key_repeater.c](./key_repeater.c) that is similar in concept to the
"rapid fire" feature many game controllers come with. The intent behind this is
that the user can hold down a key and while it is pressed, a keycode will be
repeatedly sent. I have found this useful in certain games and during game
development.

The duration of the key press as well as the time between key presses is
slightly randomized by design. This is to simulate more realistic human
behavior. By setting the minimum and maximum duration fields to the same value
in the configuration, this randomization can be disabled.

**Note:** Please be aware that this might be against the terms of service in
certain games so use your own discretion before using this feature.

### How to Use

Define the repeater and then configure and allocate it in your keymap's
initialization process:

```c
static struct key_repeater_t* click_repeater = NULL;

void keyboard_post_init_user(void) {
    // Seed the random number generator which is used by the key repeater
    srand(timer_read32());

    // Configure and instantiate a key repeater for mouse button 1 "rapid fire"
    struct key_repeater_config_t cfg = {
        .key = KC_BTN1,             // Press mouse button 1 (Left click)
        .key_duration_min = 20,     // Press key for 20 to 50 milliseconds
        .key_duration_max = 50,
        .wait_duration_min = 90,    // Wait for 90 to 140 milliseconds before pressing again
        .wait_duration_max = 140,
    };

    click_repeater = kr_new(&cfg);
}
```

Make sure the key repeater is polled during matrix scanning:

```c
void matrix_scan_user(void) {
    kr_poll(click_repeater);
}
```

Define a custom keycode that will enable/disable the repeater: 

```c
enum {
    RP_BTN1 = SAFE_RANGE, // Click repeatedly while key is held
};
```

Assign the keycode to a key in your `LAYOUT(...)` macro.

Define the logic to enable/disable the repeater when the custom keycode is
pressed or released:

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case RP_BTN1:
        if (record->event.pressed) {
            kr_enable(click_repeater);
        } else {
            kr_disable(click_repeater);
        }
        return false;
    default:
        return true;
    }
}
```

For a full working example in own of my own keymaps, see:
[keyboards/cozykeys/speedo/v3/keymaps/pcewing/keymap.c](../../keyboards/cozykeys/speedo/v3/keymaps/pcewing/keymap.c)
