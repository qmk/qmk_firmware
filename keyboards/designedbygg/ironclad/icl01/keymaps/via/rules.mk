VIA_ENABLE = yes

# Reduce RAM usage
ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
LTO_ENABLE = yes
endif