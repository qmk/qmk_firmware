# Minifan layout

Compile options
---------------

In ![./base_numpad.h](./base_numpad.h) this base layout is configured.

• Single numpad.

This number pad choice only has a number pad for the right hand. The
usual modifiers are in their expected places.

The single numbers pad variation is also a compile option for the _common
layer_ `_PAD`, albeit without a super/subscript auxilery layer.

• Dual numpad.

This numbers pad choice has a number pad for each hand. There are two 
number pads together on the keyboard at once.

Numpad keymaps
==============

Single numpad
-------------

──────────Numpad───────────────

![Minivan layout Image BASEdef](http://socialism.nl/misc/minivan/minivan_base_layer_numpad_single_vd.jpg)
Layer: `..._BASE`

![Minivan layout Image BASEdef](http://socialism.nl/misc/minivan/minivan_nsy_layer_numpad_single_vd.jpg)
Layer: `..._NSY`

──────────in common────────────

The otherwise ‛common’ layers are not directly available in this special layout.
You can still reach them as normal through your other Base layer.

For more about the other layers, see ➡ ![readme.md](./readme.md) ⬅

![Minivan illustration Overview layers by key, Numpad single](http://socialism.nl/misc/minivan/minivan-all-layers-clear-visualization-by-key_numpad_single_2000_vi.jpg)


Layers (text)

     Layer _ALT_BASE (Number pad, with NumLock on)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
                                           <|>
     !AlterGo NUMS: xxx   xxx   xxx   xxx   | =     7     8     9    -   Bspc  // NUMS: to ¹/₁
     LCtl     xxx   xxx   xxx   xxx   xxx   | *     4     5     6    +   RCtl
     LSht     xxx   xxx   xxx   xxx   xxx   | /     1     2     3    ,   RSht  
     ------------------------------------------------------------------------
                   LAlt   Del    Tab   Ent  | NumL  0     .     RAlt      
                                           <|>           
                   <1   ±  <2    <3    <4   | 4>    3> ±  2>    1>  
                      LGUI                  |        RGUI¹

     Layer _ALT_BASE (Number pad, with NumLock off)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring >pin>pink2>
                                           <|>
     !AlterGo NUMS: xxx   xxx   xxx   xxx   | =     Home  Up    PgUp  -   Bspc  // NUMS: to ¹/₁
     LCtl     xxx   xxx   xxx   xxx   xxx   | *     Left  5     Right +   RCtl  // modified 5
     LSht     xxx   xxx   xxx   xxx   xxx   | /     End   Down  PgDn  ,   RSht  
     -------------------------------------------------------------------------
                   LAlt   Del    Tab   Ent  | NumL  Ins   Del   RAlt      
                                           <|>
                   <1   ±  <2    <3    <4   | 4>    3> ±  2>    1>  
                        ^                   |          ^
                       LGUI                 |         RGUI¹         


     ₁) Note anomaly: additional hardware key ‛arrow’ shifted one to the left.

- - -
 
     Layer _ALT_NSY (Number pad, with NumLock on/off)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
                                           <|>
     BASE     xxx   xxx   xxx   xxx   xxx   | =     ⁷₇    ⁸₈    ⁹₉   -   Bspc
     LCtl     xxx   xxx   xxx   xxx   xxx   | *     ⁴₄    ⁵₅    ⁶₆   +   RCtl
     LSht     xxx   xxx   xxx   xxx   xxx   | /     ¹₁    ²₂    ³₃   ,   RSht  
     ------------------------------------------------------------------------
                   LAlt   Del    Tab   Ent  | xxx   ⁰₀    .DEL  RAlt      
                                           <|>           
                   <1   ±  <2    <3    <4   | 4>    3> ±  2>    1>  
                        ^                   |          ^
                       LGUI                 |         RGUI¹

     ₁) Note anomaly: additional hardware key ‛arrow’ shifted one to the left.

Dual numpad
-----------

![Minivan layout all](http://socialism.nl/misc/minivan/minivan_keycapview_numpad_double_vg.jpg)

──────────Numpad───────────────

![Minivan layout Image BASEdef](http://socialism.nl/misc/minivan/minivan_base_layer_numpad_double_vg.jpg)
Layer: `..._BASE`

![Minivan layout Image BASEdef](http://socialism.nl/misc/minivan/minivan_nsy_layer_numpad_double_vd.jpg)
Layer: `..._NSY`

──────────in common────────────

The otherwise ‛common’ layers are not directly available in this special layout.
You can still reach them as normal through your other Base layer.

For more about the other layers, see ➡ ![readme.md](./readme.md) ⬅

![Minivan illustration Overview layers by key, Numpad double](http://socialism.nl/misc/minivan/minivan-all-layers-clear-visualization-by-key_numpad_double_2000_vi.jpg)


Layers (text)

        ───────────────Numpad────────────────

     Layer _..._BASE (Number pad, square layout)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
                                           <|>
     !AlterGo Bspc  7     8     9     -     | Bspc  7     8     9    -   Bspc  //!AlterGo: to _DEF_BASE
     =         *    4     5     6     +     | *     4     5     6    +      =
     _NSY¹     /    1     2     3     ,     | /     1     2     3    ,   _NSY¹ 
     ------------------------------------------------------------------------
                   xxx     0     .     Ent  | NumL  0     .     Ent
                                           <|>
                   <1   ±  <2    <3    <4   | 4>    3> ±  2>    1>  
                        ^                   |          ^
                       LGUI                 |         RGUI²

     Layer _..._BASE (Number pad, with NumLock off)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring >pin>pink2>
                                           <|>
     !AlterGo Bspc  Home  Up    PgUp  -     | Bspc  Home  Up    PgUp  -   Bspc  //!AlterGo: to _DEF_BASE 
     =         *    Left  5     Right +     | *     Left  5     Right +      =  // modified 5
     _NSY¹     /    End   Down  PgDn  ,     | /     End   Down  PgDn  ,   _NSY¹
     -------------------------------------------------------------------------
                   xxx     Ins   Del   Ent  | NumL  Ins   Del   Ent
                                           <|>
                   <1   ±  <2    <3    <4   | 4>    3>  ± 2>    1>  
                        ^                   |           ^
                       LGUI                 |          RGUI²
 
     ₁) Toggle to the accompanying Super-Sub-Script (_NSY) layer.
     ₂) Note anomaly: additional hardware key ‛arrow’ shifted one to the left.

- - -

     Layer _..._BASE (super-/sub-script numbers, Numlock on/off)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
                                           <|>
     BASE     Bspc  ⁷₇    ⁸₈    ⁹₉    -     | Bspc  ⁷₇    ⁸₈    ⁹₉   -   Bspc
     =         *    ⁴₄    ⁵₅    ⁶₆    +     | *     ⁴₄    ⁵₅    ⁶₆   +      =
     LSht      /    ¹₁    ²₂    ³₃    ,     | /     ¹₁    ²₂    ³₃   ,   RSht
     -*-                                   <|>                            -*- //(toggle) Access on Base
     ------------------------------------------------------------------------
                   xxx    ⁰₀     .DEL  Ent  | xxx   ⁰₀    .DEL  Ent  
                                           <|>      
                   <1   ±  <2    <3    <4   | 4>    3>  ± 2>    1>  
                        ^                   |           ^
                       LGUI                 |          RGUI¹

     ₁) Note anomaly: additional hardware key ‛arrow’ shifted one to the left.


Special Base layer Numpad
=========================

This is a layout resembling a “numbers pad”. A “numbers pad”
is a separate square on a 100% sized keyboard, or separate keypad.

Unlike more usual base layers choices, which typically contain a letters
layout and access to all the common layers, this ‛Base’ layer is
quite different. Once you have switched to it, you lack keys to access
all ‛common’ layers. 

You can only switch back to your ‛regular’ base layer, or switch to a
second form of the numbers pad. This second layer is called “auxilery”
layer here, but technically it is the same thing as the numbers/symbols
`_NSY` layer, which accompanies a letters layer like Qwerty or Dvorak.

Use the top left key from the numbers pad layer, to switch back to the
other ‛Base’ layer. This is also unique to this special ‛Base’ layer,
but similar to the way the “common layers” switch back to Base.

The other Base layer (once you are in this Number Pad layer) for most
people will be a letters layer with Qwerty, Dvorak or some other layout
on it, in which the keyboard will start up.  To reach the numbers pad
Base layer, use the key ‛Other Base’ on the `_RAR` layer.


Led colors
----------

The led colors for this ‛Base’ layer are different from the usual. They show
the state of the Numbers Lock, on or off. Colors are green/light-blue/blue to
indicate Numbers Lock is off, which means the navigation cluster is active.
Colors are blue/light-blue/green to indicate the Numbers Lock is on,
meaning you can type numbers. 

This follows the same scheme as the `_PAD` layer, which in turn follows
the logic of the `_NSY` (numbers/symbols) layer being blue, and the `_MOV`
(movement/navigation) layer being green, in such a way that the left most
led is the indicator thereof, following reading direction left to right. The
brightness of the leds is diminished, to indicate the difference with `_PAD` 
layer (whether or not that layer is compiled).


Auxilery numpad layer
---------------------

With the numbers pad layer comes a second layer, as is normal for
all Base layer choices. This second layer is the same as the normal
numbers pad, except the numbers are in super- ⁽¹²³⁾ or sub-script
₍₁₂₃₎. 

The numbers on the second layer become subscript when Shift is pressed,
otherwise they are in super-script. These super-/sub-script forms of the
numbers Unicode (see the `_RAR` layer).

This second form of numbers pad is reached from keys on the numbers pad
Base layer. You can switch back to the regular numbers pad, with the
upper/left key.  Another key stroke from there on the upper/left key,
will bring you back to what is likely your regular typing layer.


Auxilery numpad layer led colors
--------------------------------

For the second layer that comes with it, with super-/sub-script numbers,
the led colors are what they “normally” are (for other compile
choices) for this layer (the ‛Alternate‛ Base accompanying layer,
usually numbers/symbols): blue/blue/light-blue.  There is no indication
of Numbers Lock on this layer, although a few keys are altered by Numbers
Lock (Dot/Delete ‛.’, and Enter).


‛Arrow’ additional hardware key
===============================

Unlike with other layers: the optional ‛arrow’ hardware key on the
right hand is not inserted between the last and second last keys on the
right, and neither is it set to the configurable default value (toggle
`_MOV` layer). Instead, this key is inserted one key over to the left,
and it is set to GUI.

The reason is that this GUI will line up with the GUI on the ‛Base’
layer. If combined with the ‛command’ hardware key on the right, set
to the other GUI, you can reach all Numbers Pad keys with all modifiers,
including both GUIs.

Another reason is that a typical use of the additional hardware
key on the right (called ‛Arrow’) will by default lead to a navigation
layer, however the Numbers Pad already has its own navigation. To add
a toggle to `_MOV` would be a matter of convenience, whereas not being
able to reach all Numbers Pad keys with either GUI could represent a
serious problem.

Downsides to this design are the loss of default ‛Arrow’ hardware key
use on this layer, and a sort of gap of one key in the Numbers Pad layout.
The downsides seem to be matters of style and convenience, whereas not 
being able to type whatever you can on a 100% keyboard could be a serious
problem for someone (keyboard shortcuts mainly).

There is no default solution to type everything with all modifiers
including the GUIs, without adding the additional hardware key(s).
Obviously it is possible to just stick a GUI on a free spot, but that 
makes things chaotic. Single pad Numbers Pad could be re-arranged to
make room for GUI, which would loose more of its similarity to other 
keyboards.


Numbers pads everywhere ?
=========================

Perhaps the amount of options for a numberical keypad are a bit overkill.
It had to do with how it developed.

For some overview of your options:

     ①  Common layer numerical keypad. Just another layer, like `_RAR`, `_BON`, etc.

       1. You can have a numerical keypad in the _common layers._
       2. You can also remove this layer entirely.

       3. This “common layers” numbers pad is activated through the Base layer, on Left Shift tap.
       4. Returns to ‛Default Base’ with upper/left key.

       5. Variation of form: right hand square form, resembling a key pad on
                             other keyboards.
       6. Variation of form: the numbers in a straight line, resembling the 
                            `_NSY` layer and other layers.

     ② A numerical keypad on the other ‛Base’ layer, in the dual layout system.

       1. You can have a numerical keypad on the ‛Alternate Base’ position.
       2. You can also put something different on ‛Alternate Base’, such as a
          Colemak layout.

       3. This layer is activated through the `_RAR` layer, by choosing ‛Other
          Base’. 
       4. Returns to ‛Default Base’ with upper/left key, effectively the same as with
          the common numerical keypad layer, and all other common layers.
    
       5. Variation of form: right hand square form, resembling a key pad on
                             other keyboards.
       6. Variation of form: dual handed square form, so you have a key pad for
                             each hand.

       7. For all variation of form, there is an accompanying layer which is
          the same, except the numbers are in Unicode super (unshifted) and
          sub-script (shifted).

Some examples:

①  As close to a 100% ‛regular’ keyboard as possible.

  If you have no use for ‛Alternate Base’ with anything else, you could put
  the single handed numerical keypad there, and remove the common `_PAD` layer
  to have less mental clutter.

  This makes accessing `_MOV` on Left Shift easier, you have modifiers with 
  the numerical keypad, and you have super/sub-script as well (although its use
  is probably rather rare).

②  The predictable numbers typing option.

  If you want ‛Alternate Base’ to have something else (or nothing
  at all), keep the `_PAD` layer, and choose straight line numbers,
  so that you don't have to learn a second way to type numbers, if you
  ever have a need to type keypad numbers (which could be quite rare).

  In this version, you are not envisioning the use of keypad navigation,
  but rather use regular `_MOV` layer navigation. (This was the original
  programming on the keyboard, before more options developed; it follows
  the overall logic that the same or similar keys are in the same or
  similar positions.)

③  The everything option.

  You could keep both `_PAD` with straight lined up numbers if you like typing
  all numbers the same way, and also compile numpad single square on ‛Alternate
  Base’ to have good access to a regular numerical keypad, should you ever need
  it, and/or to have an easier to access navigation cluster there (easier than
  navigation on the straight line numpad variation that is, where navigation
  is difficult). 

④  The numerical keyboard specialist.

  You could compile it for both hands, if you type so much on a numerical 
  keypad, that it is useful to be fast on it with either hand. 

  It will be harder to type on the double numerical keyboard with modifiers 
  (Shift, Control, Alt), but if you compile with the common numbers pad layer, 
  you can reach such combinations there. To keep things similar, you can compile
  this common numbers pad layer with numbers in square form, rather than a straight
  line.
