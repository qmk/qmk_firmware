# Debounce algorithms

Debounce algorithms belong in this folder.

## Types of debounce algorithms

1) Timestamp vs cycles
   * Cycles-based debouncing waits n cycles, decreasing count by one each matrix_scan
     * Recommended naming convention: ```cy_*```
   * Timestamp-based debouncing stores the millisecond the change occurred, and does subraction to figure out time elapsed.
     * Timestamp-based debouncing is usually superior
     * Recommended naming convention: ```ts_*```

2) Symmetric vs Asymmetric
   * Symmetric - apply the same debouncing algorithm, to both key-up and key-down events.
     * Recommended naming convention: ```*_sym_*```
   * Asymmetric - apply different debouncing algorithms to key-down and key-up events. E.g. Eager key-down, Defer key-up.
     * Recommended naming convention: ```*_asym_*``` followed by details of the type of algorithm in use, in order, for key-down and then key-up

3) Eager vs Defer
   * Eager - any key change is reported immediately. All further inputs for DEBOUNCE ms are ignored.
     * Recommended naming conventions:
        * ```*_sym_eager_*```
        * ```*_asym_eager_*_*```: key-down is using eager algorithm
        * ```*_asym_*_eager_*```: key-up is using eager algorithm
   * Defer - wait for no changes for DEBOUNCE ms before reporting change.
     * Recommended naming conventions:
        * ```*_sym_defer_*```
        * ```*_asym_defer_*_*```: key-down is using eager algorithm
        * ```*_asym_*_defer_*```: key-up is using eager algorithm

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

The default algorithm is is of type Timestamp, Symmetric, Defer, and Global, named: ```ts_sym_defer_g```

## List of algorithms

A list of currently implemented algorithms:

* ```ts_sym_defer_g``` (the current default)
* ```ts_sym_eager_pk```
* ```ts_sym_eager_pr```
* ```ts_sym_defer_pk```

Here are a few that could be implemented:

* ```ts_sym_defer_pr```
* ```cy_sym_defer_pr```
* ```ts_sym_eager_g```
* ```ts_asym_eager_defer_pk```
* ```cy_sym_pk```

## Old names

The following old names for existing algorithms will continue to be supported,
however it is recommended to use the new names instead.

* ```sym_g``` - old name for ```ts_sym_defer_g```
* ```eager_pk``` - old name for ```ts_sym_eager_pk```
* ```sym_pk``` - old name for ```ts_sym_defer_pk```
* ```eager_pr``` - old name for ```ts_sym_eager_pr```
