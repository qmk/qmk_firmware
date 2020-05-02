# Debounce algorithms

Debounce algorithms belong in this folder.

## Types of debounce algorithms

1) Timestamp vs cycles
   * Cycles-based debouncing waits n cycles, decreasing count by one each matrix_scan
   * Timestamp-based debouncing stores the millisecond the change occurred, and does subraction to figure out time elapsed.
     * Timestamp-based debouncing is usually superior
   * Currently all built-in debounce algorithms support timestamp-based debouncing only. In the future we might
     implement cycles-based debouncing, and it will be selectable via a config.h macro.

2) Symmetric vs Asymmetric
   * Symmetric - apply the same debouncing algorithm, to both key-up and key-down events.
     * Recommended naming convention: ```sym_*```
   * Asymmetric - apply different debouncing algorithms to key-down and key-up events. E.g. Eager key-down, Defer key-up.
     * Recommended naming convention: ```asym_*``` followed by details of the type of algorithm in use, in order, for key-down and then key-up

3) Eager vs Defer
   * Eager - any key change is reported immediately. All further inputs for DEBOUNCE ms are ignored.
     * Recommended naming conventions:
        * ```sym_eager_*```
        * ```asym_eager_*_*```: key-down is using eager algorithm
        * ```asym_*_eager_*```: key-up is using eager algorithm
   * Defer - wait for no changes for DEBOUNCE ms before reporting change.
     * Recommended naming conventions:
        * ```sym_defer_*```
        * ```asym_defer_*_*```: key-down is using eager algorithm
        * ```asym_*_defer_*```: key-up is using eager algorithm

4) Global vs Per-Key vs Per-Row
   * Global - one timer for all keys. Any key change state affects global timer
     * Recommended naming convention: ```*_g```
   * Per key - one timer per key
     * Recommended naming convention: ```*_pk```
   * Per row - one timer per row
     * Recommended naming convention: ```*_pr```

## Specifying which algorithm to use

Keyboards may select which algorithm to use by adding to ```rules.mk``` the following line:
```
DEBOUNCE_TYPE = <name of algorithm>
```

To implement a fully custom debounce algorithm local to the keyboard, the following can be specified:
```
DEBOUNCE_TYPE = custom
```

The default algorithm is is of type Timestamp, Symmetric, Defer, and Global, named: ```sym_defer_g```

## List of algorithms

A list of currently implemented algorithms:

* ```sym_defer_g``` (the current default)
* ```sym_eager_pk```
* ```sym_eager_pr```
* ```sym_defer_pk```

Here are a few that could be implemented:

* ```sym_defer_pr```
* ```sym_eager_g```
* ```asym_eager_defer_pk```

## Old names

The following old names for existing algorithms will continue to be supported,
however it is recommended to use the new names instead.

* ```sym_g``` - old name for ```sym_defer_g```
* ```eager_pk``` - old name for ```sym_eager_pk```
* ```sym_pk``` - old name for ```sym_defer_pk```
* ```eager_pr``` - old name for ```sym_eager_pr```
