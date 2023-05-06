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
// Language macros to change the names of things to
// match the value of LANG_IS, and EDGE_COLS.
// it would be nice to have consistency, but there isn't.
// Keys need a prefix, layer chunks need a different suffix,
// defines that are are opposite, of keys.
//
// In order to change layer and other names to match lang.
// foo --> foo_bp or foo.

// A new language just needs entries to match so
// that it will create the proper names when LANG_IS
// set to the appropriate values.
// sonly the pfx and sfx functions need additions for
// another language.
// The rest is making sure there are keymap chunks
// defined as needed.
#define COMMA ,

#define CONCATENATE(a, ...) a ## __VA_ARGS__
#define CAT(a, ...) CONCATENATE(a, __VA_ARGS__)

// We need another one with a different name.
// The macros are painted blue otherwise.
// Cat gets used at a low level, around keys, or layers basically.
// Cat 2 is used for thumb cluster choices, any of which can contain
// a number of CATS down at the bottom. -- nested macros of the same
// name get painted blue.  So here we are. :-).  look in edge_keys.h
// for THUMBS
#define CONCATENATE2(a, ...) a ## __VA_ARGS__
#define CAT2(a, ...) CONCATENATE2(a, __VA_ARGS__)

#define CONCATENATE3(a, ...) a ## __VA_ARGS__
#define CAT3(a, ...) CONCATENATE3(a, __VA_ARGS__)


#define EMPTY()
#define DEFER(id) id EMPTY()
#define OBSTRUCT(...) __VA_ARGS__ DEFER(EMPTY)()
#define EXPAND(...) __VA_ARGS__

// Give the right keycode prefix by LANG_IS
#define LANG_PFX CAT(LANG_IS, KC)
#define COMBOKC CB
#define COMBO2KC CB2
#define BEPOKC BP
#define ENKC KC
#define US_INTKC US

// Give the right symbol suffix by LANG_IS
#define LANG_SFX CAT(CAT(LANG_IS, _), SFX)
#define LOCALE_LAYERS_SFX _LL // for counting the base layers.
#define COMBO_SFX _CB
#define COMBO2_SFX _CB2
#define BEPO_SFX _BP
#define EN_SFX _EN
#define US_INT_SFX _EN

// Give the right map chunk suffix by LANG_IS
#define LANG_MAPSFX CAT(CAT(LANG_IS, _), MAPSFX)
#define COMBO_MAPSFX _CB___
#define COMBO2_MAPSFX _CB2___
#define BEPO_MAPSFX _BP___
#define EN_MAPSFX _EN___
#define US_INT_MAPSFX _EN___

// These use the mapping above to get their job done.

// In order to create keycode names to match lang.
// A  --> BP_A or KC_A,US_A
#define LANG_KC(NAME) CAT(LANG_PFX, NAME)

// _SYMB -> _SYMB_EN
// _SYMB -> _SYMB_BP
#define LANG_N(NAME) CAT(NAME, LANG_SFX)

// In order to map chunk names to match lang.
// MAP_CHUNK(___15_BOTTOM) --> ___15_BOTTOM_EN___ or ___15_BOTTOM_BP___
#define MAP_CHUNK(NAME) CAT3(NAME, LANG_MAPSFX)


// for the oled layer map switch
#ifdef SECOND_LOCALE
#define LCASE(NAME)                          \
  case CAT2(NAME, _EN):                      \
  case CAT2(NAME, _BP):
#else
#define LCASE(NAME)                          \
  case CAT2(NAME, _EN):
#endif
