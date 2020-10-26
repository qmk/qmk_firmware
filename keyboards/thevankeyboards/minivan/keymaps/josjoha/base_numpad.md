# Minifan layout

Compiled for: Numpad
====================

This file details the compile version with `BASE_NUMPAD__ALT_BASE`.
This is a layout resembling a “numbers pad”. A “numbers pad”
is a separate block on a 100% sized keyboard, or separate keypad. This
numbers pad layer has a number pad for each hand. There are two number
pads together on the keyboard at once.

Unlike more usual base layers choices, which typically contain a letters
layout and access to all the common layers, this ‛Base’ layer is
quite different. Once you have switched to it, you lack keys to access
all ‛common’ layers. You can only switch back to your ‛regular’ base 
layer, or switch to a second form of the numbers pad.

Use the top left key from the numbers pad layer, to switch back to the
other ‛Base’ layer. The other Base layer for most people will be a
letters layer with Qwerty, Dvorak or some other layout on it, in which
the keyboard will start up.  To reach the numbers pad Base layer, use
the key ‛Other Base’ on the `_RAR` layer.

With the numbers pad layer comes a second layer, as is normal for
all Base layer choices. This second layer is the same as the normal
numbers pad, except the numbers are in super- ⁽¹²³⁾ or subscript
₍₁₂₃₎, and the upper/left key does not return to your
‛regular’ Base layer, but to the numbers pad Base layer with the
regular numbers (123…) on it. The numbers on the second layer become
subscript when Shift is pressed, otherwise they are in super-script. These
super-/sub-script forms of the numbers Unicode, which requires your
Unicode configuration is working (see the `_RAR` layer).

This second form of numbers pad is reached from keys on the numbers pad
Base layer. You can switch back to the regular numbers pad, with the
upper/left key.  Another key stroke from there on the upper/left key,
will bring you back to what is likely your regular typing layer.

Led colors
----------

The led colors for this ‛Base’ layer are also special, in that they show
the state of the “Numbers Lock”. Colors are green/light-blue/blue to
indicate “Numbers Lock” is off, meaning the navigation cluster is active.
Colors are blue/light-blue/green to indicate the “Numbers Lock” is on,
meaning you can type numbers. 

This follows the same scheme as the `_PAD` layer, which in turn follows
the logic of the `_NSY` (numbers/symbols) layer being blue, and the `_MOV`
(movement/navigation) layer being green, in such a way that the left most
led is the indicator thereof. The brightness of the leds is diminished,
to indicate the difference with `_PAD`. 

For the second layer that comes with it, with super-/sub-script
numbers, the layer led colors are what they normally are for this layer
(the ‛Alternate‛ Base accompanying layer): blue/blue/light-blue.
There is no indication of Numbers Lock on this layer, although a few
keys are altered by Numbers Lock (Dot/Delete ‛.’, and Enter).

Numpad keymaps
---------------

──────────Numpad───────────────

![Minivan layout Image BASEdef](http://socialism.nl/misc/minivan/minivan_base_layer_numpad_vd.jpg)
Layer: `..._BASE`

![Minivan layout Image BASEdef](http://socialism.nl/misc/minivan/minivan_nsy_layer_numpad_vb.jpg)
Layer: `..._NSY`

──────────in common────────────

The otherwise ‛common’ layers are not _directly_ available in this special layout.
You can still reach them as normal through your other Base layer.

For more about the other layers, see ➡ ![readme.md](./readme.md) ⬅

![Minivan illustration Overview layers by key, Numpad](http://socialism.nl/misc/minivan/minivan-all-layers-clear-visualization-by-key_numpad_2000_vd.jpg)

Layers (text)
=============

        ───────────────Numpad────────────────

     Layer _..._BASE (Number pad, with NumLock on)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
     !Alter   Bspc  7     8     9     -     | Bspc  7     8     9    -   Bspc
     =         *    4     5     6     +     | *     4     5     6    +      =
     _SSS¹     /    1     2     3     ,     | /     1     2     3    ,   _SSS¹ 
     ------------------------------------------------------------------------
                   xxx     0     .     Ent  | NumL  0     .     Ent
                                           <|>
                   <1   ±  <2    <3    <4   | 4>    3>    2>  ± 1>  
                       xxx                  |                xxx          


     Layer _..._BASE (Number pad, with NumLock off)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring >pin>pink2>
                                           <|>
     !Alter   Bspc  Home  Up    PgUp  -     | Bspc  Home  Up    PgUp  -   Bspc
     =         *    Left  xxx   Right +     | *     Left  xxx   Right +      =
     _SSS¹     /    End   Down  PgDn  ,     | /     End   Down  PgDn  ,   _SSS¹
     -------------------------------------------------------------------------
                   xxx     Ins   Del   Ent  | NumL  Ins   Del   Ent
                                           <|>
                   <1   ±  <2    <3    <4   | 4>    3>    2>  ± 1>  
                       xxx                  |                xxx          
 
     ¹) Toggle to the accompanying Super-Sub-Script (_SSS) layer.
        With regular Base layers, such as Qwerty/Dvorak, this is 
        called the Numbers&Symbols (_NSY) layer, and it is still
        called _NSY in the source code.

- - -


     Layer _..._BASE (super-/sub-script numbers)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
                                           <|>
     BASE     Bspc  ⁷₇    ⁸₈    ⁹₉    -     | Bspc  ⁷₇    ⁸₈    ⁹₉   -   Bspc
     =         *    ⁴₄    ⁵₅    ⁶₆    +     | *     ⁴₄    ⁵₅    ⁶₆   +      =
     LSht      /    ¹₁    ²₂    ³₃    ,     | /     ¹₁    ²₂    ³₃   ,   RSht
     -*-                                   <|>                            -*- //(toggle) Access on Base
     ------------------------------------------------------------------------
                   xxx    ⁰₀     .     Ent  | xxx   ⁰₀    .     Ent  
                                           <|>      
                   <1   ±  <2    <3    <4   | 4>    3>    2>  ± 1>  
                       xxx                  |                xxx          

- - -


