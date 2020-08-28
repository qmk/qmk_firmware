/*
 * License (GPL):
  
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

 * Author: © 2020 by Jos Boersema
 *
 */

// --------------------------------------v---------------------------------------
//                                 Configuration:
// --------------------------------------v---------------------------------------

        /*                            Redefine a layer in this file
         *
         * _Activate_ one or more of the below BASESFILE_LAYER_..., to redefine the layer
         * in this file. The version in ./keymap.c will be ignored. Keep in mind to use
         * transparent keys (_______) for “hold” layer switch keys on the BASE map, for
         * your new layer.
         */
// #define BASESFILE_LAYER_ACC 
// #define BASESFILE_LAYER_DRA 
// #define BASESFILE_LAYER_BON 
// #define BASESFILE_LAYER_PAD 
// #define BASESFILE_LAYER_MOV 
// #define BASESFILE_LAYER_RAR 
// #define BASESFILE_LAYER_FUN 


// --------------------------------------^---------------------------------------
//            Below here no more comfortable configuration options.....
// --------------------------------------^---------------------------------------


        /*  ⬇ */

    /* Layer _DEF_BASE: default BASE layer (Dvorak)
     *
     * - Dual use keys create a delay in the key (tap/hold keys), therefore
     *   space is not dual use (most used key), neither is hyphen.
     */ 

    [ _DEF_BASE ] = LAYOUT_redefined (

/*
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
     ⁶) Right shift when pressed with another key. Held medium long: toggle to _FUN.
*/
//
//      <pink2            , <pinky  , <ring   , <middl , <indx, <ind|, indx>, inde>, midd>, ring>, pink>, pink2>        ,
//      -*!-              ,         ,         ,        ,      ,    <|,>     ,      ,      ,      ,      ,               ,
        KC_ESC            , KC_QUOT , KC_COMM , KC_DOT , KC_P , KC_Y , KC_F , KC_G , KC_C , KC_R , KC_L , KC_BSPC       ,
        LCTL_T ( KC_TAB ) , KC_A    , KC_O    , KC_E   , KC_U , KC_I , KC_D , KC_H , KC_T , KC_N , KC_S , KC_MINS       ,
        CHOLTAP_LSHFT     , KC_SCLN , KC_Q    , KC_J   , KC_K , KC_X , KC_B , KC_M , KC_W , KC_V , KC_Z , CHOLTAP_RSHFT ,
//      -----------------------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT ) 

# ifdef TRANSMINIVAN_LEFTSIDE
                           , MO ( _PAD )
# endif

# ifdef MORE_KEY__COMMAND
                           , MORE_key1_BASE  
# endif

                           , CHOLTAP_ACCE , DUO_HOLD , LT__MOV__KC_ENT , KC_SPC , DUO_HOLD , KC__YGUI

# ifdef TRANSMINIVAN_RIGHTSIDE
                                                                                                      , MO ( _FUN )
# endif

# ifdef MORE_KEY__ARROW
                                                                                                      , MORE_key2  
# endif

                                                                                                      , CHOLTAP_LAYR
//                         ,              ,          ,               <|,>       ,          ,          ,
//      <1           ±  ±  , <2           , <3       , <4             |, 4>     , 3>       , 2>       , ±  ±  1>

                      ),

        /* ⬆⬇ */

    /* Layers _ALT_BASE, _ALT_NSY: Descramble basic layers if the computer itself is
     *                  applying Dvorak remapping.
     *
     *          When a computer is already set to Dvorak, connecting a
     *          keyboard which is natively Dvorak results in garbage.
     *          The computer side normal keycodes to Dvorak remapping goes
     *          on top of the wrong input, resulting in the following being
     *          effective:
     *
     *          _DEF_BASE layer:        |
     *          Esc  -  w  v  l  f   u  i  j  p  n  Bspc
     *          Tab  a  r  .  g  c   e  d  y  b  o  [
     *          Sht  s  '  h  t  q   x  m  ,  k  ;  Sht
     *                     Enter  Space
     *          _DEF_NSY layer:        |
     *          _DEF_BASE !  @  #  $  %   ^  &  *  (  )  Bspc
     *          [    1  2  3  4  5   \  ]  z  /  =  `
     *          Sht  0  9  8  7  6   |  }  Z  ?  +  `
     *                     Enter  Space
     *
     *          _ACC layer:        |
     *          <just semi-random character strings>
     *
     *          _DRA, _BON: same as _ACC: garbage.
     *
     *          To solve this results in the strange layout given below.
     *          The result is close to a Qwerty layout. It will not be ideal
     *          for Qwerty typers because the symbols are not arranged that
     *          well.
     */ 


    /* Layer _ALT_BASE: Descrambled _DEF_BASE layer for a computer already set to Dvorak (see above).
     *           It is a copy of _DEF_BASE, with moved around stuff, and points to _ALT_NSY instead
     *           of _DEF_NSY, because that too has some descrambled symbols. The rest is the same.
     *
     */

    [ _ALT_BASE ] = LAYOUT_redefined (

/*
     Layer _ALT_BASE (Dvorak descramble mode for letters, end result shown)
                                                  | Right hand
         <pink2     <pinky<ring <middl<index<indx2| indx2>index>middl>ring> pinky>pinky2>   // Keys by finger
         -o-                                     <|>                                    ... //-o- BASE access
         Esc        '"    ,<    .>    pP    yY    | fF    gG    cC    rR    lL         Bksp
         Tab+LCtl   aA    oO    eE    uU    iI    | dD    hH    tT    nN    sS           -_
         LSht+_PAD  ;:    qQ    jJ    kK    xX    | bB    mM    wW    vV    zZ    RSht+_FUN  // _FUN _MOV tap
             +_MOV⁵                               |
     ---------------------------------------------------------------------------------------
     Left+LAlt Del;_ACC _ALT_NSY(_DRA)  Enter+_MOV| Space  _ALT_NSY(_DRA) LGUI    Right;_RAR 
               hold     hold₍₁,₂٭₎      hold      |        hold₍₁,₂٭₎             hold     // switch type
               hold₍₂₎  ^-┃-----------------------+--------^ ┃                          // ₁₎ both = _DRA
               ┗━━━━━━━━━━╋┅───────────┄┄┄«or»┄┄┄─+─────────┅┛                          // ₂₎ both = _BON
     <1   ±    <2       <3              <4        | 4>     3>             2>   ±  1>    // Keys by number
          ^³                                                                   ^⁴   // Optional more keys


     _ALT_BASE input results in the same as _DEF_BASE with computer side Dvorak remapping. Only shown what changes:

              '"    ,<    .>    pP    yY    | fF    gG    cC    rR    lL                 // row 4, result
                    oO    eE    uU    iI    | dD    hH    tT    nN    sS   -_            // row 3, result
              ;:    qQ    jJ    kK    xX    | bB          wW    vV    zZ                 // row 2, result
     ---------------------------------------------------------------------------------------
                        _ALT_NSY                           _ALT_NSY                              // row 1, result

     (Keys for 'aA', '\|' and 'mM' are the same in Dvorak and Qwerty.)

 */
//                                                   
//
//      <pink2            , <pink, <ring, <midd, <indx, <ind|, indx>, inde>, middle> , ring>  , pink>   , pink2>        ,
//      -*-               ,      ,      ,      ,      ,    <|,>     ,      ,         ,        ,         , -!-           ,
        KC_ESC            , KC_Q , KC_W , KC_E , KC_R , KC_T , KC_Y , KC_U , KC_I    , KC_O   , KC_P    , KC_BSPC       ,
        LCTL_T ( KC_TAB ) , KC_A , KC_S , KC_D , KC_F , KC_G , KC_H , KC_J , KC_K    , KC_L   , KC_SCLN , KC_QUOT       ,
        CHOLTAP_LSHFT     , KC_Z , KC_X , KC_C , KC_V , KC_B , KC_N , KC_M , KC_COMM , KC_DOT , KC_SLSH , CHOLTAP_RSHFT ,
//      -----------------------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT )

# ifdef TRANSMINIVAN_LEFTSIDE
                           , MO ( _PAD )
# endif

# ifdef MORE_KEY__COMMAND
                           , MORE_key1_BASE
# endif

                           , CHOLTAP_ACCE , DUO_HOLD , LT__MOV__KC_ENT , KC_SPC , DUO_HOLD , KC__YGUI

# ifdef TRANSMINIVAN_RIGHTSIDE
                                                                                                      , MO ( _FUN )
# endif

# ifdef MORE_KEY__ARROW
                                                                                                      , MORE_key2  
# endif

                                                                                                      , CHOLTAP_LAYR
//                         ,              ,          ,               <|,>       ,          ,          ,
//      <1           ±  ±  , <2           , <3       , <4             |, 4>     , 3>       , 2>       , ±  ±  1>

                      ),

        /* ⬆⬇ */

    /* Layer _DEF_NSY: Numbers and symbols.
     *          Off hand Number input (-.Bksp ent (shft)tab).
     */
    // KC_TILD does not work there, because of a limitation with shifted keys (nov 2019).

    [ _DEF_NSY ] = LAYOUT_redefined (

/*
     Layer _DEF_NSY (Numbers and SYmbols)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
              -*-                          <|>                                  //(toggle) Access on _FUN
     BASE     !     @     #     $     %     | ^     &     *     (    )       Del
     Tab+LCtl 1!    2@    3#    4$    5%    | 6^    7&    8*    9(   0)  `~+RCtl
     -+LSht   [{    ]}    /?    \|    =+    | +     |     ?     {     }  `~+RSht // limitation prevents ~
     ---------------------------------------------------------------------------
     Left+LAlt ___   ___   Ent  | .   ___   LGUI  Right+RAlt
                     -*-       <|>    -*-                                         //(hold) Access on _DEF_BASE
       <1   ±  <2    <3    <4   | 4>  3>    2>  ± 1>  
*/
//
//
//      <pink2             , <pinky  , <ring   , <middl  , <index  , <indx2 |, indx2>  , index>  , middl>  , ring>   , pinky>  , pink2>             ,
//                         , -*-     ,         ,         ,         ,       <|,>        ,         ,         ,         ,         ,                    ,
        CTO_BASE           , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , KC_DEL             ,
        LCTL_T ( KC_TAB )  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , RCTL_T ( KC_GRV )  ,
        LSFT_T ( KC_MINS ) , KC_LBRC , KC_RBRC , KC_SLSH , KC_BSLS , KC_EQL  , KC_PLUS , KC_PIPE , KC_QUES , KC_LCBR , KC_RCBR , RSFT_T ( KC_TILD ) ,
//      ---------------------------------------------------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT ) 

# ifdef TRANSMINIVAN_LEFTSIDE
                           , XXXXXXX
# endif

# ifdef MORE_KEY__COMMAND
                           , MORE_key1
# endif

                           , _______ , DUO_HOLD , KC_ENT , KC_DOT , DUO_HOLD , KC__YGUI

# ifdef TRANSMINIVAN_RIGHTSIDE
                                                                                        , XXXXXXX
# endif

# ifdef MORE_KEY__ARROW
                                                                                        , MORE_key2  
# endif                                     

                                                                                        , RALT_T ( KC_RIGHT )
//                         ,         , -*-      ,      <|,>       , -*-      ,          ,
//      <1           ±  ±  , <2      , <3       , <4    |, 4>     , 3>       , 2>       , ±  ±  1>

                      ),

        /* ⬆⬇ */

    /* Layer _ALT_NSY: Descrambled _DEF_NSY layer for a computer already set to Dvorak (see just above).
     *
     */
    // KC_TILD does not work there, because of a limitation with shifted keys (nov 2019).

    [ _ALT_NSY ] = LAYOUT_redefined (

/*
     Layer _ALT_NSY (Dvorak descramble mode for numbers/symbols)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
              -*-                          <|>                                  //(toggle) Access on _FUN
     BASE     !     @     #     $     %     | ^     &     *     (    )       Del
     Tab+LCtl 1!    2@    3#    4$    5%    | 6^    7&    8*    9(   0)  `~+RCtl
     -+LSht   -_    =+    [{    \|    ]}    | }     |     {     _     +  `~+RSht            // row 2, raw
     ---------------------------------------------------------------------------
     Left+LAlt ___   ___   Ent  | .   ___   LGUI  Right+RAlt
                     -*-       <|>    -*-                                         //(hold) Access on _DEF_BASE
       <1   ±  <2    <3    <4   | 4>  3>    2>  ± 1>  

     _ALT_NSY input results in the same as _DEF_NSY with computer side Dvorak remapping. Only shown what changes:

              [{    ]}    /?           =+   |   +         ?     {     }                  // row 2, result
 */
//
//      <pink2             , <pinky  , <ring  , <middl  , <index  , <indx2 |, indx2>  , index>  , middl>  , ring>   , pinky>  , pink2>             ,
//                         , -*-     ,        ,         ,         ,       <|,>        ,         ,         ,         , -*-     ,                    ,
        CTO_BASE           , KC_EXLM , KC_AT  , KC_HASH , KC_DLR  , KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , KC_DEL             ,
        LCTL_T ( KC_TAB )  , KC_1    , KC_2   , KC_3    , KC_4    , KC_5    , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , RCTL_T ( KC_GRV )  , 
        LSFT_T ( KC_MINS ) , KC_MINS , KC_EQL , KC_LBRC , KC_BSLS , KC_RBRC , KC_RCBR , KC_PIPE , KC_LCBR , KC_UNDS , KC_PLUS , RSFT_T ( KC_TILD ) ,  
//      --------------------------------------------------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT ) 

# ifdef TRANSMINIVAN_LEFTSIDE
                           , XXXXXXX
# endif

# ifdef MORE_KEY__COMMAND
                           , MORE_key1
# endif

                           , _______ , DUO_HOLD , KC_ENT , KC_DOT , DUO_HOLD , KC__YGUI

# ifdef TRANSMINIVAN_RIGHTSIDE
                                                                                        , XXXXXXX
# endif

# ifdef MORE_KEY__ARROW
                                                                                        , MORE_key2  
# endif                                    

                                                                                        , RALT_T ( KC_RIGHT )
//                         ,        , -*-       ,      <|,>       , -*-      ,          ,
//      <1           ±  ±  , <2     , <3        , <4    |, 4>     , 3>       , 2>       , ±  ±  1>

                      ),

        /* ⬆⬇ */
 
        // See ./keymap.c for rest of layers
