/* Copyright 2021 Nick Brassel (@tzarc)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <quantum.h>
#include <xap.h>

void xap_respond_success(xap_token_t token) {
    xap_send(token, XAP_RESPONSE_FLAG_SUCCESS, NULL, 0);
}

void xap_respond_failure(xap_token_t token, xap_response_flags_t response_flags) {
    xap_send(token, response_flags, NULL, 0);
}

bool xap_respond_data(xap_token_t token, const void *data, size_t length) {
    xap_send(token, XAP_RESPONSE_FLAG_SUCCESS, data, length);
    return true;
}

bool xap_respond_data_P(xap_token_t token, const void *data, size_t length) {
    uint8_t blob[length];
    memcpy_P(blob, data, length);
    return xap_respond_data(token, blob, length);
}

bool xap_respond_u32(xap_token_t token, uint32_t value) {
    xap_send(token, XAP_RESPONSE_FLAG_SUCCESS, &value, sizeof(value));
    return true;
}

uint32_t xap_route_qmk_ffffffffffffffff_getter(void) {
    return 0x12345678;
}

bool xap_respond_get_info_json_chunk(xap_token_t token, const void *data, size_t length) {
    if(length != sizeof(uint16_t)){
        return false;
    }

    uint16_t offset = *((uint16_t*)data);
    xap_route_qmk_info_query_t ret = {0}; 

    bool get_info_json_chunk(uint16_t offset, uint8_t *data, uint8_t data_len);
    get_info_json_chunk(offset, (uint8_t *)&ret, sizeof(ret));

    return xap_respond_data(token, &ret, sizeof(ret));
}

// TODO: how to set this if "custom" is just an empty stub
#ifndef BOOTLOADER_JUMP_SUPPORTED
#    define BOOTLOADER_JUMP_SUPPORTED
#endif

#ifdef BOOTLOADER_JUMP_SUPPORTED
bool xap_respond_request_bootloader_jump(xap_token_t token, const void *data, size_t length) {
    extern uint8_t secure_status;
    uint8_t ret = secure_status == 2;

    // TODO: post to deferred queue so this request can return?
    bool res = xap_respond_data(token, &ret, sizeof(ret));
    reset_keyboard();
    return res;
}
#endif

#if ((defined(DYNAMIC_KEYMAP_ENABLE)))
bool xap_respond_dynamic_keymap_get_keycode(xap_token_t token, const void *data, size_t length) {
    if(length != sizeof(xap_route_dynamic_keymap_get_keymap_keycode_arg_t)){
        return false;
    }

    xap_route_dynamic_keymap_get_keymap_keycode_arg_t* arg = (xap_route_dynamic_keymap_get_keymap_keycode_arg_t*)data;

    uint16_t keycode = dynamic_keymap_get_keycode(arg->layer, arg->row, arg->column);
    return xap_respond_data(token, &keycode, sizeof(keycode));
}

bool xap_respond_dynamic_keymap_set_keycode(xap_token_t token, const void *data, size_t length) {
    if(length != sizeof(xap_route_dynamic_keymap_set_keymap_keycode_arg_t)){
        return false;
    }

    xap_route_dynamic_keymap_set_keymap_keycode_arg_t* arg = (xap_route_dynamic_keymap_set_keymap_keycode_arg_t*)data;

    dynamic_keymap_set_keycode(arg->layer, arg->row, arg->column, arg->keycode);
    xap_respond_success(token);
    return true;
}
#endif
