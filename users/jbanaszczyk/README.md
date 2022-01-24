Copyright 2022 jbanaszczyk https://github.com/jbanaszczyk

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

---

# User Space for jbanaszczyk

## DO_NOT_SLEEP

* Configure `do_not_sleep.h`
  * define `DO_NOT_SLEEP_TIMEOUT`
    * for testing purposes use some small value, for example `4`
  * define `DO_NOT_SLEEP_ACTION_KEY`. good choices are: 
    * `KC_LCTL`
    * `KC_WAKE`
  * define or undefine `DO_NOT_SLEEP_START_LOCKED`
* Make sure, that `KC_DO_NOT_SLEEP_START` and `KC_DO_NOT_SLEEP_STOP` are defined
  * example: `jbanaszczyk_keycodes.h`
* Edit `rules.mk` (see below)
* Include `do_not_sleep_process(keycode, record)` within `process_record_user(uint16_t keycode, keyrecord_t *record)`
* Use calls from `jbanaszczyk.c` (look for `#ifdef DO_NOT_SLEEP`)

### example of `rules.mk`

```
DO_NOT_SLEEP_ENABLE = yes
SRC += do_not_sleep.c
ifeq ($(strip $(DO_NOT_SLEEP_ENABLE)), yes)
    OPT_DEFS += -DDO_NOT_SLEEP
endif
```

# For the future
  
## DONE

* DO_NOT_SLEEP

## TODO

* layers redo
* Grave esc: \` with alt
* Single key tilde
* raise tap dance
* Fn tap dance
* Autoreset
* qmk_firmware\keyboards\omnikeyish\dynamic_macro.h
* LTO_ENABLE

## Inspirations

* /users/alfrdmalr/readme.md
  * Leader Key Sequence: R-E-S-E-T
* /users/bbaserdem/README.md
  * locking layers
  * Mouse emulation, complete with diagonal keys.
* /users/callum/readme.md
  * Hold `sym` and `nav` together to activate the numbers layer.
* /users/replicaJunction/readme.md
  * CAPS_WORD
  * Mouse Jiggler
* shift backspaxe for delete
  * https://docs.qmk.fm/#/feature_advanced_keycodes?id=shift-backspace-for-delete