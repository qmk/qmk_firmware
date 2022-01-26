Copyright 2022 jbanaszczyk https://github.com/jbanaszczyk

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public
License as published by the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not,
see <http://www.gnu.org/licenses/>.

---

# User Space for jbanaszczyk

## DO_NOT_SLEEP

Sends a keystroke (for example KC_LCTL or KC_WAKE)

* after long period of inactivity
* to avoid computer locking

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
* Use calls from `jbanaszczyk.c` (look for `#ifdef DO_NOT_SLEEP`)
* requires DEFERRED_EXEC_ENABLE = yes

### example of `rules.mk`

```
DO_NOT_SLEEP_ENABLE = yes
ifeq ($(strip $(DO_NOT_SLEEP_ENABLE)), yes)
    OPT_DEFS += -DDO_NOT_SLEEP
    SRC += do_not_sleep.c
endif
```

## AUTO_CAPS_OFF

Automatically turns off CAPS_LOCK, SCROLL_LOCK and NUM_LOCK

* after long period of inactivity
* requires DEFERRED_EXEC_ENABLE = yes

### example of `rules.mk`

```
ifeq ($(strip $(AUTO_CAPS_OFF_ENABLE)), yes)
    OPT_DEFS += -DAUTO_CAPS_OFF
    SRC += auto_caps_off.c
endif
```

## DONE

* DO_NOT_SLEEP
* AUTO_CAPS_OFF

## TODO

## Inspirations

* /users/callum/readme.md
    * Hold `sym` and `nav` together to activate the numbers layer.
* /users/replicaJunction/readme.md
    * CAPS_WORD
