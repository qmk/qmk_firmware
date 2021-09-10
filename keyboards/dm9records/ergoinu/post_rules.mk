ifneq ($(strip $(ERGOINU)),)
  ifeq ($(findstring promicroled, $(ERGOINU)), promicroled)
    DISABLE_PROMICRO_LEDs = no
  endif
endif

ifeq ($(strip $(DISABLE_PROMICRO_LEDs)), yes)
  OPT_DEFS += -DDISABLE_PROMICRO_LEDs
endif
