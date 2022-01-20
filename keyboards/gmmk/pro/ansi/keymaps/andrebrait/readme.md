# andrebrait's GMMK Pro layout

This is pretty much the stock layout with a few things moved around.
It basically reflects my needs for both Delete and Insert being readily available for coding, as well as a full Home/PgUp/PgDwn/End column.

The differences are as follows:

- Disabled Mouse Keys (to fix issues with KVM switches and also because they're not used here anyway)
- Short DEBOUNCE time (5 ms)
- Per-key debounce algorithm (sym_defer_pk)
- RGB turns off after 20 minutes of inactivity
- RGB turns off when USB is suspended
- Layer 0:
  - Print Screen (default) -> Delete
  - Delete (default) -> Home
- Layer 1 (accessed by pressing Fn):
  - Fn + Delete -> Insert
  - Fn + Home -> Print Screen

This keymap also includes CAPS LOCK ON indicator.\
All left and right side LEDs, and the Caps key LED will turn solid red while CAPS LOCK is ON.

No other changes have been made. \
The other keys on each layer have been kept intact.
