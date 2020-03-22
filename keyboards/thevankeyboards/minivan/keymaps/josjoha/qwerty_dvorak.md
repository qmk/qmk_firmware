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
Dvorak² version.
   
Overview of layers
==================

![Minivan illustration Overview layers](http://socialism.nl/misc/minivan/minivan-flat-all-layers-visualization_qwerty_v3.jpg)

![Minivan illustration Overview layers](http://socialism.nl/misc/minivan/minivan-flat-all-layers-visualization_v3.jpg)

     Basic layers are:
      • letters (normal Qwerty layout),  Led: low-white/off⁽¹⁾ _LTR "LeTteRs"
      • numbers with remaining symbols,  Led: blue 2x)         _NSY "Numbers SYmbols"
      • function keys,                   Led: red & white ⁽²⁾  _FUN "FUNction keys"
      • and a movement layer             Led: green 2x)        _MOV "MOVement"
     Extra layers: 
      • keys like Power, Play,           Led: purple 2x)       _RAR "RARe keys"
      • number pad symbol versions       Led: green/blue ⁽³⁾   _PAD "numbers PAD"
      • accented characters é, ø, ß ...  Led: cyan 2x          _ACC "ACCented"
      • Unicode symbols, ¹, ±, ° ...     Led: yellow 2x        _DRA "DRAwings"
     Descramble _Computer_ set Dvorak (activate automatic as drop-ins for above layers)
      • Unicode symbols, etc             Led: cyan/low-white   _DDD "Descramble Drawings"
      • accented characters              Led: yellow/low-white _DDA "Descramble Accented"
      • numbers                          Led: blue/low-white   _DDL "Descramble Numbers"
      • letters                          Led: off/low-white    _DDN "Descramble Letters"


      Leds: • Breathing effect on the middle LED in color of last active non base layer.
              There is no particular reason for this (fun & games).
            • Leds left and right indicate active layer.
            • ⁽¹⁾ The led is bright when capslock is on.
            • ⁽²⁾ One led on the _FUN layer is bright white, indicating which layout
              mode (Qwerty or Dvorak) is active.
            • ⁽³⁾ The colors are reversed when numlock is on.
            • Leds can be switched on/off on the _RAR layer (MLed, SLeds).      

Qwerty+Dvorak keymaps
---------------------

──────────Qwerty───────────────

