# Copyright 2022 Manna Harbour
# https://github.com/manna-harbour/miryoku

# alternative layout options

ifneq ($(strip $(KEYMAP)),)
  OPT_DEFS += -SCOTTO_ALPHA_$(KEYMAP)
endif
