# Dvorak on the Minivan

This is a Dvorak layout for the Minivan 40% keyboard, default hardware
configuration (44 keys).

This keymap.c was edited from the default provided with this version of
QMK on Github, and the LED support was copied from ../jetpacktuxedo/
keymap. By Jos B., <joshb@xs4all.nl>


    - Basic layers are: letters (normal Dvorak layout), numbers with
      remaining symbols, function keys, and a movement layer
      (navigation and mouse).

    - The remaining layers are through the F-function layer on toggle
      keys top row.

    - Upper left key always goes back to default layer, then is Escape.

    - Shift/Alt/Control, Del/Esc and Alt with tap arrows, repeat on
      layers.

      The Right Control on the base layer is taken off, because of tap 
      delay. Right Alt as an AltGr type of thing, switches to a symbols
      layer instead.
 
    - Leds: breathing effect on the middle LED, other indicate layer.

    Base layer (0)

        Esc      '"   ,<  .>  pP  yY  fF  gG  cC  rR  lL         Bksp
        Tab+LCtl  aA   oO  eE  uU  iI  dD  hH  tT  nN  sS          -_
        LSht       ;:   qQ  jJ  kK  xX  bB  mM  wW  vV  zZ       RSht
        Left+LAlt   Del _MOV  Enter+_NSY Space  _NSY _FUN  Right+RAlt
                        hold     hold           hold toggle 
        
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
         
                
     Layer 2: Function keys. Toward any layer by toggle.
    
        _LTR _NSY _FUN _MOV _RAR _REV _ACC  F24 F23  F22  F21     xxx
        LCtl   F1   F2   F3   F4   F5   F15  F14  F13  F12  F11  RCtl
        LSht    F10  F9   F8   F7   F6   F16  F17  F18  F19  F20 RSht
        LAlt  ___     ___     ___      ___      ___       ___    RAlt
        

     Layer 3: Movement layer: mouse and hands on navigation
              Also delete/backspace, to navigate and delete together.

        _LTR    WLft WDn  WUp  WRht  xxx  Btn3 Home PgUp PgDn End    Bksp
        LCtl     MLft MDn  MUp  MRht  Btn1 Btn1 Left Up   Down Right RCtl
        LSht      Btn5 Btn4 Btn3 Butn2 xxx  Btn2 Acc0 Acc1 Acc2 xxx  RSht
        Left+LAlt  Del      ___  Sht(tab)  tab    ___    ___   Right+RAlt
        
                
    Layer 4: Dump for various unused keys. Media keys on 2nd row. I never
             use these, but just in case some future program demands them.

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
        

   Layer 6: Rarely used symbols, using Unicode Ctrl(Shft(u))HEX input,
            because AltGr or Compose did not seem to work, I rather not have
            dead keys. See https://en.wikipedia.org/wiki/Unicode_input 

        _LTR  xxx  xxx  è  È  xxx ___  👍  👎  xxx xxx    Bspc
        LCtrl  xxx  xxx  é  É   í  Í    😃   ⍨  xxx xxx  RCtrl
        LShft   xxx  xxx  ë  Ë  xxx xxx  🙂  🙁  xxx xxx RShft
        LALT  Del   ___    ___    ___     ___      ___     ___


   ... keycap color scheme, marks areas home (5), navigation (2+5), numbers (2+5).

                            011111122223
                            455552155554
                            622222111116
                              77877877

