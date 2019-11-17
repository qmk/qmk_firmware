# Dvorak on the Minivan

This is a Dvorak layout for the Minivan 40% keyboard (default 44 keys).
The accented characters would likely cover Dutch, German, French, Finnish,
Norwegian, Swedish, Italian and Spanish, besides English (Unicode input).

It also allows the same layout on a computer that is already set to Dvorak
on the computer side, by changing the default layer (see Function layer).

This keymap.c was edited from the default provided with this version of
QMK on Github, and the LED support was copied from ../jetpacktuxedo/
keymap. 
                                                By Jos B.,  joshb@xs4all.nl 


  Overview of layers
  - - - - - - - - - 

      Basic layers are: * letters (normal Dvorak layout), (Led: off)         _LTR "LeTteRs"
                        * numbers with remaining symbols, (Led: blue)        _NSY "Numbers SYmbols"
                        * function keys,                  (Led: red)         _FUN "FUNction keys"
                        * and a movement layer            (Led: green)       _MOV "MOVement"
      Extra layers: * keys like Print-Screen, CapsLock,   (Led: purple)      _RAR "RARe keys"
                    * navigation and numbers other hand,  (Led: green/blue)  _REV "REVerse hands"
                    * special characters like é.          (Led: cyan)        _ACC "ACCented"
                    * Unicode symbols and whatever else   (Led: white)       _DRA "DRAwings"
      Dvorak Descramble: * letters                        (Led: off)         _QDN "Qwerty-Dvorak Numbers"
                         * numbers                        (Led: yellow/blue) _QDL "Qwerty-Dvorak Letters"


  Usage
  =====
 
  All normal use layer switching is by thumb buttons on the base layer, all temporary.
  All layers can be set to be on persistently through the _FUN layer top row toggles.
  A few rarely used layers can only be reached by _FUN layer toggle.
  From each layer one can go back to the base layer by pressing the upper/left most button.


## To a computer already set to Dvorak remapping ...

  Tap **`_FUN`** once (7th key bottom row, to function layer), then **`!QDL`** (right/top row).
  _Layers `_QDL` and `_QDN` descramble `_LTR` and `_NYS`._
  Undo: tap **`_FUN`** once, then hit **`_!LTR`** (most left top row), or plug keyboard in/out. 
  _Base layer back to normal `_LTR`._

  This works for laptops where one may want to use the build in keyboard as Dvorak, and plug in 
  the Minivan to work in Dvorak. It results in a sort of Qwerty map which can be used as Qwerty,
  but the symbol arrangement for `\=/[]|+?{}` is probably not what a Qwerty typer would prefer.

  Layers
  ======
 
     Layer _LTR (LeTteRs, standard Dvorak)
                                            | Right hand
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>      // Keys by finger
     -*!-                                  <|>                                    // -*!- Access from all
     Esc      '"    ,<    .>    pP    yY    | fF    gG    cC    rR    lL    Bksp 
     Tab+LCtl aA    oO    eE    uU    iI    | dD    hH    tT    nN    sS      -_
     LSht     ;:    qQ    jJ    kK    xX    | bB    mM    wW    vV    zZ    RSht
     ---------------------------------------------------------------------
     Left+LAlt   Del+_DRA _MOV  Enter+_NSY| Space  _NSY _FUN    Right+_ACC            // _XYZ is to layer
                                         <|>
                 hold     hold  hold      |        hold oneshot hold                 // Layer switch type
     <1          <2       <3    <4        | 4>     3>   2>      1>                      // Keys by number

