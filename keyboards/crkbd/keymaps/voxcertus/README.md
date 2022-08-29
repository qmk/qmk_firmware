this is a colmak-dh layout with GASC home row mods.
it's built so that you can have the 36 key, 3x5 experience on a 3x6 Corne before committing to chopping your 3x6 down.

I was also having issues with both VIA and QMK Configurator, so going to code level bypasses those frustrations.

You can use this to power a 36 key handwired board if you wire like this:

switch matrix
------------------
top row ------> D4
middle row ---> C6
bottom row ---> D7
thumb row ----> E6

q col --------> F5
w col --------> F6
f col --------> F7
p col --------> B1
b col --------> B3

j col --------> F4
l col --------> F4
u col --------> F4
y col --------> F4
bksp col -----> F4

trrs wiring
---------------
D2 -----> pin 1
GND ----> pin 2
VCC ----> pin 3

these are the three pins on the side of a trrs connector from outside to in. you don't need the lone pin on the other side of the connector.
while you can really wire this connector any way you want (as long as you are consistent on both sides), do it this way to both not have to tweak
the data pin in code, and to not worry about frying your board if you plug your handwired board into a corne.

LED wiring
---------------


OLED wiring
---------------


Layers
---------------
default
  - colmak-dh with GASC home row mods
  - bksp on upper right key
  - space & enter on inner thumbs
  - tab & esc on outer thumbs
  - left middle thumb shifts to navigation & numpad layer
  - right middle thumb shifts to special char layer
  - hold left middle thumb then hold right middle thumb (left can then be released) shifts to function layer
  - oled layer names match layout
