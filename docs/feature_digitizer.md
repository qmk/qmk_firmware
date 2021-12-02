## Digitizer

The digitizer HID interface allows setting the mouse cursor position at absolute coordinates, unlike the Pointing Device feature that applies relative displacements.

To enable the digitizer interface, add the following line to your rules.mk: 

```makefile
DIGITIZER_ENABLE = yes
```

In order to change the mouse cursor position from your keymap.c file, include the digitizer header : 

```c
#include "digitizer.h"
```

This gives you access to the `digitizer` structure which members allow you to change the cursor position.

The coordinates are normalized, meaning there value must be set between 0 and 1. For the `x` coordinate, the value `0` is the leftmost position, whereas the value `1` is the rightmost position.
For the `y` coordinate, `0` is at the top and `1` at the bottom.

Here is an example setting the cursor in the middle of the screen:

```c
digitizer_t digitizer;
digitizer.x = 0.5;
digitizer.y = 0.5;
digitizer.tipswitch = 0;
digitizer.inrange = 1;
digitizer_set_report(digitizer);
```

The `tipswitch` member triggers what equates to a click when set to `1`. The `inrange` member is required for the change in coordinates to be taken. It can then be set to `0` in a new report to signal the end of the digitizer interaction, but it is not strictly required.

Once all members are set to the desired value, the `status` member needs its bitmask `DZ_UPDATED` to be set so the report is sent during the next main loop iteration.
