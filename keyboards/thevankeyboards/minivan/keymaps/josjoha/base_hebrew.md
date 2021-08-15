# Minifan layout

Compiled for: Hebrew
====================

This file details the compile version `#define BASE_HEBREW__DEF_BASE,
BASE_HEBREW__ALT_BASE`. This is a basic Hebrew layout, without niqqud.

Only the most common symbols are implemented. 
Niqqud are not implemented. 
Hebrew symbols are all done in Unicode.
This means it is not a “normal, common”
hebrew keyboard, because such keyboards likely use computer side recoding.
This is still a US language keyboard (with Unicode apabilities), in terms
of how the computer sees it.

See also ![./readme.md](./readme.md) chapter 7 _Language support_.

Design
======

The design is make it work easily with a Latin layer (Qwerty, Dvorak, etc),
together as a dual layout system. For this reason the common writing symbols
which tend to be present on the letters base layer, are kept as much as
possible in the same locations.

      '",<.>-_?/;:

Within that framework, the hebrew letters are positioned according to
the standard keyboard in Israel. When there is a conflict between these
two objectives, the hebrew letter which conflicts with a symbol is moved
to whatever open space there might be.

The hebrew alphabet has 27 symbols. The additional letter compared to Latin
(26 letters) is resolved by combining a letter with the symbol “:” on shift.
This looses the symbol “;”, which is not present on some basic hebrew layouts
either.

In all cases the hebrew layout variations will closely resemble the
standard Israeli hebrew layout. This is not about a phonetic re-ordering
to Latin letter sounds. The goal is to keep the common symbols on the
same place, to avoid typing errors when switching layouts.

Parenthesis direction seems to be dealt with at the computer side, depending
on the surrounding symbols. The keyboard is printing these symbols unchanged
from what they are in standard Latin layouts, and are represented that way
in the manual. This means for example you see '(' in the manual under the
ring-finger, this is also what the keyboard is printing, however the computer
could change that into ')' depending on the language direction of the surrounding
characters (at least it does so on GNU/Debian/Linux). This can affect: 

      (){}[]<>
      

Options
=======

You can compile the hebrew to harmonize the punctuation symbols with either
Dvorak or Qwerty. See the configuration file ![./base_hebrew.h](./base_hebrew.h)

Israeli Hebrew
-------------- 
As close to a simple standard hebrew layout as possible.
A little larger than the other options.

Dvorak with Hebrew
------------------
The letter ק gets displaced from the standard hebrew layout.

Qwerty with Hebrew
------------------
The letters ת, ץ get displaced from the standard hebrew layout.

Qwerty derivatives with Hebrew
------------------------------
It is adviced to use Qwerty with Hebrew in this case, and adjust by hand
coding if needed.  “Workman” should harmonize the same as Qwerty.
Colemak displaces the “;:” key relative to Qwerty, therefore you may
like to change the “:” shifted symbol (by hand). The obscurity of this
use case gets extreme, there will not be options for this.

Flash memory cost
-----------------

This layout adds several dozen new Unicode symbols, which takes up a certain
amount of additional space in keyboard memory. If you end up going over
the limit, you may need to change your compilation software setup, and/or
you can look into the “Eviscerations” chapter to cut away other Unicode
symbols.

Hebrew keymaps
--------------

──────────Hebrew───────────────

