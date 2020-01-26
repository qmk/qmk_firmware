# Minivan

A 40% keyboard made by https://thevankeyboards.com This Qwerty+Dvorak
keymap is for the default 12x12x12x8 arrangement (44 keys).

Compiled for: Qwerty + Dvorak 
=============================

This file details the compile version `#define QWERTY_DVORAK` which has a
Qwerty layout on the default (on startup), which can be switched to Dvorak.

To switch to Dvorak: go to the `_FUN` layer, and hit the upper/right key,
then return to BASE with upper/left key. To return to Qwerty, do the same.
Notice LED colors indicating layer.

This Qwerty + Dvorak compile version is a fair amount smaller than the
Dvorak² version (85% versus 99% of flash memory).

Qwerty+Dvorak keymaps
---------------------

──────────Qwerty───────────────
![Minivan layout Image 0](http://socialism.nl/misc/minivan_layer0_qwerty.jpg)
![Minivan layout Image 1](http://socialism.nl/misc/minivan_layer1_qwerty.jpg)
──────────Dvorak───────────────
![Minivan layout Image 0](http://socialism.nl/misc/minivan_layer0.jpg)
![Minivan layout Image 1](http://socialism.nl/misc/minivan_layer1.jpg)
──────────in common────────────
![Minivan layout Image 2](http://socialism.nl/misc/minivan_layer2_qwerty.jpg)
![Minivan layout Image 3b](http://socialism.nl/misc/minivan_layer3b.jpg)
![Minivan layout Image 4](http://socialism.nl/misc/minivan_layer4.jpg)
![Minivan layout Image 5](http://socialism.nl/misc/minivan_layer5.jpg)
![Minivan layout Image 6](http://socialism.nl/misc/minivan_layer6.jpg)
![Minivan layout Image 7](http://socialism.nl/misc/minivan_layer7.jpg)

With the right/upper key in layer `_FUN` you can switch between layers 
for Qwerty or Dvorak being active. This only affects the layers containting
letters and numbers/symbols.

  Layers (text)
  =============
                    ───────────────Qwerty─────────────────

     Layer _LTR (LeTteRs). This is standard Qwerty (#define QWERTY_DVORAK set.)
                                             | Right hand
     <pink2    <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pinky2>    // Keys by finger
     -o-                                    <|>                                    ... // -o- BASE access
     Esc       qQ    wW    eE    rR    tT    | yY    uU    iI    oO    pP         Bksp
     Tab+LCtl  aA    sS    dD    fF    gG    | hH    jJ    kK    lL    ;:           '"
     LSht+_PAD zZ    xX    cC    vV    bB    | nN    mM    ,<    .>    /?    RSht+_FUN   // _FUN _MOV tap
     -------------------------------------------------------------------
     Left+LAlt Del;_ACC _NSY  Enter+_MOV| Space  _NSY LGUI    Right;_DRA              // _XYZ is to layer
               hold     hold  hold      |        hold         hold                   // Layer switch type
     <1        <2       <3    <4        | 4>     3>   2>      1>                        // Keys by number

- - -


     Layer _NSY (Numbers and SYmbols). This fits the above Qwerty layer _LTR (#define QWERTY_DVORAK set.)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
              -*-                          <|>                                  //(toggle) Access on _FUN
     BASE     !     @     #     $     %     | ^     &     *     (    )      Bspc
     Tab+LCtl 1!    2@    3#    4$    5%    | 6^    7&    8*    9(   0)  `~+RCtl
     -+LSft   [{    ]}    -_    \|    =+    | +     |     _     {     }   `+RSft // limitation prevents ~
                          ^^                              ^  // Only differences with normal version _NSY
     -------------------------------------------------------
     Left+LAlt Del   ___   Ent  | .   ___   LGUI  Right+RAlt
                     -*-       <|>    -*-                                         //(hold) Access on _LTR
       <1      <2    <3    <4   | 4>  3>    2>    1>  


                    ───────────────Dvorak─────────────────

     Layer _DDL This is a standard Dvorak layer (#define QWERTY_DVORAK set.)
                                             | Right hand
     <pink2    <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pinky2> 
     -o-                                    <|>                                   ...  //(to) BASE access
     Esc       '"    ,<    .>    pP    yY    | fF    gG    cC    rR    lL         Bksp
     Tab+LCtl  aA    oO    eE    uU    iI    | dD    hH    tT    nN    sS           -_
     LSft+_PAD ;:    qQ    jJ    kK    xX    | bB    mM    wW    vV    zZ    RSft+_FUN   // _FUN _MOV tap
     -------------------------------------------------------------------
     Left+LAlt Del;_ACC _NSY  Enter+_MOV| Space  _NSY LGUI    Right;_DRA              // _XYZ is to layer
               hold     hold  hold      |        hold         hold                   // Layer switch type
     <1        <2       <3    <4        | 4>     3>   2>      1>                        // Keys by number

- - -

     Layer _DDN (Dvorak numbers/symbols). Fits above _DDL Dvorak (with #define QWERTY_DVORAK set.)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
              -*-                          <|>                                  //(toggle) Access on _FUN
     BASE     !     @     #     $     %     | ^     &     *     (    )      Bspc
     Tab+LCtl 1!    2@    3#    4$    5%    | 6^    7&    8*    9(   0)  `~+RCtl
     -+LSft   [{    ]}    /?    \|    =+    | +     |     ?     {     }   `+RSft // limitation prevents ~
     -------------------------------------------------------
     Left+LAlt Del   ___   Ent  | .   ___   LGUI  Right+RAlt
                     -*-       <|>    -*-                                         //(hold) Access on _LTR
       <1      <2    <3    <4   | 4>  3>    2>    1>  


                    ──────────────in common───────────────
     
     Layer _FUN (F-keys, Layer access, Set BASE key direction)
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
     toggl toggl set   toggl toggl toggl | toggl toggl                   cycles   // Type of layer switch
                 -v-                    <|>                                       // -v- One-shot setting
     BASE: NUMS: FUN<  _MOV  _RAR  _PAD  | ACCE: DRAW: xxx   xxx   xxx !Qwe/Dvo     //':' are dynamic ...
     LCtl  F1    F2    F3    F4    F5    | F6    F7    F8    F9    F10     RCtl     //... ! Qwerty/Dvorak
     LSft  F11   F12   F13   F14   F15   | F16   F17   F18   F19   F20   -*RSft     //... < toggle 'stay'
     --------------------------------------------------------                       //. -* toggle on BASE
     LAlt  LCtl&  LCtl&  LSft&  | +LCtl&LSft xxx  LGUI   RAlt
           LSft   LAlt   LAlt   | &LAlt                                    
           +xxx   +xxx   +xxx   | +xxx
                               <|>
     <1    <2     <3     <4     | 4>         3>   2>     1>                

Remarks. Unusual keys !Qwe/Dvo and FUN<. !Qwe/Dvo switches between (plain) Qwerty and Dvorak.
Default: Qwerty. FUN< toggles an immediate return to the BASE layer after pressing an F-key, 
or staying on the `_FUN` layer. Default: return to BASE.

- - -
Note: all these layers below are the same as in the 'descramble' compile version.
The only difference is that four special descramble Unicode layers are not present.
Those layers are hidden from a user perspective anyway. The two 'normal' Unicode
layers are present in Qwerty+Dvorak too (accented letters and additional symbols).
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
    
    
     Layer _DRA (DRAwings, whatever else (rendering width varies in different applications))
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                        <|>      -*-                                   //(toggle) on _FUN
     BASE  „“    ”     ¤£    ∅ ¢   ±ƒ    | ❦♥    🙂🙁  👍👎   ⁽₍    ⁾₎    Bspc
     LCtl  ¹₁    ²₂    ³₃    ⁴₄    ⁵₅    | ⁶₆    ⁷₇    ⁸₈     ⁹₉    ⁰₀    RCtl
     LSft 「─    」━   °〇   •§    …·    | ⮘⮙    ⮚⮛    ¿¡    《┄    》┅   RSft
     ---------------------------------------------
     LAlt Del   RGUI  Ent  | Spc   xxx   LGUI  ___
                          <|>                  -*-                                       //(hold) on BASE
     <1   <2    <3    <4   | 4>    3>    2>    1>  

- - -

For the the rest of the readme, see the [regular readme.md file](./readme.md),
continuing at the chapter below the layer listings: 'Why you want this layout.'
