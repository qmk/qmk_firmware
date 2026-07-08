# Eager per-key debounce (registers on first edge -> lower latency).
# Was previously in keyboards/.../6x6/rules.mk, which QMK removed along with
# DEFAULT_FOLDER; kept here at the keymap level. See readme.md.
DEBOUNCE_TYPE = sym_eager_pk
