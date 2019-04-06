Debounce algorithms belong in this folder.
Here are a few ideas

1) Global vs Per-Key vs Per-Row
 * Global - one timer for all keys. Any key change state affects global timer
 * Per key - one timer per key
 * Per row - one timer per row

2) Eager vs symmetric vs asymmetric
 * Eager - any key change is reported immediately. All further inputs for DEBOUNCE ms are ignored.
 * Symmetric - wait for no changes for DEBOUNCE ms before reporting change
 * Asymmetric - wait for different times depending on key-down/key-up. E.g. Eager key-down, DEBOUNCE ms key up.

3) Timestamp vs cycles
 * old old old code waits n cycles, decreasing count by one each matrix_scan
 * newer code stores the millisecond the change occurred, and does subraction to figure out time elapsed.
 * Timestamps are superior, i don't think cycles will ever be used again once upgraded.

The default algorithm is symmetric and global.
Here are a few that could be implemented:

sym_g.c
sym_pk.c
sym_pr.c
sym_pr_cycles.c 
eager_g.c
eager_pk.c
eager_pr.c //could be used in ergo-dox!
