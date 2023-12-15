#pragma once
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
#define LOCALE_DEFAULT CAT(LOCALE_, DEFAULT_LANG)
#define LOCALE_TWO CAT(LOCALE_, SECOND_LOCALE)

enum locales {
  LOCALE_DEFAULT = 0,
#ifdef SECOND_LOCALE
  LOCALE_TWO,
#endif
  LOCALES_END,
};
