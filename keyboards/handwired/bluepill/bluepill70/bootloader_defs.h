/* Address for jumping to bootloader on STM32 chips. */
/* It is chip dependent, the correct number can be looked up here (page 175):
 * http://www.st.com/web/en/resource/technical/document/application_note/CD00167594.pdf
 * This also requires a patch to chibios:
 *  <tmk_dir>/tmk_core/tool/chibios/ch-bootloader-jump.patch
 */

// STM32F103* does NOT have an USB bootloader in ROM (only serial),
//  so setting anything here does not make much sense
// #define STM32_BOOTLOADER_ADDRESS 0x1FFFC800
