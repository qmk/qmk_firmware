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
     * The NumLock key is now not on what usually is Space on Base (the right side
     * space bar), in an effort to resemble the layout of keypads better. A downside
     * is that it breaks the logic that “modes” (whatever they are) are altered on
     * that key, but a benefit is that you can use this to differentiate this layer
     * from _PAD.
     *
     * (While a keyboard typically has the tactile guide on the keycaps under the
     * index fingers, while the tactile guide on the numbers pad is under the middle
     * finger for number 5, I have the tactile key caps guide for under the
     * middle fingers. This is retained for the numbers pad: tactile guide under
     * number 5. Perhaps it is a downside in some ways for some, but it is a plus
     * in that you do not have to move your hand to another key, which would be awkward.)
     */ 

// When putting this layer on ‛Default’, it produced undesired side effects:
// • _RAR and _MOV hold keys on the ‛Alternate’ letters layer, failed to switch back.
// • Parts of the Numbers Pad keys got activated through transparent layer switch keys on letters layer.
// Since there is no use for Numpad on ‛Default’ Base anyway, this is simply not supported, which seems to solve the problem.

    [ _ALT_BASE ] = LAYOUT_redefined (

/*
     Layer _..._BASE (Number pad, with NumLock on)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
                                           <|>
     !Alter   Bspc  7     8     9     -     | Bspc  7     8     9    -   Bspc
     Tab       *    4     5     6     +     | *     4     5     6    +    Tab
     _SSS¹     /    1     2     3     ,     | /     1     2     3    ,   _SSS¹ 
     ------------------------------------------------------------------------
                   NumL    0     .     Ent  | 0   .     Ent   NumL      
                                           <|>
                   <1   ±  <2    <3    <4   | 4>  3>    2>  ± 1>  
                       xxx                  |              xxx          

     Layer _..._BASE (Number pad, with NumLock off)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring >pin>pink2>
                                           <|>
     !Alter   Bspc  Home  Up    PgUp  -     | Bspc  Home  Up    PgUp  -   Bspc
     Tab       *    Left  xxx   Right +     | *     Left  xxx   Right +    Tab
     _SSS¹     /    End   Down  PgDn  ,     | /     End   Down  PgDn  ,   _SSS¹
     -------------------------------------------------------------------------
                   NumL    Ins   Del   Ent  | Ins Del   Ent   NumL      
                                           <|>
                   <1   ±  <2    <3    <4   | 4>  3>    2>  ± 1>  
                       xxx                  |              xxx          
 
     ¹) Toggle to the accompanying Super-Sub-Script (_SSS) layer.
        With regular Base layers, such as Qwerty/Dvorak, this is 
        called the Numbers&Symbols (_NSY) layer, and it is still
        called _NSY in the source code.

*/
//
//      <pink2            , <pinky         , <ring   , <middl  , <indx   ,        <ind|, indx>          , inde>   , midd>   , ring>   , pink>       , pink2>        ,
//      -*!-              ,                ,         ,         ,         ,           <|,>               ,         ,         ,         ,             ,               ,
        OTHER_BASE_GO     , KC_BSPC        , KC_KP_7 , KC_KP_8 , KC_KP_9 , KC_KP_MINUS , KC_BSPC        , KC_KP_7 , KC_KP_8 , KC_KP_9 , KC_KP_MINUS , KC_BSPC       ,
        KC_TAB            , KC_KP_ASTERISK , KC_KP_4 , KC_KP_5 , KC_KP_6 , KC_KP_PLUS  , KC_KP_ASTERISK , KC_KP_4 , KC_KP_5 , KC_KP_6 , KC_KP_PLUS  , KC_TAB        ,
        CTO_NUMS          , KC_KP_SLASH    , KC_KP_1 , KC_KP_2 , KC_KP_3 , KC_COMMA    , KC_KP_SLASH    , KC_KP_1 , KC_KP_2 , KC_KP_3 , KC_COMMA    , CTO_NUMS      ,
//      -----------------------------------------------------------------------------------------------------------------
        KC_NUMLOCK

# ifdef TRANSMINIVAN_LEFTSIDE
                           , TRANS_LEFT
# endif

# ifdef MORE_KEY__COMMAND
                           , XXXXXXX
# endif

                           , KC_KP_0      , KC_KP_DOT , KC_KP_ENTER     

#     ifdef TRANSMINIVAN_MIDLEFT
                                                      , TRANS_MIDLEFT
#     endif

                                                                        , KC_KP_0 , KC_KP_DOT , KC_KP_ENTER

# ifdef TRANSMINIVAN_RIGHTSIDE
                                                                                                         , TRANS_RIGHT
# endif

# ifdef MORE_KEY__ARROW
                                                                                                         , XXXXXXX
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

    [ _ALT_NSY ] = LAYOUT_redefined (

/*
     Layer _..._BASE (super-/sub-script numbers)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
                                           <|>
     BASE     Bspc  ⁷₇    ⁸₈    ⁹₉    -     | Bspc  ⁷₇    ⁸₈    ⁹₉   -   Bspc
     Tab       *    ⁴₄    ⁵₅    ⁶₆    +     | *     ⁴₄    ⁵₅    ⁶₆   +    Tab
     LSht      /    ¹₁    ²₂    ³₃    ,     | /     ¹₁    ²₂    ³₃   ,   RSht
     -*-                                   <|>                            -*- //(toggle) Access on Base
     ------------------------------------------------------------------------
                   xxx    ⁰₀     .     Ent  | ⁰₀  .     Ent   xxx       
                                           <|>
                   <1   ±  <2    <3    <4   | 4>  3>    2>  ± 1>  
                       xxx                  |              xxx          

*/
//High/low numbers guide:
//¹₁         ²₂         ³₃         ⁴₄         ⁵₅       | ⁶₆         ⁷₇         ⁸₈         ⁹₉         ⁰₀       
//XP_DRA_BA  XP_DRA_BB  XP_DRA_BC  XP_DRA_BD  XP_DRA_BE  XP_DRA_BF  XP_DRA_BG  XP_DRA_BH  XP_DRA_BI  XP_DRA_BJ
//
//      <pink2            , <pinky         , <ring     , <middl    , <indx     ,        <ind|, indx>          , inde>     , midd>     , ring>     , pink>       , pink2>        ,
//      -*!-              ,                ,           ,           ,           ,           <|,>               ,           ,           ,           ,             ,               ,
        CTO_BASE          , KC_BSPC        , XP_DRA_BG , XP_DRA_BH , XP_DRA_BI , KC_KP_MINUS , KC_BSPC        , XP_DRA_BG , XP_DRA_BH , XP_DRA_BI , KC_KP_MINUS , KC_BSPC       ,
        KC_TAB            , KC_KP_ASTERISK , XP_DRA_BD , XP_DRA_BE , XP_DRA_BF , KC_KP_PLUS  , KC_KP_ASTERISK , XP_DRA_BD , XP_DRA_BE , XP_DRA_BF , KC_KP_PLUS  , KC_TAB        ,
        KC_LSFT           , KC_KP_SLASH    , XP_DRA_BA , XP_DRA_BB , XP_DRA_BC , KC_COMMA    , KC_KP_SLASH    , XP_DRA_BA , XP_DRA_BB , XP_DRA_BC , KC_COMMA    , KC_RSFT       ,
//      -----------------------------------------------------------------------------------------------------------------
        XXXXXXX   

# ifdef TRANSMINIVAN_LEFTSIDE
                           , TRANS_LEFT
# endif

# ifdef MORE_KEY__COMMAND
                           , XXXXXXX
# endif

                           , XP_DRA_BJ      , KC_KP_DOT , KC_KP_ENTER 

#     ifdef TRANSMINIVAN_MIDLEFT
                                  , TRANS_MIDLEFT
#     endif

                                                                        , XP_DRA_BJ , KC_KP_DOT , KC_KP_ENTER

# ifdef TRANSMINIVAN_RIGHTSIDE
                                                                                                         , TRANS_RIGHT
# endif

# ifdef MORE_KEY__ARROW
                                                                                                         , XXXXXXX
# endif

                                                                                                         , XXXXXXX
//                         ,              ,           ,               <|,>        ,           ,          ,
//      <1           ±  ±  , <2           , <3        , <4             |, 4>      , 3>        , 2>       , ±  ±  1>

                      ),

        /* ⬆⬇ */
