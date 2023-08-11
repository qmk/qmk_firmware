/*
Copyright 2023 Joe Scotto
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// config added when Tap Dance is enabled
#ifdef TAP_DANCE_ENABLE
#    ifdef TAPPING_TERM
#        undef TAPPING_TERM
#        define TAPPING_TERM 135
#    endif
#    define TAPPING_TERM_PER_KEY
#    define PERMISSIVE_HOLD
#endif
