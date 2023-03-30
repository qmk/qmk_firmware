/**
 * \defgroup pico_btstack pico_btstack
 * \brief Integration/wrapper libraries for <a href="https://github.com/bluekitchen/btstack">BTstack</a>
 * the documentation for which is <a href="https://bluekitchen-gmbh.com/btstack/">here</a>.
 *
 * The \c \b pico_btstack_ble library adds the support needed for Bluetooth Low Energy (BLE). The \c \b pico_btstack_classic library adds the support needed for Bluetooth Classic.
 * You can link to either library individually, or to both libraries thus enabling dual-mode support provided by BTstack.
 *
 * To use BTstack you need to provide a \c btstack_config.h file in your source tree and add its location to your include path.
 * The BTstack configuration macros \c ENABLE_CLASSIC and \c ENABLE_BLE are defined for you when you link the \c pico_btstack_classic and \c pico_btstack_ble libraries respectively, so you should not define them yourself.
 *
 * For more details, see <a href="https://bluekitchen-gmbh.com/btstack/develop/#how_to/">How to configure BTstack</a> and the relevant <a href="https://github.com/raspberrypi/pico-examples#pico-w-bluetooth">pico-examples</a>.
 *
 * The follow ibraries provided for you to link.
 * * \c \b pico_btstack_ble - Adds Bluetooth Low Energy (LE) support.
 * * \c \b pico_btstack_classic - Adds Bluetooth Classic support.
 * * \c \b pico_btstack_sbc_encoder - Adds Bluetooth Sub Band Coding (SBC) encoder support.
 * * \c \b pico_btstack_sbc_decoder - Adds Bluetooth Sub Band Coding (SBC) decoder support.
 * * \c \b pico_btstack_bnep_lwip - Adds Bluetooth Network Encapsulation Protocol (BNEP) support using LwIP.
 * * \c \b pico_btstack_bnep_lwip_sys_freertos - Adds Bluetooth Network Encapsulation Protocol (BNEP) support using LwIP with FreeRTOS for NO_SYS=0.
 *
 * \note The CMake function pico_btstack_make_gatt_header can be used to run the BTstack compile_gatt tool to make a GATT header file from a BTstack GATT file.
 *
 * \sa pico_btstack_cyw43 in pico_cyw43_driver, which adds the cyw43 driver support needed for BTstack including BTstack run loop support.
 */
