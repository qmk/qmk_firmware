# andrebrait's GMMK Pro layout

This is pretty much the stock layout with a few things moved around.
It basically reflects my needs for both Delete and Insert being readily available for coding, as well as a full Home/PgUp/PgDwn/End column.

The differences are as follows:

- Dedicated MacOS and Windows/Linux layers
  - Switching between them by pressing Fn + CAPS LOCK
- VIA support
- Disabled Mouse Keys (to fix issues with KVM switches and also because they're not used here anyway)
- RGB turns off after 20 minutes of inactivity
- RGB turns off when USB is suspended
- Layer 0:
  - Delete -> Insert
  - Page Up -> Delete
  - Page Down -> Home
- Layer 1 (accessed by pressing Fn):
  - Fn + Insert -> Pause
  - Fn + Delete -> Scroll Lock
  - Fn + Esc -> Clear EEPROM
  - Fn + (Left) CMD (macOS layout) -> Toggle the CMD + Q delay

On the Mac layer, pressing CMD + Q will not immediately send the combination.\
There's a configurable delay (defaults to 1 second) to send it.\
This is done mainly to prevent hitting CMD + Q by mistake when alternating between applications with CMD + Tab.

This keymap also includes CAPS LOCK ON indicator.\
All left and right side LEDs, and the Caps key LED will turn solid red while CAPS LOCK is ON.

No other changes have been made. \
The other keys on each layer have been kept intact.
