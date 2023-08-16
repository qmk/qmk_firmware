/*
  Copyright 2022 Eric Gebhart <e.a.gebhart@gmail.com>

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
*/
#ifdef QWERTY_LAYER_ENABLE
B_LAYER(LANG_N(_QWERTY), ___10_NUMBERS___, ___QWERTY___),
#endif
#ifdef NORMAN_LAYER_ENABLE
  B_LAYER(LANG_N(_NORMAN), ___10_NUMBERS___, ___NORMAN___),
#endif
#ifdef WORKMAN_LAYER_ENABLE
  B_LAYER(LANG_N(_WORKMAN), ___10_NUMBERS___, ___WORKMAN___),
#endif
