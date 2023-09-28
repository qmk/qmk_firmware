A usable default keymap for the Ferris keyboard
===============================================

Keymap adapted to my workflow using i3 and emacs (possibly some adaptations I have forgot)

It comes with a number of layers to give access to most of the keys one may need on a keyboard.

What do all these layers do?
----------------------------

### Layer 0: Base layer

On tapping the keys, our base layer is qwerty with space on the right homing thumb and backspace on the left homing thumb.

In this layer, the non-homing-thumb positions swicht temporarly to layer 1 Left hand modifiers and Numbers (left) and layer 2 Right hand modifiers and Symbols (right)

Combos
enter = j+h
esc = d+f
del = s+d
shift = f+r and j+u
ctrl = d+e and k+i
flash = q+p

c+- combos on all layers should get you back to base layer

pressing the key above where the on shot modifer would be on layer 2 and 3 together with the butten where the one shot modifier would be will give the same modifier.
E.g. u+j gives shift, k+i gives ctrl and so on.

### Layer 1: Left Modifiers and Numbers

Layer 1 is has one shot home row modifers on the left hand and numpad on the right
The top row on the left hand are function keys F1-5 F11 is where B is on the base leve and tab on g.

Letting go of the left non-homing thumb key will take you back to the base layer.

### Layer 2: Right modifers and Symbols

Layer 2 has one shot home row modifers on the right hand and symbols on the left
The top row on the right hand are function keys F6-10 F12 is where n is on the base level

Letting go of the right non-homing thumb key will take you back to the base layer.

### Layer 3: Navigation 

Tapping the left non-homing-thumb then the right will take to to the navigation layer
jklø works as in navigation in vim only moved one key to the right to get it on the home keys
uiop there is home, page down, page up, end
There are emacs macros on the left hand q quit , s save , f timestamp, d line

Tapping the left non-homing thumb key will bring you back to the base layer.

### Layer 4: Mouse 

Tapping the right non-homing-thumb then the left will take to to the mouse layer
sdfe moves the cursor
jkl are left, middle and right mouse keys
uio are up arrow, mouse scroll up and page up
m,. are down arrow, mouse scroll down and page down
h is play / pause toggle
y is media player forward and n is media player back



