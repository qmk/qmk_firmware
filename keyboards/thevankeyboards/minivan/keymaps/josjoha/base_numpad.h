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

#pragma once

// --------------------------------------v---------------------------------------
//                                 Configuration:
// --------------------------------------v---------------------------------------

        /*                      ➡ Number pad Configuration ⬅
         *
         * This concerns this Base layer in the shape of a numerical key pad, not the numerical
         * key pad layer which is part of the common layer system, which is defined and configured
         * elsewhere (see ./user_config.h).
         *
         * _Activate_ the below to have a single keypad definition on this layer, for the right
         * hand. Modifiers are also defined.
         * _Remove_ the below to have two keypad definitions on this Base layer, one for each hand.
         *
         * In both cases, you can reach the accompanying number pad layer with the super-/sub-script
         * numbers. For either option, there is a matching * super-/sub-script layer, which is
         * automatically compiled with it.
         */
  #define NUMPAD_BASE_SINGLE // _Activate_ to resemble a one handed numerical keyboard, for right hand.
                             // _Remove_ to have two numerical key pads, side by side, one for each hand.
                             //
        /* Tip: When in doubt it might be best to choose the single handed layer, because it
         * resembles a regular keyboard more, and has modifier combinations.
         */


        /*                      ➡ Removing the numbers pad _PAD layer ⬅
         *
         * You may have no use for this common layer, if you have a numerical
         * keypad on the Alternate Base already.
         *
         * While _PAD layer gives quick uncluttered access to Control, Shift and Alt
         * to modify your pointer device input, the _MOV layer does the same. You
         * end up with the same functionality, with or without _PAD, in this matter.
         *
         * This does precisely the same as REMOVE_PAD in ./user_config.h, but this
         * setting here overrides any setting in ./user_config.h
         */
//#define REMOVES_PAD // _Activate_ to strip out the _PAD layer, _remove_ to have the _PAD layer.

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


// The below sets some things up based on the above #defines.

// Stripping out _PAD layer, sets the #define used global configuration file ./user_config.h
# ifdef REMOVES_PAD         // this file
#     ifndef REMOVE_PAD     // user_config.h
#         define REMOVE_PAD  // removes _PAD layer
#     endif
# endif
// Inserting the _PAD layer, even if stripped in ./user_config.h
# ifndef REMOVES_PAD         // this file
#     ifdef REMOVE_PAD       // user_config.h
#         undef REMOVE_PAD   // activtaes _PAD layer
#     endif
# endif
