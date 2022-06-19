#![no_main]
#![no_std]
#![feature(core_ffi_c)]

use core::{ffi::c_uchar, panic::PanicInfo};

extern "C" {
    fn tty_print(s: *const c_uchar);
}
/// This function is called on panic.
#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}

#[no_mangle]
pub extern "C" fn kmain_rs() {
    unsafe {
        tty_print("rust\n".as_ptr());
    }
    loop {}
}
