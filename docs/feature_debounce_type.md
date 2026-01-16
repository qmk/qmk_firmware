# Contact bounce / contact chatter

Mechanical switches often don't have a clean single transition between pressed and unpressed states.

In an ideal world, when you press a switch, you would expect the digital pin to see something like this:
(X axis showing time
```
voltage                   +----------------------
 ^                        |
 |                        |
 |      ------------------+
          ----> time
```

However in the real world you will actually see contact bounce, which will look like multiple 1->0 and 0->1 transitions,
until the value finally settles.
```
                  +-+ +--+ +-------------
                  | | |  | |
                  | | |  | |
+-----------------+ +-+  +-+
```
The time it takes for the switch to settle might vary with switch type, age, and even pressing technique.

If the device chooses not to mitigate contact bounce, then often actions that happen when the switch is pressed are repeated
multiple times.

There are many ways to handle contact bounce ("Debouncing"). Some include employing additional hardware, for example an RC filter,
while there are various ways to do debouncing in software too, often called debounce algorithms. This page discusses software
debouncing methods available in QMK.

While technically not considered contact bounce/contact chatter, some switch technologies are susceptible to noise, meaning,
while the key is not changing state, sometimes short random 0->1 or 1->0 transitions might be read by the digital circuit, for example:
```
                  +-+
                  | |
                  | |
+-----------------+ +--------------------
```

Many debounce methods (but not all) will also make the device resistant to noise. If you are working with a technology that is
susceptible to noise, you must choose a debounce method that will also mitigate noise for you.

## Types of debounce algorithms

1) Unit of time: Timestamp (milliseconds) vs Cycles (scans)
   * Debounce algorithms often have a 'debounce time' parameter, that specifies the maximum settling time of the switch contacts.
     This time might be measured in various units:
     * Cycles-based debouncing waits n cycles (scans), decreasing count by one each matrix_scan
     * Timestamp-based debouncing stores the millisecond timestamp a change occurred, and does subtraction to figure out time elapsed.
   * Timestamp-based debouncing is usually superior, especially in the case of noise-resistant devices because settling times of physical
     switches is specified in units of time, and should not depend on the matrix scan-rate of the keyboard.
   * Cycles-based debouncing is sometimes considered inferior, because the settling time that it is able to compensate for depends on the
     performance of the matrix scanning code. If you use cycles-based debouncing, and you significantly improve the performance of your scanning
     code, you might end up with less effective debouncing. A situation in which cycles-based debouncing might be preferable is when
     noise is present, and the scanning algorithm is slow, or variable speed. Even if your debounce algorithm is fundamentally noise-resistant,
     if the scanning is slow, and you are using a timestamp-based algorithm, you might end up making a debouncing decision based on only two
     sampled values, which will limit the noise-resistance of the algorithm.
   * Currently all built-in debounce algorithms support timestamp-based debouncing only. In the future we might
     implement cycles-based debouncing, and it will be selectable via a `config.h` macro.

2) Symmetric vs Asymmetric
   * Symmetric - apply the same debouncing algorithm, to both key-up and key-down events.
     * Recommended naming convention: `sym_*`
   * Asymmetric - apply different debouncing algorithms to key-down and key-up events. E.g. Eager key-down, Defer key-up.
     * Recommended naming convention: `asym_*` followed by details of the type of algorithm in use, in order, for key-down and then key-up

3) Eager vs Defer
   * Eager - any key change is reported immediately. All further inputs for DEBOUNCE ms are ignored.
     * Eager algorithms are not noise-resistant.
     * Recommended naming conventions:
        * `sym_eager_*`
        * `asym_eager_*_*`: key-down is using eager algorithm
        * `asym_*_eager_*`: key-up is using eager algorithm
   * Defer - wait for no changes for DEBOUNCE ms before reporting change.
     * Defer algorithms are noise-resistant
     * Recommended naming conventions:
        * `sym_defer_*`
        * `asym_defer_*_*`: key-down is using defer algorithm
        * `asym_*_defer_*`: key-up is using defer algorithm

4) Global vs Per-Key vs Per-Row
   * Global - one timer for all keys. Any key change state affects global timer
     * Recommended naming convention: `*_g`
   * Per-key - one timer per key
     * Recommended naming convention: `*_pk`
   * Per-row - one timer per row
     * Recommended naming convention: `*_pr`
   * Per-key and per-row algorithms consume more resources (in terms of performance,
     and ram usage), but fast typists might prefer them over global.

## Supported Debounce Algorithms

QMK supports multiple algorithms through its debounce API.

### Debounce Time

Default debounce time is 5 milliseconds and it can be changed with the following line in `config.h`:
```
#define DEBOUNCE 10
```
::: tip
Setting `DEBOUNCE` to `0` will disable this feature.
:::

### Debounce Method

Keyboards may select one of the core debounce methods by adding the following line into `rules.mk`:
```
DEBOUNCE_TYPE = <name of algorithm>
```
Name of algorithm is one of:

| Algorithm             | Description |
| --------------------- | ----------- |
| `sym_defer_g`         | Debouncing per keyboard. On any state change, a global timer is set. When `DEBOUNCE` milliseconds of no changes has occurred, all input changes are pushed. This is the highest performance algorithm with lowest memory usage and is noise-resistant. |
| `sym_defer_pr`        | Debouncing per row. On any state change, a per-row timer is set. When `DEBOUNCE` milliseconds of no changes have occurred on that row, the entire row is pushed. This can improve responsiveness over `sym_defer_g` while being less susceptible to noise than per-key algorithm. |
| `sym_defer_pk`        | Debouncing per key. On any state change, a per-key timer is set. When `DEBOUNCE` milliseconds of no changes have occurred on that key, the key status change is pushed. |
| `sym_eager_pr`        | Debouncing per row. On any state change, response is immediate, followed by `DEBOUNCE` milliseconds of no further input for that row. |
| `sym_eager_pk`        | Debouncing per key. On any state change, response is immediate, followed by `DEBOUNCE` milliseconds of no further input for that key. |
| `asym_eager_defer_pk` | Debouncing per key. On a key-down state change, response is immediate, followed by `DEBOUNCE` milliseconds of no further input for that key. On a key-up state change, a per-key timer is set. When `DEBOUNCE` milliseconds of no changes have occurred on that key, the key-up status change is pushed. |

::: tip
`sym_defer_g` is the default if `DEBOUNCE_TYPE` is undefined.
:::

::: tip
`sym_eager_pr` is suitable for use in keyboards where refreshing `NUM_KEYS` 8-bit counters is computationally expensive or has low scan rate while fingers usually hit one row at a time. This could be appropriate for the ErgoDox models where the matrix is rotated 90°. Hence its "rows" are really columns and each finger only hits a single "row" at a time with normal usage.
:::

### Implementing your own debouncing code

You have the option to implement you own debouncing algorithm with the following steps:

* Set `DEBOUNCE_TYPE = custom` in `rules.mk`.
* Add `SRC += debounce.c` in `rules.mk`
* Implement your own `debounce.c`. See `quantum/debounce` for examples.
* Debouncing occurs after every raw matrix scan.
* Use num_rows instead of MATRIX_ROWS to support split keyboards correctly.
* If your custom algorithm is applicable to other keyboards, please consider making a pull request.
