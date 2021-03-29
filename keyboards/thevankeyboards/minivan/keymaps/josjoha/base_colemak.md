# Minifan layout

Compiled for: Colemak
=====================

This file details the compile version `#define BASE_COLEMAK__DEF_BASE, BASE_COLEMAK__ALT_BASE`.
This is a Colemak layout.

Control follows Unix logic here (left/center), not Colemak Backspace.

Colemak keymaps
---------------

──────────Colemak──────────────

![Minivan layout Image BASEdef](http://socialism.nl/misc/minivan/minivan_base_layer_colemak_ve.jpg)
Layer: `..._BASE`

![Minivan layout Image BASEdef](http://socialism.nl/misc/minivan/minivan_nsy_layer_qwerty_vb.jpg)
Layer: `..._NSY`

──────────in common────────────

(…)

For more about the other layers, see ➡ ![readme.md](./readme.md) ⬅

![Minivan illustration Overview layers by key, Colemak](http://socialism.nl/misc/minivan/minivan-all-layers-clear-visualization-by-key_colemak_2000_vh.jpg)

Layers (text)
=============

        ───────────────Colemak────────────────
     Layer _..._BASE (Letters). This is Colemak, except backspace/tab 
                                                  | Right hand
         <pink2     <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pinky2>   // Keys by finger
         -o-                                     <|>                                    ... //-o- BASE access
         Esc        qQ    wW    fF    pP    gG    | jJ    lL    uU    yY    ;:         Bksp
         Tab+LCtl   aA    rR    sS    tT    dD    | hH    nN    eE    iI    oO           '"
         LSht+_PAD  zZ    xX    cC    vV    bB    | kK    mM    ,<    .>    /?    RSht+_FUN 
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
     ₃) 'South paw' hardware configuration. Configurable, default shown.
     ₄) 'Arrow' hardware configuration  Configurable, default shown.
     ₃ ₄) There are two more optional hardware keys, to make it easier to compile for
          a 12x12x12x11 or 12x12x12x12 layouts.
     ₅) Left Shift when pressed with another key. Medium long: to toggle _PAD. Long: toggle _MOV.
     ₆) Right shift when pressed with another key. medium long: to toggle _FUN. Long: toggle _RAR.

Remarks: The left modifiers have a slight delay in combination with an outside pointer device (mouse, stylus).
It seems this will be difficult to fix, because it is spread over two devices. To avoid the
±0.2 second delay, activate a layer where the modifiers are direct (`_PAD`), using the layer toggle on left shift. 

The two keys with ';' (Del;`_ACC`, Right;`_RAR`) do not auto-repeat on double tap, like QMK normal layer-tap keys.
There is an uncluttered _Delete_ on `_PAD`, an uncluttered _Right_ arrow on the `_MOV` layer.

Holding both `_DEF_NSY` keys left and right of the "split space bar" (enter, space) results in layer `_DRA`.

Holding either one of the just above mentioned `_DEF_NSY` layer keys (<3 and 3>), with the `_ACC` layer key
(on <2) results in layer `_BON`.


- - -


     Layer _..._NSY (Numbers and SYmbols). (Same as Qwerty numbers layer.)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
              -*-                          <|>                                  //(toggle) Access on _FUN
     BASE     !     @     #     $     %     | ^     &     *     (    )       Del
     Tab+LCtl 1!    2@    3#    4$    5%    | 6^    7&    8*    9(   0)  `~+RCtl
     -+LSht   [{    ]}    -_    \|    =+    | +     |     _     {     }  `~+RSht // limitation prevents ~
                          ^^                              ^  // Only differences with Dvorak version _DEF_NSY
     ---------------------------------------------------------------------------
                 Left+LAlt ___   ___   Ent  | .   ___   RGUI  Right+RAlt
                                 -*-       <|>    -*-                 u      //(hold) Access on _DEF_BASE
                   <1   ±  <2    <3    <4   | 4>  3>    2>  ± 1>  
                        ^                                   ^
                      (LGUI)                              (_MOV)



- - -


