# qmk-sys

Rust bindings to QMK C/C++ headers.

By default, this crate only generates bindings for `quantum.h`, and the current keymap's `config.h` and `QUANTUM_KEYBOARD_H`.
Additional bindings can be specified via the `RUST_QMK_HEADERS` environment variable. (e.g: `RUST_QMK_HEADERS="rgb_matrix.h"`)

**THIS CRATE IS DESIGNED TO BE BUILT VIA QMK'S MAKEFILE BUILD SYSTEM, AND RELIES ON SEVERAL ENVIRONMENT VARIABLES / BUILD ARTIFACTS TO FUNCTION!**
