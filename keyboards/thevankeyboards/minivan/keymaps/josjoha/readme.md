# Dvorak on the Minivan

This is a Dvorak layout for the Minivan 40% keyboard, default hardware
configuration (44 keys). The accented characters would likely cover
Dutch, German, French, Finnish, Norwegian, Swedish, Italian and Spanish,
besides English.

This keymap.c was edited from the default provided with this version of
QMK on Github, and the LED support was copied from ../jetpacktuxedo/
keymap. 
          By Jos B., <joshb@xs4all.nl>


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

    Base layer (0)
                                        | Right hand
  pink2    pinky ring  middl index indx2| indx2 index middl ring  pinky pink2    // Keys by finger
                                       <|>
 Esc      '"    ,<    .>    pP    yY    | fF    gG    cC    rR    lL    Bksp 
 Tab+LCtl aA    oO    eE    uU    iI    | dD    hH    tT    nN    sS      -     //  ((syntax highlighting fix))
 LSht     ;:    qQ    jJ    kK    xX    | bB    mM    wW    vV    zZ    RSht
 ---------------------------------------------------------------------
 Left+LAlt   Del+-FUN -MOV  Enter+-NSY| Space  -NSY -FUN    Right+-ACC           // -XYZ are layer switches
                                     <|>
             hold     hold  hold      |        hold oneshot hold                 // Type of layer switch
 <1          <2       <3    <4        | 4>     3>   2>      1>                   // Keys by number

  
           One shot: de-activates after next key, tap twice to toggle.
        
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

  pink2  pinky ring  middl index indx2| indx2 index middl ring  pinky pink2 
                                     <|>
 -LTR   !     @     #     $     %     | ^     &     *     (     )        Bspc
 -+LCtl 1     2     3     4     5     | \|    =+    /?    [{    ]}    `~+RCtl
 .+LSht 0     9     8     7     6     | |     +     ?     {     }      ~+RSht
 --------------------------------------------------------
 Left+LAlt Del   Sht(tab) ---  | tab   ---   Ent   Right+RAlt
                              <|>
 <1        <2    <3       <4   | 4>    3>    2>    1>  

         
                
     Layer 2: Toward any layer by toggle (top row left). 
              Function keys. 
              The right side works with left held modifiers. The left side has
              F-keys with Control+Alt pressed, for switching virtual consoles.
    
  pink2 pinky ring  middl index indx2| indx2 index middl ring  pinky pink2 
 toggl toggl toggl toggl toggl toggl | toggl                         toggl      // Type of layer switch
                                    <|>
 -LTR  -NSY  -FUN  -MOV  -RAR  -REV  | -ACC  CAF11 CAF12 F12   F11   -DRA
 LCtl  CAF1  CAF2  CAF3  CAF4  CAF5  | F5    F4    F3    F2    F1    RCtl
 LSht  CAF10 CAF9  CAF8  CAF7  CAF6  | F6    F7    F8    F9    F10   RSht
 -----------------------------------------------
 LAlt  ---   ---   ---  | ---   ---   ---   RAlt
                       <|>
 <1    <2    <3    <4   | 4>    3>    2>    1>  
        

     Layer 3: Movement layer: mouse and hands on navigation
              Also delete/backspace, to navigate and delete together.

  pink2 pinky ring  middl index indx2| indx2 index middl ring  pinky pink2
                                    <|>
 -LTR  WLft  WDn   WUp   WRht  xxx   | Btn3  Home  PgUp  PgDn  End   Bksp
 LCtl  MLft  MDn   MUp   MRht  Btn1  | Btn1  Left  Up    Down  Right RCtl
 LSht  Btn5  Btn4  Btn3  Butn2 xxx   | Btn2  Acc0  Acc1  Acc2  xxx   RSht
 -------------------------------------------------------------
 Left+LAlt Del   ---   Sht(tab) | tab   ---   ---   Right+RAlt
                               <|>
 <1        <2    <3    <4       | 4>    3>    2>    1>  
        
                
    Layer 4: Place for keys that are not symbols or F-keys, and are found
             on many keyboards. Media keys on 2nd row. 

  pink2 pinky ring  middl index indx2| indx2 index middl ring  pinky pink2
                                    <|>
 -LTR  CapL  NumL  Pause ScrLk PrtSc | xxx   xxx   Power Sleep Wake   xxx   
 Tab   xxx   xxx   xxx   xxx   xxx   | xxx   xxx   xxx   xxx   xxx Insert
 xxx   Stop  Play  Prev  Next  Vol-  | Vol+  Mute  xxx   xxx   xxx    xxx
 ------------------------------------------------
 xxx    ---     ---   ---  | ---  ---   ---   App
                          <|>
 <1     <2      <3    <4   | 4>   3>    2>    1>  
        

    Layer 5: Reversing hands layer numbers and navigation, for one hand
             on keyboard use.  
    
  pink2  pinky ring  middl index indx2| indx2 index middl ring  pinky pink2
                                     <|>
 -LTR   End   PgDn  PgUp  Home  xxx   | xxx   xxx   xxx   xxx   xxx   Bspc
 -+LCtl Left  Down  Up    Right xxx   | 5     4     3     2     1     RCtl
 .+LSht xxx   xxx   xxx   xxx   xxx   | 6     7     8     9     0     RSht
 ----------------------------------------------------------
 Left+LAlt Del   Sht(Tab) ---  | Tab  ---   Ent   Right+Alt
        

   Layer 6: Accented characters. See source file comments for placement
            logic, although it should be fairly obvious ? Should most 
            western European languages.
            Uses https://en.wikipedia.org/wiki/Unicode_input 

            Note that you need the right input mode for your system
            This is set for Linux, third key on the bottom row.

  pink2 pinky ring  middl index indx2| indx2 index middl ring  pinky pink2
                                    <|>
 -LTR  áÁ    óÓ    éÉ    úÚ    íÍ    | ýÝ    xxx   çÇ    øØ    åÅ    Bspc
 LCtl  äÄ    öÖ    ëË    üÜ    ïÏ    | ÿŸ    œŒ    æÆ    ñÑ     ß    RCtl
 LSht  àÀ    òÒ    èÈ    ùÙ    ìÌ    | îÎ    ûÛ    êÊ    ôÔ    âÂ    RSht
 ---------------------------------------------------------
 LAlt+Left Del   Linux Ent  | Spc   ---   ---   RAlt+Right
                           <|>
 <1        <2    <3    <4   | 4>    3>    2>    1>  


   Layer 7: Unicode drawings and whatever else.

            Note that you need the right input mode for your system.

  pink2 pinky ring  middl index indx2| indx2 index middl ring  pinky pink2
                                    <|>
 -LTR  ¡     xxx   xxx   xxx   xxx   | xxx  🙂😃   👍    👎    ⍨🙁   Bspc
 LCtl  xxx   xxx   xxx   xxx   xxx   | xxx   xxx   ¿     xxx   xxx   RCtl
 LSht  xxx   xxx   xxx   xxx   xxx   | xxx   xxx   xxx   xxx   xxx   RSht
 ---------------------------------------------------------
 LAlt+Left Del   ---   Ent  | Spc   ---   ---   RAlt+Right
                           <|>
 <1        <2    <3    <4   | 4>    3>    2>    1>  


   ... keycap color scheme, marks areas home (5), navigation (2+5), numbers (2+5).

                            x1111112222x
                            x5555215555x
                            x2222211111x
                              xxxxxxxx

