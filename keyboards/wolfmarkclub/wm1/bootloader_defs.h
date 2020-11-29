/* Address for jumping to bootloader on STM32 chips. */
/* It is chip dependent, the correct number can be looked up here (page 175):
 * http://www.st.com/web/en/resource/technical/document/application_note/CD00167594.pdf
 * This also requires a patch to chibios:
 *  <tmk_dir>/tmk_core/tool/chibios/ch-bootloader-jump.patch
 */

// STM32F103 does not have a USB bootloader in ROM -- the WM1
// has a usermode USB mass storage device bootloader at the normal
// boot address -- `0x08000000`.
#define STM32_BOOTLOADER_ADDRESS 0x80000000
