# Dvorak on the Minivan

This is a Dvorak layout for the Minivan 40% keyboard (default 44 keys; 12,12,12,8).
The accented characters would likely cover Dutch, German, French, Finnish,
Norwegian, Swedish, Italian and Spanish, besides English (Unicode input).
If that in Unicode is enough, you can deactivate the dead-keys system.

This map allows the same layout on a computer that is already set to Dvorak
on the computer side. It helps with a laptop for example that you need to have _computer side_
Dvorak on for its build-in keyboard. (Only tested on Linux, may work on other systems.)

This keymap.c was edited from the default, LED support was copied/edited
from ../jetpacktuxedo/ keymap. 
                                                By Jos B.,  joshb@xs4all.nl 

Work in progress ... 
   Todo: 
   - Descramble with normal Unicode layers not finished:
      ... need to make costum LT switch for `_DDL` layer. 
   - Work on FUN layer key in BASE layer to act as one-shot for F-keys.
   - Shift is also a sort of layer key (esp. in this layout), may represent it in leds
   


  Overview of layers
  - - - - - - - - - 

     Basic layers are:
      • letters (normal Dvorak layout), (Led: low-white/off)   _LTR "LeTteRs"
      • numbers with remaining symbols, (Led: blue 2x)         _NSY "Numbers SYmbols"
      • function keys,                  (Led: red & white ⁽¹⁾) _FUN "FUNction keys"
      • and a movement layer            (Led: green 2x)        _MOV "MOVement"
     Extra layers: 
      • keys like Power, Play,          (Led: purple 2x)       _RAR "RARe keys"
      • navigation, numbers other hand, (Led: green/blue)      _REV "REVerse hands"
      • accented characters é, ø, ß ... (Led: cyan 2x)         _ACC "ACCented"
      • Unicode symbols, etc etc.       (Led: yellow 2x)       _DRA "DRAwings"
     Descramble _Computer_ set Dvorak: 
      • Unicode symbols, etc            (Led: cyan/low-white)  _DDD "Descramble Drawings"
      • accented characters             (Led: yellow/low-white)_DDA "Descramble Accented"
      • numbers                         (Led: blue/low-white)  _DDL "Descramble Numbers"
      • letters                         (Led: off/low-white)   _DDN "Descramble Letters"


      Leds: • Breathing effect on the middle LED in color of last active non base layer.
              There is no particular reason for this (fun & games).
            • Leds left and right indicate active layer.
            • ⁽¹⁾ One led on the _FUN layer is bright white, indicating which descamble
              mode is active (see below).


  Usage
  =====
 
  All normal use layer switching is by thumb buttons on the base layer,
  mostly temporary. The layers can be set to be on persistently through
  the `_FUN` layer top row toggles. A few rarely used layers can only
  be reached by `_FUN` layer toggle. From each layer one can go back
  to the BASE layer by pressing the upper/left most button.

  'Descramble' mode
  -----------------

  There are several layers for that take care of typing normally on
  a computer already set to Dvorak ('descramble' mode.)  

  The keys on `_FUN` to layers that have a 'descramble' twin, switch to
  the normal layer variant in normal mode, and to the 'descramble' 
  variant when in 'descramble' mode. The same is the case for the base
  layers `_LTR` (normal) and `_DDL` (descramble).

  Activation: go to `_FUN` layer, touch the key to the left of how you
  got to that layer. This cycles through the descramble modes.

  ⮚ When the left led is white: normal mode.
  ⮚ Right led white: full descramble mode (Linux Unicode input).
  ⮚ Middle led white: half descramble mode, with normal Unicode input system.
  ⮚ Middle led white: half descramble mode, with normal Unicode input system.
**FIXME: half-descramble is not finished.**

  With the middle led set to white, you can take advantage of a Unicode
  input mode that works on your system, if it is the same when the
  computer is set to Dvorak or not (see `_RAR` layer for Unicode input
  mode selection).

  To test it, (in Debian/Linux) go to a terminal in X and type (normal user)

        > setxkbmap -layout us -variant dvorak

  Undo:

        > setxkbmap -layout us

  This only seems to affect that terminal. 

  Layers
  ======
 
     Layer _LTR (LeTteRs, standard Dvorak)
                                            | Right hand
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>      // Keys by finger
     -o-                                   <|>                                         // -o- BASE access
     Esc      '"    ,<    .>    pP    yY    | fF    gG    cC    rR    lL    Bksp 
     Tab+LCtl aA    oO    eE    uU    iI    | dD    hH    tT    nN    sS      -_
     LSht     ;:    qQ    jJ    kK    xX    | bB    mM    wW    vV    zZ    RSht
     -------------------------------------------------------------------
     Left+LAlt Del+_ACC _NSY  Enter+_MOV| Space _NSY _FUN    Right+_DRA               // _XYZ is to layer
                              ...      <|>                                  // Activation on _FUN as BASE
               hold     hold  hold      |        hold toggl   hold                   // Layer switch type
     <1        <2       <3    <4        | 4>     3>   2>      1>                        // Keys by number

