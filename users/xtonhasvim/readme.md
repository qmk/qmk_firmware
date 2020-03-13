
# Xton has Vim!

Contains common code for Xton's vim emulation (vimulation?) layer.

Inspired/stolen from the `ergodox_ez/vim` keymap. Rewritten to be a more straightforward state machine and support more macros. Vim layers `_CMD` and `_EDIT` are designed to lay on top of an otherwise fully-functional layout. `_CMD` runs the entire vim state machine while `_EDIT` should lay across your base layer and mask off just the escape key.

Works via OSX text editing shortcuts, mainly MOD+arrow combinations. This has some limitations and only works on OSX. 

The `_CMD` layer will temporarily disable itself while *CMD* or *ALT* are held down so that typical OSX shortcuts can be used without switching out of vim mode.
