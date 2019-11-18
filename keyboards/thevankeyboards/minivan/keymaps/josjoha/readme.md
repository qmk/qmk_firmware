# Dvorak on the Minivan

This is a Dvorak layout for the Minivan 40% keyboard (default 44 keys).
The accented characters would likely cover Dutch, German, French, Finnish,
Norwegian, Swedish, Italian and Spanish, besides English (Unicode input).

It also allows the same layout on a computer that is already set to Dvorak
on the computer side.

This keymap.c was edited from the default, LED support was copied/edited
from ../jetpacktuxedo/ keymap. 
                                                By Jos B.,  joshb@xs4all.nl 


  Overview of layers
  - - - - - - - - - 

     Basic layers are:
      * letters (normal Dvorak layout), (Led: low-white/off)   _LTR "LeTteRs"
      * numbers with remaining symbols, (Led: blue 2x)         _NSY "Numbers SYmbols"
      * function keys,                  (Led: red & white *})  _FUN "FUNction keys"
      * and a movement layer            (Led: green 2x)        _MOV "MOVement"
     Extra layers: 
      * keys like Power, Play,          (Led: purple 2x)       _RAR "RARe keys"
      * navigation, numbers other hand, (Led: green/blue)      _REV "REVerse hands"
      * accented characters é, ø, ß ... (Led: cyan 2x)         _ACC "ACCented"
      * Unicode symbols, etc etc.       (Led: yellow 2x)       _DRA "DRAwings"
     Descramble _Computer_ set Dvorak: 
      * letters                         (Led: off/low-white)   _DDN "Descramble Numbers"
      * numbers                         (Led: blue/low-white)  _DDL "Descramble Letters"


      Leds: Breathing effect on the middle LED in color of last active non base layer.
      Leds left and right indicate active layer.
      *} One led on the _FUN layer is bright white, indicating which BASE layer is active.
         Left is white for _LTR BASE (normal), right is white for _DDL BASE (descramble).


  Usage
  =====
 
  All normal use layer switching is by thumb buttons on the base layer,
  all temporary, no transparent keys. All layers can be set to be on persistently through
  the \_FUN layer top row toggles. A few rarely used layers can only be reached
  by \_FUN layer toggle.  From each layer one can go back to the BASE
  layer by pressing the upper/left most button.


## To a computer already set to Dvorak remapping ...

  Tap **`_FUN`** (7th key bottom row, to function layer), then **`!DDL`** (6th key bottom row).
  _Layers `_DDL` and `_DDN` descramble `_LTR` and `_NYS`._
  Undo: tap **`_FUN`** once, then hit **`_!LTR`** (3rd key bottom row), or plug keyboard in/out. 
  _Base layer back to normal `_LTR`._
  To detect that descramble mode is (in)active, activate _FUN layer and check the leds.

  This works for computers configured to _already_ remap the input to Dvorak, such as a laptop
  that you want computer operating system side mapping to Dvorak for its build in keyboard.

  Layers
  ======
 
     Layer _LTR (LeTteRs, standard Dvorak)
                                            | Right hand
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>      // Keys by finger
     -o-                                   <|>                                         // -o- BASE access
     BASE     '"    ,<    .>    pP    yY    | fF    gG    cC    rR    lL    Bksp 
     Tab+LCtl aA    oO    eE    uU    iI    | dD    hH    tT    nN    sS      -_
     LSht     ;:    qQ    jJ    kK    xX    | bB    mM    wW    vV    zZ    RSht
     -------------------------------------------------------------------
     Left+LAlt Del+_ACC _MOV  Enter+_NSY| Space  _NSY _FUN    Right+_ACC              // _XYZ is to layer
                        ...            <|>                                  // Activation on _FUN as BASE
               hold     hold  hold      |        hold toggl   hold                   // Layer switch type
     <1        <2       <3    <4        | 4>     3>   2>      1>                        // Keys by number

