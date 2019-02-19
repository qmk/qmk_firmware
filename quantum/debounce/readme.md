Debounce algorithms belong in this folder.
Here are a few ideas

1) Global vs Per-Key vs Per-Row
 * Global - one timer for all keys. Any key change state affects global timer
 * Per key - one timer per key
 * Per row - one timer per row

2) Eager vs symmetric vs assymetric
 * Eager - any key change is reported immediately. All further inputs for DEBOUNCE ms are ignored.
 * Symmetric - wait for no changes for DEBOUNCE ms before reporting change
 * Assymetric - wait for different times depending on key-down/key-up. E.g. Eager key-down, DEBOUNCE ms key up.

3) Timestamp vs cycles
 * old old old code waits n cycles, decreasing count by one each matrix_scan
 * newer code stores the millisecond the change occurred, and does subraction to figure out time elapsed.
 * Timestamps are superior, i don't think cycles will ever be used again once upgraded.

The default algorithm is symmetric and global.
Here are a few that could be implemented:

debounce_sym_g.c
debounce_sym_pk.c 
debounce_sym_pr.c 
debounce_sym_pr_cycles.c //currently used in ergo-dox
debounce_eager_g.c
debounce_eager_pk.c
debounce_eager_pr.c //could be used in ergo-dox!