![Minivan layout Image 0](http://socialism.nl/misc/minivan/minivan_layer0_qwerty.jpg)

![Minivan layout Image 1](http://socialism.nl/misc/minivan/minivan_layer1_qwerty_v2.jpg)

──────────Dvorak───────────────

![Minivan layout Image 0](http://socialism.nl/misc/minivan/minivan_layer0_qwerty_dvorak.jpg)

![Minivan layout Image 1](http://socialism.nl/misc/minivan/minivan_layer1_qwerty_dvorak_v2.jpg)

──────────in common────────────

![Minivan layout Image 2](http://socialism.nl/misc/minivan/minivan_layer2_qwerty.jpg)

![Minivan layout Image 3b](http://socialism.nl/misc/minivan/minivan_layer3b_v2.jpg)

^ There is an alternative flat arrow configuration for this layer (see below),
and options to compile with the 'arrow' hardware layout.

![Minivan layout Image 4](http://socialism.nl/misc/minivan/minivan_layer4_v2.jpg)

![Minivan layout Image 5](http://socialism.nl/misc/minivan/minivan_layer5_v2.jpg)

![Minivan layout Image 6](http://socialism.nl/misc/minivan/minivan_layer6.jpg)

![Minivan layout Image 7](http://socialism.nl/misc/minivan/minivan_layer7_v3.jpg)

With the right/upper key in layer `_FUN` you can switch between layers 
for Qwerty or Dvorak being active. This only affects the layers containting
letters and numbers/symbols. 

The right led in Dvorak mode shows when using a layer that is different
in that mode, analogue to the `_FUN` led indicator for Dvorak.

![Minivan illustration Overview relationships](http://socialism.nl/misc/minivan/minivan-flat-all-layers-relationships_qwerty_v3.jpg)

^ Key placement between layers for Qwerty.

![Minivan illustration Overview relationships](http://socialism.nl/misc/minivan/minivan-flat-all-layers-relationships_v3.jpg)

^ Key placement between layers for Dvorak. It does not work as well for Qwerty.

![Minivan illustration Overview relationships](http://socialism.nl/misc/minivan/minivan-flat-all-layers-activation_qwerty_v3.jpg)

^ Layers are normally activated from the BASE layer (white). You can toggle them from the `_FUN` layer as well.

![Minivan illustration Overview relationships](http://socialism.nl/misc/minivan/minivan-flat-all-layers-activation_v3.jpg)

^ Layers are normally activated from the BASE layer (white). You can toggle them from the `_FUN` layer as well.

Movement layer options
----------------------

The movement layer (`_MOV`) has quite a few configuration options. You
can either have _triangle_ configuration arrows on the _left_ hand
(with navigation keys around it), or a _flat_ arrow configuration on
the _right_ hand (with navigation above it).

You can configure for the _arrow_ hardware layout (one additional hardware
key on the right). The additional key toggles to the movement layer, and
than becomes part of the arrow cluster. For both versions (_triangle_
arrows left hand or _flat_ arrows right hand) you can compile this
second arrow cluster to be completed with navigation keys (Home, End,
PageUp, PageDown).

Compile keymap.c with: 

![Minivan layout Image MOV 3 defaultf](http://socialism.nl/misc/minivan/minivan_layer3.jpg)

![Minivan layout Image MOV 3b default](http://socialism.nl/misc/minivan/minivan_layer3b_v2.jpg)

^ `#define ARROWS_TRIANGLE`

![Minivan illustration BASE towards 3](http://socialism.nl/misc/minivan/minivan_layer_illustration_0_3b_arrow_v3.jpg)

^ Illustration of accessing the arrows/navigation with a key on the BASE layer

![Minivan layout Image MOV 3b + arrow](http://socialism.nl/misc/minivan/minivan_layer3b_hardw-arrow_triangle.jpg)

^ `#define ARROWS_TRIANGLE`, `MORE_KEY__ARROW`, `MOREKEY2_ARROW_CLUSTER`, `MORE_key2 _MOV_UP`

![Minivan layout Image MOV 3b + navig](http://socialism.nl/misc/minivan/minivan_layer3b_hardw-arrow_triangle_addnav.jpg)

^ `#define ARROWS_TRIANGLE`, `MORE_KEY__ARROW`, `MOREKEY2_ARROW_CLUSTER`, `MOREKEY2_ADD_NAVIGATION`, `MORE_key2 _MOV_UP` (note change on previously BTN2/3)

![Minivan layout Image MOV 3 + arrows](http://socialism.nl/misc/minivan/minivan_layer3_hardw-arrow_flat.jpg)

^ `#define MORE_KEY__ARROW`, `MOREKEY2_ARROW_CLUSTER`, `MORE_key2 _MOV_UP`

![Minivan layout Image MOV 3 + naviga](http://socialism.nl/misc/minivan/minivan_layer3_hardw-arrow_flat_addnav.jpg)

^ `#define MORE_KEY__ARROW`, `MOREKEY2_ARROW_CLUSTER`, `MOREKEY2_ADD_NAVIGATION`, `MORE_key2 _MOV_UP` (note change on previously BTN2/3)

![Minivan layout Image MOV 3 vi arrow](http://socialism.nl/misc/minivan/minivan_layer3_vi_.jpg)

^ `#define` \[`MORE_KEY__ARROW`, `MOREKEY2_ARROW_CLUSTER`\] `VI_SWITCHERYDOO`, `#undef ARROWS_TRIANGLE`

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
     <1   ±    <2       <3    <4        | 4>     3>   2>   ±  1>                        // Keys by number

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
       <1   ±  <2    <3    <4   | 4>  3>    2>  ± 1>  


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
     <1   ±    <2       <3    <4        | 4>     3>   2>   ±  1>                        // Keys by number

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
       <1   ±  <2    <3    <4   | 4>  3>    2>  ± 1>  


                    ──────────────in common───────────────

- - -
    
     Layer _FUN (F-keys, Layer access, Set BASE key direction)
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
     toggl toggl set   toggl toggl toggl | toggl toggl                   cycles   // Type of layer switch
                 -v-                    <|>                                       // -v- One-shot setting
     BASE: NUMS: FUN<  _MOV  _RAR  _PAD  | ACCE: DRAW: xxx   xxx   xxx  !Layout     //':' are dynamic ...
     LCtl  F1    F2    F3    F4    F5    | F6    F7    F8    F9    F10     RCtl     //... ! Qwerty/Dvorak
     LSft  F11   F12   F13   F14   F15   | F16   F17   F18   F19   F20     RSft     //... < toggle 'stay'
     --------------------------------------------------------              -*-      //-*-  toggle on BASE
     LAlt  LCtl&  LCtl&  LSft&  | +LCtl&LSft xxx  LGUI   RAlt
           LSft   LAlt   LAlt   | &LAlt                                    
           +xxx   +xxx   +xxx   | +xxx
                               <|>
     <1  ± <2     <3     <4     | 4>         3>   2>  ±  1>                

Remarks. Unusual keys !Descr and FUN<. !Layout switches between Qwerty and Dvorak as BASE.
Default: off. FUN< toggles an immediate return to the BASE layer after pressing an F-key, 
or staying on the `_FUN` layer. Default: return to BASE.

- - -
    
This is the _triangle_ configuration for arrows, arrow are on left hand (WASD):

     Layer _MOV (MOVement, mouse movement on right hand)
    
     <pinky2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                        -*-              <|>                                           //(toggle) on _FUN
     BASE   PgDn  Up    PgUp  Home  Btn3  | xxx   WhDn  MsUp  WhU   WhLft Bksp
     LCtl   Left  Down  Right End   Btn1  | Btn1  MsLft MsDn  MsRht WhRht RCtl
     LSft   xxx   Acc2  Acc1  Acc0  Btn2  | Btn2  Btn3  Btn4  Btn5  xxx   RSft         //(toggle) on BASE
     ---------------------------------------------
     LAlt Del   Ent   ___ | PgUp  PgDn  LGUI  RAlt
                      -*-<|>                                                             //(hold) on BASE
     <1 ± <2    <3    <4  | 4>    3>    2>  ± 1>  


Remarks. For the Minivan _arrow_ hardware layout with arrow cluster, you get this on `BASE`:

     (…)
     LSht+_PAD ;:    qQ    jJ    kK    xX    | bB    mM    wW    vV    zZ    RSht+_FUN
     -------------------------------------------------------------------------------
     Left+LAlt Del;_ACC _NSY(_DRA) Enter+_MOV| Space  _NSY(_DRA) LGUI  _MOV  Right;_RAR 
                                                                       ^^^^           // new key (toggle)
… and this on `_MOV` for the _triangle_ configuration:

     (…)
     LSft*- xxx   Acc2  Acc1  Acc0  Btn2  | Btn2  Btn3  Btn4  Btn5  _Up_  RSft         //(toggle) on BASE
     ---------------------------------------------------------------------------
                     LAlt Del   Ent   ___ | PgUp       PgDn  _Left__Down__Right_
                                      -*-<|>                                              //(hold) on BASE
                     <1 ± <2    <3    <4  | 4>         3>     2>   _±_    1>  

… or this on `_MOV` for the _triangle_ arrow configuration with additional _navigation_ keys:

     BASE   PgDn  Up    PgUp  Home _Btn4_ | xxx   WhDn  MsUp  WhU   WhLft Bksp
     LCtl   Left  Down  Right End   Btn1  | Btn1  MsLft MsDn  MsRht WhRht RCtl
     LSft*- xxx   Acc2  Acc1  Acc0 _Btn5_ | Btn2  Btn3 _Home__PgUp_ _Up_ _PgDn_        //(toggle) on BASE
     ---------------------------------------------------------------------------
                     LAlt Del   Ent   ___ | PgUp      _End_  _Left__Down__Right_
                                      -*-<|>                                              //(hold) on BASE
                     <1 ± <2    <3    <4  | 4>         3>     2>   _±_    1>  


This is the _flat_ configuration for arrows, arrow are on right hand:

     <pinky2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                        -*-              <|>                                           //(toggle) on _FUN
     BASE   WLft  WDn   WUp   WRht  xxx   | Btn3  PgUp  Home  End   PgDn  Bksp
     LCtl   MLft  MDn   MUp   MRht  Btn1  | Btn1  Left  Up    Down  Right RCtl
     LSft*- Btn5  Btn4  Btn3  Butn2 xxx   | Btn2  Acc0  Acc1  Acc2  xxx   RSft         //(toggle) on BASE
     ---------------------------------------------
     LAlt Del   Ent   ___ | PgUp  PgDn  LGUI  RAlt
                      -*-<|>                                                             //(hold) on BASE
     <1 ± <2    <3    <4  | 4>    3>    2>  ± 1>  

For the Minivan _arrow_ hardware layout with _flat_ arrow cluster, you get this on `_MOV`:

     (…)
     LSft*- Btn5  Btn4  Btn3  Butn2 xxx   | Btn2  Acc0  Acc1  Acc2  xxx   RSft         //(toggle) on BASE
     ---------------------------------------------------------------------------
                     LAlt Del   Ent   ___ | PgUp      _Left_ _UP_  _Down__Right_
                                      -*-<|>                                           //(hold) on BASE
                     <1 ± <2    <3    <4  | 4>         3>     2>   _±_    1>  

… or this on `_MOV` for the _flat_ arrow configuration with additional _navigation_ keys:

     BASE   WLft  WDn   WUp   WRht  xxx   |_Acc2_ PgUp  Home  End   PgDn  Bksp
     LCtl   MLft  MDn   MUp   MRht  Btn1  | Btn1  Left  Up    Down  Right RCtl
     LSft*- Btn5  Btn4  Btn3  Butn2 xxx   |_Acc1_ Acc0 _PgUp__Home__End_ _PgDn_        //(toggle) on BASE
     ---------------------------------------------------------------------------
                     LAlt Del   Ent   ___ | PgUp      _Left_ _UP_  _Down__Right_
                                      -*-<|>                                           //(hold) on BASE
                     <1 ± <2    <3    <4  | 4>         3>     2>   _±_    1>  

… or this on `_MOV` for the _flat_ arrow configuration, […], and vi(1) layout:

     <pinky2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                        -*-              <|>                                           //(toggle) on _FUN
     BASE   WLft  WDn   WUp   WRht  xxx   |_Acc2_ PgUp  Home  End   PgDn  Bksp
     LCtl   MLft  MDn   MUp   MRht  Btn1  | Left  Down  Up    Right Btn1  RCtl         // vi as in Qwerty
     LSft*- Btn5  Btn4  Btn3  Butn2 xxx   |_Acc1_ Acc0 _PgUp__Home__End_ _PgDn_        //(toggle) on BASE
     ---------------------------------------------------------------------------
                     LAlt Del   Ent   ___ | PgUp      _Left_ _Down__Up_  _Right_       // vi as in Qwerty
                                      -*-<|>                                           //(hold) on BASE
                     <1 ± <2    <3    <4  | 4>         3>     2>   _±_    1>  

The #defines for these various compile variations are at the top of keymap.c.
For the 'arrow' hardware layout (additional key on the right), keys on the first
row are sacrificed and lost. The right most key on the second row is also lost.
The two keys on places 3 and 4 when counting from the right on the second row,
are being moved to the spots for Btn2 and Btn3 on the hand that also has the 
arrows (those keys are otherwise twice defined for left and right hand).
- - -
    
    
     _RAR (RARely used keys) (Only through _FUN layer)
    
     <pink2<pinky <ring <middl <indexx<indx2| indx2>index>middl>ring> pinky> pink2>
                               -*-         <|>                                         //(toggle) on _FUN
     BASE  xxx    xxx   xxx    xxx    xxx   | xxx   Play  Next  Prev  Stop   NumL
     P     Power• Wake• Sleep• Pause• ScrLk | PrtSc xxx   Vol+  Vol-  Mute   CapL     // • requires Shift
     Ü     uLNX   uBSD  uOSX   uWIN   uWNC  | xxx   xxx   xxx   xxx   Insert  APP     // Ü(nicode) tester
     ------------------------------------------------
     MLed  SLeds RGUI  xxx  | RSft(•) xxx   LGUI  ___                    // Middle-led, Side-leds: on/off
                           <|>
     <1  ± <2    <3    <4   | 4>      3>    2>  ± 1>  

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
     -*-------------------------------------------------                            //-*-  toggle on BASE
     LAlt     Del   Tab   ENT  |  NUML  xxx   LGUI  RAlt
                              <|>
     <1   ±   <2    <3    <4   | 4>     3>    2>  ± 1>  

Remarks: The keys between `.DEL` and `*`, `+` and `RSft` constitute sort of
navigation clusters.

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
     <1 ± <2    <3    <4   | 4>    3>    2>  ± 1>  

- - -
    
    
     Layer _DRA (DRAwings, whatever else (rendering width might vary in different applications))

     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                        <|>      -*-                                   //(toggle) on _FUN
     BASE  „“    ”🛠   ¤£    ∅ ¢   ±ƒ    | ❦♥    🙂🙁  👍👎   ⁽₍    ⁾₎    Bspc
     LCtl  ¹₁    ²₂    ³₃    ⁴₄    ⁵₅    | ⁶₆    ⁷₇    ⁸₈     ⁹₉    ⁰₀    RCtl
     LSft 「─    」━   °〇   •§    …·    | ☐ ☒   ☑ 🗹   ¿¡    《┄    》┅   RSft         // ☐☒☑🗹 or ⮘⮙⮚⮛
     ----------------------------------------------
     LAlt Del   ___   Ent  | Spc   ___   LGUI  RGUI
                -*-       <|>      -*-                                                   //(hold) on BASE
     <1 ± <2    <3    <4   | 4>    3>    2>  ± 1>  

- - -
   
![Minivan illustration layer subsets](http://socialism.nl/misc/minivan/minivan-layer-subsets_qwerty-dvorak.jpg)

^ This is how the layers are activated, depending on mode.

- - -

For the the rest of the readme, see the [regular readme.md file](./readme.md),
at chapter _Why you want this layout._

