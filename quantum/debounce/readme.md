# Debouncers

Debounce algorithms belong in this folder.

Debouncers have two main properties:

1) Number of timers
 * Global - one timer for all keys (any key state change affects a global timer)
 * Per key - one timer per key
 * Per row - one timer per row

2) How `DEBOUNCE` is applied
 * Eager - any key change is reported immediately, all further inputs for `DEBOUNCE` ms are ignored
 * Symmetric - wait for no changes for `DEBOUNCE` ms before reporting change
 * Asymmetric - wait for different times depending on key-down/key-up (e.g. eager key-down, `DEBOUNCE` ms key up)

### Note: Timestamp vs cycles

Old old old code waits `n` cycles, decreasing a `count` variable by `1` each `matrix_scan`. Newer code stores the millisecond the change occurred, and uses arithmetic to figure out time elapsed. The use of timestamps is preferable; counting calls to `matrix_scan` is prone to accumulating timing errors.

## Available debouncers:

The default algorithm `sym_g` is symmetric and global. The following algorithms are available:
 * `eager_pk`
 * `eager_pr`
 * `sym_g`
 * `sym_pk`
