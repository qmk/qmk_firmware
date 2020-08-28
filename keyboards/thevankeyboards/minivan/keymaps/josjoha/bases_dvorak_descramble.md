# Minifan layout

Compiled for: Dvorak² 
=====================

This file details the compile version `#define BASES_DVORAK_DESCRAMBLE`
which has a Dvorak layout, and a special version of Dvorak so that you can
type Dvorak on a computer *already* set to do Dvorak layout re-mapping.

This can be useful on for example a laptop, for which the build-in
keyboard should to be in Dvorak. An external keyboard which normally
types Dvorak, will not yield Dvorak in this case, unless you reconfigure
something on your computer.

With *this* Dvorak² keymap, you can type both normally in Dvorak,
plus by activating its ‛descramble’ mode (see Chapter below) you
can directly type on a computer already set to Dvorak.

Dvorak² keymaps
---------------

──────────Dvorak───────────────

![Minivan layout Image BASEdef-alt](http://socialism.nl/misc/minivan/minivan_base_layer_dvorak_va.jpg)
Layer: `DEF&ALT_BASE`

![Minivan layout Image NSYdef-alt](http://socialism.nl/misc/minivan/minivan_nsy_layer_dvorak_va.jpg)
Layer: `DEF&ALT_NSY`

──────────in common────────────

(…) 

For the other layers, see ➡ ![readme.md](./readme.md) ⬅

Layers (text)
=============
 
         Layer _DEF_BASE (LeTteRs, standard Dvorak)
                                                  | Right hand
         <pink2     <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pinky2>   // Keys by finger
         -o-                                     <|>                                    ... //-o- BASE access
         Esc        '"    ,<    .>    pP    yY    | fF    gG    cC    rR    lL         Bksp
         Tab+LCtl   aA    oO    eE    uU    iI    | dD    hH    tT    nN    sS           -_
         LSht+_PAD  ;:    qQ    jJ    kK    xX    | bB    mM    wW    vV    zZ    RSht+_FUN⁶
             +_MOV⁵                               |
     ---------------------------------------------------------------------------------------
     Left+LAlt Del;_ACC _DEF_NSY(_DRA)  Enter+_MOV| Space  _DEF_NSY(_DRA) LGUI    Right;_RAR 
               hold     hold₍₁,₂٭₎      hold      |        hold₍₁,₂٭₎             hold     // switch type
               hold₍₂₎  ^-┃-----------------------+--------^ ┃                          // ₁₎ both = _DRA
               ┗━━━_BON━━━╋┅───────────┄┄┄«or»┄┄┄─+─────────┅┛                          // ₂₎ both = _BON
     <1   ±    <2       <3              <4        | 4>     3>             2>   ±  1>    // Keys by number
          ^³                                                                   ^⁴   // Optional more keys
     
     ₁) Dual hold for _DRA, single hold for _DEF_NSY. Marked by: ^--…--^
     ₂) Hold key “<2” with either٭ key “<3” or “3>” for _BON, single hold “<2” for _ACC. Marked: ┗━━…━━┛
     ³) 'South paw' hardware configuration 
     ⁴) 'Arrow' hardware configuration 
     ³ ⁴) There are two more optional hardware keys, to make it easier to compile for
          a 12x12x12x11 or 12x12x12x12 layouts.
     ⁵) Left Shift when pressed with another key. Medium long: to toggle _PAD. Long: toggle _MOV.
     ⁶) Right shift when pressed with another key, otherwise toggle to _FUN.

Remarks: The left modifiers have a slight delay in combination with an outside pointer device (mouse, stylus).
It seems this will be difficult to fix, because it is spread over two devices. To avoid the
±0.2 second delay, activate a layer where the modifiers are direct (`_PAD`), using the layer toggle on left shift. 

The two keys with ';' (Del;`_ACC`, Right;`_RAR`) do not auto-repeat on double tap, like QMK normal layer-tap keys.
There is an uncluttered _Delete_ on `_PAD`, an uncluttered _Right_ arrow on the `_MOV` layer.

Holding both `_DEF_NSY` keys left and right of the "split space bar" (enter, space) results in layer `_DRA`.

Holding either one of the just above mentioned `_DEF_NSY` layer keys (<3 and 3>), with the `_ACC` layer key
(on <2) results in layer `_BON`.

