# Minifan layout

Compiled for: Dvorak² 
=====================

This file details the compile version `#define BASE_DVORAK_DESCRAMBLE__ALT_BASE`
which has a special version of Dvorak so that you can type Dvorak on a computer
*already* set to do Dvorak layout re-mapping.

This can be useful on for example a laptop, for which the build-in
keyboard should to be in Dvorak.

Dvorak² keymaps
---------------

──────────Dvorak───────────────

![Minivan layout Image BASEdef-alt](http://socialism.nl/misc/minivan/minivan_base_layer_dvorak_ve.jpg)
Layer: `..._BASE`

![Minivan layout Image NSYdef-alt](http://socialism.nl/misc/minivan/minivan_nsy_layer_dvorak_vb.jpg)
Layer: `..._NSY`

──────────in common────────────

(…) 

For more about the other layers, see ➡ ![readme.md](./readme.md) ⬅

![Minivan illustration Overview layers by key, Dvorak](http://socialism.nl/misc/minivan/minivan-all-layers-clear-visualization-by-key_dvorak_2000_vh.jpg)

Layers (text)
=============
 
          Layer _ALT_BASE (Dvorak descramble mode for letters)
                                                  | Right hand
          <pink2    <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pinky2>    // Keys by finger
          -o-                                    <|>                                    ... // -o- BASE access
          Esc       '"    ,<    .>    pP    yY    | fF    gG    cC    rR    lL         Bksp
          Tab+LCtl  aA    oO    eE    uU    iI    | dD    hH    tT    nN    sS           -_
          LSht+_PAD ;:    qQ    jJ    kK    xX    | bB    mM    wW    vV    zZ    RSht+_FUN
              +_MOV⁵                              |                                   +_RAR⁶
     ---------------------------------------------------------------------------------------
     Left+LAlt Del;_ACC _ALT_NSY(_DRA)  Enter+_MOV| Space  _ALT_NSY(_DRA) RGUI    Right;_RAR 
               hold     hold₍₁,₂٭₎      hold      |        hold₍₁,₂٭₎             hold     // switch type
               hold₍₂₎  ^-┃-----------------------+--------^ ┃                          // ₁₎ both = _DRA
               ┗━━━━━━━━━━╋┅───────────┄┄┄«or»┄┄┄─+─────────┅┛                          // ₂₎ both = _BON
     <1   ±    <2       <3              <4        | 4>     3>             2>   ±  1>    // Keys by number
          ^³                                                                   ^⁴   // Optional more keys
        (LGUI)                                                               (_MOV)

     ₁) Dual hold for _DRA, single hold for _DEF_NSY. Marked by: ^--…--^
     ₂) Hold key “<2” with either٭ key “<3” or “3>” for _BON, single hold “<2” for _ACC. Marked: ┗━━…━━┛
     ₃) 'South paw' hardware configuration. Configurable, default shown.
     ₄) 'Arrow' hardware configuration  Configurable, default shown.
     ₃ ₄) There are two more optional hardware keys, to make it easier to compile for
          a 12x12x12x11 or 12x12x12x12 layouts.
     ₅) Left Shift when pressed with another key. Medium long: to toggle _PAD. Long: toggle _MOV.
     ₆) Right shift when pressed with another key. medium long: to toggle _FUN. Long: toggle _RAR.


     This layer input results in the same as normal Dvorak if computer side Dvorak remapping is occuring.
     Only shown what changes:

              '"    ,<    .>    pP    yY    | fF    gG    cC    rR    lL                 // row 4, result
                    oO    eE    uU    iI    | dD    hH    tT    nN    sS   -_            // row 3, result
              ;:    qQ    jJ    kK    xX    | bB          wW    vV    zZ                 // row 2, result
     -------------------------------------------------------------------------------
                        _ALT_NSY                           _ALT_NSY                              // row 1, result

     (Keys for 'aA', '\|' and 'mM' are the same in Dvorak and Qwerty.)

- - -
    
     Layer _ALT_NSY (Dvorak descramble mode for numbers-symbols)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
              -*-                          <|>                                  //(toggle) Access on _FUN
     BASE     !     @     #     $     %     | ^     &     *     (    )       Del
     Tab+LCtl 1!    2@    3#    4$    5%    | 6^    7&    8*    9(   0)  `~+RCtl
     -+LSht   -_    =+    [{    \|    ]}    | }     |     {     _     +  `~+RSht            // row 2, raw
     ---------------------------------------------------------------------------
                 Left+LAlt ___   ___   Ent  | .   ___   RGUI  Right+RAlt
                                 -*-       <|>    -*-                        //(hold) Access on _DEF_BASE
                   <1   ±  <2    <3    <4   | 4>  3>    2>  ± 1>  
                        ^                                   ^
                      (LGUI)                              (_MOV)

     This layer input results in the same as regular Dvorak _..._NSY layer, if computer side Dvorak remapping
     is occuring. Only shown what changes:

              [{    ]}    /?           =+   |   +         ?     {     }                  // row 2, result

- - -

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
  encoding selection). This more or less means there is one more Unicode
  encoding option than already standard in QMK: 'descrambled' version for 
  Linux (Shift-Control-U HEX) encoding, for use on a computer *already* set to
  Dvorak.

  To test it, (in Debian/Linux) go to a terminal in X and type (normal user)

        > setxkbmap -layout us -variant dvorak

  Undo:

        > setxkbmap -layout us

  Unicode on Windos operating system may require to install something special.


Key associations
----------------
Key placement associations between layers for Dvorak.

![Minivan layout Image associations](http://socialism.nl/misc/minivan/minivan-relationships_dvorak-descramble_1500_vd.jpg)

