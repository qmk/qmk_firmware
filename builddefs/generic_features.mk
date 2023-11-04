# Copyright 2021 QMK
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

SPACE_CADET_ENABLE ?= yes
GRAVE_ESC_ENABLE ?= yes

GENERIC_FEATURES = \
    AUTOCORRECT \
    CAPS_WORD \
    COMBO \
    COMMAND \
    DEFERRED_EXEC \
    DIGITIZER \
    DIP_SWITCH \
    DYNAMIC_KEYMAP \
    DYNAMIC_MACRO \
    GRAVE_ESC \
    HAPTIC \
    KEY_LOCK \
    KEY_OVERRIDE \
    LEADER \
    PROGRAMMABLE_BUTTON \
    REPEAT_KEY \
    SECURE \
    SPACE_CADET \
    SWAP_HANDS \
    TAP_DANCE \
    WPM \
    DYNAMIC_TAPPING_TERM \
    TRI_LAYER

define HANDLE_GENERIC_FEATURE
    # $$(info "Processing: $1_ENABLE $2.c")
    SRC += $$(wildcard $$(QUANTUM_DIR)/process_keycode/process_$2.c)
    SRC += $$(wildcard $$(QUANTUM_DIR)/$2/$2.c)
    SRC += $$(wildcard $$(QUANTUM_DIR)/$2.c)
    VPATH += $$(wildcard $$(QUANTUM_DIR)/$2/)
    OPT_DEFS += -D$1_ENABLE
endef

$(foreach F,$(GENERIC_FEATURES),\
    $(if $(filter yes, $(strip $($(F)_ENABLE))),\
        $(eval $(call HANDLE_GENERIC_FEATURE,$(F),$(shell echo $(F) | tr '[:upper:]' '[:lower:]'))) \
    ) \
)
