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
// Accented character and dead key layers.
#ifdef BEPO_ENABLE
#ifdef ACCENTED_LAYER_ENABLE
T_LAYER(_ACCENTED_BP, ___ACCENTED_BP___),
#endif
#ifdef MORTE_LAYER_ENABLE
  T_LAYER(_MORTE_BP, ___MORTE_BP___),
#endif
#ifdef ACCENTED_MORTE_LAYER_ENABLE
  T_LAYER(_ACCENTED_MORTE_BP, ___ACCENTED_MORTE_BP___),
#endif
#endif
