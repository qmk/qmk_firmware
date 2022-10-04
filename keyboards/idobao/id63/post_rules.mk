# The Denwir D60 case has a sealed/solid undercase,
#  this enables switching off thoes LEDs
# Usage:  `make idobao/id63:default UNDERGLOW=off`

UNDERGLOW ?= yes
ifneq ($(strip $(UNDERGLOW)), yes)
  OPT_DEFS += -DID63_DISABLE_UNDERGLOW
endif
