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

// See the user configuration file: ./base_numpad.h

// --------------------------------------^---------------------------------------
//            Below here no more comfortable configuration options.....
// --------------------------------------^---------------------------------------

// This is moved into ./user_config.h, because global #defines are affected.
//((#include "./base_numpad.h" // Pull in the user configuration))

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
     *
     * The left/upper key, where normally BASE is located, is now OTHER_BASE.
     * That switches the board to the ‛Default’ layout, which is effectively the
     * same way as a return to BASE in the sense of BASE being the letters/layer
     * switch layer. “Other Base” reached from the normal letters/layer-switching 
     * BASE layout will then turn the keyboard into these number pads layers.
     *
     * A modified Numbers&Symbols layer _NSY is still supplied with this Numbers
     * Pad layout (as with other Base layers).
     * 
     * The standard numbers pad layer _PAD also still exists. That one has the
     * numbers arranged differently. 
     *
     */ 

// When putting this layer on ‛Default’, it produced undesired side effects:
// • _RAR and _MOV hold keys on the ‛Alternate’ letters layer, failed to switch back.
// • Parts of the Numbers Pad keys got activated through transparent layer switch keys on letters layer.
// Since there is no use for Numpad on ‛Default’ Base anyway, this is simply not supported, which seems to solve the problem.


