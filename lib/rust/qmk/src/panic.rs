#[panic_handler]
fn my_panic(_info: &core::panic::PanicInfo<'_>) -> ! {
    loop {}
}