- - -

     Layer _DEF_NSY (Numbers and SYmbols)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
              -*-                          <|>                                  //(toggle) Access on _FUN
     BASE     !     @     #     $     %     | ^     &     *     (    )       Del
     Tab+LCtl 1!    2@    3#    4$    5%    | 6^    7&    8*    9(   0)  `~+RCtl
     -+LSht   [{    ]}    /?    \|    =+    | +     |     ?     {     }  `~+RSht // limitation prevents ~
     ---------------------------------------------------------------------------
                 Left+LAlt ___   ___   Ent  | .   ___   LGUI  Right+RAlt
                                 -*-       <|>    -*-                        //(hold) Access on _DEF_BASE
                   <1   ±  <2    <3    <4   | 4>  3>    2>  ± 1>  

- - -

As a user you don't need to know this layer, because the output is the same as `_DEF_BASE`

          Layer _ALT_BASE (Dvorak descramble mode for letters)
                                                  | Right hand
          <pink2    <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pinky2>    // Keys by finger
          -o-                                    <|>                                    ... // -o- BASE access
          Esc       '"    ,<    .>    pP    yY    | fF    gG    cC    rR    lL         Bksp
          Tab+LCtl  aA    oO    eE    uU    iI    | dD    hH    tT    nN    sS           -_
          LSht+_PAD ;:    qQ    jJ    kK    xX    | bB    mM    wW    vV    zZ    RSht+_FUN   // _FUN _MOV tap
              +_MOV⁵                              |
     ---------------------------------------------------------------------------------------
     Left+LAlt Del;_ACC _ALT_NSY(_DRA)  Enter+_MOV| Space  _ALT_NSY(_DRA) LGUI    Right;_RAR 
               hold     hold₍₁,₂٭₎      hold      |        hold₍₁,₂٭₎             hold     // switch type
               hold₍₂₎  ^-┃-----------------------+--------^ ┃                          // ₁₎ both = _DRA
               ┗━━━━━━━━━━╋┅───────────┄┄┄«or»┄┄┄─+─────────┅┛                          // ₂₎ both = _BON
     <1   ±    <2       <3              <4        | 4>     3>             2>   ±  1>    // Keys by number
          ^³                                                                   ^⁴   // Optional more keys
     (See `_DEF_BASE` for more information. It is almost the same except for letter placement.)

     _ALT_BASE input results in the same as _DEF_BASE with computer side Dvorak remapping. Only shown what changes:

              '"    ,<    .>    pP    yY    | fF    gG    cC    rR    lL                 // row 4, result
                    oO    eE    uU    iI    | dD    hH    tT    nN    sS   -_            // row 3, result
              ;:    qQ    jJ    kK    xX    | bB          wW    vV    zZ                 // row 2, result
     -------------------------------------------------------------------------------
                        _ALT_NSY                           _ALT_NSY                              // row 1, result

     (Keys for 'aA', '\|' and 'mM' are the same in Dvorak and Qwerty.)

Remarks. This layer is seamlessly activated with 'descramble,' see `_DEF_BASE` (works the same).

- - -
    
As a user you don't need to know this layer, because the output is the same as `_DEF_NSY`

     Layer _ALT_NSY (Dvorak descramble mode for numbers-symbols)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
              -*-                          <|>                                  //(toggle) Access on _FUN
     BASE     !     @     #     $     %     | ^     &     *     (    )       Del
     Tab+LCtl 1!    2@    3#    4$    5%    | 6^    7&    8*    9(   0)  `~+RCtl
     -+LSht   -_    =+    [{    \|    ]}    | }     |     {     _     +  `~+RSht            // row 2, raw
     ---------------------------------------------------------------------------
                 Left+LAlt ___   ___   Ent  | .   ___   LGUI  Right+RAlt
                                 -*-       <|>    -*-                        //(hold) Access on _DEF_BASE
                   <1   ±  <2    <3    <4   | 4>  3>    2>  ± 1>  

     _ALT_NSY input results in the same as _DEF_NSY with computer side Dvorak remapping. Only shown what changes:

              [{    ]}    /?           =+   |   +         ?     {     }                  // row 2, result

Remarks. This layer is seamlessly activated with 'descramble' (alternate BASE)

- - -

For the other layers, see ➡ ![readme.md](./readme.md) ⬅

Special feature: 'Descramble' mode
==================================

![Minivan descramble Dvorak](http://socialism.nl/misc/minivan/minivan_descramble.jpg)

  This is an option to take care of typing normally on a computer already
  set to Dvorak ('descramble' mode.)  

  Activation: go to `_RAR` layer, than touch what is space bar on the BASE layer
  (the key just right from the middle on the first row). This cycles through the modes.

      ⮚ When the left led is white: normal mode.
      ⮚ Right led white: full descramble mode (Linux descrambled Unicode input).
      ⮚ Middle led white: half descramble mode, with normal Unicode input system.

  With the middle led set to white, you can take advantage of a Unicode
  input mode that works on your system, if it is the same when the
  computer is set to Dvorak or not (see `_RAR` layer for Unicode input
  encoding selection). (The speed measurement middle led use is overridden
  by the `_RAR` layer.) This more or less means there is one more Unicode
  encoding option than already standard in QMK: 'descrambled' version for 
  Linux (Shift-Control-U HEX) encoding, for use on a computer *already* set to
  Dvorak.

  To test it, (in Debian/Linux) go to a terminal in X and type (normal user)

        > setxkbmap -layout us -variant dvorak

  Undo:

        > setxkbmap -layout us

  Unicode on Windos may require to install something special.


Key associations
----------------
Key placement associations between layers for Dvorak.

![Minivan layout Image associations](http://socialism.nl/misc/minivan/minivan-relationships_dvorak-descramble_1500_va.jpg)

