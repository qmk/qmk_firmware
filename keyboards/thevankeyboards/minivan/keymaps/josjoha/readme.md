# Dvorak on the Minivan

This is a Dvorak layout for the Minivan 40% keyboard, default hardware
configuration (44 keys).

This keymap.c was edited from the default provided with this version of
QMK on Github, and the LED support was copied from ../jetpacktuxedo/
keymap. This has a breathing effect on the third LED. The other LEDs
where set to indicate the active layer.


    - Basic layers are: letters (normal Dvorak layout), numbers with
      remaining symbols, and a movement layer (navigation and mouse).

    - Upper left key always goes back to default layer, then is Escape.

    - The remaining two layers are through the F-function layer on toggle
      keys top row. Those are seldom used layers (rare keys and reverse 
      hand numbers / navigation).

    - Shift/Alt/Control, Del/Esc and Alt holds with tap arrows, repeat
      on layers where it can means something, to keep it simple.

      The Right Control on the base layer is taken off, because it
      causes the hyphen to wait for processing a short time, which trips
      up typing.  For the same reason space is not a tap toggle key.

      Other tap-toggles exist for less used keys: enter, tab, Alt tap
      arrows (mainly used to scroll videos when not typing). The
      modifiers Alt/Shift/Control are on the outside of the board,
      to make it easier to access when using a mouse/tablet and
      reposition hand (things like 3D editing).

    - Usual layer switching by thumb hold keys, allows both hands to
      continue typing better. There are two for layer 1, which has all
      the symbols and numbers, to be able to type left and switch layer
      with the right hand, and vice versa.


    Base layer

          Esc      '"   ,<  .>  pP  yY  fF  gG  cC  rR  lL         Bksp
          Tab+LCtl  aA   oO  eE  uU  iI  dD  hH  tT  nN  sS          -_
          LSht       ;:   qQ  jJ  kK  xX  bB  mM  wW  vV  zZ       RSht
          Left+LAlt   Del _MOV  Enter+_NSY Space  _NSY _FUN  Right+RAlt
                          hold      hold          hold toggle 
        
    Layer 1: Numbers and symbols.

             The numbers are on one hand, to prevent layer hold key
             swapping when typing a longer number, and to be able to
             type without holding a layer key down with the same hand.
             They follow the standard fingers 1-5, and then stay on the
             same hand, but repeat the traditional fingers for each,
             meaning that 4, 5, 6, 7, index finger, 3 and 8 middle
             fingers, etc. It seems easier to learn the new layout
             that way.

             Off hand Number input (-.Bksp ent (shft)tab), a bit like
             a numpad. Tab to jump cells, - for negative numbers, etc.

             The symbols /=\ are repeated on the home row, but reversed
             to put less used \| in the weaker position (jumps a key).
             Symbols [] are put under () on the same fingers, seems to
             make it more harmoneous / easier to remember.

             Tilde ~ does not work there without Shift, because of
             some limitation with Shift on tap keys. This part is for
             compatibility with the Pok3r keyboard, where the right hand
             second row keys are not programmable (MWVZ). Hence they
             are programmed here with superfluous symbols already available
             on the home row with Shift plus layer. This three way combination
             is not ideal, but these symbols are at least usually typed
             as singles, and it is on the home row.

         _LTR      !   @   #   $   %   ^   &   *   (   )           Bspc
         -+LCtl     1   2   3   4   5   \|  =+  /?  [{  ]}      `~+RCtl
         .+LSht      0   9   8   7   6    |   +   ?   {   }      ~+RSht
         Left+LAlt   Del   Sht(tab) ___      tab   ___  Ent  Right+RAlt
         
                
     Layer 2: Function keys. This is also on a toggle because F-keys
              get used with Alt and Control, making it a difficult 
              combination if also a layer key needs to be held down.

              Toward any layer by toggle, so that layers can also be
              available without holding a layer key down.
    
        _LTR _NSY _FUN _MOV _RAR  xxx  xxx  F24 F23  F22  F21     xxx
        LCtl   F1   F2   F3   F4   F5   F15  F14  F13  F12  F11  RCtl
        LSht    F10  F9   F8   F7   F6   F16  F17  F18  F19  F20 RSht
        LAlt  ___     ___     ___      ___      ___       ___    RAlt
        

     Layer 3: Movement layer: mouse and hands on navigation
              Also delete/backspace, to navigate and delete together.
              The direction layout is four in a row, because it makes the
              mapping easier on the board in my opinion, but it does not
              matter that much.

        _LTR    WLft WDn  WUp  WRht  xxx  Btn3 Home PgUp PgDn End    Bksp
        LCtl     MLft MDn  MUp  MRht  xxx  Btn1 Left Up   Down Right RCtl
        LSht      Btn5 Btn4 Btn3 Butn2 Btn1 Btn2 Acc0 Acc1 Acc2 xxx  RSht
        Left+LAlt  Del      ___  Sht(tab)  tab    ___    ___   Right+RAlt
        
                
    Layer 4: Dump for various unused keys. Media keys on 2nd row. I never
             use these, but just in case some future program demands them.

         _LTR CapL NumL Pause ScrLk PrtSc xxx  xxx  Power Sleep Wake    xxx   
         tab   xxx  xxx   xxx   xxx  xxx   xxx  xxx  xxx  xxx    xxx Insert
         xxx    Stop Play  Prev  Next Vol-  Vol+ Mute xxx  xxx   xxx    xxx
         xxx    ___     ___      ___       ___      ___      ___        App
        

    Layer 5: Reversing hands layer numbers and navigation, for one hand
             on keyboard use.  Generally follows numbers layer. One reason
             to have a second navigation cluster and numbers is because
             it keeps the mirrored logic going if one needs to use an
             arrow cluster or numbers on the other hand than normal.
    
        _LTR    End  PgDn PgUp Home  xxx  xxx  xxx  xxx  xxx  xxx     Bspc
        -+LCtl    Left Down Up   Right xxx  5    4    3    2    1     RCtl
        .+LSht     xxx  xxx  xxx  xxx   xxx  6    7    8    9    0    RSht
        Left+LAlt Del    Sht(Tab)  ___      Tab    ___     Ent   Right+Alt
        
