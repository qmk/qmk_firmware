# Dvorak on the Minivan

This is a Dvorak layout for the Minivan 40% keyboard, default hardware
configuration (44 keys).

This keymap.c was edited from the default provided with this version of
QMK on Github, and the LED support was copied from ../jetpacktuxedo/
keymap. By Jos B., <joshb@xs4all.nl>


    - Basic layers are: * letters (normal Dvorak layout), (Led: off)
                        * numbers with remaining symbols, (Led: blue)
                        * function keys,                  (Led: red)
                        * and a movement layer            (Led: green)
      Extra layers: * keys like Print-Screen, CapsLock,   (Led: purple)
                    * navigation and numbers other hand,  (Led: green/blue)
                    * special characters like é.          (Led: cyan)

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

    Base layer (0)

        Esc      '"       ,<  .>  pP  yY  fF  gG  cC  rR  lL         Bksp
        Tab+LCtl  aA       oO  eE  uU  iI  dD  hH  tT  nN  sS          -_
        LSht       ;:       qQ  jJ  kK  xX  bB  mM  wW  vV  zZ       RSht
        Left+LAlt   Del+_FUN _MOV  Enter+_NSY Space  _NSY _FUN  Right+_ACC
                        hold hold        hold        hold oneshot*)   hold
  
        *) One shot: de-activates after next key, tap twice to toggle.
        
    Layer 1: Numbers and symbols.

             The numbers are on one hand, to prevent layer hold key
             swapping when typing a longer number, and to be able to
             type without holding a layer key down with the same hand.
             They follow the standard fingers 1-5, and then stay on the
             same hand, but repeat the traditional fingers for each.

             Tilde ~ does not work there without Shift, because of
             some limitation with Shift on tap keys. This part is for
             compatibility with the Pok3r keyboard, where the right hand
             second row keys are not programmable (MWVZ). Hence they
             are programmed with superfluous symbols.

        _LTR      !   @   #   $   %   ^   &   *   (   )           Bspc
        -+LCtl     1   2   3   4   5   \|  =+  /?  [{  ]}      `~+RCtl
        .+LSht      0   9   8   7   6    |   +   ?   {   }      ~+RSht
        Left+LAlt   Del   Sht(tab) ___      tab   ___  Ent  Right+RAlt
         
                
     Layer 2: Toward any layer by toggle (top row left). 
              Function keys. 
              The right side works with left held modifiers. The left side has
              F-keys with Control+Alt pressed, for switching virtual consoles.
    
        _LTR _NSY  _FUN _MOV _RAR _REV _ACC CAF11 CAF12 F12 F11    xxx
        LCtl  CAF1  CAF2 CAF3 CAF4 CAF5 F5   F4    F3    F2  F1   RCtl
        LSht   CAF10 CAF9 CAF8 CAF7 CAF6 F6   F7    F8    F9  F10 RSht
        LAlt    ___    ___      ___        ___      ___     ___   RAlt
        

     Layer 3: Movement layer: mouse and hands on navigation
              Also delete/backspace, to navigate and delete together.

        _LTR    WLft WDn  WUp  WRht  xxx  Btn3 Home PgUp PgDn End    Bksp
        LCtl     MLft MDn  MUp  MRht  Btn1 Btn1 Left Up   Down Right RCtl
        LSht      Btn5 Btn4 Btn3 Butn2 xxx  Btn2 Acc0 Acc1 Acc2 xxx  RSht
        Left+LAlt  Del      ___  Sht(tab)  tab    ___    ___   Right+RAlt
        
                
    Layer 4: Place for keys that are not symbols or F-keys, and are found
             on many keyboards. Media keys on 2nd row. 

        _LTR CapL NumL Pause ScrLk PrtSc xxx  xxx  Power Sleep Wake    xxx   
        tab   xxx  xxx   xxx   xxx  xxx   xxx  xxx  xxx  xxx    xxx Insert
        xxx    Stop Play  Prev  Next Vol-  Vol+ Mute xxx  xxx   xxx    xxx
        xxx    ___     ___      ___       ___      ___      ___        App
        

    Layer 5: Reversing hands layer numbers and navigation, for one hand
             on keyboard use.  
    
        _LTR    End  PgDn PgUp Home  xxx  xxx  xxx  xxx  xxx  xxx     Bspc
        -+LCtl    Left Down Up   Right xxx  5    4    3    2    1     RCtl
        .+LSht     xxx  xxx  xxx  xxx   xxx  6    7    8    9    0    RSht
        Left+LAlt Del    Sht(Tab)  ___      Tab    ___     Ent   Right+Alt
        

   Layer 6: Rarely used symbols, Unicode: <Ctrl(Shft(u))> <HEX input> <space>.
            AltGr or Compose did not seem to work for me, I rather not have
            dead keys. See https://en.wikipedia.org/wiki/Unicode_input 
            With tap-dances this could work ok for quite a few accented letters,
            but only basic codes supported at time of this writing).

        _LTR  xxx  xxx  è  È  xxx ___  👍  👎  xxx xxx    Bspc
        LCtrl  xxx  xxx  é  É   í  Í    😃   ⍨  xxx xxx  RCtrl
        LShft   xxx  xxx  ë  Ë  xxx xxx  🙂  🙁  xxx xxx RShft
        LALT  Del   ___    ___    ___     ___      ___     ___


   ... keycap color scheme, marks areas home (5), navigation (2+5), numbers (2+5).

                            x1111112222x
                            x5555215555x
                            x2222211111x
                              xxxxxxxx

