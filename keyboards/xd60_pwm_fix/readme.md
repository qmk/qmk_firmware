XD60 w/ PWM Fix
==

## Backlight PWM Flicker Fix
The XD60 v2 has the transistor controlling the backlight LEDs connected to pin F5. That pin does not support hardware PWM, so a software version is used. This causes flicker when you press keys.

Pin B5 does support hardware PWM.

So you can fix this by cutting the traces connected to F5 and B5. There are at least a couple versions of the board out there, so you should trace the connections yourself before cutting them. Connect the MOSFET gate pin to B5 using wire. Then connect the column (formerly connected to B5) to F5.

This is based on the findings [here](https://www.reddit.com/r/MechanicalKeyboards/comments/6xsd5c/modification_discovered_the_org60_pcb_has_a/).

## Inverted Backlight PWM Fix
Most boards use a MOSFET as a sink for the LEDs. On the XD60 v2 PCB I have, that is inverted, and the MOSFET serves as the source. This means the PWM is backwards by default. I've added the BACKLIGHT_INVERT flag in config.h and accompanying code to fix this.
