# Minivan (Dvorak² or Qwerty+Dvorak)

A 40% keyboard made by https://thevankeyboards.com This Qwerty+Dvorak
keymap is for the default 12x12x12x8 arrangement (44 keys).

Qwerty + Dvorak
===============

This file details the compile version `#define QWERTY_DVORAK` which has a
Qwerty layout on the default (on startup), which can be switched to Dvorak.

To switch to Dvorak: go to the `_FUN` layer, and hit the upper/right key,
then return to BASE with upper/left key. To return to Qwerty, do the same.
Notice LED colors indicating layer.

This Qwerty + Dvorak compile version is a fair amount smaller than the
Dvorak² version (85% versus 99% of flash memory).

Layers:
-------

There are two layers different from the normal compile version: letters, 
and numbers/symbols.

                                Qwerty

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


                            
                                Dvorak

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


For the other layers, see [regular readme.md file](./readme.md)
Wherever that readme refers to 'descramble,' in this compile
version it would mean a shift into standard Dvorak, in place for
the Dvorak-descramble 'full' mode (right led indicator).
