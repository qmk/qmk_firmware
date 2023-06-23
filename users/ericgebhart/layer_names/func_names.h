/*
  Copyright 2018-2022 Eric Gebhart <e.a.gebhart@gmail.com>

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

// functional layers that would be different by language

#ifdef ACCENTS_LAYER_ENABLE
LANG_N(_ACCENTS),
#endif
#ifdef MORTE_LAYER_ENABLE
  LANG_N(_MORTE),
#endif
#ifdef ACCENTS_MORTE_LAYER_ENABLE
    LANG_N(_ACCENTS_MORTE),
#endif

#ifdef SYMBOL_LAYER_ENABLE
  LANG_N(_SYMB),
#endif
#ifdef KEYPAD_LAYER_ENABLE
  LANG_N(_KEYPAD),
#endif
#ifdef TOPROWS_LAYER_ENABLE
  LANG_N(_TOPROWS),
#endif
