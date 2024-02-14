
$(shell python3 keyboards/beekeeb/piantor/keymaps/qkekos/magic_sturdy/generete_magic_data.py)

VIA_ENABLE = yes
AUTOCORRECT_ENABLE = yes

LTO_ENABLE = yes
KEY_LOCK_ENABLE = yes
NKRO_ENABLE = yes
COMBO_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes
CONSOLE_ENABLE = yes
CAPS_WORD_ENABLE = yes
REPEAT_KEY_ENABLE = yes
KEY_LOCK_ENABLE = yes
TAP_DANCE_ENABLE = yes

VPATH += keyboards/gboards

SRC += combos/general.c

SRC += general/utils.c
SRC += general/caps_word.c
SRC += general/led.c
SRC += general/oneshot.c
SRC += general/swapper.c
SRC += general/custom_keys.c
SRC += general/lower_layer.c
SRC += general/arrows.c

SRC += localization/language_swapper.c
SRC += localization/lang_independant.c

SRC += magic_sturdy/general.c
SRC += magic_sturdy/context_magic.c

SRC += overrides/general.c

SRC += tap_dances/general.c
SRC += tap_dances/multiaction_core.c
SRC += tap_dances/sequences.c

SRC += tap_holds/mod_layer_taps.c
SRC += tap_holds/get_hold.c
SRC += tap_holds/general.c
SRC += tap_holds/interceptions.c

SRC += typing_modes/case_modes.c
SRC += typing_modes/fence.c
