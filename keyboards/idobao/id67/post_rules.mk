# Some ID67 variants (v1 base build & "Bestype") have a solid back plate,
#  this enables switching off thoes LEDs
# Usage:  `make idobao/id67:default UNDERGLOW=off`

UNDERGLOW ?= yes
ifneq ($(strip $(UNDERGLOW)), yes)
  OPT_DEFS += -DID67_DISABLE_UNDERGLOW
endif
