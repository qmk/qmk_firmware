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

    /* Layer _..._BASE: default BASE layer (Dvorak)
     *
     * This thing is different from the usual different letters arrangement.
     * It is a numbers pad, one for the left hand, and one for the right
     * hand. Both are as identical as possible. The use case is the same as
     * a number pad keyboard: single handed numbers input.
     *
     * The number 5 is under the middle finger home row, as expected for blind
     * number pad typing.
     * The “,” is added, because it is used in some languages, where in English 
     * the “.” is used (such as Dutch).
     * Tab is added because it is useful in spreadsheets.
     *
     * The left/upper key, where normally BASE is located, is now OTHER_BASE.
     * That switches the board to the ‛Default’ layout (assuming this layout is
     * compiled on the ‛Alternate’), which is effectively the
     * same way as a return to BASE in the sense of BASE being the letters/layer
     * switch layer. “Other Base” reached from the normal letters/layer-switching BASE layout
     * will then turn the keyboard into these number pads.
     *
     * A modified Numbers&Symbols layer _NSY is still supplied with this Numbers
     * Pad layout, to have faster access to more symbols. 
     * 
     * The standard numbers pad layer _PAD also still exists. That one has the
     * numbers arranged differently. Both these layers provide the numbers in their
     * numbers pad keycode variant. That is not the same keycode as the other set
     * of numbers. Some computer programs use the difference, even if they appear the
     * same and/or are treated the same in other computer programs.
     *
     * (While a keyboard typically has the tactile guide on the keycaps under the
     * index fingers, while the tactile guide on the numbers pad is under the middle
     * finger for number 5, I have the tactile guide for regular typing under the
     * middle fingers. This is retained for the numbers pad: tactile guide under
     * number 5. Perhaps it is a downside in some ways for some, but it is a plus
     * in that you do not have to move your hand to another key, which could be awkward.
     * It seems to be a minor/irrelevant issue.)
     */ 

