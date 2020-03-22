# Minivan 
A 40% keyboard made first by TheVan Keyboards
_https://thevankeyboards.com_ now taken over by TKC
_https://thekey.company_

This keymap works on Minivan hardware variants with 44, 45 and
46 keys. It can be compiled for Dvorak only, or Qwerty + Dvorak.

![Minivan layout all](http://socialism.nl/misc/minivan/minivan-all-layers-visualization_v3.jpg)

make example:

     … Download the repository, resolve software dependencies etc..
     … If you want to change compile options (or whatever else): open keymap.c (etc).
     > cd […]/qmk_firmware
     > make thevankeyboards/minivan:josjoha
     > su
     # dfu-programmer atmega32u4 erase
     # dfu-programmer atmega32u4 flash thevankeyboards_minivan_josjoha.hex
     # dfu-programmer atmega32u4 start

Usage
-----
 
  Layer switching is by thumb hold buttons on the base layer,
  and on the shifts (those are toggles). The layers can be set to be on
  persistently through the `_FUN` layer top row. If toggled, from
  each layer one can go back to the BASE layer by pressing the upper/left
  most button. Changing keyboard mode (Dvorak/Dvorak-descramble, or 
  Qwerty/Dvorak, depending on your compile option choices) is on the `_FUN`
  layer, top right button.

Compile options ...
===================

These are the compile options, defined at the top of ![keymap.c](./keymap.c)

 - Hardware key configurations: _default_ (44), _arrow_ (45), _south paw_ (45), _arrow_ + _south paw_ (46).
 - What the additional hardware keys for _arrow,_ _south paw_ should be.
 - An arrow cluster for _arrow_ hardware configuration:
 - Navigation keys around _arrow_ hardware configuration arrow cluster.
 - Layouts: Dvorak² or Qwerty+Dvorak (see below).
 - Startup in the alternate BASE layer (for example Qwerty or Dvorak).
 - Navigation cluster in a triangle (WASD), flat layout or vi(1) layout.
 - Switching the GUIs left/right.  
 - To what layer should _left shift_ toggle.
 - Compile with symbols ☐ ☒ ☑ 🗹 (checkboxes) or ⮘ ⮙ ⮚ ⮛ (pointers).
 - You can change the symbol 'ƒ' Dutch guilder into a Euro symbol €.

In addition the symbol 🛠 can be easily reconfigured in `unicode_macros.c`.
There are some tokens to help port the layout to a board with 47 or 48 keys (`J1_J2`).

![Minivan illustration 0](http://socialism.nl/misc/minivan/minivan_illustration_arrow_southpaw.jpg)

Compile option for: Dvorak² or Qwerty+Dvorak
--------------------------------------------
These keymaps can be compiled either in a Dvorak version which also allows typing
normally on a computer already set to Dvorak (Dvorak²), or in a version that can
switch between Qwerty and Dvorak. 

This readme file assumes the Dvorak with Dvorak-descramble compile version (Dvorak²).
For the layers in the Qwerty+Dvorak version, see ![qwerty dvorak.md](./qwerty_dvorak.md)

   
Overview of layers
==================

![Minivan illustration Overview layers](http://socialism.nl/misc/minivan/minivan-flat-all-layers-visualization_v3.jpg)

     Basic layers are:
      • letters (normal Dvorak layout),  Led: low-white/off⁽¹⁾ _LTR "LeTteRs"
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
            • ⁽²⁾ One led on the _FUN layer is bright white, indicating which descramble
              mode is active (see below).
            • ⁽³⁾ The colors are reversed when numlock is on.
            • Leds can be switched on/off on the _RAR layer (MLed, SLeds).      

Dvorak² keymaps
---------------
See below for other compile variants of `_MOV`.

![Minivan layout Image 0](http://socialism.nl/misc/minivan/minivan_layer0.jpg)

![Minivan layout Image 1](http://socialism.nl/misc/minivan/minivan_layer1_v2.jpg)

![Minivan layout Image 2](http://socialism.nl/misc/minivan/minivan_layer2.jpg)

![Minivan layout Image 3b](http://socialism.nl/misc/minivan/minivan_layer3b_v2.jpg)

^ There is an alternative flat arrow configuration for this layer (see below),
and options to compile with the 'arrow' hardware layout.

![Minivan layout Image 4](http://socialism.nl/misc/minivan/minivan_layer4_v2.jpg)

![Minivan layout Image 5](http://socialism.nl/misc/minivan/minivan_layer5_v2.jpg)

![Minivan layout Image 6](http://socialism.nl/misc/minivan/minivan_layer6.jpg)

![Minivan layout Image 7](http://socialism.nl/misc/minivan/minivan_layer7_v3.jpg)

^ The right led in 'descramble' mode shows when using a layer that is different
in that mode, analogue to the `_FUN` led indicator for 'descramble' (not shown
in above graphics).

![Minivan illustration Overview relationships](http://socialism.nl/misc/minivan/minivan-flat-all-layers-relationships_v3.jpg)

^ Key placement between layers for Dvorak. It does not work as well for Qwerty.

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

'Descramble' mode
=================

![Minivan descramble Dvorak](http://socialism.nl/misc/minivan/minivan_descramble.jpg)

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

Layers (text)
=============
 
     Layer _LTR (LeTteRs, standard Dvorak)

                                             | Right hand
     <pink2    <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pinky2>    // Keys by finger
     -o-                                    <|>                                    ... // -o- BASE access
     Esc       '"    ,<    .>    pP    yY    | fF    gG    cC    rR    lL         Bksp
     Tab+LCtl  aA    oO    eE    uU    iI    | dD    hH    tT    nN    sS           -_
     LSht+_PAD ;:    qQ    jJ    kK    xX    | bB    mM    wW    vV    zZ    RSht+_FUN   // _FUN _MOV tap
     -------------------------------------------------------------------------------
     Left+LAlt Del;_ACC _NSY(_DRA)  Enter+_MOV| Space  _NSY(_DRA) LGUI    Right;_RAR  // _XYZ is to layer
               hold     hold₍₂₎     hold      |        hold₍₂₎    hold    hold       // Layer switch type
                        ^---------------------+--------^                              // both hold = _DRA
     <1   ±    <2       <3    <4              | 4>     3>         2>   ±  1>            // Keys by number
          ^¹                                                           ^²           // Optional more keys
     
     ¹) 'South paw' hardware configuration (#define J1)
     ²) 'Arrow' hardware configuration (#define J4)
     ¹ ²) There are two more optional hardware keys (#define J2, J3), to make it easier to compile for
          a 12x12x12x11 or 12x12x12x12 layouts.

Remarks: The left modifiers have a slight delay in combination with an outside pointer device (mouse, stylus).
It seems this will be difficult to fix, because it is spread over two devices. To avoid the
±0.2 second delay, activate a layer where the modifiers are direct, using the layer toggle on left shift. 

The two keys with ';' (Del;`_ACC`, Right;`_RAR`) do not auto-repeat on double tap, like QMK normal layer-tap keys.
There is an uncluttered _Delete_ and _Right_ on the `_NSY` or `_MOV` layer respectively.

Holding both `_NSY` keys left and right of the "split space bar" results in layer `_DRA` (or
`_DDD` where appropriate, with the same result).

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
       <1   ±  <2    <3    <4   | 4>  3>    2>  ± 1>  

- - -
     
     Layer _FUN (F-keys, Layer access, Set BASE key direction)
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
     toggl toggl set   toggl toggl toggl | toggl toggl                   cycles   // Type of layer switch
                 -v-                    <|>                                       // -v- One-shot setting
     BASE: NUMS: FUN<  _MOV  _RAR  _PAD  | ACCE: DRAW: xxx   xxx   xxx   !Descr     //':' are dynamic ...
     LCtl  F1    F2    F3    F4    F5    | F6    F7    F8    F9    F10     RCtl     //...  ! 'descramble'
     LSft  F11   F12   F13   F14   F15   | F16   F17   F18   F19   F20     RSft     //... < toggle 'stay'
     --------------------------------------------------------              -*-      //-*-  toggle on BASE
     LAlt  LCtl&  LCtl&  LSft&  | +LCtl&LSft xxx  LGUI   RAlt
           LSft   LAlt   LAlt   | &LAlt                                    
           +xxx   +xxx   +xxx   | +xxx
                               <|>
     <1  ± <2     <3     <4     | 4>         3>   2>  ±  1>                

Remarks. Unusual keys !Descr and FUN<. !Descr cycles through the 'descramble' modes. 
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
   
     Layer _DDA: same as _ACC, but internally coded for 'descramble' mode.
    
Remarks. This layer is seamlessly activated with 'descramble'

- - -
    
    
     Layer _DRA (DRAwings, whatever else (rendering width might vary in different applications))

     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                        <|>      -*-                                   //(toggle) on _FUN
     BASE  „“    ”🛠   ¤£    ∅ ¢   ±ƒ    | ❦♥    🙂🙁  👍👎   ⁽₍    ⁾₎    Bspc
     LCtl  ¹₁    ²₂    ³₃    ⁴₄    ⁵₅    | ⁶₆    ⁷₇    ⁸₈     ⁹₉    ⁰₀    RCtl
     LSft 「─    」━   °〇   •§    …·    | ☐ ☒   ☑ 🗹   ¿¡    《┄    》┅   RSft          // ☐☒☑🗹 or ⮘⮙⮚⮛
     ----------------------------------------------
     LAlt Del   ___   Ent  | Spc   ___   LGUI  RGUI
                -*-       <|>      -*-                                                   //(hold) on BASE
     <1 ± <2    <3    <4   | 4>    3>    2>  ± 1>  

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
       <1   ±  <2    <3    <4   | 4>  3>    2>  ± 1>  

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
     LSft+_PAD zZ    xX    cC    vV    bB    | nN    mM    ,<    .>    /?    RSft+_FUN   // _FUN _MOV tap
     -------------------------------------------------------------------
     Left+LAlt Del;_ACC _NSY  Enter+_MOV| Space  _NSY LGUI    Right;_DRA              // _XYZ is to layer
               hold     hold  hold      |        hold         hold                   // Layer switch type
     <1   ±    <2       <3    <4        | 4>     3>   2>   ±  1>                        // Keys by number


     _DDL input results in the same as _LTR with computer side Dvorak remapping. Only shown what changes:

              '"    ,<    .>    pP    yY    | fF    gG    cC    rR    lL                 // row 4, result
                    oO    eE    uU    iI    | dD    hH    tT    nN    sS   -_            // row 3, result
              ;:    qQ    jJ    kK    xX    | bB          wW    vV    zZ                 // row 2, result

     (Keys for 'aA', '\|' and 'mM' are the same in Dvorak and Qwerty.)

Remarks. This layer is seamlessly activated with 'descramble,' see `_LTR` (works the same).

- - -
   
![Minivan illustration layer subsets](http://socialism.nl/misc/minivan/minivan-layer-subsets_dvorak-descramble.jpg)

^ This is how the layers are activated, depending on mode.

Why you want this layout
========================

⮚  This layout seems easy to learn and predictable. It has a lot on it.

⮚  The Dvorak/Qwerty layer (BASE) is an unaltered standard Dvorak/Qwerty
  layout, except what physically cannot fit (numbers, right pinky
  symbols).  Despite the crammed space, you have left & rigth arrow,
  GUI, Backspace, Delete and Esc.  The tap keys are typically keys that
  you do not use when in fluent typing (enter, tab, etc).

⮚  Every time you have 0-9 enumerations / numbers, they are on the same
  fingers as a standard keyboard, except on the home row (numbers,
  numpad numbers, F-keys, super- and sub-script numbers).

⮚  The symbols normally reached by shifting a number, are also still on
  the same fingers: on the third row, accessed by pressing either
  thumb NUMS key.  You can reach the entire alpha-numerical set in two
  layers. There being a NUMS key for each hand makes the NUMS layer
  comfortable to reach left/right handed.

⮚  The lowest symbols row on NUMS copies the logic that the braces are
  normally under right hand ring and pinky fingers (numbers 90), and
  therefore on this second row the parathesis and square brackets are
  also on the ring and pinky fingers.  All the unshifted symbols are on
  the left hand, and they mirror over in the shifted form to the right
  hand. This means every finger has one symbol up a row, and one down
  a row, instead of on a common layout where the right pinky finger has
  to do much of this work alone. The / next to \ is easier to recall
  (I think). Then come =+|?, which needs to be learned.

⮚  On all layers possible / needed the modifiers are in their usual spots,
  and so is backspace, Delete.

⮚  Because one often uses an F-key only once, the layer switches back
  to BASE after an F-key is used. This can be disabled/enabled with the
  appropriate key stroke on that layer. Because it is hard to touch more
  than 3 keys, there are modifier combination keys on this layer. The
  logic is that they are written left to right, starting from the top
  with Control plus Shift, then Control plus Alt, as if cascading down.

⮚  Leds indicate what layer and mode you are in. You can switch them off.

⮚  The movement layer has a bunch of layout options, and allows for mouse
  use. WASD (as in Qwerty) arrow style, or flat on the right hand, or
  flat as in vi(1). With the 'arrow' hardware layout (one more hardware
  key on the right), you can quickly reach an arrow cluster by tapping
  in the center of it from the BASE layer.

⮚  The layer with Power buttons protects you from accidental keystrokes
  on the critical keys. Media keys arrangement you may want to change
  to what you are used to. Otherwise it will have to be learned.

⮚  The number pad layer is quickly in reach on tapping left space. This
  makes it easy to get to modifdiers Control, Shift and Alt without build
  in delays (unlike on BASE layer, where they must share the space with
  other functions). There are some blocks where the number pad navigation
  comes back, which makes it easier to remember where what is, but it
  is not so obvious. This will have to be learned if one uses those keys.

⮚  The accented layer makes it possible to set the keyboard in a mode
  on the computer side without dead-keys. It makes it easy to remember
  where your accented characters are.  The upper row left for example
  has the vowels repeated, with accents going up. The letter 'å'
  is on the same finger as 'a' but other hand, 'ß' is on the spot of
  's', etc. Not all is logical however, or has vague logic (ý being
  'near y'). One will have to learn some things by heart. Some things
  are clustered, perhaps vaguely.

⮚  The last layer adds a fair amount of fun stuff to spice up your
  writing. Write H₂O, 2⁷·⁰=128, ±8 °C, §2.1, 2 ³/₈" etc. Some logic
  is fairly obvious such as ⁽⁾ on the same keys as (), and quotation
  marks on the same keys as on the BASE layer, while others have vague
  or no logic to their placement such as ° (Degrees symbol), 🙂 and
  others, which would have to be learned. You also have correct quotation
  marks for some languages. Dutch: „he said” English: “he said”.
 
⮚  With the 'descramble' mode, you never have to fear not being able to
  use your keyboard. This mode is completely seamless, everything works
  exactly the same.

⮚  You could use the Qwerty+Dvorak compile version if you somehow have
  a use for both, but not for 'descramble' (typing Dvorak on a computer
  already set to Dvorak). Keymap.c has an option to easily change
  ƒ into €.

⮚  On average every key has 9 meanings (including upper/lower case).

》》 Conclusion: most is as normal or has some logic to it to help you
  remember, a bunch is better than your normal keyboard, some things
  rarely used will have to be learned. 

  **400% the capability in 40% the size.**


Use case
--------
  The use case this keymap is designed for: PCs with GNU/Debian/Linux (etc),
  Linux laptop already set to Dvorak _hence 'descramble'_. Being able on the move
  to operate other operating systems owned by others _hence non-Linux
  Unicode modes._ Editing in vim / websites etc. _hence no dead keys,_
  programming (shell, C (like) languages) _hence decent access to basic
  symbols._ Writing in Dutch _hence accented characters_. Using a tiling
  window manager _hence a LGUI on base layer._ AltGr or Compose seemed
  difficult to configure / use _hence accented and symbols layer._ Compatibility
  with the Pok3r keyboard _hence the (non)shift symbols on row 2 left side._
  For use with 3D editing _hence a delete on base layer, Control, Alt, Shift on 
  left edge and quick toggle access to `_PAD,` on left shift for faster
  modifiers and tab key._ 

  It seems this keymap should be fine for most usual purposes.
  Some of the more recent key additions like an e-mail button is not on
  it. You can add things like that if you like obviously (some room left
  on `_RAR`.)


Trouble shooting
----------------
  When you flash your board, suddenly your Unicode doesn't work, or your
  leds seem to be broken. What seems to happen sometimes is that after
  flashing the value of a user option ends up in a diffderent state than
  you expected.

  Leds not working: try going to `_RAR` layer, and hit the key MLeds and SLeds,
  which switch Leds on/off.

  Unicode is chaos: try going to `_RAR` layer, and hit the Unicode operating
  system buttons.

Todo
----
        - Other _ACC, _DDA layers, for different languages or just more funky
          unicode.
        - Support for More common layouts like Colemak, Qwertz, Azerty, on
          the _DDL layer.
  
        These could be #defines in the configuration block for the user,
        and cut out/in the relevant code. To offer something that works
        only as an alternative to QWERTY_DVORAK (such as a QWERTY_AZERTY
        option) is fine.  Almost nobody will use the 'descramble' system
        anyway, and that is a lot of tedious work to remap. It will be
        nice if a layout follows the common version of that layout as
        closely as possible. The _LTR/_DDL and _NSY/_DDN layers have the
        same status, they should both work perfectly with everything.

        Writer of this (Jos B,) will probably not do it, but if someone likes 
        to contribute something, that should work.


BUGS
----
  The tilde ~ on the numbers/symbols layer should logically be reached on the second
  row without the need for _shift,_ however there seems to be a QMK limitation
  with this. No work around has been attempted as of yet. (It seems to be a minor issue;
  using shift for once seems OK.)

  Only tested on Linux (FIXME).


Authors
-------
  This keymap.c was edited from the Minivan default, LED support was
  copied/edited from ../jetpacktuxedo/ keymap. Thanks to QMK support
  for their help.  Written on the Minivan 🙂 「Dvorak² 44 ⮚triangle⮘」.

  Written by: Jos B. [contact](https://market.socialism.nl/author/ "get e-mail address there")

  You can let me know if you find any bugs / problems, or if you like using
  it too 👍.

  Contributions to this key map:
      - …

