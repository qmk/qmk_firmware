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
     * Timestamp-based debouncing stores the millisecond timestamp a change occurred, and does substraction to figure out time elapsed.
   * Timestamp-based debouncing is usually superior, especially in the case of noise-resistant devices because settling times of physical
     switches is specified in units of time, and should not depend on the matrix scan-rate of the keyboard.
   * Cycles-based debouncing is sometimes considered inferior, because the settling time that it is able to compensate for depends on the
     performance of the matrix scanning code. If you use cycles-based debouncing, and you significantly improve the performance of your scanning
     code, you might end up with less effective debouncing. A situation in which cycles-based debouncing might be preferable is when
     noise is present, and the scanning algorithm is slow, or variable speed. Even if your debounce algorithm is fundamentally noise-resistant,
     if the scanning is slow, and you are using a timestamp-based algorithm, you might end up making a debouncing decision based on only two
     sampled values, which will limit the noise-resistance of the algorithm.
   * Currently all built-in debounce algorithms support timestamp-based debouncing only. In the future we might
     implement cycles-based debouncing, and it will be selectable via a ```config.h``` macro.

2) Symmetric vs Asymmetric
   * Symmetric - apply the same debouncing algorithm, to both key-up and key-down events.
     * Recommended naming convention: ```sym_*```
   * Asymmetric - apply different debouncing algorithms to key-down and key-up events. E.g. Eager key-down, Defer key-up.
     * Recommended naming convention: ```asym_*``` followed by details of the type of algorithm in use, in order, for key-down and then key-up

3) Eager vs Defer
   * Eager - any key change is reported immediately. All further inputs for DEBOUNCE ms are ignored.
     * Eager algorithms are not noise-resistant.
     * Recommended naming conventions:
        * ```sym_eager_*```
        * ```asym_eager_*_*```: key-down is using eager algorithm
        * ```asym_*_eager_*```: key-up is using eager algorithm
   * Defer - wait for no changes for DEBOUNCE ms before reporting change.
     * Defer algorithms are noise-resistant
     * Recommended naming conventions:
        * ```sym_defer_*```
        * ```asym_defer_*_*```: key-down is using defer algorithm
        * ```asym_*_defer_*```: key-up is using defer algorithm

4) Global vs Per-Key vs Per-Row
   * Global - one timer for all keys. Any key change state affects global timer
     * Recommended naming convention: ```*_g```
   * Per-key - one timer per key
     * Recommended naming convention: ```*_pk```
   * Per-row - one timer per row
     * Recommended naming convention: ```*_pr```
   * Per-key and per-row algorithms consume more resources (in terms of performance,
     and ram usage), but fast typists might prefer them over global.

## Debounce algorithms supported by QMK

QMK supports multiple debounce algorithms through its debounce API.
The logic for which debounce method called is below. It checks various defines that you have set in ```rules.mk```

```
DEBOUNCE_DIR:= $(QUANTUM_DIR)/debounce
DEBOUNCE_TYPE?= sym_defer_g
ifneq ($(strip $(DEBOUNCE_TYPE)), custom)
    QUANTUM_SRC += $(DEBOUNCE_DIR)/$(strip $(DEBOUNCE_TYPE)).c
endif
```

### Debounce selection

| DEBOUNCE_TYPE    | Description                                          | What else is needed           |
| -------------    | ---------------------------------------------------  | ----------------------------- |
| Not defined      | Use the default algorithm, currently sym_defer_g     | Nothing                       |
| custom           | Use your own debounce code                           | ```SRC += debounce.c``` add your own debounce.c and implement necessary functions |
| Anything Else    | Use another algorithm from quantum/debounce/*        | Nothing                       |

**Regarding split keyboards**:
The debounce code is compatible with split keyboards.

### Selecting an included debouncing method
Keyboards may select one of the already implemented debounce methods, by adding to ```rules.mk``` the following line:
```
DEBOUNCE_TYPE = <name of algorithm>
```
Where name of algorithm is one of:
* ```sym_defer_g``` - debouncing per keyboard. On any state change, a global timer is set. When ```DEBOUNCE``` milliseconds of no changes has occurred, all input changes are pushed.
  * This is the current default algorithm. This is the highest performance algorithm with lowest memory usage, and it's also noise-resistant.
* ```sym_eager_pr``` - debouncing per row. On any state change, response is immediate, followed by locking the row ```DEBOUNCE``` milliseconds of no further input for that row. 
For use in keyboards where refreshing ```NUM_KEYS``` 8-bit counters is computationally expensive / low scan rate, and fingers usually only hit one row at a time. This could be
appropriate for the ErgoDox models; the matrix is rotated 90°, and hence its "rows" are really columns, and each finger only hits a single "row" at a time in normal use.
* ```sym_eager_pk``` - debouncing per key. On any state change, response is immediate, followed by ```DEBOUNCE``` milliseconds of no further input for that key
* ```sym_defer_pk``` - debouncing per key. On any state change, a per-key timer is set. When ```DEBOUNCE``` milliseconds of no changes have occurred on that key, the key status change is pushed.

### A couple algorithms that could be implemented in the future:
* ```sym_defer_pr```
* ```sym_eager_g```
* ```asym_eager_defer_pk```

### Use your own debouncing code
You have the option to implement you own debouncing algorithm. To do this:
* Set ```DEBOUNCE_TYPE = custom``` in ```rules.mk```.
* Add ```SRC += debounce.c``` in ```rules.mk```
* Add your own ```debounce.c```. Look at current implementations in ```quantum/debounce``` for examples.
* Debouncing occurs after every raw matrix scan.
* Use num_rows rather than MATRIX_ROWS, so that split keyboards are supported correctly.
* If the algorithm might be applicable to other keyboards, please consider adding it to ```quantum/debounce```

### Old names
The following old names for existing algorithms will continue to be supported, however it is recommended to use the new names instead.

* sym_g - old name for sym_defer_g
* eager_pk - old name for sym_eager_pk
* sym_pk - old name for sym_defer_pk
* eager_pr - old name for sym_eager_pr
