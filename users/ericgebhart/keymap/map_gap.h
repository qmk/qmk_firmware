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
#ifdef MTGAP_LAYER_ENABLE
B_LAYER(LANG_N(_MTGAP), ___10_NUMBERS___, ___MTGAP___),
#endif

#ifdef CTGAP_LAYER_ENABLE
  B_LAYER(LANG_N(_CTGAP), ___10_NUMBERS___, ___CTGAP___),
#endif

#ifdef APT_LAYER_ENABLE
  B_LAYER(LANG_N(_APT), ___10_NUMBERS___, ___APT___),
#endif

#ifdef CANARY_LAYER_ENABLE
  B_LAYER(LANG_N(_CANARY), ___10_NUMBERS___, ___CANARY___),
#endif
