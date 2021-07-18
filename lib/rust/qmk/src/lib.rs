#![no_std]
#![allow(clippy::empty_loop)]
#![cfg_attr(feature = "malloc", feature(alloc_prelude, alloc_error_handler))]

// re-export raw qmk-sys bindings under the "bindgen" module
pub use qmk_sys as bindgen;

mod panic;

// optionally hook into QMK's malloc/alloc
#[cfg(feature = "malloc")]
extern crate alloc;
#[cfg(feature = "malloc")]
pub mod malloc;
