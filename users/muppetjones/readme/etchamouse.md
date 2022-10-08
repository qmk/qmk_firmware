# Etch-a-Mouse

Encoder-based mouse movement with acceleration!

## Usage

- Add the following to your rules.mk

  ```
  ENCODER_ENABLE = yes
  POINTING_DEVICE_ENABLE = yes
  ```

- Add the following block to your keymap.c

  ```
  #ifdef ENCODER_ENABLE
  void encoder_update_user(uint8_t index, bool clockwise) {
  #    ifdef POINTING_DEVICE_ENABLE
      encoder_update_mouse(index, clockwise);
  #    endif
      return;
  #endif
  ```

> NOTE: I use the mousekey keycodes to add button one and two into my keymap.

## How It Works

> This implementation uses the pointing device library, but it reuses several
> of the same parameters from the mouse key acceleration.

> The PD library is very light weight, but it does not animate cursor movement.
> tl;dr: The mouse movement will not be smooth!

The acceleration has four parts:

```
initial speed + (delta * time * count)
```

1. **Initial Speed**. Uses the `MOUSEKEY_INITIAL_SPEED` parameter.
2. **Delta**. Uses the `MOUSEKEY_MOVE_DELTA` parameter.
3. **Time**. The faster you turn, the faster you move.

   Subtract the time elapsed since the last actuation from a tapping term,
   defined by `TAPPING_TERM_MOUSE_ENCODER`†, with a minimum value of 1.

4. **Count**. The more you turn, the faster you move.

   Count of the total number of actuations. This value will decay over time.

† _I probably could and will eventually use `TAPPING_TERM`, but I did not want
to mess up my tap mods while experimenting with acceleration._

## Diagonal Movement

Counting the number of actuations for a given axis allows us to persist movement
along a given axis to give us some diagonal movement when moving both axes,
which also helps with the acceleration a bit and makes the movement less blocky.

## Time-based Decay (a.k.a., Deceleration)

Originally, the actuation count zeroed out once the tapping term elapsed, but
this made the movement very choppy. Instead, the count will degrade on every
refresh after the tapping term has been exceeded; unfortunately, a refresh only
occurs on an actuation on either axis, so once the time elapsed exceeds the
persistence term, the count is cleared, which also removes any movement in that
axis.
