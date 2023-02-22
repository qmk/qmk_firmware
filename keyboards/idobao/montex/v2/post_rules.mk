# some (if not most) Montex have a solid back plate,
#  this enables switching off the bottom facing LEDs
# Usage:  `make idobao/montex/v2:default UNDERGLOW=off`

UNDERGLOW ?= yes
ifneq ($(strip $(UNDERGLOW)), yes)
  OPT_DEFS += -DID27_DISABLE_UNDERGLOW
endif
