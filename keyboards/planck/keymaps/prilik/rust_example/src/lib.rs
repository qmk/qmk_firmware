#![no_std]
#![feature(alloc_prelude)]

#[macro_use]
extern crate alloc;

#[global_allocator]
static ALLOCATOR: qmk::malloc::MallocFreeAlloc = qmk::malloc::MallocFreeAlloc;

pub mod keymap;
