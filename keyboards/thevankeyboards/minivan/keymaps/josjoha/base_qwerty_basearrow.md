# Minifan layout

Compiled for: Qwerty with arrows on Base
========================================
This version of Qwerty puts arrows on Base, and assumes the 'arrow' hardware key.

You have to manually set *#define `MORE_KEY__ARROW`* in `./user_config.h`, 
to let compilation know you have that additional hardware key.

If not compiled with ‛Arrow’ hardware key, Base will not contain ‛Down arrow’.
You do not have to worry about what to set the additional hardware key to, on
the Base layer. This will be set to Down Arrow, to complete that arrow cluster.

Is arrows on Base efficient ?
=============================
This variation of Qwerty is not necessarily the recommended version of
Qwerty for a board with the additional ‛Arrow’ hardware key.
The regular Qwerty compile option can provide good arrow access. 

Putting directional arrow keys on the Base layer will cost you several
keys on the Base layer: hold to layer `_RAR` (power, media, etc. layer),
GUI, and ‛/?’.

• The ‛/?’ key is displaced to the `_NSY` (numbers & symbols) layer, and is not 
  in the default spot for a Qwerty layout.

• The GUI key is lost. You could decide to also use the ‛south paw’/‛command’ 
  hardware key, which is a GUI by default. 

• Hold key to `_RAR` layer is lost. You can only reach `_RAR` layer using the
  right shift toggle, which is on a short timer.


Have it both ways
=================
You could compile regular Qwerty on one of the Base pairs (‛Default’ or 
‛Alternate’), and Qwerty _with Arrows on Base_ on the other. That way
you can switch to see what works for you. You could leave it like
that, and choose what you want depending on what you are doing. 

Dual layout combination with Qwerty Base Arrow
==============================================
The option `QWERTY_BASEARROW_HARMONIZE` in `./base_qwerty_basearrow.h` is set
by default, causing the key ‛/?’ in the _regular_ Qwerty layout to _also_ be
located in the same spot as in this ‛Qwerty with Arrows on Base’ layout. 

See also: ![./base_qwerty_basearrow.h](./base_qwerty_basearrow.h).
See also: ![./base_qwerty.md](./base_qwerty.md) for the reason behind this.


Qwerty keymaps
--------------

──────────Qwerty───────────────

![Minivan layout Image BASEdef](http://socialism.nl/misc/minivan/minivan_base_layer_qwerty_basearrow_va.jpg)
Layer: `..._BASE`

![Minivan layout Image BASEdef](http://socialism.nl/misc/minivan/minivan_nsy_layer_qwerty_basearrow_vb.jpg)
Layer: `..._NSY`

──────────in common────────────

(…)

For more about the other layers, see ➡ ![readme.md](./readme.md) ⬅

![Minivan illustration Overview layers by key, Qwerty arrows on Base](http://socialism.nl/misc/minivan/minivan-all-layers-clear-visualization-by-key_qwerty_basearrow_2000_vj.jpg)

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
     -+LSht   [{    ]}    -_    \|    =+    | +     |     _     {     }   ~+RSht // See _BON for ‛`’
                          ^^                              ^  // Only differences with normal version _..._NSY
     ---------------------------------------------------------------------------
     Left+LAlt ___   ___   Ent  | .   ___   LGUI  Right+RAlt
                     -*-       <|>    -*-                                         //(hold) Access on _..._BASE
       <1   ±  <2    <3    <4   | 4>  3>    2>  ± 1>  
            ^                                   ^
          (RGUI)                              (_MOV)



- - -
