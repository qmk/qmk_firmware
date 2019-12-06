# Dvorak² no-dead-keys

This is a Dvorak layout for the Minivan 40% keyboard (default 44 keys; 12,12,12,8).
The accented characters would likely cover Dutch, German, French, Finnish,
Norwegian, Swedish, Italian and Spanish, besides English (Unicode input).
It has two Unicode layers, so that the dead-keys system can be de-activated.

This keymap allows the same layout on a computer that is already set to Dvorak
on the computer side, such as a laptop that you need the built-in keyboard to be
mapped to Dvorak. (Only tested on Linux, should work on other systems.)

This keymap.c was edited from the default, LED support was copied/edited
from ../jetpacktuxedo/ keymap. 
                                                By Jos B.,  joshb@xs4all.nl 

   


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
            • ⁽¹⁾ One led on the _FUN layer is bright white, indicating which descramble
              mode is active (see below).
            • Leds can be switched on/off on the _RAR layer (MLed, SLeds).      


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

  Activation: go to `_FUN` layer, touch the upper/right key (Backspace 
  on base layer). This cycles through the descramble modes.

  ⮚ When the left led is white: normal mode.
  ⮚ Right led white: full descramble mode (Linux descrambled Unicode input).
  ⮚ Middle led white: half descramble mode, with normal Unicode input system.

  With the middle led set to white, you can take advantage of a Unicode
  input mode that works on your system, if it is the same when the
  computer is set to Dvorak or not (see `_RAR` layer for Unicode input
  encoding selection). This more or less means there is one more Unicode
  encoding option than already standard in QMK: 'descrambled' version of 
  Linux (Shift-Control-U HEX) encoding.

  To test it, (in Debian/Linux) go to a terminal in X and type (normal user)

        > setxkbmap -layout us -variant dvorak

  Undo:

        > setxkbmap -layout us


  Layers
  ======
 
     Layer _LTR (LeTteRs, standard Dvorak)
                                            | Right hand
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>      // Keys by finger
     -o-                                   <|>                              ...        // -o- BASE access
     Esc      '"    ,<    .>    pP    yY    | fF    gG    cC    rR    lL    Bksp 
     Tab+LCtl aA    oO    eE    uU    iI    | dD    hH    tT    nN    sS      -_
     LSht     ;:    qQ    jJ    kK    xX    | bB    mM    wW    vV    zZ    RSht
     -------------------------------------------------------------------
     Left+LAlt Del;_ACC _NSY  Enter+_MOV| Space _NSY _FUN     Right;_DRA              // _XYZ is to layer
               hold     hold  hold      |        hold mixed   hold                   // Layer switch type
     <1        <2       <3    <4        | 4>     3>   2>      1>                        // Keys by number

Remarks: The 'Tab' on Left-Control causes a slight delay for using Control in combination with a mouse.
It seems this will be difficult to fix, because it is spread over two devices. To avoid the
±0.2 second delay, activate a layer where Left-Control is direct, such as `_FUN`.

The two keys with ';' (Del;`_ACC`, Right;`_DRA`) do not auto-repeat on double tap, like QMK normal layer-tap keys.
There is an uncluttered _Delete_ and _Right_ on the `_NSY` layer.