# ifndef NUMPAD_BASE_SINGLE 

    [ _ALT_BASE ] = LAYOUT_redefined (

/*
     Layer _..._BASE (Number pad, square layout)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
                                           <|>
     !AlterGo Bspc  7     8     9     -     | Bspc  7     8     9    -   Bspc  //!AlterGo: to _DEF_BASE
     =         *    4     5     6     +     | *     4     5     6    +      =
     _NSY¹     /    1     2     3     ,     | /     1     2     3    ,   _NSY¹ 
     ------------------------------------------------------------------------
                   xxx     0     .     Ent  | NumL  0     .     Ent
                                           <|>
                   <1   ±  <2    <3    <4   | 4>    3>    2>  ± 1>  
                       xxx                  |                xxx          

     Layer _..._BASE (Number pad, with NumLock off)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring >pin>pink2>
                                           <|>
     !AlterGo Bspc  Home  Up    PgUp  -     | Bspc  Home  Up    PgUp  -   Bspc  //!AlterGo: to _DEF_BASE 
     =         *    Left  5     Right +     | *     Left  5     Right +      =  // modified 5
     _NSY¹     /    End   Down  PgDn  ,     | /     End   Down  PgDn  ,   _NSY¹
     -------------------------------------------------------------------------
                   xxx     Ins   Del   Ent  | NumL  Ins   Del   Ent
                                           <|>
                   <1   ±  <2    <3    <4   | 4>    3>    2>  ± 1>  
                       xxx                  |                xxx          
 
     ¹) Toggle to the accompanying Super-Sub-Script (_NSY) layer.

*/
//
//      <pink2        , <pinky         , <ring   , <middl  , <indx   ,        <ind|, indx>          , inde>   , midd>   , ring>   , pink>       , pink2>      ,
//      -*!-          ,                ,         ,         ,         ,           <|,>               ,         ,         ,         ,             ,             ,
        OTHER_BASE_GO , KC_BSPC        , KC_KP_7 , KC_KP_8 , KC_KP_9 , KC_KP_MINUS , KC_BSPC        , KC_KP_7 , KC_KP_8 , KC_KP_9 , KC_KP_MINUS , KC_BSPC     ,
        KC_KP_EQUAL   , KC_KP_ASTERISK , KC_KP_4 , KC_KP_5 , KC_KP_6 , KC_KP_PLUS  , KC_KP_ASTERISK , KC_KP_4 , KC_KP_5 , KC_KP_6 , KC_KP_PLUS  , KC_KP_EQUAL ,
        CTO_NUMS      , KC_KP_SLASH    , KC_KP_1 , KC_KP_2 , KC_KP_3 , KC_KP_COMMA , KC_KP_SLASH    , KC_KP_1 , KC_KP_2 , KC_KP_3 , KC_KP_COMMA , CTO_NUMS    ,
//      -------------------------------------------------------------------------------------------------------------------------------------------------------
        XXXXXXX

#     ifdef TRANSMINIVAN_LEFTSIDE
                      , TRANS_LEFT  
#     endif

#     ifdef MORE_KEY__COMMAND
                      , XXXXXXX
#     endif

                      , KC_KP_0    , KC_KP_DOT , KC_KP_ENTER     

#     ifdef TRANSMINIVAN_MIDLEFT
                                               , TRANS_MIDLEFT 
#     endif

                                                               , KC_NUMLOCK , KC_KP_0 , KC_KP_DOT 

#     ifdef TRANSMINIVAN_RIGHTSIDE
                                                                                                 , TRANS_RIGHT  
#     endif                                                                              
                                                                                     
#     ifdef MORE_KEY__ARROW                                                              
                                                                                                 , XXXXXXX
#     endif                                                                              
                                                                                     
                                                                                                               , KC_KP_ENTER
//                    ,            ,           ,             <|,>           ,         ,          ,
//      <1      ±  ±  , <2         , <3        , <4           |, 4>         , 3>      , 2>       , ±  ± 1>

                      ),

        /* ⬆⬇ */

    /* Layer _ALT_NSY: super-/sub-script numbers numpad, square layout
     */

    [ _ALT_NSY ] = LAYOUT_redefined (

/*
     Layer _..._BASE (super-/sub-script numbers, Numlock on/off)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
                                           <|>
     BASE     Bspc  ⁷₇    ⁸₈    ⁹₉    -     | Bspc  ⁷₇    ⁸₈    ⁹₉   -   Bspc
     =         *    ⁴₄    ⁵₅    ⁶₆    +     | *     ⁴₄    ⁵₅    ⁶₆   +      =
     LSht      /    ¹₁    ²₂    ³₃    ,     | /     ¹₁    ²₂    ³₃   ,   RSht
     -*-                                   <|>                            -*- //(toggle) Access on Base
     ------------------------------------------------------------------------
                   xxx    ⁰₀     .DEL  Ent  | xxx   ⁰₀    .DEL  Ent  
                                           <|>      
                   <1   ±  <2    <3    <4   | 4>    3>    2>  ± 1>  
                       xxx                  |                xxx          


*/
//High/low numbers guide:
//¹₁         ²₂         ³₃         ⁴₄         ⁵₅       | ⁶₆         ⁷₇         ⁸₈         ⁹₉         ⁰₀       
//XP_DRA_BA  XP_DRA_BB  XP_DRA_BC  XP_DRA_BD  XP_DRA_BE  XP_DRA_BF  XP_DRA_BG  XP_DRA_BH  XP_DRA_BI  XP_DRA_BJ
//
//      <pink2      , <pinky         , <ring     , <middl    , <indx     ,        <ind|, indx>          , inde>     , midd>     , ring>     , pink>       , pink2>      ,
//      -*!-        ,                ,           ,           ,           ,           <|,>               ,           ,           ,           ,             ,             ,
        CTO_BASE    , KC_BSPC        , XP_DRA_BG , XP_DRA_BH , XP_DRA_BI , KC_KP_MINUS , KC_BSPC        , XP_DRA_BG , XP_DRA_BH , XP_DRA_BI , KC_KP_MINUS , KC_BSPC     ,
        KC_KP_EQUAL , KC_KP_ASTERISK , XP_DRA_BD , XP_DRA_BE , XP_DRA_BF , KC_KP_PLUS  , KC_KP_ASTERISK , XP_DRA_BD , XP_DRA_BE , XP_DRA_BF , KC_KP_PLUS  , KC_KP_EQUAL ,
        KC_LSFT     , KC_KP_SLASH    , XP_DRA_BA , XP_DRA_BB , XP_DRA_BC , KC_KP_COMMA , KC_KP_SLASH    , XP_DRA_BA , XP_DRA_BB , XP_DRA_BC , KC_KP_COMMA , KC_RSFT     ,
//      -----------------------------------------------------------------------------------------------------------------------------------------------------------------
        XXXXXXX   

#     ifdef TRANSMINIVAN_LEFTSIDE
                    , TRANS_LEFT
#     endif

#     ifdef MORE_KEY__COMMAND
                    , XXXXXXX
#     endif

                    , XP_DRA_BJ , KC_KP_DOT , KC_KP_ENTER 

#     ifdef TRANSMINIVAN_MIDLEFT
                                                          , TRANS_MIDLEFT  
#     endif

                                                          , XXXXXXX       , XP_DRA_BJ , KC_KP_DOT   

#     ifdef TRANSMINIVAN_RIGHTSIDE
                                                                                                  , TRANS_RIGHT
#     endif                                                                                                   
                                                                                                          
#     ifdef MORE_KEY__ARROW                                                                                   
                                                                                                  , XXXXXXX
#     endif                                                                                                   
                                                                                                          
                                                                                                  , KC_KP_ENTER
//                  ,           ,           ,           <|,>              ,           ,           ,
//      <1    ±  ±  , <2        , <3        , <4         |, 4>            , 3>        , 2>        , ±  ±  1>

                      ),

        /* ⬆⬇ */

