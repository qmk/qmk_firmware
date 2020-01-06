# Minivan

A 40% keyboard made by https://thevankeyboards.com This Dvorak keymap is for
the default 12x12x12x8 arrangement.

![Minivan layout Image](https://i.postimg.cc/BvgMMv0c/minivan-layer0-900.jpg)
![Minivan layout Image](https://i.postimg.cc/VvSgfBbD/minivan-layer1-900.jpg)
![Minivan layout Image](https://i.postimg.cc/BQKpRp3v/minivan-layer2-900.jpg)
![Minivan layout Image](https://i.postimg.cc/Y9PNsGyg/minivan-layer3b-900.jpg)
![Minivan layout Image](https://i.postimg.cc/HsXKbdV3/minivan-layer4-900.jpg)
![Minivan layout Image](https://i.postimg.cc/ZRjfw5rz/minivan-layer5-900.jpg)
![Minivan layout Image](https://i.postimg.cc/L4Z0M2BR/minivan-layer6-900.jpg)
![Minivan layout Image](https://i.postimg.cc/FHsH6W5t/minivan-layer7-900.jpg)

The accented characters would likely cover Dutch, German, French, Finnish,
Norwegian, Swedish, Italian and Spanish, besides English (Unicode input).
It has two Unicode layers, so that the dead-keys system can be de-activated.

This keymap allows the same layout on a computer that is already set to Dvorak
on the computer side, such as a laptop that you need the built-in keyboard to be
mapped to Dvorak.

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
      • number pad symbol versions      (Led: green/blue)      _PAD "numbers PAD"
      • accented characters é, ø, ß ... (Led: cyan 2x)         _ACC "ACCented"
      • Unicode symbols, etc etc.       (Led: yellow 2x)       _DRA "DRAwings"
     Descramble _Computer_ set Dvorak (activate automatic as drop-ins for above layers)
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
 
  Normal layer switching is by thumb buttons on the base layer (hold),
  and on the shifts (those are toggles). The layers can be set to be on
  persistently through the `_FUN` layer top row toggles. A few layers
  can only be reached by `_FUN` layer toggle. From each layer one can
  go back to the BASE layer by pressing the upper/left most button.

  'Descramble' mode
  -----------------

  There are several layers for that take care of typing normally on
  a computer already set to Dvorak ('descramble' mode.)  

  The keys on `_FUN` to layers that have a 'descramble' twin, switch to
  the normal layer variant in normal mode, and to the 'descramble' 
  variant when in 'descramble' mode. This includes the base layers
  `_LTR` (normal) and `_DDL` (descramble).

  Activation: go to `_FUN` layer, than touch the upper/right key 
  (Backspace on base layer). This cycles through the descramble modes.

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

  Unicode on Windos may require to install something special.

  Layers
  ======
 
     Layer _LTR (LeTteRs, standard Dvorak)
                                             | Right hand
     <pink2    <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pinky2>    // Keys by finger
     -o-                                    <|>                                    ... // -o- BASE access
     Esc       '"    ,<    .>    pP    yY    | fF    gG    cC    rR    lL         Bksp
     Tab+LCtl  aA    oO    eE    uU    iI    | dD    hH    tT    nN    sS           -_
     LSht+_PAD ;:    qQ    jJ    kK    xX    | bB    mM    wW    vV    zZ    RSht+_FUN   // _FUN _PAD tap
     -------------------------------------------------------------------
     Left+LAlt Del;_ACC _NSY  Enter+_MOV| Space  _NSY LGUI    Right;_DRA              // _XYZ is to layer
               hold     hold  hold      |        hold         hold                   // Layer switch type
     <1        <2       <3    <4        | 4>     3>   2>      1>                        // Keys by number

Remarks: The left modifiers have a slight delay in combination with an outside pointer device (mouse, stylus).
It seems this will be difficult to fix, because it is spread over two devices. To avoid the
±0.2 second delay, activate a layer where the modifiers are direct, using the layer toggle on left shift. 

The two keys with ';' (Del;`_ACC`, Right;`_DRA`) do not auto-repeat on double tap, like QMK normal layer-tap keys.
There is an uncluttered _Delete_ and _Right_ on the `_NSY` or `_MOV` layer respectively.

- - -

     Layer _NSY (Numbers and SYmbols)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
              -*-                          <|>                                  //(toggle) Access on _FUN
     BASE     !     @     #     $     %     | ^     &     *     (    )      Bspc
     Tab+LCtl 1!    2@    3#    4$    5%    | 6^    7&    8*    9(   0)  `~+RCtl
     -+LSft   [{    ]}    /?    \|    =+    | +     |     ?     {     }   `+RSft // limitation prevents ~
     -------------------------------------------------------
     Left+LAlt Del   ___   Ent  | .   ___   LGUI  Right+RAlt
                     -*-       <|>    -*-                                         //(hold) Access on _LTR
       <1      <2    <3    <4   | 4>  3>    2>    1>  

- - -
     
     Layer _FUN (F-keys, Layer access, Set BASE key direction)
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
     toggl toggl set   toggl toggl toggl | toggl toggl                   cycles   // Type of layer switch
                 -v-                    <|>                                       // -v- One-shot setting
     BASE: NUMS: FUN<  _MOV  _RAR  _PAD  | ACCE: DRAW: xxx   xxx   xxx   !Descr     //':' are dynamic ...
     LCtl  F1    F2    F3    F4    F5    | F6    F7    F8    F9    F10     RCtl     //...  ! 'descramble'
     LSft  F11   F12   F13   F14   F15   | F16   F17   F18   F19   F20   -*RSft     //... < toggle 'stay'
     -------------------------------------------------------                        //. -* toggle on BASE
     LAlt  LCtl&  LGUI  LCtl& | LSft& +LCtl&LSft LGUI   RAlt
           LSft         LAlt  | LAlt  &LAlt                                    
           +xxx         +xxx  | +xxx  +xxx
                             <|>
     <1    <2     <3    <4    | 4>    3>         2>     1>                

Remarks. Unusual keys !Descr and FUN<. !Descr cycles through the 'descramble' modes. 
Default: off. FUN< toggles an immediate return to the BASE layer after pressing an F-key, 
or staying on the `_FUN` layer. Default: return to BASE.

- - -
    
    
     Layer _MOV (MOVement, mouse movement on left hand)
    
     <pinky2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                        -*-              <|>                                           //(toggle) on _FUN
     BASE   PgDn  Up    PgUp  Home  Btn3  | xxx   WhDn  MsUp  WhU   WhLft Bksp
     LCtl   Left  Down  Right End   Btn1  | Btn1  MsLft MsDn  MsRht WhRht RCtl
     LSft*- xxx   Acc2  Acc1  Acc0  Btn2  | xxx   Btn2  Btn3  Btn4  Btn5  RSft         //(toggle) on BASE
     ---------------------------------------------------------
     LAlt Del   Ent   ___ | PgUp  PgDn  LGUI  RAlt
                      -*-<|>                                                             //(hold) on BASE
     <1   <2    <3    <4  | 4>    3>    2>    1>  

Remarks. It is fairly easy to switch from this horizontal arrow layout, to a wasd layout which also
switches left with right hand. See `ARROW_TRIANGLE` and `ARROW_LEFT` #defines at the top of keymap.c.

A memory assist is that the weaker fingers go down and that down is end, it takes power to go up;
index and middle fingers are stronger than ring and pinky fingers.

- - -
    
    
     _RAR (RARely used keys) (Only through _FUN layer)
    
     <pink2<pinky <ring <middl <indexx<indx2| indx2>index>middl>ring> pinky> pink2>
                               -*-         <|>                                         //(toggle) on _FUN
     BASE  xxx    xxx   xxx    xxx    xxx   | xxx   Play  Next  Prev  Stop   NumL
     P     Power• Wake• Sleep• Pause• ScrLk | PrtSc xxx   Vol+  Vol-  Mute   CapL     // • requires Shift
     Ü     uLNX   uBSD  uOSX   uWIN   uWNC  | xxx   xxx   xxx   xxx   Insert xxx      // Ü(nicode) tester
     ------------------------------------------------
     MLed  SLeds RGUI  xxx  | RSft(•) xxx   LGUI  App                    // Middle-led, Side-leds: on/off
                           <|>
     <1    <2    <3    <4   | 4>      3>    2>    1>  

Remarks. Ü is a Unicode tester key. uLNX for Linux Unicode input encoding, uBSD
for BSD Unix, uWIN for Windos, uWNC for another Windos encoding. The
change is retained between on/off power cycles.

MLed switches on/off the middle led, SLeds switches on/off the side leds.

The keys marked with • require Shift to be activated, as a means of preventing 
accidents. Shift is on (BASE) 'space' which also reduces accidents (combinations
which are never pressed normally). The 'P' key in front is meant as a memory
assist.

- - -
    
    
     Layer _PAD Numbers Pad (special symbol versions; regular '1' is not the same as this numpad '1', etc)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                      -*-  <|>                                         //(toggle) on _FUN
     BASE     xxx   xxx   .DEL  4LEFT 2DOWN | 8UP   6RGHT *     xxx   xxx   Bspc
     LCtl     1END  2DOWN 3PGDN 4LEFT 5     | 6RGHT 7HOME 8UP   9PGUP 0INS     -
     LSft     xxx   xxx   /     xxx   =     | +     3PGDN 1END  7HOME 9PGUP RSft
     -*-------------------------------------------------                               //(toggle) on BASE
     LAlt     Del   Tab   ENT  |  NUML  xxx   LGUI  RAlt
                              <|>

Remarks: The keys between `.DEL` and `*`, `+` and `RSft` constitute left handed
navigation clusters. The other keys are on the same locations as their normal
counter parts. Numlock is on (BASE) 'space', mirroring the special use of that
key in `_RAR` (as Shift).

- - -
    
    
     Layer _ACC (ACCented characters, see _RAR layer for input modes)
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                        <|>-*-                                         //(toggle) on _FUN
     BASE  áÁ    óÓ    éÉ    úÚ    íÍ    | ýÝ    ĳĲ    çÇ    øØ    åÅ    Bspc 
     Tab   äÄ    öÖ    ëË    üÜ    ïÏ    | ÿŸ    œŒ    æÆ    ñÑ     ß    RCtl
     LSht  àÀ    òÒ    èÈ    ùÙ    ìÌ    | îÎ    ûÛ    êÊ    ôÔ    âÂ    RSht
     ---------------------------------------------
     LAlt ___   RGUI  Ent  | Spc   xxx   LGUI  xxx
          -*-             <|>                                                            //(hold) on BASE
     <1   <2    <3    <4   | 4>    3>    2>    1>  

- - -
   
     Layer _DDA: same as _ACC, but internally coded for 'descramble' mode.
    
Remarks. This layer is seamlessly activated with 'descramble'

- - -
    
    
     Layer _DRA (DRAwings, whatever else (rendering width varies in different applications))
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                        <|>      -*-                                   //(toggle) on _FUN
     BASE  „“    ”     ¤£    ∅ ¢   ±ƒ    | ❦♥    🙂🙁  👍👎   ⁽₍    ⁾₎    Bspc
     LCtl  ¹₁    ²₂    ³₃    ⁴₄    ⁵₅    | ⁶₆    ⁷₇    ⁸₈     ⁹₉    ⁰₀    RCtl
     LSft 「─    」━   °〇   •§    …·    | ⮘⮙    ⮚⮛    ¿¡    《┄    》┅   RSft
     ---------------------------------------------
     LAlt xxx   RGUI  Ent  | Spc   xxx   LGUI  ___
                          <|>                  -*-                                       //(hold) on BASE
     <1   <2    <3    <4   | 4>    3>    2>    1>  

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
     Left+LAlt Del   ___   Ent  | .   ___   LGUI  Right+RAlt
                     -*-       <|>    -*-                                         //(hold) Access on _LTR
       <1      <2    <3    <4   | 4>  3>    2>    1>  

     _DDN input results in the same as _NSY with computer side Dvorak remapping. Only shown what changes:

              [{    ]}    /?           =+   |   +         ?     {     }                  // row 2, result

Remarks. This layer is seamlessly activated with 'descramble'

- - -


     Layer _DDL (Dvorak descramble mode for letters)
                                             | Right hand
     <pink2    <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pinky2> 
     -o-                                    <|>                                   ...  //(to) BASE access
     Esc       qQ    wW    eE    rR    tT    | yY    uU    iI    oO    pP         Bksp
     Tab+LCtl  aA    sS    dD    fF    gG    | hH    jJ    kK    lL    ;:           '"
     LSft+_MOV zZ    xX    cC    vV    bB    | nN    mM    ,<    .>    /?    RSft+_FUN   // _FUN _MOV tap
     -------------------------------------------------------------------
     Left+LAlt Del;_ACC _NSY  Enter+_MOV| Space  _NSY LGUI    Right;_DRA              // _XYZ is to layer
               hold     hold  hold      |        hold         hold                   // Layer switch type
     <1        <2       <3    <4        | 4>     3>   2>      1>                        // Keys by number


     _DDL input results in the same as _LTR with computer side Dvorak remapping. Only shown what changes:

              '"    ,<    .>    pP    yY    | fF    gG    cC    rR    lL                 // row 4, result
                    oO    eE    uU    iI    | dD    hH    tT    nN    sS   -_            // row 3, result
              ;:    qQ    jJ    kK    xX    | bB          wW    vV    zZ                 // row 2, result

     (Keys for 'aA', '\|' and 'mM' are the same in Dvorak and Qwerty.)

Remarks. This layer is seamlessly activated with 'descramble,' see `_LTR` (works the same).

- - -
   
  Modifiers
  =========


    - Shift/Alt/Control/GUI, Del/Esc and Alt with tap arrows, repeat on
      several layers, to have the same effect regardless of the order
      in which keys are pressed.

    - Exception:  the Right Control on the base layer is taken off, because
      of tap delay. QMK allows one to press-hold to the numerical layer
      for example, then press a right modifier like right Control, release
      numerical layer, and access the base layer with that modifier
      (Right-Contro-A for example); so it is still possible, just not
      needed, Left-Control-A will suffice in all to me known cases.)

    - Exception: Right Alt on the base layer is taken off, instead it switches to
      an accented letters layer. It becomes a bit like a private subset
      of AltGr symbols.

    - LGUI is the only one on the BASE layer of the two GUIs (or OS keys
      or other names for these keys). You can switch the RGUI for LGUI
      with a #define in keymap.c.


  **Device Space**
  
     (…)
     Checking file size of thevankeyboards_minivan_josjoha.hex               [WARNINGS]
     * The firmware size is approaching the maximum - 28384/28672 (98%, 288 bytes free)


  Use case
  ========

  The use case this keymap is designed for: PCs with GNU/Debian/Linux (etc),
  Linux laptop already set to Dvorak _hence 'descramble'_, being able on the move
  to operate other operating systems owned by others _hence non-Linux
  Unicode modes,_ editing in vim / websites etc. _hence no dead keys,_
  programming (shell, C (like) languages) _hence decent access to basic
  symbols,_ writing in Dutch _hence accented characters_, using a tiling
  window manager _hence a LGUI on base layer,_ AltGr or Compose seemed
  difficult to configure / use _hence accented and symbols layer,_ compatibility
  with the Pok3r keyboard _hence the (non)shift symbols on row 2 left side,_
  for use with 3D editing _hence a delete on base layer, Control, Alt, Shift on 
  left edge and quick toggle access to `_PAD,` on left shift._ 

  It seems this keymap should be fine for most usual purposes.
  Some of the more recent key additions like an e-mail button is not on
  it.

  BUGS
  ====

  (Unknown at time of this writing.) Only tested on Linux (FIXME).

  You can let me know if you find any bugs / problems, or if you like using
  it too 👍.
