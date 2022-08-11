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

// --------------------------------------^---------------------------------------
//            Below here no more comfortable configuration options.....
// --------------------------------------^---------------------------------------


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

        /*  ⬇ */

    /* Layer _..._BASE: Qwerty with arrows on Base, normal BASE layer and 'default' layer
     *
     * - This version of Qwerty puts arrows on Base, and assumes the 'arrow' hardware key.
     *   When not compiled with 'arrow' hardware key, Base will not contain ‛down arrow’.
     *
     *   This does not mean that this is the recommended version of Qwerty in general for
     *   the 'arrow' hardware key with Qwerty. Regular Qwerty works with the additional
     *   hardware key 'arrow'. The regular Qwerty compile option just works differently
     *   than this version with arrows on Base. Regular qwerty has the additional hardware
     *   key on the right be a toggle to _MOV layer, where you then have arrows in the same 
     *   area. Notice further that in all cases, you have a hold key to the _MOV layer under
     *   what is colloqually known as the ‛left space bar’, which leads to convenient arrow
     *   keys in the home row.
     *
     *   Putting directional arrow keys on the Base layer will cost you several keys on 
     *   the Base layer: hold _RAR, GUI, and ‛/?’. 
     *   • The ‛/?’ key is displaced to the _NSY layer.
     *   • The GUI key is lost. You could decide to also use the ‛south paw’/‛command’ 
     *     hardware key, which is a GUI by default. 
     *   • Hold key to _RAR layer is lost. You can only reach _RAR layer, using the right
     *     shift toggle, which is on a short timer.
     *
     *   My recommendation would be: see if you can make things work with regular Qwerty 
     *   if you are a 10 fingers typist, first. Moving your hand to this arrow cluster 
     *   seems to be a high cost to pay. You will also loose the default location for ‛/?’.
     *
     *   For special need situations regarding this right hand row1/2 arrow cluster, a
     *   tap to _MOV layer on the ‛arrow’ hardware key, should be a reasonable cost to
     *   pay, if a situation is already important enough to decide to move your hand there.
     *   For short uses of arrow keys, holding to the _MOV layer is the most efficient.
     *
     *   If you are not a 10 finger typist though, holding a key to _MOV layer seems to be
     *   inconvenient, and thus arrows on Base could be better for you.
     *
     *   Hence my conclusion: only compile ‛Qwerty with arrows on Base’ if the regular
     *   Qwerty isn't working for you.
     *  
     */ 