- - -

     Layer _NSY (Numbers and SYmbols, with Pok3r compatibility in mind regarding MWVZ)
    
     <pink2 <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
            -*-                          <|>                                        // -*- Access on _FUN
     _LTR   !     @     #     $     %     | ^     &     *     (     )        Bspc
     -+LCtl 1!    2@    3#    4$    5%    | \|    =+    /?    [{    ]}    `~+RCtl
     .+LSht 0)    9(    8*    7&    6^    | |     +     ?     {     }      `+RSht //limitation prevents ~
     --------------------------------------------------------
     Left+LAlt Del   Sht(tab) ___  | tab   ___   Ent   Right+RAlt
                              -*- <|>      -*-                                      // -*- Access on base
     <1        <2    <3       <4   | 4>    3>    2>    1>  

- - -
    
    
     Layer _FUN (F-keys, CAF means Control+Alt+F-key)
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
     base  toggl toggl toggl toggl toggl | toggl toggl             toggl base           // Type of switch
                 -*-                    <|>                                       // -*- Locks _Fun layer
     !LTR  _NSY  _FUN  _MOV  _RAR  _REV  | _ACC  _DRA  F12   F11   _QDN  !QDL      // ! set default layer
     LCtl  CAF1  CAF2  CAF3  CAF4  CAF5  | F5    F4    F3    F2    F1    RCtl
     LSht  CAF10 CAF9  CAF8  CAF7  CAF6  | F6    F7    F8    F9    F10   RSht
     -----------------------------------------------
     LAlt  xxx   xxx   xxx  | xxx   xxx   ___   RAlt
                           <|>            -*-                        // -*- Access on base -*- (one shot)
     <1    <2    <3    <4   | 4>    3>    2>    1>  

- - -
    
    
     Layer _MOV (MOVement, mouse movement on left hand)
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                       -*-              <|>                                                // -*- on _FUN
     _LTR  WLft  WDn   WUp   WRht  xxx   | Btn3  Home  PgUp  PgDn  End   Bksp
     LCtl  MLft  MDn   MUp   MRht  Btn1  | Btn1  Left  Up    Down  Right RCtl
     LSht  Btn5  Btn4  Btn3  Butn2 xxx   | Btn2  Acc0  Acc1  Acc2  xxx   RSht
     -------------------------------------------------------------
     Left+LAlt Del   ___   Sht(tab) | tab   xxx   xxx   Right+RAlt
                     -*-           <|>                                                     // -*- on base
     <1        <2    <3    <4       | 4>    3>    2>    1>  

- - -
    
    
     _RAR (RARely used keys) (Only through _FUN layer)
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                             -*-        <|>                                                    // on _FUN
     _LTR  CapL  NumL  Pause ScrLk PrtSc | xxx   xxx   Power Sleep Wake   xxx   
     Tab   uLNX  uBSD  uOSX  uWIN  uWNC  | xxx   xxx   xxx   xxx   xxx Insert
     xxx   Stop  Play  Prev  Next  Vol-  | Vol+  Mute  xxx   xxx   xxx    xxx
     ------------------------------------------------
     xxx    xxx     xxx   xxx  | xxx  xxx   xxx   App
                              <|>
     <1     <2      <3    <4   | 4>   3>    2>    1>  

- - -
    
    
     Layer _REV (REVerse hands) (Only through _FUN layer)
    
     <pink2 <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                    -*-  <|>                                                   // on _FUN
     _LTR   End   PgDn  PgUp  Home  xxx   | xxx   xxx   xxx   xxx   xxx   Bspc
     -+LCtl Left  Down  Up    Right xxx   | 5%    4$    3#    2@    1!    RCtl
     .+LSht xxx   xxx   xxx   xxx   xxx   | 6^    7&    8*    9(    0)    RSht
     ----------------------------------------------------------
     Left+LAlt Del   Sht(Tab) xxx  | Tab  xxx   Ent   Right+Alt
                                  <|>
     <1        <2    <3       <4   | 4>   3>    2>    1>  

- - -
    
    
     Layer _ACC (ACCented characters)
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                        <|>-*-                                                 // on _FUN
     _LTR  áÁ    óÓ    éÉ    úÚ    íÍ    | ýÝ    xxx   çÇ    øØ    åÅ    Bspc
     LCtl  äÄ    öÖ    ëË    üÜ    ïÏ    | ÿŸ    œŒ    æÆ    ñÑ     ß    RCtl
     LSht  àÀ    òÒ    èÈ    ùÙ    ìÌ    | îÎ    ûÛ    êÊ    ôÔ    âÂ    RSht
     ---------------------------------------------------------
     LAlt+Left Del   Linux Ent  | Spc   xxx   xxx   ___
                               <|>                  -*-                                        // on base
     <1        <2    <3    <4   | 4>    3>    2>    1>  

- - -
    
    
     Layer _DRA (DRAwings, whatever else)
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                        <|>      -*-                                           // on _FUN
     _LTR  ¡     xxx   xxx   xxx   xxx   | xxx   🙂😃  👍    👎     ⍨🙁   Bspc
     LCtl  xxx   xxx   xxx   xxx   xxx   | xxx   xxx   ¿     xxx   xxx   RCtl
     LSht  xxx   xxx   xxx   xxx   xxx   | xxx   xxx   xxx   xxx   xxx   RSht
     ---------------------------------------------------------
     LAlt+Left ___   xxx   Ent  | Spc   xxx   xxx   RAlt+Right
               -*-             <|>                                                             // on base
     <1        <2    <3    <4   | 4>    3>    2>    1>  

- - -
    

     Layer _QDN (Dvorak descramble mode for numbers/symbols)

     <pink2 <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                         <|>                        -*-                        // on _FUN
     _LTR   !     @     #     $     %     | ^     &     *     (     )        Bspc
     -+LCtl 1!    2@    3#    4$    5%    | \|    ]}    [{    -_    =+    `~+RCtl
     .+LSht 0)    9(    8*    7&    6^    | |     }     {     _     +      `+RSht  
     --------------------------------------------------------
     Left+LAlt Del   Sht(tab) ___  | tab   ___   Ent   Right+RAlt
                              -*- <|>      -*-                                            // on _QDN base
     <1        <2    <3       <4   | 4>    3>    2>    1>  

- - -


     Layer _QDN (Dvorak descramble mode for letters)

     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                           <|>                              -!-     // on _FUN (set base)
     Esc      qQ    wW    eE    rR    tT    | yY    uU    iI    oO    pP    Bksp  
     Tab+LCtl aA    sS    dD    fF    gG    | hH    jJ    kK    lL    ;:      '"
     LSht     zZ    xX    cC    vV    bB    | nN    mM    ,<    .>    /?    RSht
     ---------------------------------------------------------------------
     Left+LAlt   Del+_DRA _MOV  Enter+_QDN| Space  _QDN _FUN    Right+_ACC
                                         <|>
                 hold     hold  hold      |        hold oneshot hold
     <1          <2       <3    <4        | 4>     3>   2>      1>

- - -
   
  Modifiers
  =========


    - Shift/Alt/Control, Del/Esc and Alt with tap arrows, repeat on
      most layers.

      Except ... the Right Control on the base layer is taken off,
      because of tap delay. Right Alt on the base layer is taken off,
      instead it switches to an accented letters layer. It becomes a bit
      like a private subset of AltGr symbols. QMK allows one to press-hold 
      to the numerical layer for example, then press a right modifier like
      right Control, release numerical layer, and access the base layer with
      that modifier (Right-Contro-A for example); so it is still possible,
      just not needed, Left-Control-A will suffice in all to me known cases.)
 
    - Leds: breathing effect on the middle LED, other indicate layer.

    See keymap.c for more comments.
