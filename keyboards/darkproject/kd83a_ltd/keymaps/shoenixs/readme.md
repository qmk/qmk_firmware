This layout was based on the SHVD3x layout and everything unnecessary was removed. Below is the text of SHVD3x:
This keymap has default layout and VIA enabled. It was optimized for minimal latency has NKRO by default and eager per key debounce algorithm.
If you experience unintended doublepresses and it bothers you then you can go to rules.mk and change DEBOUNCE_TYPE value to asym_eager_defer_pk or sym_defer_pk
Debounce algorithms responsiveness simplified: 
sym_eager_pk > asym_eager_defer_pk > sym_defer_pk
