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

 * Author: © 2021 by Jos Boersema
 *
 */

// --------------------------------------v---------------------------------------
//                                 Configuration:
// --------------------------------------v---------------------------------------

        /*          • Harmonize regular Qwerty
         * 
         * If compiling this ‛Qwerty Base Arrow’ base pair with regular Qwerty on
         * the other base pair (dual layout), the key ‛/?’ is on a different key
         * in these two layouts. This is bound to cause typing errors. With this
         * option you can cause the regular Qwerty to also have a ‛/?’ in the same
         * spot as ‛Qwerty Base Arrow’ has it, sacrificing Right Control/‛`~’ there.
         *
         * Regular Qwerty will still also have a ‛/?’ key in the normal Qwerty location.
         *
         * The key ‛`~’ can be reached through other means: just below on numbers &
         * symbols _NSY layer, or on the bonus Unicode layer _BON (on the far left, home row).
         * This is so by default, it remains unchanged.
         */
  #define QWERTY_BASEARROW_HARMONIZE // _Activate_ to harmonize the ‛/?’ key in the regular Qwerty layout.
                                     // _Remove_ leave regular Qwerty layout unchanged from default.

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

