# T4CORUN

Here is where you will find all my changes going forward as I find I was duplicating notes across multiple keyboard readme's.

Author: Victor Nguyen

- [T4CORUN](#t4corun)
	- [Compile Commands](#compile-commands)
	- [Changelog](#changelog)

## Compile Commands

```Makefile
qmk compile -kb crkbd/rev1 -km T4CORUN
qmk compile -kb planck/rev6 -km T4CORUN
qmk compile -kb dztech/dz60rgb/v2_1 -km T4CORUN
qmk compile -kb boardsource/beiwagon -km Jolit
```

## Changelog

2023-03-23 [T4CORUN/qmk_firmware@87e0f64](https://github.com/T4CORUN/qmk_firmware/commit/87e0f64c2afc5e3b21312a7bc0ccff17df42509c)

- Fixed [2023 Breaking Changes](https://docs.qmk.fm/#/ChangeLog/20230226?id=qmk-breaking-changes-2023-february-26-changelog)
	- Replaced `IGNORE_MOD_TAP_INTERRUPT_PER_KEY` for `HOLD_ON_OTHER_KEY_PRESS`. Setup structure for per key configuration, however no customizations. Everything behaves like `IGNORE_MOD_TAP_INTERRUPT`
	- Replace `TAPPING_FORCE_HOLD` for `QUICK_TAP_TERM`. Set it for 120 and setup structure for per key configuration, however no customizations
- Fixed bug in Ternary operators in my userspace `rules.mk`. It was populating `COMBO_ENABLE` instead the correct variable for each section

2023-04-09

- Setup a new fork and copied over all my files. Had many issues compiling firmware, maybe everything was messed up from me trying to rollback commits. Had "obsolete configuration" errors in hal.h from compiling muse.c
- Goal was to try to all four boards to compile
	- Wrapper: AU_TOG to AU_TOGG per doco for Planck
	- Wrapper: MU_TOG to MU_TOGG per doco for Planck
	- Wrapper: Added num row for DZ60RGB
	- Wrapper: Added func row for DZ60RGB
	- T4CORUN.h: added FUN_DEL back for DZ60RGB
	- DZ60RGB Keymap: fixed base layer because I made QWERTY_R2 only five bindings
	- DZ60RGB keymap: Changed KC_GESC to QK_GESC per doco
	- DZ60RGB keymap: CHanged KC_SLCK to KC_SCRL per doco
	- DZ60RGB keymap: changed RESET to QK_BOOT per doco
	- DZ60RGB keymap: changed EEP_RST to EE_CLR per doco
	- left artsey.h: Changed KC_PGDOWN to KC_PGDN per doco
	- left macros.c: Changed KC_LSHIFT to KC_LSFT per doco
	- left macros.c: Changed KC_LCTRL to KC_LCTL per doco
	- Beiwagon keymap: changed RESET to QK_BOOT per doco
