# The Leader Key: A New Kind of Modifier {#the-leader-key}

If you're a Vim user, you probably know what a Leader key is. In contrast to [Combos](feature_combo), the Leader key allows you to hit a *sequence* of up to five keys instead, which triggers some custom functionality once complete.

## Usage {#usage}

Add the following to your `rules.mk`:

```make
LEADER_ENABLE = yes
```

Then add the `QK_LEAD` keycode to your keymap.

## Callbacks {#callbacks}

These callbacks are invoked when the leader sequence begins and ends. In the latter you can implement your custom functionality based on the contents of the sequence buffer.

```c
void leader_start_user(void) {
    // Do something when the leader key is pressed
}

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_F)) {
        // Leader, f => Types the below string
        SEND_STRING("QMK is awesome.");
    } else if (leader_sequence_two_keys(KC_D, KC_D)) {
        // Leader, d, d => Ctrl+A, Ctrl+C
        SEND_STRING(SS_LCTL("a") SS_LCTL("c"));
    } else if (leader_sequence_three_keys(KC_D, KC_D, KC_S)) {
        // Leader, d, d, s => Types the below string
        SEND_STRING("https://start.duckduckgo.com\n");
    } else if (leader_sequence_two_keys(KC_A, KC_S)) {
        // Leader, a, s => GUI+S
        tap_code16(LGUI(KC_S));
    }
}
```

## Basic Configuration {#basic-configuration}

### Timeout {#timeout}

This is the amount of time you have to complete a sequence once the leader key has been pressed. The default value is 300 milliseconds, but you can change this by adding the following to your `config.h`:

```c
#define LEADER_TIMEOUT 350
```

### Per-Key Timeout {#per-key-timeout}

Rather than relying on an incredibly high timeout for long leader key strings or those of us without 200 wpm typing skills, you can enable per-key timing to ensure that each key pressed provides you with more time to finish the sequence. This is incredibly helpful with leader key emulation of tap dance (such as multiple taps of the same key like C, C, C).

To enable this, add the following to your `config.h`:

```c
#define LEADER_PER_KEY_TIMING
```

After this, it's recommended that you lower your timeout below 300 ms:

```c
#define LEADER_TIMEOUT 250
```

Now, something like this won't seem impossible to do without a 1000 millisecond timeout:

```c
if (leader_sequence_three_keys(KC_C, KC_C, KC_C)) {
    SEND_STRING("Per key timing is great!!!");
}
```

### Disabling Initial Timeout {#disabling-initial-timeout}

Sometimes your leader key may be too far away from the rest of the keys in the sequence. Imagine that your leader key is one of your outer top right keys - you may need to reposition your hand just to reach your leader key. This can make typing the entire sequence on time hard difficult if you are able to type most of the sequence fast. For example, if your sequence is `Leader + asd`, typing `asd` fast is very easy once you have your hands in your home row, but starting the sequence in time after moving your hand out of the home row to reach the leader key and back is not.

To remove the stress this situation produces to your hands, you can disable the timeout just for the leader key. Add the following to your `config.h`:

```c
#define LEADER_NO_TIMEOUT
```

Now, after you hit the leader key, you will have an infinite amount of time to start the rest of the sequence, allowing you to properly position your hands to type the rest of the sequence comfortably. This way you can configure a very short `LEADER_TIMEOUT`, but still have plenty of time to position your hands.

### Strict Key Processing {#strict-key-processing}

