include(ParseMakefile)

macro(process_keyboard)
    validate_json(${QMK_KEYBOARD_FOLDER_ABS}/info.json keyboard QMK_KEYBOARD_INFO_JSON_STRING)

    string(JSON KEYBOARD_NAME GET ${QMK_KEYBOARD_INFO_JSON_STRING} keyboard_name)
    string(JSON MANUFACTURER GET ${QMK_KEYBOARD_INFO_JSON_STRING} manufacturer)
    string(JSON URL GET ${QMK_KEYBOARD_INFO_JSON_STRING} url)
    string(JSON QMK_MCU GET ${QMK_KEYBOARD_INFO_JSON_STRING} processor)
    string(JSON VENDOR_ID GET ${QMK_KEYBOARD_INFO_JSON_STRING} usb vid)
    string(JSON PRODUCT_ID GET ${QMK_KEYBOARD_INFO_JSON_STRING} usb pid)
    string(JSON DEVICE_VER GET ${QMK_KEYBOARD_INFO_JSON_STRING} usb device_version)
    string(JSON DIODE_DIRECTION ERROR_VARIABLE _ GET ${QMK_KEYBOARD_INFO_JSON_STRING} diode_direction)
    string(JSON BOOTLOADER ERROR_VARIABLE _ GET ${QMK_KEYBOARD_INFO_JSON_STRING} bootloader)

    ParseMakefile(${QMK_KEYBOARD_FOLDER_ABS}/rules.mk)  
endmacro()