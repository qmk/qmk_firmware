use alloc::prelude::v1::*;

use lazy_static::lazy_static;

use qmk::bindgen::{keyrecord_t, planck_ez_keycodes, send_unicode_hex_string};

const UC_SHRG: u32 = planck_ez_keycodes::EZ_SAFE_RANGE as u32 + 1;

// example of using a crate from crates.io
lazy_static! {
    static ref SHRUG_STRING: String = {
        let mut s = "¯\\_(ツ)_/¯"
            .chars()
            // example of using "alloc" crate functionality
            .map(|c| format!("{:04X}", c as u32))
            .collect::<Vec<_>>()
            .join(" ");
        s.push('\0');
        s
    };
}

#[no_mangle]
pub unsafe extern "C" fn process_record_user_rs(keycode: u16, record: *const keyrecord_t) -> bool {
    process_record_user(keycode, &*record)
}

fn process_record_user(keycode: u16, record: &keyrecord_t) -> bool {
    if !shrug(keycode, record) {
        return false;
    }

    true
}

fn shrug(keycode: u16, record: &keyrecord_t) -> bool {
    match keycode as u32 {
        UC_SHRG => {
            if record.event.pressed {
                unsafe {
                    send_unicode_hex_string(SHRUG_STRING.as_ptr());
                }
            }
            return false;
        }
        _ => {}
    }

    true
}
