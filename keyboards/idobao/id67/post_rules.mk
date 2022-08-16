# Some ID67 variants (v1 base build & "Bestype") have a solid back plate,
#  this enables switching off thoes LEDs
# Usage:  `make idobao/id67:default UNDERGLOW=off`

ifeq ($(findstring off,$(UNDERGLOW)), off)
  $(info ** UNDERGLOW OFF)
  OPT_DEFS += -DID67_DISABLE_UNDERGLOW
else ifeq ($(findstring no,$(UNDERGLOW)), no)
  $(info ** NO UNDERGLOW)
  OPT_DEFS += -DID67_DISABLE_UNDERGLOW
else ifeq ($(findstring 0,$(UNDERGLOW)), 0)
  $(info ** Nil UNDERGLOW)
  OPT_DEFS += -DID67_DISABLE_UNDERGLOW
endif
