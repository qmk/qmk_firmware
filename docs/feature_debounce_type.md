# Debounce algorithm

QMK supports multiple debounce algorithms through its debounce API.

The logic for which debounce method called is below. It checks various defines that you have set in rules.mk

```
DEBOUNCE_DIR:= $(QUANTUM_DIR)/debounce
DEBOUNCE_TYPE?= ts_sym_defer_g
ifneq ($(strip $(DEBOUNCE_TYPE)), custom)
    QUANTUM_SRC += $(DEBOUNCE_DIR)/$(strip $(DEBOUNCE_TYPE)).c
endif
```

# Debounce selection

| DEBOUNCE_TYPE    | Description                                          | What else is needed           |
| -------------    | ---------------------------------------------------  | ----------------------------- |
| Not defined      | Use the default algorithm, currently ts_sym_defer_g  | Nothing                       |
| custom           | Use your own debounce code                           | ```SRC += debounce.c``` add your own debounce.c and implement necessary functions |
| anything_else    | Use another algorithm from quantum/debounce/*        | Nothing                       |

**Regarding split keyboards**:
The debounce code is compatible with split keyboards.

# Use your own debouncing code
* Set ```DEBOUNCE_TYPE = custom```.
* Add ```SRC += debounce.c```
* Add your own ```debounce.c```. Look at current implementations in ```quantum/debounce``` for examples.
* Debouncing occurs after every raw matrix scan.
* Use num_rows rather than MATRIX_ROWS, so that split keyboards are supported correctly.

# Changing between included debouncing methods
You can either use your own code, by including your own debounce.c, or switch to another included one.
Included debounce methods are:
* ts_sym_eager_pr - debouncing per row. On any state change, response is immediate, followed by locking the row ```DEBOUNCE``` milliseconds of no further input for that row. 
For use in keyboards where refreshing ```NUM_KEYS``` 8-bit counters is computationally expensive / low scan rate, and fingers usually only hit one row at a time. This could be
appropriate for the ErgoDox models; the matrix is rotated 90°, and hence its "rows" are really columns, and each finger only hits a single "row" at a time in normal use.
* ts_sym_eager_pk - debouncing per key. On any state change, response is immediate, followed by ```DEBOUNCE``` milliseconds of no further input for that key
* ts_sym_defer_g - debouncing per keyboard. On any state change, a global timer is set. When ```DEBOUNCE``` milliseconds of no changes has occured, all input changes are pushed.
* ts_sym_defer_pk - debouncing per key. On any state change, a per-key timer is set. When ```DEBOUNCE``` milliseconds of no changes have occured on that key, the key status change is pushed.

## Old names
The following old names for existing algorithms will continue to be supported, however it is recommended to use the new names instead.

* sym_g - old name for ts_sym_defer_g
* eager_pk - old name for ts_sym_eager_pk
* sym_pk - old name for ts_sym_defer_pk
* eager_pr - old name for ts_sym_eager_pr