By default, only the "tap keycode" portions of [Mod-Taps](mod_tap) and [Layer Taps](feature_layers#switching-and-toggling-layers) are added to the sequence buffer. This means if you press eg. `LT(3, KC_A)` as part of a sequence, `KC_A` will be added to the buffer, rather than the entire `LT(3, KC_A)` keycode.

This gives a more expected behaviour for most users, however you may want to change this.

To enable this, add the following to your `config.h`:

```c
#define LEADER_KEY_STRICT_KEY_PROCESSING
```

## Example {#example}

This example will play the Mario "One Up" sound when you hit `QK_LEAD` to start the leader sequence. When the sequence ends, it will play "All Star" if it completes successfully or "Rick Roll" you if it fails (in other words, no sequence matched).

```c
#ifdef AUDIO_ENABLE
float leader_start_song[][2] = SONG(ONE_UP_SOUND);
float leader_succeed_song[][2] = SONG(ALL_STAR);
float leader_fail_song[][2] = SONG(RICK_ROLL);
#endif

void leader_start_user(void) {
#ifdef AUDIO_ENABLE
    PLAY_SONG(leader_start_song);
#endif
}

void leader_end_user(void) {
    bool did_leader_succeed = false;

    if (leader_sequence_one_key(KC_E)) {
        SEND_STRING(SS_LCTL(SS_LSFT("t")));
        did_leader_succeed = true;
    } else if (leader_sequence_two_keys(KC_E, KC_D)) {
        SEND_STRING(SS_LGUI("r") "cmd\n" SS_LCTL("c"));
        did_leader_succeed = true;
    }

#ifdef AUDIO_ENABLE
    if (did_leader_succeed) {
        PLAY_SONG(leader_succeed_song);
    } else {
        PLAY_SONG(leader_fail_song);
    }
#endif
}
```

## Keycodes {#keycodes}

|Key                    |Aliases  |Description              |
|-----------------------|---------|-------------------------|
|`QK_LEADER`            |`QK_LEAD`|Begin the leader sequence|

## API {#api}

### `void leader_start_user(void)` {#api-leader-start-user}

User callback, invoked when the leader sequence begins.

---

### `void leader_end_user(void)` {#api-leader-end-user}

User callback, invoked when the leader sequence ends.

---

### `void leader_start(void)` {#api-leader-start}

Begin the leader sequence, resetting the buffer and timer.

---

### `void leader_end(void)` {#api-leader-end}

End the leader sequence.

---

### `bool leader_sequence_active(void)` {#api-leader-sequence-active}

Whether the leader sequence is active.

---

### `bool leader_sequence_add(uint16_t keycode)` {#api-leader-sequence-add}

Add the given keycode to the sequence buffer.

If `LEADER_NO_TIMEOUT` is defined, the timer is reset if the buffer is empty.

#### Arguments {#api-leader-sequence-add-arguments}

 - `uint16_t keycode`  
   The keycode to add.

#### Return Value {#api-leader-sequence-add-return}

`true` if the keycode was added, `false` if the buffer is full.

---

### `bool leader_sequence_timed_out(void)` {#api-leader-sequence-timed-out}

Whether the leader sequence has reached the timeout.

If `LEADER_NO_TIMEOUT` is defined, the buffer must also contain at least one key.

---

### `bool leader_reset_timer(void)` {#api-leader-reset-timer}

Reset the leader sequence timer.

---

### `bool leader_sequence_one_key(uint16_t kc)` {#api-leader-sequence-one-key}

Check the sequence buffer for the given keycode.

#### Arguments {#api-leader-sequence-one-key-arguments}

 - `uint16_t kc`  
   The keycode to check.

#### Return Value {#api-leader-sequence-one-key-return}

`true` if the sequence buffer matches.

---

### `bool leader_sequence_two_keys(uint16_t kc1, uint16_t kc2)` {#api-leader-sequence-two-keys}

Check the sequence buffer for the given keycodes.

#### Arguments {#api-leader-sequence-two-keys-arguments}

 - `uint16_t kc1`  
   The first keycode to check.
 - `uint16_t kc2`  
   The second keycode to check.

#### Return Value {#api-leader-sequence-two-keys-return}

`true` if the sequence buffer matches.

---

### `bool leader_sequence_three_keys(uint16_t kc1, uint16_t kc2, uint16_t kc3)` {#api-leader-sequence-three-keys}

Check the sequence buffer for the given keycodes.

#### Arguments {#api-leader-sequence-three-keys-arguments}

 - `uint16_t kc1`  
   The first keycode to check.
 - `uint16_t kc2`  
   The second keycode to check.
 - `uint16_t kc3`  
   The third keycode to check.

#### Return Value {#api-leader-sequence-three-keys-return}

`true` if the sequence buffer matches.

---

### `bool leader_sequence_four_keys(uint16_t kc1, uint16_t kc2, uint16_t kc3, uint16_t kc4)` {#api-leader-sequence-four-keys}

Check the sequence buffer for the given keycodes.

#### Arguments {#api-leader-sequence-four-keys-arguments}

 - `uint16_t kc1`  
   The first keycode to check.
 - `uint16_t kc2`  
   The second keycode to check.
 - `uint16_t kc3`  
   The third keycode to check.
 - `uint16_t kc4`  
   The fourth keycode to check.

#### Return Value {#api-leader-sequence-four-keys-return}

`true` if the sequence buffer matches.

---

### `bool leader_sequence_five_keys(uint16_t kc1, uint16_t kc2, uint16_t kc3, uint16_t kc4, uint16_t kc5)` {#api-leader-sequence-five-keys}

Check the sequence buffer for the given keycodes.

#### Arguments {#api-leader-sequence-five-keys-arguments}

 - `uint16_t kc1`  
   The first keycode to check.
 - `uint16_t kc2`  
   The second keycode to check.
 - `uint16_t kc3`  
   The third keycode to check.
 - `uint16_t kc4`  
   The fourth keycode to check.
 - `uint16_t kc5`  
   The fifth keycode to check.

#### Return Value {#api-leader-sequence-five-keys-return}

`true` if the sequence buffer matches.
