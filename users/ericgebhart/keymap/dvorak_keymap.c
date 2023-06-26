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
#ifdef DVORAK_LAYER_ENABLE
B_LAYER(LANG_N(_DVORAK), ___10_NUMBERS___, ___DVORAK___),
#endif
#ifdef DVORAK_RLC_IU_LAYER_ENABLE
  B_LAYER(LANG_N(_DVORAK_RLC_IU), ___10_NUMBERS___, ___DVORAK_RLC_IU___),
#endif
#ifdef BOO_LAYER_ENABLE
  B_LAYER(LANG_N(_BOO), ___10_NUMBERS___, ___BOO___),
#endif
#ifdef CAPEWELL_DVORAK_LAYER_ENABLE
  B_LAYER(LANG_N(_CAPEWELL_DVORAK), ___10_NUMBERS___, ___CAPEWELL_DVORAK___),
#endif
#ifdef AHEI_LAYER_ENABLE
  B_LAYER(LANG_N(_AHEI), ___10_NUMBERS___, ___AHEI___),
#endif