// Process user configuration wrt ‛Default’ or ‛Alternative’ spot for this layout.
# if   defined(BASE_QWERTY_BASEARROW__DEF_BASE)
    [ _DEF_BASE ] = LAYOUT_redefined (
# elif defined(BASE_QWERTY_BASEARROW__ALT_BASE)
    [ _ALT_BASE ] = LAYOUT_redefined (
# endif

/*
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
*/
//
//      <pink2            , <pink, <ring, <midd, <indx, <ind|, indx>, inde>, midd>   , ring>  , pink>   , pink2>        ,
//      -*!-              ,      ,      ,      ,      ,    <|,>     ,      ,         ,        ,         ,               ,
        KC_ESC            , KC_Q , KC_W , KC_E , KC_R , KC_T , KC_Y , KC_U , KC_I    , KC_O   , KC_P    , KC_BSPC       ,
        LCTL_T ( KC_TAB ) , KC_A , KC_S , KC_D , KC_F , KC_G , KC_H , KC_J , KC_K    , KC_L   , KC_SCLN , KC_QUOT       ,
        CHOLTAP_LSHFT     , KC_Z , KC_X , KC_C , KC_V , KC_B , KC_N , KC_M , KC_COMM , KC_DOT , KC_UP   , CHOLTAP_RSHFT ,
                                                                                            //  KC_SLSH
//      -----------------------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT ) 

# ifdef TRANSMINIVAN_LEFTSIDE
                           , MO ( _PAD )
# endif

# ifdef MORE_KEY__COMMAND
                           , MORE_key1_BASE
# endif

# ifdef SWITCH_HOLD_ACC_NSY 
                           , DUO_HOLD , CHOLTAP_ACCE 
# else
                           , CHOLTAP_ACCE , DUO_HOLD
# endif

                                                     , LEFTCENTER_THUMB

# ifdef TRANSMINIVAN_MIDLEFT
                                                     , TRANS_MIDLEFT
# endif

                                                                       , RIGHTCENTER_THUMB , DUO_HOLD

# ifdef TRANSMINIVAN_RIGHTSIDE
                                                                                                      , MO ( _FUN )
# endif                                                                                    
                                                                                           
                                                                                                                 , KC_LEFT
                                                                                                              // , KC__YGUI
                                                                                           
# ifdef MORE_KEY__ARROW                                                                    
                                                                                                                 , KC_DOWN
                                                                                                              // , MORE_key2  
# endif                                                                                    
                                                                                           
                                                                                                                 , KC_RIGHT
                                                                                                              // , CHOLTAP_LAYR
//                         ,              ,          ,               <|,>                  ,          ,          ,
//      <1           ±  ±  , <2           , <3       , <4             |, 4>                , 3>       , 2>       , ±  ±  1>

                      ),

        /* ⬆⬇ */

    /* Layer _..._NSY: Numbers and symbols, to work with the Qwerty base layer above.
     *          Off hand Number input (-.Bksp ent (shft)tab).
     */
    // KC_TILD does not work there, because of a limitation with shifted keys (nov 2019).

// Process user configuration wrt ‛Default’ or ‛Alternative’ spot for this layout.
# if   defined(BASE_QWERTY_BASEARROW__DEF_BASE)
    [ _DEF_NSY ] = LAYOUT_redefined (
# elif defined(BASE_QWERTY_BASEARROW__ALT_BASE)
    [ _ALT_NSY ] = LAYOUT_redefined (
# endif

/*
     Layer _..._NSY (Numbers and SYmbols). This fits the above Qwerty layer _..._BASE
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
              -*-                          <|>                                  //(toggle) Access on _FUN
     BASE     !     @     #     $     %     | ^     &     *     (    )       Del
     Tab+LCtl 1!    2@    3#    4$    5%    | 6^    7&    8*    9(   0)       /?
     -+LSht   [{    ]}    -_    \|    =+    | +     |     _     {     }   ~+RSht // `~ on _BON
                          ^^                              ^  // Only differences with normal version _..._NSY
     ---------------------------------------------------------------------------
     Left+LAlt ___   ___   Ent  | .   ___   LGUI  Right+RAlt
                     -*-       <|>    -*-                                         //(hold) Access on _..._BASE
       <1   ±  <2    <3    <4   | 4>  3>    2>  ± 1>  
            ^                                   ^
          (RGUI)                              (_MOV)
*/
//
//
//      <pink2             , <pinky  , <ring   , <middl  , <index  , <indx2 |, indx2>  , index>  , middl>  , ring>   , pinky>  , pink2>             ,
//                         , -*-     ,         ,         ,         ,       <|,>        ,         ,         ,         ,         ,                    ,
        CTO_BASE           , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , KC_DEL             ,
        LCTL_T ( KC_TAB )  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_SLSH            , 
        LSFT_DASH          , KC_LBRC , KC_RBRC , KC_MINS , KC_BSLS , KC_EQL  , KC_PLUS , KC_PIPE , KC_UNDS , KC_LCBR , KC_RCBR , RSFT_TILDE         , // note¹
//      ---------------------------------------------------------------------------------------------------------------------------------------------
        LALT_T ( KC_LEFT ) 

# ifdef TRANSMINIVAN_LEFTSIDE
                           , XXXXXXX
# endif

# ifdef MORE_KEY__COMMAND
                           , MORE_key1  
# endif

                           , _______ , _______ , KC_ENT

# ifdef TRANSMINIVAN_MIDLEFT
                                               , TRANS_MIDLEFT  
# endif

                                                               , KC_DOT , DUO_HOLD , KC__YGUI  

# ifdef TRANSMINIVAN_RIGHTSIDE
                                                                                              , XXXXXXX
# endif                                                                                       
                                                                                              
# ifdef MORE_KEY__ARROW                                                                       
                                                                                              , MORE_key2  
# endif                                                                                       
                                                                                              
                                                                                              , RALT_T ( KC_RGHT )
//                         ,         , -*-     ,             <|,>       , -*-      ,          ,
//      <1           ±  ±  , <2      , <3      , <4           |, 4>     , 3>       , 2>       , ±  ±  1>

// note¹
// Sacrificing RCTL, because ‛/’ is a major much used symbol,
// which seem to warrant being uncluttered. ‛`’ exists also on _BON
// (uncluttered). This breaks the logic that all these standard symbols 
// exist on this layer _NSY. However, ` and ~ are often in a diminutive 
// placement on mini keyboards, and ‛arrows on top’ was always going to
// be a stretch for a keyboard like this. The other option is to have a
// special macro to put tilde ‛~’ and accent grave ‛`’ both on Shift,
// but it doesn't seem to make much difference, and makes the firmware
// even larger.
                      ),

        /* ⬆⬇ */
