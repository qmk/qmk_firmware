# The Denwir D60 case has a sealed/solid undercase,
#  this enables switching off thoes LEDs
# Usage:  `make idobao/id61:default UNDERGLOW=off`

ifeq ($(findstring off,$(UNDERGLOW)), off)
  OPT_DEFS += -DID61_DISABLE_UNDERGLOW
else ifeq ($(findstring no,$(UNDERGLOW)), no)
  OPT_DEFS += -DID61_DISABLE_UNDERGLOW
else ifeq ($(findstring 0,$(UNDERGLOW)), 0)
  OPT_DEFS += -DID61_DISABLE_UNDERGLOW
endif