# else // NUMPAD_BASE_SINGLE is defined ====================================================================

    [ _ALT_BASE ] = LAYOUT_redefined (

/*
     
     * Layer Numbers Pad on Base:
     *        « See also documentation in keymap.c at _PAD layer, of which this is almost entirely a copy »
     *        One difference is the key to go to the _ALT_NSY layer (denoted “NUMS:” just below).
     *        The other difference is the key to switch to default Base and also immediately goes there
     *        (denoted “!AlterGo” here).
     
     Layer _ALT_BASE (Number pad, with NumLock on)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
                                           <|>
     !AlterGo NUMS: xxx   xxx   xxx   xxx   | =     7     8     9    -   Bspc  // NUMS: to ¹/₁
     LCtl     xxx   xxx   xxx   xxx   xxx   | *     4     5     6    +   RCtl
     LSht     xxx   xxx   xxx   xxx   xxx   | /     1     2     3    ,   RSht  
     ------------------------------------------------------------------------
                   LAlt   Del    Tab   Ent  | NumL  0     .     RAlt      
                                           <|>           
                   <1   ±  <2    <3    <4   | 4>    3>    2>  ± 1>  
                       xxx                  |                xxx          

     Layer _ALT_BASE (Number pad, with NumLock off)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring >pin>pink2>
                                           <|>
     !AlterGo NUMS: xxx   xxx   xxx   xxx   | =     Home  Up    PgUp  -   Bspc  // NUMS: to ¹/₁
     LCtl     xxx   xxx   xxx   xxx   xxx   | *     Left  5     Right +   RCtl  // modified 5
     LSht     xxx   xxx   xxx   xxx   xxx   | /     End   Down  PgDn  ,   RSht  
     -------------------------------------------------------------------------
                   LAlt   Del    Tab   Ent  | NumL  Ins   Del   RAlt      
                                           <|>
                   <1   ±  <2    <3    <4   | 4>    3>    2>  ± 1>  
                       xxx                  |                xxx          
 
*/

//High/low numbers guide:
//¹₁         ²₂         ³₃         ⁴₄         ⁵₅       | ⁶₆         ⁷₇         ⁸₈         ⁹₉         ⁰₀       
//XP_DRA_BA  XP_DRA_BB  XP_DRA_BC  XP_DRA_BD  XP_DRA_BE  XP_DRA_BF  XP_DRA_BG  XP_DRA_BH  XP_DRA_BI  XP_DRA_BJ
//
//      <pink2        , <pinky   , <ring   , <middl  , <index  , <indx2 |, indx2>         , index>  , middl>  , ring>   , pinky>      , pink2>  ,
//                    ,          ,         ,         ,         , -*-   <|,>               ,         ,         ,         ,             ,         ,
        OTHER_BASE_GO , CTO_NUMS , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_KP_EQUAL    , KC_KP_7 , KC_KP_8 , KC_KP_9 , KC_KP_MINUS , KC_BSPC ,
        KC_LCTL       , XXXXXXX  , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_KP_ASTERISK , KC_KP_4 , KC_KP_5 , KC_KP_6 , KC_KP_PLUS  , KC_RCTL ,
        KC_LSFT       , XXXXXXX  , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_KP_SLASH    , KC_KP_1 , KC_KP_2 , KC_KP_3 , KC_KP_COMMA , KC_RSFT ,
//      ------------------------------------------------------------------------------------------------------------------------------------
        KC_LALT 

#     ifdef TRANSMINIVAN_LEFTSIDE
                      , TRANS_LEFT  
#     endif

#     ifdef MORE_KEY__COMMAND
                      , MORE_key1
#     endif

                      , KC_DEL     , KC_TAB , KC_KP_ENTER

#     ifdef TRANSMINIVAN_MIDLEFT
                                            , TRANS_MIDLEFT
#     endif

                                                            , KC_NUMLOCK , KC_KP_0 , KC_KP_DOT  

#     ifdef TRANSMINIVAN_RIGHTSIDE
                                                                                               , TRANS_RIGHT
#     endif

#     ifdef MORE_KEY__ARROW
                                                                                               , MORE_key2  
#     endif

                                                                                               , KC_RALT
//                    ,            ,        ,             <|,>           ,         ,           ,
//      <1  ± ±       , <2         , <3     , <4           |, 4>         , 3>      , 2>        , ±  ±  1>

                      ),

        /* ⬆⬇ */

    [ _ALT_NSY ] = LAYOUT_redefined (

/*
     
     * Layer Numbers Pad on Base:
     *        This layer is the same as the above, except the numbers are in super-/sub-script.
     *
     
     Layer _ALT_NSY (Number pad, with NumLock on/off)
    
     <pink2   <pinky<ring <middl<index<indx2| indx2>index>middl>ring>pin>pink2>
                                           <|>
     BASE     xxx   xxx   xxx   xxx   xxx   | =     ⁷₇    ⁸₈    ⁹₉   -   Bspc
     LCtl     xxx   xxx   xxx   xxx   xxx   | *     ⁴₄    ⁵₅    ⁶₆   +   RCtl
     LSht     xxx   xxx   xxx   xxx   xxx   | /     ¹₁    ²₂    ³₃   ,   RSht  
     ------------------------------------------------------------------------
                   LAlt   Del    Tab   Ent  | NumL  ⁰₀    .DEL  RAlt      
                                           <|>           
                   <1   ±  <2    <3    <4   | 4>    3>    2>  ± 1>  
                       xxx                  |                xxx          

*/

//High/low numbers guide:
//¹₁         ²₂         ³₃         ⁴₄         ⁵₅       | ⁶₆         ⁷₇         ⁸₈         ⁹₉         ⁰₀       
//XP_DRA_BA  XP_DRA_BB  XP_DRA_BC  XP_DRA_BD  XP_DRA_BE  XP_DRA_BF  XP_DRA_BG  XP_DRA_BH  XP_DRA_BI  XP_DRA_BJ
//
//      <pink2   , <pinky  , <ring   , <middl  , <index  , <indx2 |, indx2>         , index>    , middl>    , ring>     , pinky>      , pink2>  ,
//               ,         ,         ,         ,         , -*-   <|,>               ,           ,           ,           ,             ,         ,
        CTO_BASE , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_KP_EQUAL    , XP_DRA_BG , XP_DRA_BH , XP_DRA_BI , KC_KP_MINUS , KC_BSPC ,
        KC_LCTL  , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_KP_ASTERISK , XP_DRA_BD , XP_DRA_BE , XP_DRA_BF , KC_KP_PLUS  , KC_RCTL ,
        KC_LSFT  , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_KP_SLASH    , XP_DRA_BA , XP_DRA_BB , XP_DRA_BC , KC_KP_COMMA , KC_RSFT ,
//      -----------------------------------------------------------------------------------------------------------------------------------
        KC_LALT 

#     ifdef TRANSMINIVAN_LEFTSIDE
                 , TRANS_LEFT   
#     endif

#     ifdef MORE_KEY__COMMAND
                 , MORE_key1
#     endif

                 , KC_DEL     , KC_TAB , KC_KP_ENTER

#     ifdef TRANSMINIVAN_MIDLEFT
                                       , TRANS_MIDLEFT
#     endif

                                                       , KC_NUMLOCK , XP_DRA_BJ , KC_KP_DOT    

#     ifdef TRANSMINIVAN_RIGHTSIDE
                                                                                            , TRANS_RIGHT
#     endif

#     ifdef MORE_KEY__ARROW
                                                                                            , MORE_key2  
#     endif

                                                                                            , KC_RALT
//               ,            ,        ,             <|,>           ,           ,           ,
//      <1  ± ±  , <2         , <3     , <4           |, 4>         , 3>        , 2>        , ±  ±  1>

                      ),

# endif // NUMPAD_BASE_SINGLE 

        /* ⬆⬇ */