- - -

     Layer _NSY (Numbers and SYmbols)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
              -*-                          <|>                                  //(toggle) Access on _FUN
     BASE     !     @     #     $     %     | ^     &     *     (    )      Bspc
     Tab+LCtl 1!    2@    3#    4$    5%    | 6^    7&    8*    9(   0)  `~+RCtl
     -+LSft   [{    ]}    /?    \|    =+    | +     |     ?     {     }   `+RSft // limitation prevents ~
     -------------------------------------------------------
     Left+LAlt Del   ___   Ent  | .   ___   ,     Right+RAlt
                     -*-       <|>    -*-                                         //(hold) Access on _LTR
       <1      <2    <3    <4   | 4>  3>    2>    1>  

Remarks. There is a bit of numbers entry here with -,.Tab, also see `_REV` for that.

- - -
    
     Layer _FUN (F-keys, Layer access, Set BASE key direction)
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
     toggl toggl set   toggl toggl toggl | toggl toggl                   cycles   // Type of layer switch
                 -v-                    <|>                                       // -v- One-shot setting
     BASE: NUMS: FUN<  _MOV  _RAR  _REV  | ACCE: DRAW: xxx   xxx   xxx   !Descr     //':' are dynamic ...
     LCtl  F1    F2    F3    F4    F5    | F6    F7    F8    F9    F10     RCtl     //... ! 'descramble'
     LSft  F11   F12   F13   F14   F15   | F16   F17   F18   F19   F20     RSft     //... < toggle 'stay'
     ----------------------------------------------------------
     LAlt  LCtl&   LCtl&   LSft& | +LCtl&LSft xxx   BASE   RAlt
           LSft    LAlt    LAlt  | &LAlt                                     
           +xxx    +xxx    +xxx  | +xxx
                                <|>                 -*-                         //(toggle) Acces -*- base
     <1    <2      <3      <4    | 4>         3>    2>     1>                

Remarks. Unusual keys !Descr and FUN<. !Descr cycles through the 'descramble' modes. 
Default: off. FUN< toggles an immediate return to the BASE layer after pressing an F-key, 
or staying on the `_FUN` layer. Default: return to BASE.

- - -
    
    
     Layer _MOV (MOVement, mouse movement on left hand)
    
     <pinky2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                           -*-              <|>                                        //(toggle) on _FUN
     BASE      WLft  WDn   WUp   WRht  xxx   | Btn3  PgUp  Home  End   PgDn  Bksp
     Tab+LCtl  MLft  MDn   MUp   MRht  Btn1  | Btn1  Left  Up    Down  Right RCtl
     LSft      Btn5  Btn4  Btn3  Butn2 xxx   | Btn2  Acc0  Acc1  Acc2  xxx   RSft
     --------------------------------------------------------
     Left+LAlt Del   Ent   ___ | PgUp  PgDn  BASE  Right+RAlt
                           -*-<|>                                                        //(hold) on BASE
     <1        <2    <3    <4  | 4>    3>    2>    1>  

Remarks. It is fairly easy to switch from this vim-like layout, to a wasd layout, and/or
to switch left with right hand. See `ARROW_TRIANGLE` and `ARROW_LEFT` #defines at the top of keymap.c.

- - -
    
    
     _RAR (RARely used keys) (Only through _FUN layer)
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                             -*-        <|>                                            //(toggle) on _FUN
     BASE  xxx   xxx   xxx   xxx   xxx   | xxx   Play  Next  Prev  Stop  NumL
     P     Power Wake  Sleep Pause ScrLk | PrtSc xxx   Vol+  Vol-  Mute  CapL        // P(ower) indicator
     Ü     uLNX  uBSD  uOSX  uWIN  uWNC  | xxx   xxx   xxx   xxx   xxx Insert         // Ü(nicode) tester
     ----------------------------------------------
     MLed  SLeds xxx   xxx  | xxx   xxx   BASE  App                      // Middle-led, Side-leds: on/off
                           <|>
     <1    <2    <3    <4   | 4>    3>    2>    1>  

Remarks. Ü is a Unicode tester key. uLNX for Linux Unicode input encoding, uBSD
for BSD Unix, uWIN for Windos, uWNC for another Windos encoding. The
change is retained between on/off power cycles.

MLed switches on/off the middle led, SLeds switches on/off the side leds.

- - -
    
    
     Layer _REV (REVerse hands) (Only through _FUN layer)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                      -*-  <|>                                         //(toggle) on _FUN
     BASE     PgDn  End   Home  PgUp  xxx   | xxx   xxx   xxx   xxx   xxx   Bspc
     Tab+LCtl Left  Down  Up    Right xxx   | 6^    7&    8*    9(    0)    RCtl
     -+LSft   xxx   xxx   xxx   xxx   xxx   | 5%    4$    3#    2@    1!    RSft
     -----------------------------------------------------------
     Left+LAlt Del   PgDn     PgUp | .    xxx   ,     Right+RAlt
                                  <|>
     <1        <2    <3       <4   | 4>   3>    2>    1>  

Remarks. This layer does not follow the navigation configuration #define settings 
used for the `_MOV` layer (it seemed to become convoluted and overkill to add it).

- - -
    
    
     Layer _ACC (ACCented characters, see _RAR layer for input modes)
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                        <|>-*-                                         //(toggle) on _FUN
     BASE  áÁ    óÓ    éÉ    úÚ    íÍ    | ýÝ    ĳĲ    çÇ    øØ    åÅ    Bspc 
     LCtl  äÄ    öÖ    ëË    üÜ    ïÏ    | ÿŸ    œŒ    æÆ    ñÑ     ß    RCtl
     LSht  àÀ    òÒ    èÈ    ùÙ    ìÌ    | îÎ    ûÛ    êÊ    ôÔ    âÂ    RSht
     --------------------------------------------------
     LAlt+Left ___   LGUI  Ent  | Spc   RGUI  BASE  ___
               -*-             <|>                                                       //(hold) on BASE
     <1        <2    <3    <4   | 4>    3>    2>    1>  

- - -
   
     Layer _DDA: same as _ACC, but internally coded for 'descramble' mode.
    
Remarks. This layer is seamlessly activated with 'descramble'

- - -
    
    
     Layer _DRA (DRAwings, whatever else (rendering width varies in different applications))
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                        <|>      -*-                                   //(toggle) on _FUN
     BASE  „“    ⁽₍    ⁾₎    ”     ❦♥    | ±ƒ    🙂😃  👍     👎    ⍨🙁   Bspc
     LCtl  ¹₁    ²₂    ³₃    ⁴₄    ⁵₅    | ⁶₆    ⁷₇    ⁸₈     ⁹₉    ⁰₀    RCtl
     LSft 「     」    °〇   •§    …·    | ⮘⮙    ⮚⮛    ¿¡    《     》    RSft
     ---------------------------------------------------------
     LAlt+Left xxx   xxx   Ent  | Spc   xxx   BASE  ___
                               <|>                  -*-                                  //(hold) on BASE
     <1        <2    <3    <4   | 4>    3>    2>    1>  

- - -
   
     Layer _DDD: same as _DRA, but internally coded for 'descramble' mode.

Remarks. This layer is seamlessly activated with 'descramble'
    
- - -
    
     Layer _DDN (Dvorak descramble mode for numbers/symbols)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
              -*-                          <|>                                  //(toggle) Access on _FUN
     BASE     !     @     #     $     %     | ^     &     *     (    )      Bspc
     Tab+LCtl 1!    2@    3#    4$    5%    | 6^    7&    8*    9(   0)  `~+RCtl
     -+LSht   -_    =+    [{    \|    ]}    | }     |     {     _     +   `+RSht            // row 2, raw
     -------------------------------------------------------
     Left+LAlt Del   ___   Ent  | .   ___   ,     Right+RAlt
                     -*-       <|>    -*-                                         //(hold) Access on _LTR
       <1      <2    <3    <4   | 4>  3>    2>    1>  

     _DDN input results in the same as _NSY with computer side Dvorak remapping. Only shown what changes:

              [{    ]}    /?           =+   |   +         ?     {     }                  // row 2, result

Remarks. This layer is seamlessly activated with 'descramble'

- - -


     Layer _DDL (Dvorak descramble mode for letters)

                                            | Right hand
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2> 
     -o-                                   <|>                              ...        //(to) BASE access
     Esc      qQ    wW    eE    rR    tT    | yY    uU    iI    oO    pP    Bksp
     Tab+LCtl aA    sS    dD    fF    gG    | hH    jJ    kK    lL    ;:      '"
     LSft     zZ    xX    cC    vV    bB    | nN    mM    ,<    .>    /?    RSft
     ------------------------------------------------------------------
     Left+LAlt Del;_DDA _DDN  Enter+_MOV| Space _DDN _FUN    Right;_DDD        // _XYZ are layer switches
               or:;_ACC                <|>                   or:;_DRA        // When in 'half descramble'
               hold     hold  hold      |       hold toggl   hold                 // Type of layer switch
     <1        <2       <3    <4        | 4>    3>   2>      1>                         // Keys by number



     _DDL input results in the same as _LTR with computer side Dvorak remapping. Only shown what changes:

              '"    ,<    .>    pP    yY    | fF    gG    cC    rR    lL                 // row 4, result
                    oO    eE    uU    iI    | dD    hH    tT    nN    sS   -_            // row 3, result
              ;:    qQ    jJ    kK    xX    | bB          wW    vV    zZ                 // row 2, result

     (Keys for 'aA', '\|' and 'mM' are the same in Dvorak and Qwerty.)

Remarks. This layer is seamlessly activated with 'descramble,' see `_LTR` (works the same).

- - -
   
  Modifiers
  =========


    - Shift/Alt/Control, Del/Esc and Alt with tap arrows, repeat on
      most layers.

    - Exception:  the Right Control on the base layer is taken off, because
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

  (Since I know this map already … how to go about some changes quickly…)

  For basic adaptation of this map to get the right characters for you,
  you could have a look at layers `_RAR`, `_ACC`, and `_DRA`, and 
  then see what layers to set for the 2nd, 3rd or 6th, 8th key on the
  bottom row.


  **Dual language or layout**

  The 'descramble' letters layer is basically a Qwerty layout, but it is
  not the best for that. With some minor tweaks it would be better, 
  sacrificing the ability to type on a computer already set to Dvorak.
  Another fun use of the second layout is a completely different language
  like Arabic or Chinese; or the other way around so that the default
  is the other language.


  **Device Space**
  
  Not much can be added without removing things.

     (…)
     Checking file size of thevankeyboards_minivan_josjoha.hex               [WARNINGS]
     * The firmware size is approaching the maximum - 27938/28672 (97%, 734 bytes free)


  **Other formfactor keyboards**

  To use this layout on a keyboard with more keys on the bottom row
  (like the Planck) it seems you would need to add some keys to the
  first row in each of the 12 layers. An interesting use of more keys
  could be: assign a key to each of the layer-tap key thus avoiding
  the slight hold delay with a mouse; add layer-hold keys to `_RAR` and
  `_REV`; more navigation on the base layer; some accented or Unicode
  that you use the most, etc.

  Keyboards with fewer keys: the `_REV` layer would be the first
  to repurpose I guess. One of the `_NSY` layer hold keys to it,
  to accomodate the lost characters, or use another layer hold key.

  Personal remarks
  ================

  It seems to be an intuitive and effective map. What can be the same
  on layers is the same, like Control or Backspace (not always true
  though). It is so much better for using vim to not deal with dead-keys
  issues (how do you press _Control-^_ or access a _register_ or _mark_
  with dead-keys getting in the way ?).

  Since the accented characters are logically arranged, they are easy to
  find. It is fun to have the expanded character set on `_DRA`, to be able
  to do super-² and subscript₍₂₎, 「unusual brace styles」, and for typing the
  all important 〇… It is nice to be able to plug and play on any computer,
  including a laptop set to Dvorak already.

  Feel free to let me know if you like it, and _not_ let me know if you _don't_
  like it ;-P.

  Thanks to the awesomeness of **QMK and the Minivan**.  👍🙂 

  JB
