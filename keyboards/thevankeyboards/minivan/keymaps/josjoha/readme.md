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

    See keymap.c for layout and comments.
 
     Layer _LTR
                                            | Right hand
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>   // Keys by finger
                                           <|>
     Esc      '"    ,<    .>    pP    yY    | fF    gG    cC    rR    lL    Bksp     //" ((syntax highlighting fix))
     Tab+LCtl aA    oO    eE    uU    iI    | dD    hH    tT    nN    sS      -_
     LSht     ;:    qQ    jJ    kK    xX    | bB    mM    wW    vV    zZ    RSht
     ---------------------------------------------------------------------
     Left+LAlt   Del+_FUN _MOV  Enter+_NSY| Space  _NSY _FUN    Right+_ACC           // _XYZ are layer switches
                                         <|>
                 hold     hold  hold      |        hold oneshot hold                 // Type of layer switch
     <1          <2       <3    <4        | 4>     3>   2>      1>                   // Keys by number


     Layer _NSY
    
     <pink2 <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                         <|>
     _LTR   !     @     #     $     %     | ^     &     *     (     )        Bspc
     -+LCtl 1     2     3     4     5     | \|    =+    /?    [{    ]}    `~+RCtl
     .+LSht 0     9     8     7     6     | |     +     ?     {     }      ~+RSht
     --------------------------------------------------------
     Left+LAlt Del   Sht(tab) ___  | tab   ___   Ent   Right+RAlt
                                  <|>
     <1        <2    <3       <4   | 4>    3>    2>    1>  
    
    
    
     Layer _FUN
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
     toggl toggl toggl toggl toggl toggl | toggl                         toggl      // Type of layer switch
                                        <|>
     _LTR  _NSY  _FUN  _MOV  _RAR  _REV  | _ACC  CAF11 CAF12 F12   F11   _DRA
     LCtl  CAF1  CAF2  CAF3  CAF4  CAF5  | F5    F4    F3    F2    F1    RCtl
     LSht  CAF10 CAF9  CAF8  CAF7  CAF6  | F6    F7    F8    F9    F10   RSht
     -----------------------------------------------
     LAlt  ___   ___   ___  | ___   ___   ___   RAlt
                           <|>
     <1    <2    <3    <4   | 4>    3>    2>    1>  
    
    
     Layer _MOV
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                        <|>
     _LTR  WLft  WDn   WUp   WRht  xxx   | Btn3  Home  PgUp  PgDn  End   Bksp
     LCtl  MLft  MDn   MUp   MRht  Btn1  | Btn1  Left  Up    Down  Right RCtl
     LSht  Btn5  Btn4  Btn3  Butn2 xxx   | Btn2  Acc0  Acc1  Acc2  xxx   RSht
     -------------------------------------------------------------
     Left+LAlt Del   ___   Sht(tab) | tab   ___   ___   Right+RAlt
                                   <|>
     <1        <2    <3    <4       | 4>    3>    2>    1>  
    
    
     _RAR
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                        <|>
     _LTR  CapL  NumL  Pause ScrLk PrtSc | xxx   xxx   Power Sleep Wake   xxx   
     Tab   xxx   xxx   xxx   xxx   xxx   | xxx   xxx   xxx   xxx   xxx Insert
     xxx   Stop  Play  Prev  Next  Vol-  | Vol+  Mute  xxx   xxx   xxx    xxx
     ------------------------------------------------
     xxx    ___     ___   ___  | ___  ___   ___   App
                              <|>
     <1     <2      <3    <4   | 4>   3>    2>    1>  
    
    
    
     Layer _REV
    
     <pink2 <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                         <|>
     _LTR   End   PgDn  PgUp  Home  xxx   | xxx   xxx   xxx   xxx   xxx   Bspc
     -+LCtl Left  Down  Up    Right xxx   | 5     4     3     2     1     RCtl
     .+LSht xxx   xxx   xxx   xxx   xxx   | 6     7     8     9     0     RSht
     ----------------------------------------------------------
     Left+LAlt Del   Sht(Tab) ___  | Tab  ___   Ent   Right+Alt
                                  <|>
     <1        <2    <3       <4   | 4>   3>    2>    1>  
    
    
    
     Layer _ACC
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                        <|>
     _LTR  áÁ    óÓ    éÉ    úÚ    íÍ    | ýÝ    xxx   çÇ    øØ    åÅ    Bspc
     LCtl  äÄ    öÖ    ëË    üÜ    ïÏ    | ÿŸ    œŒ    æÆ    ñÑ     ß    RCtl
     LSht  àÀ    òÒ    èÈ    ùÙ    ìÌ    | îÎ    ûÛ    êÊ    ôÔ    âÂ    RSht
     ---------------------------------------------------------
     LAlt+Left Del   Linux Ent  | Spc   ___   ___   RAlt+Right
                               <|>
     <1        <2    <3    <4   | 4>    3>    2>    1>  
    
    
    
     Layer _DRA
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                        <|>
     _LTR  ¡     xxx   xxx   xxx   xxx   | xxx  🙂😃   👍    👎    ⍨🙁   Bspc
     LCtl  xxx   xxx   xxx   xxx   xxx   | xxx   xxx   ¿     xxx   xxx   RCtl
     LSht  xxx   xxx   xxx   xxx   xxx   | xxx   xxx   xxx   xxx   xxx   RSht
     ---------------------------------------------------------
     LAlt+Left Del   ___   Ent  | Spc   ___   ___   RAlt+Right
                               <|>
     <1        <2    <3    <4   | 4>    3>    2>    1>  
    
