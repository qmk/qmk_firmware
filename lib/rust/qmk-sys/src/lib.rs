#![no_std]
#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]
#![allow(dead_code)]
#![allow(safe_packed_borrows)] // this is a bit dangerous...
#![allow(clippy::all)]

pub mod ctypes {
    #[repr(u8)]
    pub enum c_void {
        #[doc(hidden)]
        __variant1,
        #[doc(hidden)]
        __variant2,
    }

    pub type c_char = u8;
    pub type c_schar = i8;
    pub type c_uchar = u8;
    pub type c_short = i16;
    pub type c_ushort = u16;
    pub type c_int = i32;
    pub type c_uint = u32;
    pub type c_float = f32;
    pub type c_double = f64;
    pub type c_long = i32;
    pub type c_longlong = i64;
    pub type c_ulong = u32;
    pub type c_ulonglong = u64;
    pub type intmax_t = i64;
    pub type uintmax_t = u64;

    pub type size_t = usize;
    pub type ptrdiff_t = isize;
    pub type intptr_t = isize;
    pub type uintptr_t = usize;
    pub type ssize_t = isize;
}

include!(concat!(env!("OUT_DIR"), "/bindings.rs"));