// Process user configuration wrt ‛Default’ or ‛Alternative’ spot for this layout.
# if   defined(BASE_PAD__DEF_BASE)
    [ _DEF_BASE ] = LAYOUT_redefined (
# elif defined(BASE_PAD__ALT_BASE)
    [ _ALT_BASE ] = LAYOUT_redefined (
# endif

/*
     Layer _..._BASE (Number pad, with NumLock on)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
              -*-                          <|>                               //(toggle) Access on _FUN
     !Alter   Bspc  7     8     9     -     | Bspc  7     8     9    -   Bspc
     Tab       *    4     5     6     +     | *     4     5     6    +    Tab
     _NSY      /    1     2     3     ,     | /     1     2     3    ,   _NSY 
     ------------------------------------------------------------------------
                   NumL    0     .     Ent  | 0   .     Ent   NumL      
                                 -*-       <|>    -*-                        //(hold) Access on _DEF_BASE
                   <1   ±  <2    <3    <4   | 4>  3>    2>  ± 1>  
                       ___                  |              ___          

     Layer _..._BASE (Number pad, with NumLock off)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring >pin>pink2>
              -*-                          <|>                                  //(toggle) Access on _FUN
     !Alter   Bspc  Home  Up    PgUp  -     | Bspc  Home  Up    PgUp  -   Bspc
     Tab       *    Left  xxx   Right +     | *     Left  xxx   Right +    Tab
     _NSY¹     /    End   Down  PgDn  ,     | /     End   Down  PgDn  ,   _NSY¹
     -------------------------------------------------------------------------
                   NumL    0     .     Ent  | 0   .     Ent   NumL      
                                 -*-       <|>    -*-                        //(hold) Access on _DEF_BASE
                   <1   ±  <2    <3    <4   | 4>  3>    2>  ± 1>  
                       ___                  |              ___          
 
     ¹) Toggle to the accompanying symbols/numbers layer.

*/
//
//      <pink2            , <pinky         , <ring   , <middl  , <indx   ,        <ind|, indx>          , inde>   , midd>   , ring>   , pink>       , pink2>        ,
//      -*!-              ,                ,         ,         ,         ,           <|,>               ,         ,         ,         ,             ,               ,
        OTHER_BASE        , KC_BSPC        , KC_KP_7 , KC_KP_8 , KC_KP_9 , KC_KP_MINUS , KC_BSPC        , KC_KP_7 , KC_KP_8 , KC_KP_9 , KC_KP_MINUS , KC_BSPC       ,
        KC_TAB            , KC_KP_ASTERISK , KC_KP_4 , KC_KP_5 , KC_KP_6 , KC_KP_PLUS  , KC_KP_ASTERISK , KC_KP_4 , KC_KP_5 , KC_KP_6 , KC_KP_PLUS  , KC_TAB        ,
        CTO_NUMS          , KC_KP_SLASH    , KC_KP_1 , KC_KP_2 , KC_KP_3 , KC_COMMA    , KC_KP_SLASH    , KC_KP_1 , KC_KP_2 , KC_KP_3 , KC_COMMA    , CTO_NUMS      ,
//      -----------------------------------------------------------------------------------------------------------------
        KC_NUMLOCK

# ifdef TRANSMINIVAN_LEFTSIDE
                           , MO ( _PAD )
# endif

# ifdef MORE_KEY__COMMAND
                           , MORE_key1_BASE  
# endif

                           , KC_KP_0      , KC_KP_DOT , KC_KP_ENTER     , KC_KP_0 , KC_KP_DOT , KC_KP_ENTER

# ifdef TRANSMINIVAN_RIGHTSIDE
                                                                                                         , MO ( _FUN )
# endif

# ifdef MORE_KEY__ARROW
                                                                                                         , MORE_key2  
# endif

                                                                                                         , KC_NUMLOCK
//                         ,              ,           ,               <|,>        ,           ,          ,
//      <1           ±  ±  , <2           , <3        , <4             |, 4>      , 3>        , 2>       , ±  ±  1>

                      ),

        /* ⬆⬇ */

    /* Layer _..._NSY: Numbers and symbols.
     *          Off hand Number input (-.Bksp ent (shft)tab).
     */
    // KC_TILD does not work there, because of a limitation with shifted keys (nov 2019).

// Process user configuration wrt ‛Default’ or ‛Alternative’ spot for this layout.
# if   defined(BASE_PAD__DEF_BASE)
    [ _DEF_NSY ] = LAYOUT_redefined (
# elif defined(BASE_PAD__ALT_BASE)
    [ _ALT_NSY ] = LAYOUT_redefined (
# endif

/*
     Layer _..._NSY (Numbers and SYmbols)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
              -*-                          <|>                                  //(toggle) Access on _FUN
     BASE     !     @     #     $     %     | ^     &     *     (    )       Del
     Tab+LCtl ¹₁    ²₂    ³₃    ⁴₄    ⁵₅    | ⁶₆    ⁷₇    ⁸₈    ⁹₉   ⁰₀  `~+RCtl
     -+LSht   [{    ]}    /?    \|    =+    | +     |     ?     {     }  `~+RSht // limitation prevents ~
     ---------------------------------------------------------------------------
     Left+LAlt ___   ___   Ent  | .   ___   LGUI  Right+RAlt
                     -*-       <|>    -*-                                         //(hold) Access on _..._BASE
       <1   ±  <2    <3    <4   | 4>  3>    2>  ± 1>  
*/
//
//
//      <pink2             , <pinky    , <ring     , <middl    , <index    , <indx2   |, indx2>    , index>    , middl>    , ring>     , pinky>    , pink2>             ,
//                         , -*-       ,           ,           ,           ,         <|,>          ,           ,           ,           ,           ,                    ,
        CTO_BASE           , KC_EXLM   , KC_AT     , KC_HASH   , KC_DLR    , KC_PERC   , KC_CIRC   , KC_AMPR   , KC_ASTR   , KC_LPRN   , KC_RPRN   , KC_DEL             ,
        LCTL_T ( KC_TAB )  , XP_DRA_BA , XP_DRA_BB , XP_DRA_BC , XP_DRA_BD , XP_DRA_BE , XP_DRA_BF , XP_DRA_BG , XP_DRA_BH , XP_DRA_BI , XP_DRA_BJ , RCTL_T ( KC_GRV )  ,
        LSFT_T ( KC_MINS ) , KC_LBRC   , KC_RBRC   , KC_SLSH   , KC_BSLS   , KC_EQL    , KC_PLUS   , KC_PIPE   , KC_QUES   , KC_LCBR   , KC_RCBR   , RSFT_T ( KC_TILD ) ,
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
