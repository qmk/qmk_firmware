use core::alloc::{GlobalAlloc, Layout};

#[alloc_error_handler]
fn alloc_error(layout: Layout) -> ! {
    // it's CURRENT_YEAR, if your keyboard isn't printing allocation errors,
    // what are you even doing?
    unsafe {
        let mut buf = [0; 16];
        usize_to_buf(&mut buf, layout.size());
        crate::bindgen::send_string("keyboard allocation error: \0".as_ptr());
        crate::bindgen::send_string(buf.as_ptr());
    }
    loop {}
}

/// Global Allocator that hooks into malloc/free
pub struct MallocFreeAlloc;

unsafe impl GlobalAlloc for MallocFreeAlloc {
    unsafe fn alloc(&self, layout: Layout) -> *mut u8 {
        crate::bindgen::malloc(layout.size() as u32) as *mut u8
    }
    unsafe fn dealloc(&self, ptr: *mut u8, _layout: Layout) {
        crate::bindgen::free(ptr as *mut crate::bindgen::ctypes::c_void)
    }
}

fn usize_to_buf(dst: &mut [u8], mut x: usize) {
    let mut p = 0;
    while x != 0 {
        dst[p] = (x % 10) as u8 + b'0';
        x /= 10;
        p += 1;
    }
    dst[..p].reverse();
    // null terminator
    dst[p] = 0;
}
