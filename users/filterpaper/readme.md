Copyright 2021 @filterpaper

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

# Summary

Common user space code for a few custom keyboards. See https://docs.qmk.fm/#/feature_userspace?id=userspace-sharing-code-between-keymaps for more details.
## File list
* `config.h`	Self-explainatory QMK configuration options
* `rules.mk`	Makefile rules for common and keyboard-specific features
* `keyboard.c`	Common keyboard code and RGB specific functions
* `oled.c`		Corne split keyboard OLED code with bongo cat
