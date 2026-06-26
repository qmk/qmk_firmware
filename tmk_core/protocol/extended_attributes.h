/* Spdx-License-Identifer: GPL-2.0-or-later OR APACHE-2.0 */
#pragma once

#include <stdint.h>

#ifndef CONCAT
#    define CONCAT(a, b) a##b
#endif

#if defined(KEYBOARD_EXT_ATTR_VENDOR_LAYOUT)
#    if defined(KEYBOARD_EXT_ATTR_PHYSICAL_LAYOUT)
#        error "specified both vendor and standard layout"
#    endif
#    define KEYBOARD_EXT_ATTR_PHYSICAL_LAYOUT vendor
#    define KEYBOARD_VENDOR_LAYOUT KEYBOARD_EXT_ATTR_VENDOR_LAYOUT
#else
#    define KEYBOARD_VENDOR_LAYOUT 0
#endif /* defined(KEYBOARD_ATTR_VENDOR_LAYOUT) */

#define KEYBOARD_PHYSICAL_LAYOUT_unkown 0
#define KEYBOARD_PHYSICAL_LAYOUT_ANSI 1
#define KEYBOARD_PHYSICAL_LAYOUT_KS 2
#define KEYBOARD_PHYSICAL_LAYOUT_ISO 3
#define KEYBOARD_PHYSICAL_LAYOUT_ABNT 4
#define KEYBOARD_PHYSICAL_LAYOUT_JIS 5
#define KEYBOARD_PHYSICAL_LAYOUT_vendor 6
#define KEYBOARD_PHYSICAL_LAYOUT_(layout) CONCAT(KEYBOARD_PHYSICAL_LAYOUT_, layout)
#define KEYBOARD_PHYSICAL_LAYOUT KEYBOARD_PHYSICAL_LAYOUT_(KEYBOARD_EXT_ATTR_PHYSICAL_LAYOUT)

#if !defined(KEYBOARD_EXT_ATTR_KEY_TYPE)
#    define KEYBOARD_EXT_ATTR_KEY_TYPE unkown
#endif

#define KEYBOARD_KEY_TYPE_unkown 0
#define KEYBOARD_KEY_TYPE_full 1
#define KEYBOARD_KEY_TYPE_low 2
#define KEYBOARD_KEY_TYPE_zero 3
#define KEYBOARD_KEY_TYPE_(keytype) CONCAT(KEYBOARD_KEY_TYPE_, keytype)
#define KEYBOARD_KEY_TYPE KEYBOARD_KEY_TYPE_(KEYBOARD_EXT_ATTR_KEY_TYPE)

#ifndef KEYBOARD_EXT_ATTR_FORM_FACTOR
#    define KEYBOARD_EXT_ATTR_FORM_FACTOR unkown
#endif

#define KEYBOARD_FORM_FACTOR_unkown 0
#define KEYBOARD_FORM_FACTOR_full_size 1
#define KEYBOARD_FORM_FACTOR_compact 2
#define KEYBOARD_FORM_FACTOR_(form_factor) CONCAT(KEYBOARD_FORM_FACTOR_, form_factor)
#define KEYBOARD_FORM_FACTOR KEYBOARD_FORM_FACTOR_(KEYBOARD_EXT_ATTR_FORM_FACTOR)

#ifdef KEYBOARD_EXT_ATTR_IETF_LANGUAGE_TAG
#    define KEYBOARD_PRIMARY_LOCALE KEYBOARD_EXT_ATTR_IETF_LANGUAGE_TAG
#    define KEYBOARD_EXT_ATTR_LOCALE(locale_index) locale_index
#else
#    define KEYBOARD_EXT_ATTR_LOCALE(locale_index) 0
#endif

/*
 * TODO: implement consumer remote control report for keyboard input assists.
 */
#ifndef KEYBOARD_IMPLEMENTED_INPUT_ASSIST_CONTROLS
#    define KEYBOARD_IMPLEMENTED_INPUT_ASSIST_CONTROLS 0
#endif

typedef struct [[gnu::packed]] keyboard_extended_attributes {
#ifdef KEYBOARD_SHARED_EP
    uint8_t report_id;
#endif
    uint8_t form_factor;
    uint8_t key_type;
    uint8_t physical_layout;
    uint8_t vendor_physical_layout;
    uint8_t ietf_language_tag_index;
    uint8_t implemented_assist_controls;
} keyboard_extended_attributes_t;

#ifdef KEYBOARD_SHARED_EP
#    define KEYBOARD_EXT_ATTR_REPORT_ID_INIT(id) .report_id = id,
#else
#    define KEYBOARD_EXT_ATTR_REPORT_ID_INIT(id)
#endif

#define KEYBOARD_EXT_ATTR_INIT_(id_init, locale_index, ...) {id_init.form_factor = KEYBOARD_FORM_FACTOR, .key_type = KEYBOARD_KEY_TYPE, .physical_layout = KEYBOARD_PHYSICAL_LAYOUT, .vendor_physical_layout = KEYBOARD_VENDOR_LAYOUT, .ietf_language_tag_index = locale_index, .implemented_assist_controls = KEYBOARD_IMPLEMENTED_INPUT_ASSIST_CONTROLS, __VA_ARGS__}
/**
 * \brief initialize keyboard_extended_attributes_t
 * \param locale_index - String Descriptor index for the Keyboard Locale String (IETF BCP 47 Language Tag)
 *      representing the (primary) locale of the printed keycap legend set.
 * \param - overrides in unbraced .field = value list form.
 * \returns - initializer_list for a keyboard_extended_attributes_t or struct keyboard_extended_attributes
 */
#define KEYBOARD_EXT_ATTR_INIT(locale_index, ...) KEYBOARD_EXT_ATTR_INIT_(KEYBOARD_EXT_ATTR_REPORT_ID_INIT(REPORT_ID_KEYBOARD), KEYBOARD_EXT_ATTR_LOCALE(locale_index), __VA_ARGS__) // override defaults
