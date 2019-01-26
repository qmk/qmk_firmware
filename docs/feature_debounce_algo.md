# Debounce algorithm

QMK supports multiple debounce algorithms through its debounce API.

The underlying debounce algorithm is determined by which matrix.c file you are using.

The logic for which debounce method called is below. It checks various defines that you have set in rules.mk

```
ifeq ($(strip $(DEBOUNCE_ALGO)), manual)
    # Do nothing. do your debouncing in matrix.c
else ifeq ($(strip $(DEBOUNCE_ALGO)), sym_g)
    QUANTUM_SRC += $(DEBOUNCE)/debounce_sym_g.c
else ifeq ($(strip $(DEBOUNCE_ALGO)), eager_pk)
    QUANTUM_SRC += $(DEBOUNCE)/debounce_eager_pk.c
else # default algorithm
    QUANTUM_SRC += $(DEBOUNCE)/debounce_sym_g.c
endif
```

# Debounce selection

| DEBOUNCE_ALGO    | Description                                                 | What to do                    |
| -------------    | ---------------------------------------------------         | ----------------------------- |
| Not defined      | You are using the included matrix.c and debounce.c          | Nothing. Debounce_sym_g will be compiled, and used if necessary |
| manual           | Use your own debounce.c                                     | ```SRC += debounce.c``` add your own debounce.c and implement necessary functions |
| sym_g / eager_pk | You are using the included matrix.c and debounce.c          | Use an alternative debounce algorithm |

**Regarding split keyboards**: 
The debounce code is compatible with split keyboards.

# Use your own debouncing code
* Set ```DEBOUNCE_ALGO = manual```.
* Add ```SRC += debounce.c```
* Add your own ```debounce.c```. Look at included ```debounce_sym_g.c```s for sample implementations.
* Debouncing occurs after every raw matrix scan.

# Changing between included debouncing methods
You can either use your own code, by including your own debounce.c, or switch to another included one.
Included debounce methods are:
* debounce_eager_pk - debouncing per key. On any state change, response is immediate, followed by ```DEBOUNCE_DELAY``` millseconds of no further input for that key
* debounce_sym_g - debouncing per keyboard. On any state change, a global timer is set. When ```DEBOUNCE_DELAY``` milliseconds of no changes has occured, all input changes are pushed.