- - -

     Layer _NSY (Numbers and SYmbols)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
              -*-                          <|>                                      // -*- Access on _FUN
     BASE     !     @     #     $     %     | ^     &     *     (    )      Bspc
     Tab+LCtl 1!    2@    3#    4$    5%    | 6^    7&    8*    9(   0)  `~+RCtl
     -+LSft   [{    ]}    /?    \|    =+    | +     |     ?     {     }   `+RSft // limitation prevents ~
     -------------------------------------------------------
     Left+LAlt Del   ___   Ent  | .   ___   ,     Right+RAlt
                     -*-       <|>    -*-                                           // -*- Access on _LTR
       <1      <2    <3    <4   | 4>  3>    2>    1>  

- - -
    
     Layer _FUN (F-keys, Layer access, Set BASE key direction)
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
     toggl toggl toggl toggl toggl toggl | toggl toggl             toggl toggl    // Type of layer switch
                 -*-                    <|>                                         // Access -*- _FUN
     BASE: NUMS: _FUN  _MOV  _RAR  _REV  | ACCE: DRAW: xxx   xxx   xxx   xxx        //':' are dynamic ...
     LCtl  F1    F2    F3    F4    F5    | F6    F7    F8    F9    F10   RCtl
     LSft  F11   F12   F13   F14   F15   | F16   F17   F18   F19   F20   RSft
     --------------------------------------------------------------------
     LAlt  LCtl&   LCtl&   LSft& | +LCtl&LSft !Descramble BASE   RAlt         // ! sets 'descramble' mode
           LSft    LAlt    LAlt  | &LAlt      (cycles)                    
           +xxx    +xxx    +xxx  | +xxx                                                    // When tapped
                                <|>                       -*-                           // Acces -*- base
     <1    <2      <3      <4    | 4>         3>          2>     1>       

- - -
    
    
     Layer _MOV (MOVement, mouse movement on left hand)
    
     <pinky2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                           -*-              <|>                                            // -*- on _FUN
     BASE      WLft  WDn   WUp   WRht  xxx   | Btn3  PgUp  Home  End   PgDn  Bksp
     Tab+LCtl  MLft  MDn   MUp   MRht  Btn1  | Btn1  Left  Up    Down  Right RCtl
     LSft      Btn5  Btn4  Btn3  Butn2 xxx   | Btn2  Acc0  Acc1  Acc2  xxx   RSft
     -------------------------------------------------------------
     Left+LAlt Del   Ent   ___ | PgUp  PgDn  xxx   Right+RAlt
                           -*-<|>                                                          // -*- on BASE
     <1        <2    <3    <4  | 4>    3>    2>    1>  

- - -
    
    
     _RAR (RARely used keys) (Only through _FUN layer)
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                             -*-        <|>                                                    // on _FUN
     BASE  P     Power Wake  Sleep xxx   | xxx   Play  Next  Prev  Stop  NumL        // P(ower) indicator
     Tab   xxx   xxx   Pause ScrLk PrtSc | xxx   xxx   Vol+  Vol-  Mute  CapL
     Ü     uLNX  uBSD  uOSX  uWIN  uWNC  | xxx   xxx   xxx   xxx   xxx Insert         // Ü(nicode) tester
     ----------------------------------------------
     xxx   xxx   xxx   xxx  | xxx   xxx   xxx   App
                           <|>
     <1    <2    <3    <4   | 4>    3>    2>    1>  

- - -
    
    
     Layer _REV (REVerse hands) (Only through _FUN layer)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                      -*-  <|>                                                 // on _FUN
     BASE     PgDn  End   Home  PgUp  xxx   | xxx   xxx   xxx   xxx   xxx   Bspc
     Tab+LCtl Left  Down  Up    Right xxx   | 6^    7&    8*    9(    0)    RCtl
     -+LSft   xxx   xxx   xxx   xxx   xxx   | 5%    4$    3#    2@    1!    RSft
     ----------------------------------------------------------
     Left+LAlt Del   PgDn     PgUp | .    xxx   ,     Right+Alt
                                  <|>
     <1        <2    <3       <4   | 4>   3>    2>    1>  

- - -
    
    
     Layer _ACC (ACCented characters, see _RAR layer for input modes)
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                        <|>-*-                                                 // on _FUN
     BASE  áÁ    óÓ    éÉ    úÚ    íÍ    | ýÝ    ĳĲ    çÇ    øØ    åÅ    Bspc 
     LCtl  äÄ    öÖ    ëË    üÜ    ïÏ    | ÿŸ    œŒ    æÆ    ñÑ     ß    RCtl
     LSht  àÀ    òÒ    èÈ    ùÙ    ìÌ    | îÎ    ûÛ    êÊ    ôÔ    âÂ    RSht
     --------------------------------------------------
     LAlt+Left ___   LGUI  Ent  | Spc   RGUI  xxx   ___
               -*-             <|>                  -*-                                        // on BASE
     <1        <2    <3    <4   | 4>    3>    2>    1>  

- - -
   
     Layer _DDA: same as _ACC, but internally coded for 'descramble' mode.
    
- - -
    
    
     Layer _DRA (DRAwings, whatever else (rendering width varies in different applications))
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                        <|>      -*-                                           // on _FUN
     BASE  „“    ⁽₍    ⁾₎    ”     ❦♥    | ƒƑ    🙂😃  👍     👎    ⍨🙁   Bspc
     LCtl  ¹₁    ²₂    ³₃    ⁴₄    ⁵₅    | ⁶₆    ⁷₇    ⁸₈     ⁹₉    ⁰₀    RCtl
     LSft 「     」    °〇   •§    ±·    | ⮘⮙    ⮚⮛    ¿¡    《     》    RSft
     ---------------------------------------------------------
     LAlt+Left xxx   xxx   Ent  | Spc   xxx   xxx   RAlt+Right
                               <|>                                              
     <1        <2    <3    <4   | 4>    3>    2>    1>  

- - -
   
     Layer _DDD: same as _DRA, but internally coded for 'descramble' mode.
    
- - -
    
     Layer _DDN (Dvorak descramble mode for numbers/symbols)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
              -*-                          <|>                                      // -*- Access on _FUN
     BASE     !     @     #     $     %     | ^     &     *     (    )      Bspc
     Tab+LCtl 1!    2@    3#    4$    5%    | 6^    7&    8*    9(   0)  `~+RCtl
     -+LSht   -_    =+    [{    \|    ]}    | }     |     {     _     +   `+RSht            // row 2, raw
     -------------------------------------------------------
     Left+LAlt Del   ___   Ent  | .   ___   ,     Right+RAlt
                     -*-       <|>    -*-                                           // -*- Access on _LTR
       <1      <2    <3    <4   | 4>  3>    2>    1>  

     _DDN input results in the same as _NSY with computer side Dvorak remapping. Only shown what changes:

              [{    ]}    /?           =+   |   +         ?     {     }                  // row 2, result

- - -


     Layer _DDL (Dvorak descramble mode for letters)

     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
     -o-                                   <|>                              -*-     // -o- BASE, -*- _FUN
     Esc      qQ    wW    eE    rR    tT    | yY    uU    iI    oO    pP    Bksp          // row 4,  raw
     Tab+LCtl aA    sS    dD    fF    gG    | hH    jJ    kK    lL    ;:      '"          // row 3,  raw
     LSht     zZ    xX    cC    vV    bB    | nN    mM    ,<    .>    /?    RSht          // row 2,  raw
     -------------------------------------------------------------------
     Left+LAlt Del+_DDA _DDN  Enter+_MOV| Space _DDN _FUN    Right+_DDD           
                                       <|>...                               // Activation on _FUN as BASE
               hold     hold  hold      |       hold toggl   hold
     <1        <2       <3    <4        | 4>    3>   2>      1>


     _DDL input results in the same as _LTR with computer side Dvorak remapping. Only shown what changes:

              '"    ,<    .>    pP    yY    | fF    gG    cC    rR    lL                // row 4, result
                    oO    eE    uU    iI    | dD    hH    tT    nN    sS                // row 3, result
              ;:    qQ    jJ    kK    xX    | bB          wW    vV    zZ                // row 2, result

     (Keys for 'aA', '\|' and 'mM' are the same in Dvorak and Qwerty.)

- - -
   
  Modifiers
  =========


    - Shift/Alt/Control, Del/Esc and Alt with tap arrows, repeat on
      most layers.

    - Except ... the Right Control on the base layer is taken off, because
      of tap delay. QMK allows one to press-hold to the numerical layer
      for example, then press a right modifier like right Control, release
      numerical layer, and access the base layer with that modifier
      (Right-Contro-A for example); so it is still possible, just not
      needed, Left-Control-A will suffice in all to me known cases.)

    - Right Alt on the base layer is taken off, instead it switches to
      an accented letters layer. It becomes a bit like a private subset
      of AltGr symbols.
  
  Hacking & slashing 
  ==================

  The 'descramble' letters layer is basically a Qwerty layout, because
  that becomes Dvorak after computer side remapping. However it is not
  the best Qwerty layout, because the symbols on the `_DDN` layer are
  not optimal for direct Qwerty use. With some minor tweaks there, you
  could use it as a good Qwerty layout for a pretty full featured dual
  layout board.

  For basic adaptation of this map to get the right characters for you,
  you could have a look at layers `_RAR`, `_ACC`, and `_DRA`, and 
  then see what layers to set for the 2nd and 8th keys on the bottom row.

  If you do and it works I could add a link to your map here if you like.
  

    See keymap.c for more comments.