![Minivan layout Image BASEdef-alt](http://socialism.nl/misc/minivan/minivan_base_layer_hebrew_ve.jpg)
Layer: `..._BASE`

![Minivan layout Image NSYdef-alt](http://socialism.nl/misc/minivan/minivan_nsy_layer_hebrew_ve.jpg)
Layer: `..._NSY`

──────────in common────────────

(…) 

For more about the other layers, see ➡ ![readme.md](./readme.md) ⬅

![Minivan illustration Overview layers by key, Hebrew](http://socialism.nl/misc/minivan/minivan-all-layers-clear-visualization-by-key_hebrew_2000_vi.jpg)

Layers (text)
=============

                                            HEBREW_ISRAEL
                                                  | Right hand
         <pink2     <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pinky2>   // Keys by finger
         -o-                                     <|>                                    ... //-o- BASE access
         Escxxxxxxxx/;xxxx׳xxxxxקxxxxxרxxxxxאxxxxx|xטxxxxxוxxxxxןxxxxxםxxxxxפxxxxxxxxxxBksp
         Tab+LCtlxxxשxxxxxדxxxxxג/RLMxכx₪xxxעxxxxx|xיxxxxxחxxxxxל/LRMxךxxxxxף:xxxxxxxxxxx,״ //Right-Left-Mark
         LSht+_PADxxזxxxxxסxxxxxבxxxxxהxxxxxנxxxxx|xמxxxxxצxxxxxת<xxxxץ>xxxx.?xxxxRSht+_FUN //<>os side flip?
             +_MOV⁵                               |                                   +_RAR⁶
     ---------------------------------------------------------------------------------------
 
                                            HEBREW_QWERTY 
                                                  | Right hand
         <pink2     <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pinky2>   // Keys by finger
         -o-                                     <|>                                    ... //-o- BASE access
         Escxxxxxxxxת•xxxxץ•xxxxקxxxxxרxxxxxאxxxxx|xטxxxxxוxxxxxןxxxxxםx׳xxxפx״xxxxxxxxBksp
         Tab+LCtlxxxשxxxxxדxxxxxג/RLMxכx₪xxxעxxxxx|xיxxxxxחxxxxxל/LRMxךxxxxxף:xxxxxxxxxxx'" //Right-Left-Mark
         LSht+_PADxxזxxxxxסxxxxxבxxxxxהxxxxxנxxxxx|xמxxxxxצxxxxx,<xxxx.>xxxx/?xxxxRSht+_FUN
             +_MOV⁵                               |                                   +_RAR⁶
     ---------------------------------------------------------------------------------------
         (…)

                                            HEBREW_DVORAK
         Layer _..._BASE (LeTteRs, standard Hebrew)
                                                  | Right hand
         <pink2     <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pinky2>   // Keys by finger
         -o-                                     <|>                                    ... //-o- BASE access
         Escxxxxxxxx'"xxxx,<xxxx.>xxxxרxxxxxאxxxxx|xטxxxxxוxxxxxןxxxxxםx׳xxxפx״xxxxxxxxBksp
         Tab+LCtlxxxשxxxxxדxxxxxג/RLMxכx₪xxxעxxxxx|xיxxxxxחxxxxxל/LRMxךxxxxxףxxxxxxxxxxxxx־ //Right/Left-Mark
         LSht+_PADxxז:xxxxסxxxxxבxxxxxהxxxxxנxxxxx|xמxxxxxצxxxxxתxxxxxץxxxxxק•xxxxRSht+_FUN
             +_MOV⁵                               |                                   +_RAR⁶
     ---------------------------------------------------------------------------------------
     Left+LAlt Del;_ACC _DEF_NSY(_DRA)  Enter+_MOV| Space  _DEF_NSY(_DRA) RGUI    Right;_RAR 
               hold     hold₍₁,₂٭₎      hold      |        hold₍₁,₂٭₎             hold     // switch type
               hold₍₂₎  ^-┃-----------------------+--------^ ┃                          // ₁₎ both = _DRA
               ┗━━━_BON━━━╋┅───────────┄┄┄«or»┄┄┄─+─────────┅┛                          // ₂₎ both = _BON
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
     ⁷) Letters marked with • are displaced from standard hebrew layout.

Remarks: The left modifiers have a slight delay in combination with an outside pointer device (mouse, stylus).
It seems this will be difficult to fix, because it is spread over two devices. To avoid the
±0.2 second delay, activate a layer where the modifiers are direct (`_PAD`), using the layer toggle on left shift. 

The two keys with ';' (Del;`_ACC`, Right;`_RAR`) do not auto-repeat on double tap, like QMK normal layer-tap keys.
There is an uncluttered _Delete_ on `_PAD`, an uncluttered _Right_ arrow on the `_MOV` layer.

Holding both `_DEF_NSY` keys left and right of the "split space bar" (enter, space) results in layer `_DRA`.

Holding either one of the just above mentioned `_DEF_NSY` layer keys (<3 and 3>), with the `_ACC` layer key
(on <2) results in layer `_BON`.

(The `x` around the letters is to prevent certain display systems to change the direction of letters.)
- - -

     Layer _..._NSY (Numbers and SYmbols)
    
                                      HEBREW_ISRAEL & HEBREW_QWERTY (_ becomes ־ Maqaf)
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
              -*-                          <|>                                  //(toggle) Access on _FUN
     BASExxxxx!xxxxx@xxxxx#xxxxx$xxxxx%xxxxx|x^xxxxx&xxxxx*xxxxx(xxxx)xxxxxxxDel
     Tab+LCtlx1!xxxx2@xxxx3#xxxx4$xxxx5%xxxx|x6^xxxx7&xxxx8*xxxx9(xxx0)xx`~+RCtl
     -+LShtxxx[{xxxx]}xxxx-_xxxx\|xxxx=+xxxx|x+xxxxx|xxxxx־xxxxx{xxxxx}xxx~+RSht
                                                          ^                       // Only difference with Qwerty
     ---------------------------------------------------------------------------
                 Left+LAlt ___   ___   Ent  | .   ___   RGUI  Right+RAlt
                                 -*-       <|>    -*-                        //(hold) Access on _DEF_BASE
                   <1   ±  <2    <3    <4   | 4>  3>    2>  ± 1>  
                        ^                                   ^
                      (LGUI)                              (_MOV)


                                      HEBREW_DVORAK (Same as standard Dvorak)
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
              -*-                          <|>                                  //(toggle) Access on _FUN
     BASE     !     @     #     $     %     | ^     &     *     (    )       Del
     Tab+LCtl 1!    2@    3#    4$    5%    | 6^    7&    8*    9(   0)  `~+RCtl
     -+LSht   [{    ]}    /?    \|    =+    | +     |     ?     {     }   ~+RSht 
     ---------------------------------------------------------------------------
     (…)
- - -
