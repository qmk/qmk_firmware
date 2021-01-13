# Minivan 
A 40% keyboard made first by TheVan Keyboards
_https://thevankeyboards.com_ now taken over by TKC
_https://thekey.company_

![Minivan layout all](http://socialism.nl/misc/minivan/minivan-all-layers-visualization_vb.jpg)

This keymap functions on Minivan hardware variants with 44, 45 and
46 keys. It may also function on 12x12x12x[11|12] boards.

For some ‛common layers’ (numbers pad, movement), different versions can be chosen than shown just below in this by layer view:

![Minivan illustration Overview layers](http://socialism.nl/misc/minivan/minivan-all-layers-clear-visualization_1500_vd.jpg)

By key view:

![Minivan illustration Overview layers by key](http://socialism.nl/misc/minivan/minivan-all-layers-clear-visualization-by-key_2000_ve.jpg)

*make example:*

     … Download the repository, resolve software dependencies etc..
     … If you want to change compile options: edit user_config.h
     > cd […]/qmk_firmware
     > make thevankeyboards/minivan:josjoha
     > su
     # dfu-programmer atmega32u4 erase
     # dfu-programmer atmega32u4 flash thevankeyboards_minivan_josjoha.hex
     # dfu-programmer atmega32u4 start

This “Mini*fan*” layout is explained in several readme files, with
links to the others files in this readme. The common system is explained
in this readme.md file. The options for the letters and number/symbol
layer pairs (two pairs in the dual layout) are explained in their
separate readme file, see immediately below.

Base layouts
============
You can have two of these layouts on your keyboard, and switch between them.
They are presented here in a sort of simplified keycaps view. See the manual for
each layout for more details. See further down for the *other layers* that these
layouts have in common.

Normal layouts
--------------
These are layouts for commonly used configurations, such as Qwerty or Dvorak.

If a base layer pair has its own user configuration options, they are located
in `./base_NAME.h` by convention. Example: `./base_numpad.c` is configured in
`./base_numpad.h` and has its manual in `./base_numpad.md`.

Qwerty
------

![Minivan layout all](http://socialism.nl/misc/minivan/minivan_keycapview_qwerty_vc.jpg)

For the readme about the Qwerty version, see ➡ ![base_qwerty.md](./base_qwerty.md) ⬅

Dvorak
------

![Minivan layout all](http://socialism.nl/misc/minivan/minivan_keycapview_dvorak_vc.jpg)

For the readme about the Dvorak version, see ➡ ![base_dvorak.md](./base_dvorak.md) ⬅

Dvorak² 
-------

Regular Dvorak for a computer already set to Dvorak.

For the readme about the Dvorak² version, see ➡ ![base_dvorak_descramble.md](./base_dvorak_descramble.md) ⬅

Colemak
-------

![Minivan layout all](http://socialism.nl/misc/minivan/minivan_keycapview_colemak_vc.jpg)

For the readme about the Colemak version, see ➡ ![base_colemak.md](./base_colemak.md) ⬅

Special layouts
===============
These are unusual layouts. Most people will probably only want one of these on the ‛Alternate’ layout,
with a normal layout on ‛Default’. How this works is explained below.

Numbers pad
-----------

![Minivan layout all](http://socialism.nl/misc/minivan/minivan_keycapview_numpad_single_va.jpg)

For the readme about the Numpad version, see ➡ ![base_numpad.md](./base_numpad.md) ⬅


The common system
=================

![Minivan layout all](http://socialism.nl/misc/minivan/minivan_keycapview_common_vc.jpg)

Main features 
-------------

     • Dual layout. Several layouts to choose from (example: Qwerty
       and Dvorak dual layout). Easy to add more layouts.
     • Expanded character set. western European accented characters
       (ëøßœç…); sub- super-script numbers (¹₂…) quite a few additional
       symbols such as 《 ± • ☑  ❦ √ ┣ ≠ 》…
     • Typing speed measuring. Led changes color with your speed. You can 
       ask for a report on your current and average typing speeds.
     • Text size measuring. If you want to type some amount of words or
       characters, the middle led will go from green to red as you go,
       and prevent you going over the limit.

Layer access
------------
This graphic shows how layers are reached from the ‛Default base’ layer.

![Minivan layout Image associations](http://socialism.nl/misc/minivan/minivan-default-base-layer-activation_1500_vd.jpg)


The upper/left key which returns to the base layer (letters) on the number layers
 `_DEF_NSY` and `_ALT_NSY` always point to their base layer: `_DEF_BASE` and
`_ALT_BASE` respectively. All the other layers also point to the appropriate base
or numbers layer, depending on which base layer (default or alternate) is active.

(There are some unimportant artefacts due to some transparent layer
switching keys, allowing for example to switch from a toggled `_NSY`
layer to the `_ACC` layer with a key on the first row, or to go back
to base from a toggled `_MOV` layer with what is the `<enter>` key on 
BASE, etc. These accidental layer switching possibilities are not shown.)

You can switch between the default base layer (typically letters), and
another base layer, the alternate base layer (also typically letters),
on the `_RAR` layer with key ‛Other BASE’. Each base layer comes
with its own second layer, typically numbers-symbols. The other 
layers are used common between the default and alternate base layers.

Example: The default base layer can be a Dvorak layout, and the alternate
base layer can be a Qwerty layout, or vice versa. Both will use the same
layer for Function keys, movement, number pad, additional unicode, etc.

The BASE layers and their numbers layer are detailed in files beginning
with `./base_…` (links below).

                   Layer overview:                    Defined in:

        • Default Letters / BASE                   ┓
        • Default Numbers-symbols                  ┃
                                                   ┣ ./base_….c/md files
              • Alternate Letters / BASE           ┃
              • Alternate numbers-symbols layout   ┛

           • Numbers pad                           ┓
           • Accented characters                   ┃
           • Additional Unicode characters         ┃
           • More Additional Unicode characters    ┣ ./keymap.c(etc)/readme.md
           • Movement arrows/mouse                 ┃   “The common system”
           • Function keys / layer toggles         ┃
           • Power, media, Speed, Text size, etc.  ┛

A layout defined in `./base_…` can have the common layers re-defined
from what is detailed in _this_ file that you read now. The re-defined
layer will be the same one for both the ‛default’ and ‛alternate’ layouts
in the dual layout system. 

Example: if a layout defined in ./base….c/md redefines the `_ACC`
layer there to have French accented letters in better places for French,
you will reach that same French adapted `_ACC` layer from either of
the two BASE layers in the dual layout (one is for instance Qwerty,
the other Dvorak).

Led colors for layers
=====================

      • letters                          Led: low-white/teal/off⁽¹⁾          _DEF_BASE "Default base"
        • letters (alternate)              Led: off/teal/low-white           _ALT_BASE "Alternate base"
      • numbers                          Led: blue/blue/blue                 _DEF_NSY "Default Numbers SYmbols"
        • numbers (alternate)              Led: blue/blue/low-white          _ALT_NSY "Alternate Numbers SYmbols"
      • number pad symbol versions       Led: green/low-white/blue ⁽²⁾       _PAD "numbers PAD"
      • accented characters é, ø, ß …    Led: cyan/cyan/cyan                 _ACC "ACCented"
      • Unicode symbols, ¹, ±, ° …       Led: yellow/yellow/yellow           _DRA "DRAwings"
      • Unicode symbols, ①, ‰, ÷ …       Led: off/yellow/off                 _BON "Bonus"
      • function keys,                   Led: red/red/orange ⁽³⁾             _FUN "FUNction keys"
      • and a movement layer             Led: green/green/green              _MOV "MOVement"
      • keys like Power, Play,           Led: white/purple/purple ⁽⁴⁾        _RAR "RARe keys"

      Leds:
            • ⁽¹⁾ The low-white led is bright-white when capslock is on. Optionally the middle led (cyan) can
                  show the color of the last layer that was active.
            • ⁽²⁾ The colors are reversed blue/low-white/green when numlock is on. 
                  Left led color memory aid: same as either numbers or movement layer for numlock on/off.
            • ⁽³⁾ The colors are reversed to orange/red/red when set to de-activate after one F-key press.
            • ⁽⁴⁾ The colors are reversed purple/purple/white, indicating which of the two base layers
                  is active (see below).
            • Middle led: Breathing effect. When not breathing, keyboard is not working normally with the computer.
                        - When speed measurement is active, the middle led color indicates the speed, unless
                          text size counting set to a maximum is active.
                        - When text size counting is active and set to a maximum amount, the middle led color 
                          indicates progress to the limit from green to red, flipping white/red on the limit.
                        - When on BASE layer it shows a teal color, or (compile option) the layer most recently active.
                        - When the left/right leds are off, when on BASE, it shows a teal color (not last active), even
                          if so compiled.
            • Leds can be switched on/off on the _RAR layer (SLeds, MLed).

layout
------

Below you will first see the **‛default BASE layer’,** with the
keys that are different in various common layouts (Qwerty, Dvorak,
etc) blanked out. Then its accompanying **‛default `_NSY` layer’**
(numbers and symbols `123...!@#...`), also with such keys just showing
blanks. After that the same for the **‛alternate BASE layer’** and
its accompanying **‛alternate `_NSY` layer’** (the second layout in
the dual layout). What comes in the blanks is typically to be defined
at compile time, by what set of BASE layer pairs to choose. The ‛BASE’
and ‛`_NSY`’ layers have their own readme files, which show what comes
on the blanks (see above).

Example: if you choose the ‛Qwerty + Dvorak’ compile option, you
will have Qwerty on the ‛default BASE’ and a matching ‛default NSY’ 
layer, with Dvorak on the ‛alternate BASE’ and its ‛alternate NSY’ 
layer.

![Minivan layout Image BASEdef](http://socialism.nl/misc/minivan/minivan_base_layer_hide_def_base_vd.jpg)
Layer: `DEF_BASE`

![Minivan layout Image NSYdef](http://socialism.nl/misc/minivan/minivan_nsy_layer_hide_def_base_vb.jpg)
Layer: `DEF_NSY`

![Minivan layout Image BASEalt](http://socialism.nl/misc/minivan/minivan_base_layer_hide_alt_base_vd.jpg)
Layer: `ALT_BASE`

![Minivan layout Image NSYalt](http://socialism.nl/misc/minivan/minivan_nsy_layer_hide_alt_base_vb.jpg)
Layer: `ALT_NSY`

![Minivan layout Image PAD](http://socialism.nl/misc/minivan/minivan_pad_layer_vc.jpg)
Layer: `_PAD`

^ See below for a different configuration of the numbers pad keys. See above for a Base layout for a numbers pad.

![Minivan layout Image ACC](http://socialism.nl/misc/minivan/minivan_acc_layer_vc.jpg)
Layer: `_ACC`

![Minivan layout Image DRA](http://socialism.nl/misc/minivan/minivan_dra_layer_vc.jpg)
Layer: `_DRA`

![Minivan layout Image BON](http://socialism.nl/misc/minivan/minivan_bon_layer_vb.jpg)
Layer: `_BON`

![Minivan layout Image FUN](http://socialism.nl/misc/minivan/minivan_fun_layer_vb.jpg)
Layer: `_FUN`

![Minivan layout Image MOV](http://socialism.nl/misc/minivan/minivan_mov_layer_triangle_hw-basic-and-allkeys_vb.jpg)
Layer: `_MOV`

^ There is an alternative flat arrow configuration for this layer (see below),
and options to compile with the 'arrow' hardware layout.

![Minivan layout Image RAR](http://socialism.nl/misc/minivan/minivan_rar_layer_vc.jpg)
Layer: `_RAR`

Movement layer options
----------------------

The movement layer (`_MOV`) has quite a few configuration options. You
can either have _triangle_ configuration arrows on the _left_ hand
(with navigation keys around it), or a _flat_ arrow configuration on
the _right_ hand (with navigation above it).

You can configure for the _arrow_ hardware layout (one additional hardware
key on the right). The additional key on the BASE layer can toggle to the
movement layer, and than becomes part of the arrow cluster. For both
versions (_triangle_ arrows left hand or _flat_ arrows right hand) you
can compile this second arrow cluster to be completed with navigation keys
(Home, End, PageUp, PageDown).

      Weighing the options …

To get arrow keys under easy reach, it may be good to realize that
you can in any case quite easily reach the `_MOV` layer in three ways.
Both a hold and a toggle can be done by the left hand alone.
①  press and hold the 4th key on the 1st row;
②  hold the left shift key for a short while, toggles;
②  hardest: by toggling first to the `_FUN` layer, and then toggle to `_MOV`. 

The *arrow* hardware layout with the compile option for arrow cluster,
allows additionally a toggle to the `_MOV` layer done only by the right 
hand, and those arrows being there for the right hand.

If you use a tiling *window manager* (such as i3wm), you may want
to press GUI with an arrow quite often. If the GUI is displaced by the
arrow cluster on `_MOV`, you will need to activate the movement
layer (`_MOV`) *after* BASE layer GUI. To have to press keys in a specific
order is slightly less comfortable. To resolve this you can activate
the left side additional hardware key (‛South Paw’ or ‛Command’) as
well, and configure it as a GUI.

Options to compile it that way are mentioned below the layer. You
can find the configuration block and mentioned option in `./user_config.h`.

![Minivan layout Image MOV 3 defaultf](http://socialism.nl/misc/minivan/minivan_mov_layer_flat_hw-basic_vb.jpg)

![Minivan layout Image MOV 3b default](http://socialism.nl/misc/minivan/minivan_mov_layer_triangle_hw-basic_vb.jpg)

^ `#define ARROWS_TRIANGLE`

![Minivan illustration BASE towards 3](http://socialism.nl/misc/minivan/minivan_layer_illustration_base_mov_hw-arrow_vb.jpg)

^ Illustration of accessing the arrows/navigation with a key on the BASE layer

![Minivan layout Image MOV 3b + arrow](http://socialism.nl/misc/minivan/minivan_mov_layer_hardw-arrow_triangle_vb.jpg)

^ `#define ARROWS_TRIANGLE`, `MORE_KEY__ARROW`, `MOREKEY2_ARROW_CLUSTER`, `MORE_key2 _MOV_UP`

![Minivan layout Image MOV 3b + navig](http://socialism.nl/misc/minivan/minivan_mov_layer_hardw-arrow_triangle_addnav_vb.jpg)

^ `#define ARROWS_TRIANGLE`, `MORE_KEY__ARROW`, `MOREKEY2_ARROW_CLUSTER`, `MOREKEY2_ADD_NAVIGATION`, `MORE_key2 _MOV_UP` (note change on previously BTN2/3)

![Minivan layout Image MOV 3 + arrows](http://socialism.nl/misc/minivan/minivan_mov_layer_hardw-arrow_flat_vb.jpg)

^ `#define MORE_KEY__ARROW`, `MOREKEY2_ARROW_CLUSTER`, `MORE_key2 _MOV_UP`

![Minivan layout Image MOV 3 + naviga](http://socialism.nl/misc/minivan/minivan_mov_layer_hardw-arrow_flat_addnav_vb.jpg)

^ `#define MORE_KEY__ARROW`, `MOREKEY2_ARROW_CLUSTER`, `MOREKEY2_ADD_NAVIGATION`, `MORE_key2 _MOV_UP` (note change on previously BTN2/3)

![Minivan layout Image MOV 3 vi arrow](http://socialism.nl/misc/minivan/minivan_mov_layer_vi_vb.jpg)

^ `#define` \[`MORE_KEY__ARROW`, `MOREKEY2_ARROW_CLUSTER`\] `VI_SWITCHERYDOO`, `#undef ARROWS_TRIANGLE`

Numbers pad layer options
-------------------------

This concerns the numbers pad layer, the one that is part of the common layers.

![Minivan layout Image PAD](http://socialism.nl/misc/minivan/minivan_pad_layer_vc.jpg)

![Minivan layout Image PAD squared](http://socialism.nl/misc/minivan/minivan_pad_layer_squared_vb.jpg)

^ `#define NUMPAD_COMMON_SQUARE`


Compile options
===============

         Layout (as in Dvorak, Qwerty, Colemak, etc)

 • You can use the keyboard with two different letters/number-symbols layouts, switching between them.

 • You can compile the keyboard as a single layout (see ‛Eviscerations’).

 • Startup in the alternate BASE layer (for example Qwerty or Dvorak).

         Hardware

 • Hardware key configurations: _default_ (44), _arrow_ (45), _south paw_ (45), _arrow_ + _south paw_ (46).

![Minivan illustration 0](http://socialism.nl/misc/minivan/minivan_illustration_arrow_southpaw.jpg)
   (On the `_RAR` layer, the additional _south paw_ key is more to the right.)

 • What the additional hardware keys for _arrow,_ _south paw_ should be.

 • It is possible to compile the keymap with 11, 12, 13 keys on the bottom row (see 
   `TRANSMINIVAN_LEFTSIDE`, etc). Untested FIXME.

         Navigation cluster

 • An arrow cluster for _arrow_ hardware configuration, on the `_MOV` layer.

 • Navigation keys around _arrow_ hardware configuration arrow cluster on `_MOV` layer.

 • Navigation cluster in a triangle (WASD) (left hand), flat layout with optional vi(1) layout (right hand).

         Special functions

 • Set speed measuring on/off at keyboard startup.

 • Set text size measuring on/off at keyboard startup.

         Changing symbols

 • Switching the GUIs left/right.  

 • You can change the symbol 'ƒ' Dutch guilder into a Euro symbol €.

 • Compile with symbols ☐ ☒ ☑ 🗹 (checkboxes) or ⮘ ⮙ ⮚ ⮛ (pointers).

 • Reduce firmware size/bloat: remove or eviscerate Unicode layer(s).

 For the complete list, see `./user_config.h`. It has a table of contents.

Layers (text)
=============
 
         Layer _DEF_BASE (Letters layer, see ./base* files for what comes on ‛__’)
                                                  | Right hand
         <pink2     <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pinky2>   // Keys by finger
         -o-                                     <|>                                    ... //-o- BASE access
         Esc        __    __    __    __    __    | __    __    __    __    __         Bksp
         Tab+LCtl   __    __    __    __    __    | __    __    __    __    __           __
         LSht+_PAD  __    __    __    __    __    | __    __    __    __    __    RSht+_FUN 
             +_MOV⁵                               |                                   +_RAR⁶
     ---------------------------------------------------------------------------------------
     Left+LAlt Del;_ACC _..._NSY(_DRA)  Enter+_MOV| Space  _..._NSY(_DRA) RGUI    Right;_RAR 
               hold     hold₍₁,₂٭₎      hold      |        hold₍₁,₂٭₎             hold     // switch type
               hold₍₂₎  ^-┃-----------------------+--------^ ┃                          // ₁₎ both = _DRA
               ┗━━━_BON━━━╋┅───────────┄┄┄«or»┄┄┄─+─────────┅┛                          // ₂₎ both = _BON
     <1   ±    <2       <3              <4        | 4>     3>             2>   ±  1>    // Keys by number
          ^³                                                                   ^⁴   // Optional more keys
        (LGUI)                                                               (_MOV)
     
     ₁) Dual hold for _DRA, single hold for _..._NSY. Marked by: ^--…--^
     ₂) Hold key “<2” with either٭ key “<3” or “3>” for _BON, single hold “<2” for _ACC. Marked: ┗━━…━━┛
     ³) 'South paw' hardware configuration. Configurable, default shown.
     ⁴) 'Arrow' hardware configuration  Configurable, default shown.
     ³ ⁴) There are two more optional hardware keys, to make it easier to compile for
          a 12x12x12x11 or 12x12x12x12 layouts.
     ⁵) Left Shift when pressed with another key. Medium long: to toggle _PAD. Long: toggle _MOV.
     ⁶) Right shift when pressed with another key. medium long: to toggle _FUN. Long: toggle _RAR.

Remarks: The left modifiers have a slight delay in combination with an outside pointer device (mouse, stylus).
It seems this will be difficult to fix, because it is spread over two devices. To avoid the
±0.2 second delay, activate a layer where the modifiers are direct (`_PAD`, `_MOV`), using the layer toggle on
left shift. 

The two keys with ';' (Del;`_ACC`, Right;`_RAR`) do not auto-repeat on double tap, like QMK normal layer-tap keys.

There is an uncluttered _Delete_ on `_PAD`, an uncluttered _Right_ arrow on the `_MOV` layer.

There is an uncluttered _Tab_ on both the `_DRA` and `_ACC` layers. They can be modified with _Control_ there.

Holding both `_..._NSY` keys left and right of the "split space bar" (enter, space) results in layer `_DRA`.

Holding either one of the just above mentioned `_..._NSY` layer keys (<3 and 3>), with the `_ACC` layer key
(on <2) results in layer `_BON`.

- - -

     Layer _..._NSY (Numbers and SYmbols, ./base* files for what comes on ‛__’)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
              -*-                          <|>                                  //(toggle) Access on _FUN
     BASE     __    __    __    __    __    | __    __    __    __   __     Bspc
     Tab+LCtl __    __    __    __    __    | __    __    __    __   __  __+RCtl
     -+LSht   __    __    __    __    __    | __    __    __    __   __  __+RSht 
     ---------------------------------------------------------------------------
                 Left+LAlt ___   ___   Ent  | .   ___   RGUI  Right+RAlt
                                 -*-       <|>    -*-                        //(hold) Access on _DEF_BASE
                   <1   ±  <2    <3    <4   | 4>  3>    2>  ± 1>  
                        ^                                   ^
                      (LGUI)                              (_MOV)

- - -
     
     Layer _FUN (F-keys, Layer access)
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
     toggl toggl set   toggl toggl toggl | toggl toggl                            // Type of layer switch
                                        <|>                                       
     BASE: NUMS: _PAD  _ACC  _DRA  _BON  | _MOV  _RAR  xxx   xxx   xxx   Bspc       //':' are dynamic ...
     LCtl  F1    F2    F3    F4    F5    | F6    F7    F8    F9    F10   RCtl
     LSht  F11   F12   F13   F14   F15   | F16   F17   F18   F19   F20   RSht     
     ---------------------------------------------------------------------*--       //-*-  toggle on BASE
              LAlt  LCtl&  LCtl&  LSht&  | FUN< +LCtl&LSht RGUI   RAlt              //... < toggle 'stay'
                    LSht   LAlt   LAlt   |      &LAlt                                    
                    +xxx   +xxx   +xxx   |      +xxx
                                        <|>
              <1  ± <2     <3     <4     | 4>   3>         2>  ±  1>                
                  ^                                            ^
                (LGUI)                                       (_MOV)

Remarks.  FUN< toggles an immediate return to the BASE layer after pressing an F-key, 
or staying on the `_FUN` layer. Right led yellow indicates F-layer stays active.

- - -
    
This is the _triangle_ configuration for arrows, arrow are on left hand (WASD):

     Layer _MOV (MOVement, mouse movement on right hand)
    
     <pinky2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                         <|>-*-                                
     BASE   PgDn  Up    PgUp  Home  Btn3  | xxx   WhDn  MsUp  WhU   WhLft Bksp
     LCtl   Left  Down  Right End   Btn1  | Btn1  MsLft MsDn  MsRht WhRht RCtl
     LSht   xxx   Acc2  Acc1  Acc0  Btn2  | Btn2  Btn3  Btn4  Btn5  xxx   RSht
     -------------------------------------------------------------------------
                     LAlt Del   Ent   ___ | PgUp  PgDn  RGUI  RAlt
                                      -*-<|>                                                 
                     <1 ± <2    <3    <4  | 4>    3>    2>  ± 1>  
                        ^                                   ^
                      (LGUI)                              (DOWN)


Remarks. For the Minivan _arrow_ hardware layout with arrow cluster, you get this on `BASE`:

     (…)
     LSht+_PAD ;:    qQ    jJ    kK    xX    | bB    mM    wW    vV    zZ    RSht+_FUN
     -------------------------------------------------------------------------------
     Left+LAlt Del;_ACC _..._NSY(_DRA) Enter+_MOV| Space  _..._NSY(_DRA) RGUI  _MOV  Right;_RAR 
                                                                               ^^^^     // new key (toggle)

… and this on `_MOV` for the _triangle_ configuration:

     (…)
     LSht*- xxx   Acc2  Acc1  Acc0  Btn2  | Btn2  Btn3  Btn4  Btn5  _Up_  RSht
     ---------------------------------------------------------------------------
                     LAlt Del   Ent   ___ | PgUp       PgDn  _Left__Down__Right_
                                      -*-<|>                                 
                     <1 ± <2    <3    <4  | 4>         3>     2>   _±_    1>  
                        ^
                      (LGUI)

… or this on `_MOV` for the _triangle_ arrow configuration with additional _navigation_ keys:

     BASE   PgDn  Up    PgUp  Home _Btn4_ | xxx   WhDn  MsUp  WhU   WhLft Bksp
     LCtl   Left  Down  Right End   Btn1  | Btn1  MsLft MsDn  MsRht WhRht RCtl
     LSht*- xxx   Acc2  Acc1  Acc0 _Btn5_ | Btn2  Btn3 _Home__PgUp_ _Up_ _PgDn_
     ---------------------------------------------------------------------------
                     LAlt Del   Ent   ___ | PgUp      _End_  _Left__Down__Right_
                                      -*-<|>                                  
                     <1 ± <2    <3    <4  | 4>         3>     2>   _±_    1>  
                        ^
                      (LGUI)


This is the _flat_ configuration for arrows, arrow are on right hand:

     <pinky2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                         <|>-*-                              
     BASE   WLft  WDn   WUp   WRht  xxx   | Btn3  PgUp  Home  End   PgDn  Bksp
     LCtl   MLft  MDn   MUp   MRht  Btn1  | Btn1  Left  Up    Down  Right RCtl
     LSht*- Btn5  Btn4  Btn3  Butn2 xxx   | Btn2  Acc0  Acc1  Acc2  xxx   RSht
     -------------------------------------------------------------------------
                     LAlt Del   Ent   ___ | PgUp  PgDn  RGUI  RAlt
                                      -*-<|>                                                
                     <1 ± <2    <3    <4  | 4>    3>    2>  ± 1>  
                        ^                                   ^
                      (LGUI)                              (DOWN)

For the Minivan _arrow_ hardware layout with _flat_ arrow cluster, you get this on `_MOV`:

     (…)
     BASE   WLft  WDn   WUp   WRht  xxx   | Btn3  PgUp  Home  End   PgDn  Bksp
     LCtl   MLft  MDn   MUp   MRht  Btn1  | Btn1  Left  Up    Down  Right RCtl
     LSht*- Btn5  Btn4  Btn3  Butn2 xxx   | Btn2  Acc0  Acc1  Acc2  xxx   RSht
     ---------------------------------------------------------------------------
                     LAlt Del   Ent   ___ | PgUp      _Left_ _UP_  _Down__Right_
                                      -*-<|>                                 
                     <1 ± <2    <3    <4  | 4>         3>     2>   _±_    1>  
                        ^   
                      (LGUI)

… or this on `_MOV` for the _flat_ arrow configuration with additional _navigation_ keys:

     BASE   WLft  WDn   WUp   WRht  xxx   |_Acc2_ PgUp  Home  End   PgDn  Bksp
     LCtl   MLft  MDn   MUp   MRht  Btn1  | Btn1  Left  Up    Down  Right RCtl
     LSht*- Btn5  Btn4  Btn3  Butn2 xxx   |_Acc1_ Acc0 _PgUp__Home__End_ _PgDn_
     ---------------------------------------------------------------------------
                     LAlt Del   Ent   ___ | PgUp      _Left_ _UP_  _Down__Right_
                                      -*-<|>                                  
                     <1 ± <2    <3    <4  | 4>         3>     2>   _±_    1>  
                        ^ 
                      (LGUI)

… or this on `_MOV` for the _flat_ arrow configuration, […], and vi(1) layout:

     <pinky2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                         <|>-*-                                 
     BASE   WLft  WDn   WUp   WRht  xxx   |_Acc2_ PgUp  Home  End   PgDn  Bksp
     LCtl   MLft  MDn   MUp   MRht  Btn1  | Left  Down  Up    Right Btn1  RCtl         // vi as in Qwerty
     LSht*- Btn5  Btn4  Btn3  Butn2 xxx   |_Acc1_ Acc0 _PgUp__Home__End_ _PgDn_
     ---------------------------------------------------------------------------
                     LAlt Del   Ent   ___ | PgUp      _Left_ _Down__Up_  _Right_       // vi as in Qwerty
                                      -*-<|>                                  
                     <1 ± <2    <3    <4  | 4>         3>     2>   _±_    1>  
                        ^
                      (LGUI)

For the 'arrow' hardware layout (additional key on the right), keys on the first
row are sacrificed and lost. The right most key on the second row is also lost.
The two keys on places 3 and 4 when counting from the right on the second row,
are being moved to the spots for Btn2 and Btn3 on the hand that also has the 
arrows (those keys are otherwise twice defined for left and right hand).

- - -
    
     _RAR (RARe keys. Power keys, Unicode mode, Alternate BASE, Media, Brightness, Speed, Size, leds, …)
    
     <pink2<pinky <ring <middl <indexx<indx2| indx2>index>middl>ring> pinky> pink2>
                                           <|>      -*-                                //(toggle) on _FUN
     BASE  Cnt/Mx Cnull CWmin  CRprt  Speed | SRprt Play  Next  Prev  Stop RSht(•)   
     CapsL Power• Wake• Sleep• Pause• ScrLk | PrtSc xxx   Vol+  Vol-  Mute Insert     // • requires Shift
     ☑     uLNX   uBSD  uOSX   uWIN   uWNC  | xxx   xxx   Bri+  Bri-  xxx     APP     // Ü(nicode) tester
     ----------------------------------------------------------------------------
                     SLed  MLeds LGUI  xxx  | !Alter  xxx   RGUI  ___   // Mid-led, Side-leds, !Alternate
                                           <|>                    -*-                   // (Hold) on BASE
                     <1  ± <2    <3    <4   | 4>      3>    2>  ± 1>  
                         ^                                      ^
                       (LGUI)                                 (_MOV)

Remarks. !Alter switches between normal and alternate BASE layer.

☑ is a Unicode tester key. uLNX for Linux Unicode input encoding, uBSD
for BSD Unix, uWIN for Windos, uWNC for another Windos encoding. The
change is retained between on/off power cycles.

MLed switches on/off the middle led, SLeds switches on/off the side leds.

The keys marked with • require Shift to be activated, as a means of
preventing accidents. Shift here is on (BASE) 'Backspace' (upper/right key)
which also reduces accidents (combinations which are never pressed
normally). If you press these keys without 'shift' they print their own
name between angled brackets. Example: pressing the 2nd key on the 3rd
row prints `“<POWER>”`.

Bri+, Bri-: screen brightness (if your system supports it.)

Speed: toggles speed measuring on/off. SRprt: writes your speed.
See topic about Speed measuring.

Cnt/Mx, Cnull CWmin, CRprt: text size measuring. See topic.

- - -
    
    
     Layer _PAD Numbers Pad (special symbol versions; regular '1' is not the same as this numpad '1', etc)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                    -*-                    <|>                                         //(toggle) on _FUN
     BASE     xxx   xxx   .DEL  4LEFT 2DOWN | 8UP   6RGHT *     xxx   xxx   Bspc
     LCtl     1END  2DOWN 3PGDN 4LEFT 5     | 6RGHT 7HOME 8UP   9PGUP 0INS     -
     LSht     xxx   xxx   /     xxx   =     | +     3PGDN 1END  7HOME 9PGUP RSht
     -*-------------------------------------------------------------------------    //-*-  toggle on BASE
                  LAlt     Del   Tab   ENT  |  NUML  xxx   RGUI  RAlt
                                           <|>
                  <1   ±   <2    <3    <4   | 4>     3>    2>  ± 1>  
                       ^                                       ^
                     (LGUI)                                  (_MOV)

Remarks: The keys between `.DEL` and `*`, `+` and `RSht` constitute sort of
navigation clusters, to make it easier to find the number pad versions thereof.

This is the variety for `_PAD` layer, which resembles a numerical keypad:

     Layer _PAD (Number pad, square layout)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
                                           <|>
     BASE     xxx   xxx   xxx   xxx   xxx   | =     7HOME 8UP   9PGUP -   Bspc
     LCtl     xxx   xxx   xxx   xxx   xxx   | *     4LEFT 5     6RGHT +   RCtl
     LSht     xxx   xxx   xxx   xxx   xxx   | /     1END  2DOWN 3PGDN ,   RSht  
     ------------------------------------------------------------------------
                   LAlt   Del    Tab   ENT  | NUML  0INS  .DEL  RAlt      
                                           <|>           
                   <1   ±  <2    <3    <4   | 4>    3>  ± 2>    1>  
                        ^                               ^ 
                      (LGUI)                          (RGUI)¹

     ₁) Note anomaly, see Base Numpad for details `./base_numpad.md`.
        Different placement and different meaning, compared to the usual common layers.

- - -
    
    
     Layer _ACC (ACCented characters, see _RAR layer for input modes)
    
     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                       -*-              <|>                                            //(toggle) on _FUN
     BASE  áÁ    óÓ    éÉ    úÚ    íÍ    | ýÝ    ĳĲ    çÇ    øØ    åÅ    Bspc 
     Tab   äÄ    öÖ    ëË    üÜ    ïÏ    | ÿŸ    œŒ    æÆ    ñÑ     ß    RCtl 
     LSht  àÀ    òÒ    èÈ    ùÙ    ìÌ    | îÎ    ûÛ    êÊ    ôÔ    âÂ    RSht
     ------------------------------------------------------------------------
                   LAlt ___   ___   Ent  | Spc   ___   ___   RAlt 
                        -*-             <|>                                              //(hold) on BASE
                   <1 ± <2    <3    <4   | 4>    3>    2>  ± 1>  
                      ^                                    ^
                    (LGUI)                               (_MOV)

- - -
    
    
     Layer _DRA (DRAwings, whatever else (rendering width might vary in different applications))

     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                             -*-        <|>                                            //(toggle) on _FUN
     BASE  “„    ”≤    £≥    ∅ ¢   ±ƒ    | ❦♥    🙂🙁  👍👎   ⁽₍    ⁾₎    Bspc 
     LCTL  ¹₁    ²₂    ³₃    ⁴₄    ⁵₅    | ⁶₆    ⁷₇    ⁸₈     ⁹₉    ⁰₀     Tab 
     LSht 「━    」─   °〇   •§    …·    | ☐☒   ☑🗹     ¿¡    《┄    》┅   RSht     //  ☐ ☒ ☑ 🗹 or ⮘ ⮙ ⮚ ⮛
     -------------------------------------------------------------------------
                   LAlt ___   ___   Ent  | Spc   ___   ___   RAlt 
                              -*-       <|>      -*-                                     //(hold) on BASE
                   <1 ± <2    <3    <4   | 4>    3>    2>  ± 1>  
                      ^                                    ^
                    (LGUI)                               (_MOV)

Remarks. ☐ ☒ ☑ 🗹 or ⮘ ⮙ ⮚ ⮛
- - -

     Layer _BON (Bonus layer, a variety of more stuffs.)

     <pink2<pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pink2>
                                   -*-  <|>                                            //(toggle) on _FUN
     BASE  ‛ 🛠  ’ ⬆   ¤ 🄯   ∑ ©   ‰ ‱   | ★ ٭   😊 ⍨  ×  ⃰   √     ⁻ ⁺    Bksp
     xxx   ① ⬅   ② ⬇   ③ ➡   ④ ┏   ⑤  ┓  | ⑥ ┃   ⑦ ┇   ⑧ ╋   ⑨     ⓪ ∞    — ≈     // — is a dash (larger)
     LSht  ‹     ›     ÷     ☞ ┗   ≠  ┛  | ✗ ┣   ✓ ┫   ⚠     «     »      RSht
     -------------------------------------------------------------------------
                  Left  ___   ___   Ent  | Spc   ___   ___   Right
                        -*-   -*-       <|>      -*-                                // Activation on BASE
                  <1  ± <2    <3    <4   | 4>    3>    2>  ± 1>  
                      ^                                    ^
                    (LGUI)                               (_MOV)
    
- - -


Key associations
----------------
The keymap was designed to have the same or similar keys on the same key
or close to it, on different layers. Sometimes the association goes by
what finger is used, and/or on what row. For example the symbol ‛(’
on the numbers-symbols layer (`_NSY`), becomes the symbol ‛⁽’ on
another layer.  When the same finger (right hand ring finger) is moved
from the 4th row (up) instead down to the 2nd, it becomes ‛《’ in
one layer, and ‛«’ on another.  When the ring finger on the other
hand (left) is used on the 2nd layer, it becomes ‛›’ in one layer,
and ‛」’ in another. These are all brace related symbols, opening
and closing next to each other.

![Minivan layout Image associations](http://socialism.nl/misc/minivan/minivan-relationships_common_1500_va.jpg)

`_ACC` layer:

  Tab is on the left for `_ACC`, following the logic that you move your thumb
  to the left to activate `_ACC`, with Right-Control on the right. 

  The left hand has vowels, which repeat in three rows with the same accent,
  following Dvorak letter placement. The letter 'å'
  is on the same finger as 'a' but other hand, 'ß' is on the spot of
  's', etc. Some things are clustered, perhaps vaguely.

              Grave is a line going up, thus on upper row. é
              Acute is a line going down, thus on lower row. è
              Diaereses is dots going horizontal, thus middle. ë
              Diareses is umlaut which is most frequent if
                 including German, thus home row. ë
              There is no room for Caret on the left, thus it is
                 on the right, following same-finger logic (O 
                 is ring finger, etc).
              Caret is on the lower row to make room for versions 
                 of 'n' and 'c' near their normal position.
              There is no room for ÿŸ on the normal y, because
                 íÍ is on it, which is more important, and to
                 keep the logic of that block, therefore it is
                 as close to it as can be.
              øØ and åÅ follow the same-finger logic (a is left
                 hand pinky, etc), and are on remaining spots.
              œŒ and æÆ are on remaining spots, both close
                 to êÊ for the e in there, the œŒ being further
                 to the left to follow the same finger logic on
                 that right hand side: a on the right, o on the left.

`_DRA` layer, memory aids:

  Tab on the `_DRA` layer is the other option from what it is on `_ACC`
  layer. Pressing two thumbs has no left or right bias. Tab is therefor
  on the right on `_DRA`, with Left-Control on the left.

        Row 4, Key 2:  “ on '", the opening „“ at the ‛open’ of the keyboard (left/up)
        Row 4, Key 3:  ” to the right of opening “, ≤ on <
        Row 4, Key 4:  £ this is where the £ is on an English keyboard, on 'any' money symbols ¤; ≥ on >
        Row 4, Key 5:  ∅ looks like ¢, and ¢ (cent) is on $ (money) 
        Row 4, Key 6:  ± percentages %‰‱ and money ƒ are numerical ?
        Row 4, Key 7:  ❦ ♥ left of 🙂, on top of ★
        Row 4, Key 8:  🙂 🙁 on 😊 ⍨ 
        Row 4, Key 9:  👍 👎 «no reason», next to 😊 (emoticons)
        Row 4, Key 10: ⁽₍ on (
        Row 4, Key 11: ⁾₎ on )
        Row 3, Key 2:  ¹₁ on 1
        Row 3, Key 3:  ²₂ on 2
        Row 3, Key 4:  ³₃ on 3
        Row 3, Key 5:  ⁴₄ on 4
        Row 3, Key 6:  ⁵₅ on 5
        Row 3, Key 7:  ⁶₆ on 6
        Row 3, Key 8:  ⁷₇ on 7
        Row 3, Key 9:  ⁸₈ on 8
        Row 3, Key 10: ⁹₉ on 9
        Row 3, Key 11: ⁰₀ on 0
        Row 2, Key 2: 「 on [, ━ mirrors other side ┅, the heavy ones are on the outside of the board, like a shell
        Row 2, Key 3:  」 on ], ─ mirrors other side ┄
        Row 2, Key 4:  ° «no reason», 〇 also a circle
        Row 2, Key 5:  • «no reason», § also an item marker
        Row 2, Key 6:  … «no reason», · also a dot
        Row 2, Key 7:  ☐ ☒  «no reason» (+ resembles ‛☒’), ✗
        Row 2, Key 8:  ☑ 🗹  next to ✗ ☐ ☒
        Row 2, Key 9:  ¿¡ on ‛?’
        Row 2, Key 10: 《 on {, ┄ «no reason» (opposite side from ━)
        Row 2, Key 11: 》 on }, ┅ «no reason» (opposite side from ─)

`_BON` layer, memory aids:

        Row 4, Key 2: ‛ on ' (`_DEF_BASE`), 🛠 «no reason»
        Row 4, Key 3: ’ (closing) to the right of ‛ (opening); ⬆ on UP arrow in WASD `_MOV` layer configuration
        Row 4, Key 4: ¤ (‛any currency’)on £ (`_DEF_BASE`); 🄯 (‛Copyleft’), sortof money(legal), ¤ is a circle for ‛social’
        Row 4, Key 5: ∑ on $ (`_..._NSY`) and ¢ (`_DRA`) money symbols, money is often added; © (‛Copyright’), ∑$ for ‛accumulate money’
        Row 4, Key 6: ‰ ‱ on % (`_..._NSY`)
        Row 4, Key 7: ★ ٭ on ♥ ❦ (`_DRA`)
        Row 4, Key 8: 😊 ⍨ on 🙂 🙁 (`_DRA`)
        Row 4, Key 9: × (multiplication)  ⃰(up asterisk) on * (`_..._NSY`)
        Row 4, Key 10: √ because Øø (`_ACC`) seems to divide something, and √ also does that, proximity to ⁻⁺ (exponential)
        Row 4, Key 11: ⁻⁺ on Åå (`_ACC`) because circle suggests exponent placement, row 4/key 11 is up/right on keyboard
        Row 3, Key 2: ① on 1 (`_..._NSY`); ⬅  on LEFT arrow in WASD `_MOV` layer configuration
        Row 3, Key 3: ② on 2 (`_..._NSY`); ⬇ on DOWN arrow in WASD `_MOV` layer configuration
        Row 3, Key 4: ③ on 3 (`_..._NSY`); ➡ on RIGHT arrow in WASD `_MOV` layer configuration
        Row 3, Key 5: ④ on 4 (`_..._NSY`); ┏ forms a square with box drawing on row 2 (See note¹).
        Row 3, Key 6: ⑤ on 5 (`_..._NSY`); ┓          ''                 ''
        Row 3, Key 7: ⑥ on 6 (`_..._NSY`); ┃ continue box drawing on right hand symmetry
        Row 3, Key 8: ⑦ on 7 (`_..._NSY`); ┇          ''                 ''
        Row 3, Key 9: ⑧ on 8 (`_..._NSY`); ╋ continues box drawings, figure ‛8’ also has a crossing of 2 lines
        Row 3, Key 10: ⑨ on 9 (`_..._NSY`); 
        Row 3, Key 11: ⓪ on 0 (`_..._NSY`); ∞ on 0 for round & round, forever
        Row 3, Key 12: — (dash) on - (`_..._BASE`) (hyphen); ≈ on ~ (`_..._NSY`)
        Row 2, Key 2: ⑪ on 1 row above (`_..._NSY`); ‹ on 「 (`_DRA`)
        Row 2, Key 3: ⑫ on 2 row above (`_..._NSY`); › on 」 (`_DRA`)
        Row 2, Key 4: ⑬ on 3 row above (`_..._NSY`); ÷ on / (`_..._NSY`) (divisions)
        Row 2, Key 5: ⑭ on 4 row above (`_..._NSY`); ☞ on • (`_DRA`); ┗   forms a square with box drawing on row 3
        Row 2, Key 6: ⑮ on 5 row above (`_..._NSY`); ≠ on = (`_..._NSY`); ┛        ''                 ''
        Row 2, Key 7: ⑯ on 6 row above (`_..._NSY`); ✗ on ☒ (`_..._NSY`); ┣ continues right-hand symmetry & line from row 3
        Row 2, Key 8: ⑰ on 7 row above (`_..._NSY`); ✓ on ☑ 🗹 (`_DRA`); ┫                ''                       ''
        Row 2, Key 9: ⑱ on 8 row above (`_..._NSY`); ⚠ on ¡ (`_DRA`) (inverted !)
        Row 2, Key 10: ⑲ on 9 row above (`_..._NSY`); « on { (`_..._NSY`), 《 (`_DRA`)
        Row 2, Key 11: ⑩ on 0 row above (`_..._NSY`); » on } (`_..._NSY`), 》 (`_DRA`)
   
  ¹) Fitting horizontal bars for the box drawings ┅ ━ are on `_DRA`.
           

Usage
-----
 
  Layer switching is by thumb hold buttons on the base layer,
  and on the shifts (those are toggles). The layers can be set to be on
  persistently through the `_FUN` layer top row keys. If toggled, from
  each layer one can go back to the BASE layer by pressing the upper/left
  most button. Changing keyboard mode (what base layer pairs are active)
  is on the `_RAR` layer (‛Other BASE’).

  If you need ‛Control’ + ‛Tab’, look for the `_DRA` or `_ACC` layer.

  A repeating ‛Enter’ is on `_NSY` layer, same key. 

  If you need to press ‛Delete’, it is on the BASE layer, but that 
  key does not repeat automatically. If you need a ‛Delete’ which repeats,
  you can try to press to `_MOV` layer same key, or the `_NSY` layer top/right.

  (You could think of putting a regular repeating ‛Delete’ or ‛Tab’ on an
  additional hardware key (“Command” or “South paw”).)

Speed measuring
===============

      ‛Speed’ starts speed measuring.
      ‛SRprt’ stands for ‛Speed Report’:
                • Tap to get your speed report.
                • Hold for a while for led color compilation (see below).
      ☞ Text size counting (see below) middle led colors take precedence,
        when a maximum is set, over layer colors or speed measurement.

  Details

With the key ‛Speed’ on the `_RAR` layer, the speed of your latest
25 keypresses is computed, as well as a the average of your batches of
25 keys. The speed is displayed as the color of the middle led, which
otherwise shows the layer color. A bright white middle led indicates
‛Speed’ has just been activated.

With the key ‛SRprt’ (short for ‛Speed Report’), the keyboard
will write your typing speed either in keystrokes per second (k/s)
or words-per-minute (wpm), depending on your compilation configuration.

“Keystrokes per second” uses the following format: `<A k/s B.B k/s
Cx25keys>`. A is the amount of key presses per second (k/s) of your
last batch, B.B is your average over the last C batches of keys.
When using “Words per minute”, A is in word-per-minute, B is also
in words-per-minute: `<A wpm B wpm Cx25keys>`, no decimal precision.
Example: <150wpm;108wpm20x25keys>

Batches with 0 k/s are not counted to the average.  This computation
is different from total-keys / total-time, which is not supported (you
could arrive at it by keeping time separately). When you get the report,
the led shows the color for the average, until you switch layers.

The time starts running immediately on the first 25 keys when you press
‛Speed’. ‛Speed Report’ always reports on the last already completed
25 keys, which matches the middle led color on that moment (not a
running average on the point of pressing, which would be the next batch
shown). Shift, backspace, delete and BASE layer activated layer changes
do not count as keypresses. Delete and backspace therefore produce speed
penalties. Typical text keys all get counted.  Navigation / arrow keys
on the `_MOV` layer do not get counted.  Some unusual keypresses
might be undefined whether or not they get counted (test to find out).

In practice this means: you can type; take a long break without it
affecting your average (batch with 0 k/s is ignored, or at worst you
have one slow batch reducing your total average if the break was not
long enough to fall down to 0 k/s); finish typing; take your time
pressing `_RAR` on the BASE layer and then ‛Speed Report’ to get your
speed written as if you typed it on the keyboard.

     Led color compilation assist

If you hold the ‛Speed Report’ key for one second, it will increment the
speed, and led color accordingly. This can be helpful when configuring
your speed measuring compile settings. This works best with speed
measuring set off. Press on/off to reset to 0. See `./user_config.h`
Multiply the number with 12 to get the words-per-minute equivalent.
1k/s = 12wpm, 2k/s = 24wpm, 3k/s = 36wpm, 4k/s = 48wpm, 5k/s = 60 wpm
6k/s = 72wpm, 7k/s = 84wpm, 8k/s = 96wpm, 9k/s = 108wpm, 10k/s = 120wpm
11k/s = 132wpm, 12k/s = 144wpm, 13k/s = 156wpm, 14k/s = 168wpm.

Text size measuring
===================

      ‛Cnt/Mx’ stands for ‛Count/Maximum’: 
                • Tap to start counting, tap again to suspend.
                • Hold > 0.5 seconds for maximum menu.
      ‛Cnull’ stands for ‛Count null’:
                • Tap to set the counts to zero.
      ‛CWmin’ stands for ‛Count Word minus’:
                • Tap to detract one word from the word count. 
                • Hold > 0.5 seconds to detract 10 words.
      ‛CRprt’ stands for ‛Count Report’:
                • Tap to get a counting report. 
      ☞ ‛Count’ and ‛Speed’ (see above) reports get added to the
        character count, but not to the word count.
      ☞ Auto-repeating keys do not get counted as characters.

  Details

You can count your text by character and word, by activating the key
‛Count’ on the `_RAR` layer. Pressing ‛Count’ again will suspend
counting, pressing it yet again resumes where the count left off earlier.
The middle led turns cyan when no maximum is set (see below),
or to green when it is set.

You can set a maximum to type, with the ‛Cnt/Mx’ key.  In your
editor (or wherever typing these characters is harmless) you will get
the following menu by pressing the ‛Cnt/MX’ key for at least half
a second: `<Nc|w>`. In here: *N* stands for your numerical input, *c*
for a maximum count in *characters* or *w* for a maximum in *words.*

Start typing a number, finish with either *c* or *w* to make the maximum
be counted in either characters or words. If you want to leave the
menu before giving *c* or *w*, enter a *dot* ‛.’ or ‛Escape’,
which will leave the maximum value at 0 (zero). A maximum value of zero
implies there is no maximum.

Setting a maximum of 1000 characters looks like so:

        Hold ‛Cnt/MX’ results in: `<Nc|w>` 
        Then type “1000” results in: `<Nc|w>1000`
        Then type “c” results in: `<Nc|w>1000->1000c`
        At this point the keyboard is out of this special input menu.

        The keyboard indicates what it accepted as your input, by 
        repeating the number, just before your last input is being printed.

With a maximum established, the middle led color goes from green to red,
as you type. When the maximum is reached, the keyboard will output a
Backspace character for every key you subsequently press, making it
impossible to go any further, until text size counting has been disabled,
or the count is reduced. The middle led changes color between red and 
white while at the maximum set size, for every new input character.

To get your word count report, press ‛CReport’ short for: ‛Count
Report’.  It comes in the form: `<Ac;Bw>`, where A is your character
count, and B is your word count. Example: `<5420c;547w>`. 

When a maximum is established, the report will only be given in
either characters or words, and the maximum is given with it, like so:
`<66w>[200w]`. 66 words have been written, a maximum of 200 words has
been set.

If you have a maximum established and use it across different articles,
you no longer have the total count. You can activate speed measuring,
which in its report includes the total characters pressed.

          Usage

It is assumed that you will take the report in the document you are
editing, and then delete it. If you do character counting, the value of 
the report itself is added to the character count. Therefore you should
delete that without using an auto-repeating on the deletion key. That
way the characters are subtracted again.

If you count in words, the report is not added to the word count. You
can delete it however you want.

This works the same for a ‛*Speed* Report’ you might like to take.
You can take it in the document, and then delete it in the same,
without affecting the text size counting in characters or words.
When deleting keys with Backspace or Delete, the character count goes down
accordingly, the word count does not.

Words are counted by counting Space and Enter key presses. Immediately
repeating blanks do not add to the word count.  You can only manually
subtract from the word count, using the key ‛CWmin’ short for ‛Count
Word minus’. This means that if you delete sections in your document,
while counting in words, you need to manually subtract the same words.

Example: after typing something and then typing `<Enter>` twice to start a
new paragraph, counts for one word. When deleting three words with their
three blank areas, then tapping ‛Count Word minus’ three times,
should result in an accurate word count. To add words to the count,
type mock ones and then delete them: “x x x x” adds *three* words,
“y y  y ” also adds three words (three separate blank spaces).

Keep in mind that it is not actually words that are counted, but the
blanks in between. The keyboard only knows your current and
last characters, it has no idea how it looks what you end up typing.

Layer changes, shift and unusual/complex keys do not get counted.
Navigation, arrow and mouse keys do not get counted. Auto-repeating
of keys does not affect the *character* count, therefore should be avoided
if you want to count in characters.

Making your own base layer(s)
=============================
You can insert your own `_DEF_BASE`, `_DEF_NSY` and/or `_ALT_BASE`, `_ALT_NSY`
BASE plus number/symbols layer pairs, integrate it nicely with the rest 
of the code, and re-define a special characters layer to go with it if
you want (etc). The idea is to make it easy to change the alphanumerical
keys, while leaving the modifiers, layer switch keys etc. the same. 
`YOUR_KEYMAP` stands for a name you choose.

First we will look at a simple keymap, without its own configuration
options or header file.

     ① Make a file named: `./base_YOUR_KEYMAP.c`), with at least 
       those two layers: _..._BASE and _..._NSY. It is probably best to
       copy one of the existing `./base_....c` files, and edit that.

     ② Add a #define to `./user_config.h`:
       #define BASE_YOUR_KEYMAP__DEF_BASE
       #define BASE_YOUR_KEYMAP__ALT_BASE
       Under the topic ‛Base layers’ there is a comment to help you.

     ③ Edit ./keymap.c to have your new file #included, using your just defined
       preprocessor element. Close to the other #includes is a comment there to
       help you. Look just under the line with this, in ./keymap.c:

       const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
       (…)
       // // ⬇ insert your ./base_YOUR_KEYMAP.c #include here:

       // # if defined(BASE_YOUR_KEYMAP__DEF_BASE) || defined(BASE_YOUR_KEYMAP__ALT_BASE)
       // #     include "./base_YOUR_KEYMAP.c" // Your Keymap.
       // # endif

Now you have integrated your base layers alternative. To compile it:

     ④ _Activate_ your #define BASES_YOUR_KEYMAP__DEF_BASE or 
       BASES_YOUR_KEYMAP__ALT_BASE in `./user_config.h`,
       _Remove_ any other base layers from being defined on the
       same spot _DEF_BASE or _ALT_BASE to prevent a conflict.

     ⑤ Check Pre-processing with:
       > gcc -E keymap.c | less

     ⑥ Compile and flash to your keyboard.

You can redefine any layer in your new `./base_YOUR_KEYMAP.c`
You can do that by setting one or more of the `BASESFILE_LAYER_...` defines in 
your own `./base_YOUR_KEYMAP.c` file. See near the top of an existing 
`./base_....c` file for clues.
`_ACC` in particular is a layer meant to augment a keymap with special 
characters for a given language/layout in the base layer(s). Perhaps you
want to redefine it, for example.

Example: Having done the above points ① ➡ ④ for a `./base_YOUR_KEYMAP.c` file. 
Let's say you re-arranged keys on `_ACC` to suit ... French.

     ⑦ In your `./base_YOUR_KEYMAP.c`:
       #define `BASESFILE_LAYER_ACC`
       The `_ACC` in ./keymap.c will now be ignored.

You can re-define `_ACC` in your own file. 

     ⑧ Copy an existing `_ACC` layer into `./base_YOUR_KEYMAP.c` 
       Edit it so that French characters like ‛Ç’ ‛«»’, ‛œ’, ‛æ’,
       ‛ô’, ‛é’ etc. are in positions that work best. You can look in
       `unicode_weurope.h` to find some Unicode points already defined.

     ⑨ Compile and flash to your keyboard.

Now we will look at a more complicated keymap, where you are also altering
preprocessor constants defined in `./user_config.h`. (Warning, perhaps this
is overkill … ;-)

Example: the `./base_numpad.c` has an option to entirely eviscerate the
`_PAD` layer, for convenience. (Why is this even useful ? Good question !
One reason could be that it can set up a default, so that anyone who chooses
this `./base_numpad.c` Base layer, automatically is eviscerating the `_PAD`
_common_ layer, without having to do anything else. On the downside, it
could be confusing that one option is configured in two places.)

Having done the above points ⑦ ➡ ⑧ as well, let's say for some reason you
need to reverse Left GUI and Right GUI.

      ⑨ Copy your User Configuration Block at the top of your `./base_YOUR_KEYMAP.c`
        and the GPL License, and place that in a new _header_ file: 
        `./base_YOUR_KEYMAP.h` 
    
      ① ⓪  Write the necessary code to set and unset the constant
           `SWITCH_GUIS` in your `./base_YOUR_KEYMAP.h` file You are encouraged
           to write code which overrides any setting in `./user_config.h, for
           those constants which you choose to affect, for simplicity sake. 
           (This is not a C programming manual, so it won't get into this.)
   
      ① ①  Look in `./user_config.h`, and #include your header file there, in
           a similar way as was done for your C code file. It should be just
           below the user configuration block, and has a template for you.
   
      ① ②  Compile, flash and test.
   
      ① ③  It would be nice to put a remark on the general preprocessor constants
           which you might be affecting, that your keymap could be affecting them.
           You would edit the ./user_config.h comments with a short one line notice,
           such as:
   
           *
           * ⚠ Note: ./base_YOUR_KEYMAP.h can overrides this setting, if compiled with that ‛Base’ layer.
           */

Putting your `*.h` header file in `./user_config.h` isn't strictly
necessary, unless you alter “general preprocessor constants”
defined in `./user_config` (not local constants for your keymap only).

Perhaps a separate header file is overkill. On the other hand, whatever
preprocessor logic is necessary after user configuration has been given,
can be handled in one place, if #included as suggested. It allows you
to override the settings in `./user_config.h` from your header file
(because it is #included immediately below those). If a user is playing with
keymaps Base compile choices, it could be convenient to play with
`./base_YOUR_KEYMAP.h` settings, have everything that could be relevant
close at hand, then forgetting about those settings once compiling
with another Base layer, and be able to return to it with previous
configuration already done.

You can also just #include your header file at the top of your 
`./base_YOUR_KEYMAP.h` file, if it does not touch anything else but your
local keymap.

Eviscerations
-------------

Cutting down the keymap reduces the firmware size, and helps reducing
mental clutter from having masses of symbols you might never want to use.

You can compile as a single layout. Define only a ‛Default’ base pair,
and set `MINIFAN_SINGLE_LAYOUT` (`./user_config.h`). The leds for the
base layers letters and numbers&symbols, will show up as they would for
the ‛Alternate’ layer in a dual layout compilation.

You can remove the layers `_ACC`, `_DRA` and/or `_BON` (see
`./user_config.h` around `REMOVE_ACC`). 

➡ If you remove `_ACC` and `_BON` *without* repurposing the key
which changes to the `_ACC` layer by not _activating_ one of the
provided #defines there, that key will become a good old Delete key
(which repeats).

You can remove a set of symbols from one or more of Unicode layers,
such as not having box drawing characters on `_BON`, or no sub-script
numbers on `_DRA`.


Trouble shooting
----------------
  • Flashing firmware

  When you flash your board, suddenly your Unicode doesn't work, or your
  leds seem to be broken. What seems to happen sometimes is that after
  flashing the value of a user option ends up in a different state than
  you expected.


  • Unicode

  Unicode is chaos: try going to `_RAR` layer, and hit the Unicode
  operating system buttons.


  • Leds

  Leds not working: try going to `_RAR` layer, and hit the key MLeds
  and SLeds, which switch Leds on/off.


  • Middle led

  Middle led not showing layer: you may have compiled it with speed
  measuring on at startup.


  • Weird layer jumping

  You weirdly end up on the `_PAD`, `_FUN` or some other layer while
  typing ? This is a typing mistake. You have to learn that unnecessary
  pressing of the Shift keys, which on most keyboards and in most 
  applications has no effect, now suddenly does have an effect.

  It should never activate to the layer, if you hit another key to get
  a capital letter. It will always go to a layer, if you hit it by itself.

  It can help to set `_PAD` in numerical mode, so that you will just type
  some numbers, rather than fly all over the place with arrows and 
  navigation. For the `_FUN` layer, you could put it in one stroke mode, to
  reduce the consequences of the mistake. After a while you will likely
  stop making the mistake.


  • Difficult/impossible key combinations ?

  An example of a difficult key combination is: the modifier Control, 
  Shift, or Alt, with media key “volume up” (or down, etc). It may 
  work to press and hold “Control” (which should communicate “Control
  depressed”), then activate `_RAR` layer with the hold key (which 
  communicates nothing to the computer attached to the keyboard), 
  press and let go “volume up” (which should communicate just that), let
  go of the `_RAR` layer (which again communicates nothing), let go of
  the Control key (which should communicate “Control released”).. 

  Since this keymap was written on one particular set up, it might be
  that you run into difficulty with rare key combinations (unknown
  to the author) which are sometimes used for keyboard shortcuts.
  If so, you could think of changing the source yourself, contacting the
  author, or the QMK help system. Perhaps we can work out a solution.

Why you want this layout
------------------------

☞  This layout seems easy to learn and predictable.

☞  The Dvorak/Qwerty layer (BASE) is an unaltered standard Dvorak/Qwerty
  layout, except what physically cannot fit (numbers, right pinky
  symbols). 

☞  Every time you have 0-9 enumerations / numbers, they are on the same
  fingers as a standard keyboard.

☞  The symbols normally reached by shifting a number, are also still on
  the same fingers.

☞  On all layers possible / needed the modifiers are in their usual spots.

☞  Because one often uses an F-key only once, the layer can switch back
  to BASE after an F-key is used.

☞  Because it is hard to touch more than 3 keys, there are modifier
  combination keys on `_FUN` layer for use with F-keys.

☞  The movement layer has a bunch of layout options, and allows for mouse
  use.

☞  The layer with Power buttons protects you from accidental keystrokes
  on the critical keys. 

☞  If you need working with Control/Shift/Alt and a pointing device in
  right hand, you can quickly get uncluttered such keys by tapping left shift.

☞  The accented layer makes it possible to set the keyboard in a mode
  on the computer side without dead-keys. Dead-keys slow typing down, and
  make some editors (like vi) hard to use.

☞  The first Unicode layer adds a fair amount of fun stuff to spice up 
  your writing. Write H₂O, 2⁷·⁰=128, ±8 °C, §2.1, 2 ³/₈", a note⁴, £ 6.²⁵
  etc.
        
☞  The second Unicode layer adds a proper dash — and French style
  quotations «»‹› and other stuff. ①  «Ça va bien», ②  5 × 3 ≠ 14,
  ③  .083% ÷ 2 ≈ 4‱ ➡  4.₁₅‱

                  ┏━━━━━━┓
                  ┃ test ┃
                ┅━╋━━━━━━┛
                  ┇ ④

☞  With the 'descramble' mode (Dvorak² Compile option), you never have
  to fear not being able to use your keyboard. Plug and play.

☞  Easy to create your own dual layout for letters / numbers.

☞  On average every key has more than 9 meanings (including upper/lower case).

☞  Speed and text size measuring.

☞  Because a 40% keyboard is small, you may be able take it where needed and
  not have your typing get confused by typing on something else. 

➡ Conclusion: most is as normal or has some logic to it to help you
  remember, a bunch is better than your normal keyboard, some things
  will just have to be learned. There is a lot more on it than on your
  normal keyboard, and you never have to leave the home row for it.


Use case
--------
  The use case this keymap was originally designed for and on: a PC
  with GNU/Debian/Linux (etc), secondary Linux laptop already set to
  Dvorak _hence 'descramble'_. Being able on the move to operate other
  operating systems owned by others _hence non-Linux Unicode modes._
  Editing in vim / websites etc. _hence no dead keys,_ programming
  (shell, C (like) languages) _hence decent access to basic symbols._
  Writing in Dutch _hence accented characters_. Using a tiling window
  manager _hence a GUI on base layer._ AltGr or Compose seemed difficult
  to configure / use _hence accented and unicode layers._ For use with 3D
  editing _hence a delete on base layer, Control, Alt, Shift on left edge
  and quick toggle access to `_PAD` or `_MOV` on left shift for faster
  modifiers and tab key._ Some input fields used have a text maximum,
  without showing a character or word count, _hence text size counting._


Todo
----
        … Support for more common layouts.

        … Support/testing for other keyboards. If this is to support
          keyboards other than 12×12×12×[8-12] and/or different leds,
          it seems best to isolate all Minivan layers in one subdirectory, 
          then copy/edit that to other subdirectories for those keyboards.


BUGS
----
  No real bugs known currently. Just some minor issues …

  The tilde ~ on the numbers-symbols layer should logically be reached on the second
  row without the need for _shift,_ however there seems to be a QMK limitation
  with this. No work around has been attempted as of yet. (It seems to be a minor issue;
  using shift for once seems OK.)

  `LCTL_T` `( KC_TAB )` is not seen as a blank by word counting, use as Control is not
  ignored in character counting. (This minor issue is ignored for now. Tab is not
  normally used in text writing.)

  The eviscerations may not have been worked out yet into the ultimate scrubbing of
  everything that may have become redundent, because it does complicate the code with
  a lot of #defines. Perhaps it should be done eventually, if there is an actual need.
  “Premature optimization is the root of all evil.” - Donald Knuth. 

  Only tested on Linux (FIXME).


Authors
-------
  This keymap.c was edited from the Minivan default, original LED
  support was copied/edited from ../jetpacktuxedo/ keymap. Thanks to 
  QMK support for their help. Written on the Minivan.

  Written by: Jos B. [contact](https://market.socialism.nl/author/ "get e-mail address there")

  _Personal note:_ This keymap came about because of a need for an efficient keymap. 
  Once the two variations of Dvorak where made, it seemed easy to add a Qwerty
  for those users for a dual layout keymap. Things got out of hand from there …

  You can let me know if you find any bugs / use problems, have improvements,
  a new `./base_...c/.md` keymap, or just if you like using it too 👍.

  Contributions to this key map:
      - …

