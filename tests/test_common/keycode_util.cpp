#include "keycode_util.hpp"
#include <cstdint>
extern "C" {
#include "action_code.h"
#include "keycode.h"
#include "quantum_keycodes.h"
#include "util.h"
}
#include <string>
#include <iomanip>
#include <map>

extern std::map<uint16_t, std::string> KEYCODE_ID_TABLE;

std::string get_mods(uint8_t mods) {
    std::stringstream s;
    if ((mods & MOD_RCTL) == MOD_RCTL) {
        s << XSTR(MOD_RCTL) << " | ";
    } else if ((mods & MOD_LCTL) == MOD_LCTL) {
        s << XSTR(MOD_LCTL) << " | ";
    }

    if ((mods & MOD_RSFT) == MOD_RSFT) {
        s << XSTR(MOD_RSFT) << " | ";
    } else if ((mods & MOD_LSFT) == MOD_LSFT) {
        s << XSTR(MOD_LSFT) << " | ";
    }

    if ((mods & MOD_RALT) == MOD_RALT) {
        s << XSTR(MOD_RALT) << " | ";
    } else if ((mods & MOD_LALT) == MOD_LALT) {
        s << XSTR(MOD_LALT) << " | ";
    }

    if ((mods & MOD_RGUI) == MOD_RGUI) {
        s << XSTR(MOD_RGUI) << " | ";
    } else if ((mods & MOD_LGUI) == MOD_LGUI) {
        s << XSTR(MOD_LGUI) << " | ";
    }

    auto _mods = s.str();

    if (_mods.size()) {
        _mods.resize(_mods.size() - 3);
    }

    return std::string(_mods);
}

std::string get_qk_mods(uint16_t keycode) {
    std::stringstream s;
    if ((keycode & QK_RCTL) == QK_RCTL) {
        s << XSTR(QK_RCTL) << " | ";
    } else if ((keycode & QK_LCTL) == QK_LCTL) {
        s << XSTR(QK_LCTL) << " | ";
    }

    if ((keycode & QK_RSFT) == QK_RSFT) {
        s << XSTR(QK_RSFT) << " | ";
    } else if ((keycode & QK_LSFT) == QK_LSFT) {
        s << XSTR(QK_LSFT) << " | ";
    }

    if ((keycode & QK_RALT) == QK_RALT) {
        s << XSTR(QK_RALT) << " | ";
    } else if ((keycode & QK_LALT) == QK_LALT) {
        s << XSTR(QK_LALT) << " | ";
    }

    if ((keycode & QK_RGUI) == QK_RGUI) {
        s << XSTR(QK_RGUI) << " | ";
    } else if ((keycode & QK_LGUI) == QK_LGUI) {
        s << XSTR(QK_LGUI) << " | ";
    }

    auto _mods = s.str();

    if (_mods.size()) {
        _mods.resize(_mods.size() - 3);
    }

    return std::string(_mods);
}

std::string generate_identifier(uint16_t kc) {
    std::stringstream s;
    if (IS_QK_MOD_TAP(kc)) {
        s << "MT(" << get_mods(QK_MOD_TAP_GET_MODS(kc)) << ", " << KEYCODE_ID_TABLE.at(kc & 0xFF) << ")";
    } else if (IS_QK_LAYER_TAP(kc)) {
        s << "LT(" << +QK_LAYER_TAP_GET_LAYER(kc) << ", " << KEYCODE_ID_TABLE.at(kc & 0xFF) << ")";
    } else if (IS_QK_TO(kc)) {
        s << "TO(" << +QK_TO_GET_LAYER(kc) << ")";
    } else if (IS_QK_MOMENTARY(kc)) {
        s << "MO(" << +QK_MOMENTARY_GET_LAYER(kc) << ")";
    } else if (IS_QK_DEF_LAYER(kc)) {
        s << "DF(" << +QK_DEF_LAYER_GET_LAYER(kc) << ")";
    } else if (IS_QK_TOGGLE_LAYER(kc)) {
        s << "TG(" << +QK_TOGGLE_LAYER_GET_LAYER(kc) << ")";
    } else if (IS_QK_LAYER_TAP_TOGGLE(kc)) {
        s << "TT(" << +QK_LAYER_TAP_TOGGLE_GET_LAYER(kc) << ")";
    } else if (IS_QK_ONE_SHOT_LAYER(kc)) {
        s << "OSL(" << +QK_ONE_SHOT_LAYER_GET_LAYER(kc) << ")";
    } else if (IS_QK_LAYER_MOD(kc)) {
        s << "LM(" << +QK_LAYER_MOD_GET_LAYER(kc) << ", " << get_mods(QK_LAYER_MOD_GET_MODS(kc)) << ")";
    } else if (IS_QK_ONE_SHOT_MOD(kc)) {
        s << "OSM(" << get_mods(QK_ONE_SHOT_MOD_GET_MODS(kc)) << ")";
    } else if (IS_QK_MODS(kc)) {
        s << "QK_MODS(" << KEYCODE_ID_TABLE.at(QK_MODS_GET_BASIC_KEYCODE(kc)) << ", " << get_qk_mods(kc) << ")";
    } else if (IS_QK_TAP_DANCE(kc)) {
        s << "TD(" << +(kc & 0xFF) << ")";
    } else {
        // Fallback - we didn't found any matching keycode, generate the hex representation.
        s << "unknown keycode: 0x" << std::hex << kc << ". Add conversion to " << XSTR(generate_identifier);
    }

    return std::string(s.str());
}

std::string get_keycode_identifier_or_default(uint16_t keycode) {
    auto identifier = KEYCODE_ID_TABLE.find(keycode);
    if (identifier != KEYCODE_ID_TABLE.end()) {
        return identifier->second;
    }

    KEYCODE_ID_TABLE[keycode] = generate_identifier(keycode);

    return KEYCODE_ID_TABLE[keycode];
}