- - -

     Layer _NSY (Numbers and SYmbols, with Pok3r compatibility in mind regarding MWVZ)
    
     <pink2 <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
            -*-                          <|>                                        // -*- Access on _FUN
     BASE   !     @     #     $     %     | ^     &     *     (     )        Bspc
     -+LCtl 1!    2@    3#    4$    5%    | \|    =+    /?    [{    ]}    `~+RCtl
     .+LSht 0)    9(    8*    7&    6^    | |     +     ?     {     }      `+RSht //limitation prevents ~
     ------------------------------------------------------------
     Left+LAlt Del   Sht(tab) ___  | tab   ___   Ent   Right+RAlt
                              -*- <|>      -*-                                      // -*- Access on _LTR
     <1        <2    <3       <4   | 4>    3>    2>    1>  

- - -
    
    
     Layer _FUN (F-keys, CAF means Control+Alt+F-key)
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
     toggl toggl toggl toggl toggl toggl | toggl toggl             toggltoggl           // Type of switch
                 -*-                    <|>
     BASE  _NSY  _FUN  _MOV  _RAR  _REV  | _ACC  _DRA  F12   F11   _DDN  _DDL
     LCtl  CAF1  CAF2  CAF3  CAF4  CAF5  | F5    F4    F3    F2    F1    RCtl
     LSht  CAF10 CAF9  CAF8  CAF7  CAF6  | F6    F7    F8    F9    F10   RSht
     -----------------------------------------------
     LAlt  xxx   !LTR  xxx  | xxx   !DDL  ___   RAlt                                 // ! sets BASE layer
                           <|>            -*-                                       // -*- Access on base
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
                     -*-           <|>                                                     // -*- on BASE
     <1        <2    <3    <4       | 4>    3>    2>    1>  

- - -
    
    
     _RAR (RARely used keys) (Only through _FUN layer)
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                             -*-        <|>                                                    // on _FUN
     _LTR  P     Power Wake  Sleep xxx   | xxx   Play  Next  Prev  Stop  NumL        // P(ower) indicator
     Tab   xxx   xxx   Pause ScrLk PrtSc | xxx   xxx   Vol+  Vol-  Mute  CapL
     Ü     uLNX  uBSD  uOSX  uWIN  uWNC  | xxx   xxx   xxx   xxx   xxx Insert         // Ü(nicode) tester
     ----------------------------------------------
     xxx   xxx   xxx   xxx  | xxx   xxx   xxx   App
                           <|>
     <1    <2    <3    <4   | 4>    3>    2>    1>  

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
    
    
     Layer _ACC (ACCented characters, see _RAR layer for input modes)
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                        <|>-*-                                                 // on _FUN
     _LTR  áÁ    óÓ    éÉ    úÚ    íÍ    | ýÝ    xxx   çÇ    øØ    åÅ    Bspc
     LCtl  äÄ    öÖ    ëË    üÜ    ïÏ    | ÿŸ    œŒ    æÆ    ñÑ     ß    RCtl
     LSht  àÀ    òÒ    èÈ    ùÙ    ìÌ    | îÎ    ûÛ    êÊ    ôÔ    âÂ    RSht
     --------------------------------------------------
     LAlt+Left ___   LGUI  Ent  | Spc   RGUI  xxx   ___
               -*-             <|>                  -*-                                        // on BASE
     <1        <2    <3    <4   | 4>    3>    2>    1>  

- - -
    
    
     Layer _DRA (DRAwings, whatever else)
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                        <|>      -*-                                           // on _FUN
     _LTR  ¡     xxx   xxx   xxx   xxx   | xxx   🙂😃  👍    👎     ⍨🙁   Bspc
     LCtl  xxx   xxx   xxx   xxx   xxx   | xxx   xxx   ¿     xxx   xxx   RCtl
     LSht  xxx   xxx   xxx   xxx   xxx   | xxx   xxx   xxx   xxx   xxx   RSht
     ---------------------------------------------------------
     LAlt+Left xxx   xxx   Ent  | Spc   xxx   xxx   RAlt+Right
                               <|>                                              
     <1        <2    <3    <4   | 4>    3>    2>    1>  

- - -
    

     Layer _DDN (Dvorak descramble mode for numbers/symbols)

     <pink2 <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                         <|>                        -*-                        // on _FUN
     _LTR   !     @     #     $     %     | ^     &     *     (     )        Bspc
     -+LCtl 1!    2@    3#    4$    5%    | \|    ]}    [{    -_    =+    `~+RCtl
     .+LSht 0)    9(    8*    7&    6^    | |     }     {     _     +      `+RSht  
     ------------------------------------------------------------
     Left+LAlt Del   Sht(tab) ___  | tab   ___   Ent   Right+RAlt
                              -*- <|>      -*-                                                 // on _DDL
     <1        <2    <3       <4   | 4>    3>    2>    1>  

- - -


     Layer _DDL (Dvorak descramble mode for letters)

     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
     -o-                                   <|>                              -*-     // -o- BASE, -*- _FUN
     Esc      qQ    wW    eE    rR    tT    | yY    uU    iI    oO    pP    Bksp  
     Tab+LCtl aA    sS    dD    fF    gG    | hH    jJ    kK    lL    ;:      '"
     LSht     zZ    xX    cC    vV    bB    | nN    mM    ,<    .>    /?    RSht
     -------------------------------------------------------------------
     Left+LAlt Del+_ACC _MOV  Enter+_DDN| Space  _DDN _FUN    Right+_ACC
                                       <|>       ...                        // Activation on _FUN as BASE
               hold     hold  hold      |        hold toggl   hold
     <1        <2       <3    <4        | 4>     3>   2>      1>

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

  For basic adaptation of this map to get the right characters for you, you
  could have a look at layers `_RAR`, `_ACC`, and `_DRA`, and look at what
  you want accessed easily using those layers, accessed by the 2nd and last
  layer hold keys on the bottom row. For example if one is German and wants
  media keys, one could put `_RAR` on the 2nd (to have media right), and
  `_ACC` on the 7th. If this leaves ß awkward on the right, you could move
  it to the left on that layer.

  Another interesting adaptation is to rework the keys on the `_DDL` and
  `_DDN` "descramble" layers, to for example a whole other language with 
  different letter symbols, or just a usable Qwerty. For both BASE
  layouts there are two dedicated maps (88 keys total), which could be
  extended by adding a layer like `_ACC` to one side only, and `_DRA` to
  the other, by pointing the layer hold keys on each of the BASE layers
  to only one of those.

  If you do and it works I could add a link to your map here if you like.
  

    See keymap.c for more comments.
