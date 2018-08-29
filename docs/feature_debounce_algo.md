# Debounce algorithm

QMK supports multiple debounce algorithms through its debounce API.

The underlying debounce algorithm is determined by which matrix.c file you are using.

The logic for which debounce method called is below. It checks various defines that you have set in rules.mk

```
ifeq ($(strip $(SPLIT_KEYBOARD)), yes)
    # Do nothing, debouncing is inside matrix.c inside split_common
else ifeq ($(strip $(DEBOUNCE_ALGO)), manual)
    # Do nothing. do your debouncing in matrix.c
else ifeq ($(strip $(DEBOUNCE_ALGO)), sym_g)
    TMK_COMMON_SRC += $(DEBOUNCE)/debounce_sym_g.c
else ifeq ($(strip $(DEBOUNCE_ALGO)), eager_pk)
    TMK_COMMON_SRC += $(DEBOUNCE)/debounce_eager_pk.c
else ifeq ($(strip $(CUSTOM_MATRIX)), yes)
    # Do nothing. Custom matrix code.
else # default algorithm
    TMK_COMMON_SRC += $(DEBOUNCE)/debounce_sym_g.c
endif
```

# Debounce selection
The following is for keyboards where ```SPLIT_KEYBOARD``` is **not** defined as ```YES```

| DEBOUNCE_ALGO    | CUSTOM_MATRIX | Description                                                 | What to do                    |
| -------------    |  -------------| ---------------------------------------------------         | ----------------------------- |
| Not defined      | Not defined   | You are using the included matrix.c and debounce.c          | Nothing. Debounce_sym_g used. |
| manual           | Not defined   | You are using the included matrix.c but your own debounce.c | ```SRC += debounce.c``` add your own debounce.c and implement necessary functions |
| sym_g / eager_pk | Not defined   | You are using the included matrix.c and debounce.c          | Nothing. Chosen debounce method used. |
| Not defined      | YES           | You have your own matrix.c, and your own debounce           | Write the fully debounced matrix into matrix.c's matrix |
| manual           | YES           | Same as above                                               | same as above                                           |
| sym_g/ eager_pk  | YES           | You are using your own matrix.c, but included debounce      | Write the raw matrix values into matrix.c's matrix      |

**Note**: 
If ```SPLIT_KEYBOARD = YES``` is defined, the algorithm inside split_common will be used.
A future pull request will fix this to use the debounce.c code.

# Use your own debouncing code
* Set ```DEBOUNCE_ALGO = manual```.
* Add ```SRC += debounce.c```
* Add your own ```debounce.c```. Look at included debounce.c's for sample implementations.
* Debouncing occurs after every raw matrix scan.

# Changing between included debouncing methods
You can either use your own code, by including your own debounce.c, or switch to another included one.
Included debounce methods are:
* debounce_eager_pk - debouncing per key. On any state change, response is immediate, followed by ```DEBOUNCE_DELAY``` millseconds of no further input for that key
* debounce_sym_g - debouncing per keyboard. On any state change, a global timer is set. When ```DEBOUNCE_DELAY``` milliseconds of no changes has occured, all input changes are pushed.


