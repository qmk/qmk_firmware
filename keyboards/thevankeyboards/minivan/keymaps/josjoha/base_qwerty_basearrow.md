# Minifan layout

Compiled for: Qwerty with arrows on Base
========================================

This version of Qwerty puts arrows on Base, and assumes the 'arrow' hardware key.

You have to manually set *#define `MORE_KEY__ARROW`* in `./user_config.h`, 
When not compiled with ‛Arrow’ hardware key, Base will not contain ‛Down arrow’.
You do however not have to worry about what to set the additional hardware key to.
This will default to Down Arrow on Base.


Weighing the options
====================

     Summary: The regular Qwerty compile option probably provides superior arrow access.

This variation of Qwerty is not necessarily the recommended version
of Qwerty for a board with the additional ‛Arrow’ hardware key. Use
this compile option with caution, because this is a costly trade-off
for marginal benefits.

For all compile cases, this and regular Qwerty included: you already
have a hold key to the `_MOV` (movement) layer under what is colloqually
known as the ‛left space bar’, which leads to convenient arrow keys
in the home row, and there are Left and Right arrow keys on the Base layer
(non repeating).

Since regular Qwerty with the ‛Arrow’ key arrow cluster, also affords arrows
in the same spot, putting arrow legend keycaps there will be functional, without
the need to put arrows directly on the Base layer.

Putting directional arrow keys on the Base layer will cost you several keys on 
the Base layer: hold to layer `_RAR` (power, media, etc. layer), GUI, and ‛/?’. 

• The ‛/?’ key is displaced to the `_NSY` (numbers & symbols) layer, and is not 
  in the default spot for a Qwerty layout.

• The GUI key is lost. You could decide to also use the ‛south paw’/‛command’ 
  hardware key, which is a GUI by default. 

• Hold key to `_RAR` layer is lost. You can only reach `_RAR` layer using the
  right shift toggle, which is on a short timer.


Recommended strategy
====================

If you are a 10 fingers typist, look first if you can make things work
with regular Qwerty.  If you find that you are constantly using the
toggle to the `_MOV` layer to reach the arrow cluster at the right /
close-in corner of the board, you could start thinking about making
that faster by using this “Qwerty with arrows on Base” variety,
if the cost of loosing/displacing keys does not bother you.

If you are not a 10 finger typist, arrows on Base could be a better
option for you.


Going caveman with space age tools
==================================

Most people prefer mini keyboards, because you can leave your hands at the
home row. It is a faster and more certain way of typing. While on 100%
keyboards you may have to clumsily reach over for all kinds of keys,
including the arrow cluster, this is not something you would want to
replicate on a superior keyboard.

Don't use your precious 40% keyboard to dig holes in the ground, my man. 
100% keyboards are made for that job. That is why they are so big. 


Qwerty keymaps
--------------

──────────Qwerty───────────────

![Minivan layout Image BASEdef](http://socialism.nl/misc/minivan/minivan_base_layer_qwerty_basearrow_va.jpg)
Layer: `..._BASE`

![Minivan layout Image BASEdef](http://socialism.nl/misc/minivan/minivan_nsy_layer_qwerty_basearrow_va.jpg)
Layer: `..._NSY`

──────────in common────────────

(…)

For more about the other layers, see ➡ ![readme.md](./readme.md) ⬅

![Minivan illustration Overview layers by key, Qwerty arrows on Base](http://socialism.nl/misc/minivan/minivan-all-layers-clear-visualization-by-key_qwerty_basearrow_2000_va.jpg)

Layers (text)
=============

        ───────────────Qwerty─────────────────

     Layer _..._BASE (Letters). This is Qwerty with arrows on Base
                                                  | Right hand
         <pink2     <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pinky2>   // Keys by finger
         -o-                                     <|>                                    ... //-o- BASE access
         Esc        qQ    wW    eE    rR    tT    | yY    uU    iI    oO    pP         Bksp
         Tab+LCtl   aA    sS    dD    fF    gG    | hH    jJ    kK    lL    ;:           '"
         LSht+_PAD  zZ    xX    cC    vV    bB    | nN    mM    ,<    .>    Up    RSht+_FUN
             +_MOV⁵                               |                                   +_RAR⁶
     ---------------------------------------------------------------------------------------
     Left+LAlt Del;_ACC _..._NSY(_DRA)  Enter+_MOV| Space  _..._NSY(_DRA) Left    Right
               hold     hold₍₁,₂٭₎      hold      |        hold₍₁,₂٭₎                      // switch type
               hold₍₂₎  ^-┃-----------------------+--------^ ┃                          // ₁₎ both = _DRA
               ┗━━━_BON━━━╋┅───────────┄┄┄«or»┄┄┄─+─────────┅┛                          // ₂₎ both = _BON
     <1   ±    <2       <3              <4        | 4>     3>             2>   ±  1>    // Keys by number
          ^³                                                                   ^⁴   // Optional more keys
        (RGUI)                                                               (Down)

     ₁) Dual hold for _DRA, single hold for _..._NSY. Marked by: ^--…--^
     ₂) Hold key “<2” with either٭ key “<3” or “3>” for _BON, single hold “<2” for _ACC. Marked: ┗━━…━━┛
     ₃) 'South paw' hardware configuration. Configurable, default shown.
     ₄) 'Arrow' hardware configuration. Set to Down Arrow.
     ₃ ₄) There are two more optional hardware keys, to make it easier to compile for
          a 12x12x12x11 or 12x12x12x12 layouts.
     ₅) Left Shift when pressed with another key. Medium long: to toggle _PAD. Long: toggle _MOV.
     ₆) Right shift when pressed with another key. medium long: to toggle _FUN. Long: toggle _RAR.

Remarks: The left modifiers have a slight delay in combination with an outside pointer device (mouse, stylus).
It seems this will be difficult to fix, because it is spread over two devices. To avoid the
±0.2 second delay, activate a layer where the modifiers are direct (`_PAD`), using the layer toggle on left shift. 

The key with ';' (Del;`_ACC`) does not auto-repeat on double tap, like QMK normal layer-tap keys.
There is an uncluttered _Delete_ on `_PAD`.

Holding both `_DEF_NSY` keys left and right of the "split space bar" (enter, space) results in layer `_DRA`.

Holding either one of the just above mentioned `_DEF_NSY` layer keys (<3 and 3>), with the `_ACC` layer key
(on <2) results in layer `_BON`.


- - -


     Layer _..._NSY (Numbers and SYmbols). This fits the above Qwerty layer _..._BASE
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
              -*-                          <|>                                  //(toggle) Access on _FUN
     BASE     !     @     #     $     %     | ^     &     *     (    )       Del
     Tab+LCtl 1!    2@    3#    4$    5%    | 6^    7&    8*    9(   0)       /?
     -+LSht   [{    ]}    -_    \|    =+    | +     |     _     {     }  `~+RSht
                          ^^                              ^  // Only differences with normal version _..._NSY
     ---------------------------------------------------------------------------
     Left+LAlt ___   ___   Ent  | .   ___   LGUI  Right+RAlt
                     -*-       <|>    -*-                                         //(hold) Access on _..._BASE
       <1   ±  <2    <3    <4   | 4>  3>    2>  ± 1>  
            ^                                   ^
          (RGUI)                              (_MOV)



- - -
