# The Denwir D60 case has a sealed/solid undercase,
#  this enables switching off thoes LEDs
# Usage:  `make idobao/id61:default UNDERGLOW=off`

UNDERGLOW ?= yes
ifneq ($(strip $(UNDERGLOW)), yes)
  OPT_DEFS += -DID61_DISABLE_UNDERGLOW
endif
