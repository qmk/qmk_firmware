# Don’t do a tricolor flashing-light wave when the computer is shut down in Windows,
# or when the machine is sleeping in macOS
SLEEP_LED_ENABLE = no

# other debounce types: sym_g (whole-keyboard, default), eager_pr (eager per-row), eager_pk (per-key)

DEBOUNCE_DIR:= $(QUANTUM_DIR)/debounce
DEBOUNCE_TYPE?= eager_pr
ifneq ($(strip $(DEBOUNCE_TYPE)), custom)
    QUANTUM_SRC += $(DEBOUNCE_DIR)/$(strip $(DEBOUNCE_TYPE)).c
endif
