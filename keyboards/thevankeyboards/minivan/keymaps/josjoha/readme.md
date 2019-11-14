# Dvorak on the Minivan

This is a Dvorak layout for the Minivan 40% keyboard, default hardware
configuration (44 keys). The accented characters would likely cover
Dutch, German, French, Finnish, Norwegian, Swedish, Italian and Spanish,
besides English.

This keymap.c was edited from the default provided with this version of
QMK on Github, and the LED support was copied from ../jetpacktuxedo/
keymap. 
          By Jos B.,  joshb@xs4all.nl 


    - Basic layers are: * letters (normal Dvorak layout), (Led: off)
                        * numbers with remaining symbols, (Led: blue)
                        * function keys,                  (Led: red)
                        * and a movement layer            (Led: green)
      Extra layers: * keys like Print-Screen, CapsLock,   (Led: purple)
                    * navigation and numbers other hand,  (Led: green/blue)
                    * special characters like é.          (Led: cyan)
                    * Unicode symbols and whatever else   (Led: white)

    - Upper left key always goes back to default layer, then is Escape.

    - All layers can be statically active by toggling to the function
      layer, and then to the desired layer (top row left side).

    - Shift/Alt/Control, Del/Esc and Alt with tap arrows, repeat on
      layers.

      Except ... the Right Control on the base layer is taken off,
      because of tap delay. Right Alt on the base layer is taken off,
      instead it switches to a symbols layer (a bit like a private subset
      of AltGr symbols). (QMK allows one to press-hold to the numerical 
      layer, press a right modifier, release numerical layer, and access
      the base layer with that modifier; so it is still possible, just
      not needed.)
 
    - Leds: breathing effect on the middle LED, other indicate layer.

    See keymap.c for layout.
