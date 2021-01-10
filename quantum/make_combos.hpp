#ifndef MAKE_COMBO_HPP
#define MAKE_COMBO_HPP

#include <stddef.h>
#include <stdint.h>

extern "C" {
#include "process_combo.h"
}

namespace impl {

struct sink {
    template <typename... Items>
    explicit constexpr sink(Items&&...) {}
};

template <size_t... Size>
constexpr size_t constexpr_sum() {
    size_t result = 0;
    sink{(result += Size)...};
    return result;
}

template <uint8_t First, uint8_t... Rest>
constexpr uint8_t constexpr_max() {
    uint8_t result = First;
    sink{(result = (Rest > result ? Rest : result))...};
    return result;
}

template <char... String>
struct progmem_string {
    static const char PROGMEM value[sizeof...(String) + 1];
};

template <char... String>
const char progmem_string<String...>::value[sizeof...(String) + 1] = {String..., '\0'};

}  // namespace impl

template <typename CharT, CharT... String>
constexpr auto& operator"" _pgm() {
    return impl::progmem_string<String...>::value;
}

struct combo_term {
    uint16_t value;
};

struct combo_urgent {};

static constexpr uint8_t ALL_LAYER_COMBOS = 0xff;

struct layout_combo_key {
    uint8_t value;

    constexpr layout_combo_key() : value(0xff) {}
    /* implicit */ constexpr layout_combo_key(hid_keyboard_keypad_usage) : value(0xff) {}  // for KC_NO
    /* implicit */ constexpr layout_combo_key(uint8_t value) : value(value) {}
};

struct combo_template {
    combo_action      action{};
    combo_action_type action_type{};
    uint8_t           keys[COMBO_KEY_COUNT]{};
    size_t            key_count;
    uint16_t          combo_term = COMBO_TERM;
    bool              urgent     = false;

    template <typename ActionType, typename KeyType, size_t KeyCount, typename... Metadata>
    constexpr combo_template(ActionType action, const KeyType (&keys)[KeyCount], Metadata... metadata) : key_count(KeyCount) {
        set_action(action);
        for (size_t i = 0; i < KeyCount; ++i) {
            this->keys[i] = static_cast<uint8_t>(keys[i]);
        }
        impl::sink{(set_metadata(metadata), 0)...};
    }

    constexpr void set_action(uint16_t keycode) {
        action.keycode = keycode;
        action_type    = COMBO_ACTION_KEYCODE;
    }

    constexpr void set_action(combo_callback function) {
        action.function = function;
        action_type     = COMBO_ACTION_FUNCTION;
    }

    constexpr void set_action(const char* string) {
        action.string = string;
        action_type   = COMBO_ACTION_STRING;
    }

    constexpr void set_metadata(::combo_term metadata) { combo_term = metadata.value; }

    constexpr void set_metadata(::combo_urgent) { urgent = true; }
};

template <uint8_t LayerId, size_t ComboCount>
struct combo_layer_ref {
    combo_template (&combos)[ComboCount];
};

template <uint8_t LayerId, size_t ComboCount>
constexpr combo_layer_ref<LayerId, ComboCount> combo_layer(combo_template(&&array)[ComboCount]) {
    return {array};
}

template <size_t LayerCount, size_t TotalComboCount>
struct combo_storage_data {
    combo_layer_data layers[LayerCount]{};
    combo_data       combos[TotalComboCount]{};

    constexpr combo_storage_data() {
        for (size_t i = 0; i < LayerCount; ++i) {
            layers[i].combo_count  = 0;
            layers[i].combo_offset = 0;
        }
    }
};

constexpr void copy_combo_template(const combo_template& temp, combo_data& dest) {
    dest.action = temp.action;

    for (uint8_t j = 0; j < COMBO_KEY_BLOCKS_COUNT; ++j) {
        dest.key_mask[j] = 0;
    }

    for (uint8_t j = 0; j < temp.key_count; ++j) {
        const uint8_t combo_key = temp.keys[j];
        dest.key_mask[combo_key / 16] |= (1 << (combo_key % 16));
    }

    combo_metadata metadata{};
    metadata.unpacked.combo_term  = temp.combo_term;
    metadata.unpacked.urgent      = temp.urgent;
    metadata.unpacked.action_type = temp.action_type;
    dest.metadata                 = metadata;
}

template <uint8_t LayerId, size_t ComboCount, size_t LayerCount, size_t TotalComboCount>
constexpr void fill_in_combo_layer(combo_layer_ref<LayerId, ComboCount> layer, combo_storage_data<LayerCount, TotalComboCount>& storage_data, size_t& combos_offset) {
    for (size_t i = 0; i < ComboCount; ++i) {
        copy_combo_template(layer.combos[i], storage_data.combos[combos_offset + i]);
    }

    storage_data.layers[LayerId].combo_count  = ComboCount;
    storage_data.layers[LayerId].combo_offset = combos_offset;

    combos_offset += ComboCount;
}

template <uint8_t LayerId, size_t ComboCount, size_t LayerCount, size_t TotalComboCount, size_t UniversalComboCount>
constexpr void fill_in_combo_layer(combo_layer_ref<LayerId, ComboCount> layer, combo_storage_data<LayerCount, TotalComboCount>& storage_data, size_t& combos_offset, combo_layer_ref<ALL_LAYER_COMBOS, UniversalComboCount> universal_combos) {
    for (size_t i = 0; i < ComboCount; ++i) {
        copy_combo_template(layer.combos[i], storage_data.combos[combos_offset + i]);
    }

    for (size_t i = 0; i < UniversalComboCount; ++i) {
        copy_combo_template(universal_combos.combos[i], storage_data.combos[combos_offset + ComboCount + i]);
    }

    storage_data.layers[LayerId].combo_count  = ComboCount + UniversalComboCount;
    storage_data.layers[LayerId].combo_offset = combos_offset;

    combos_offset += ComboCount + UniversalComboCount;
}

template <uint8_t... LayerIds, size_t... ComboCounts>
constexpr auto make_combos_data(combo_layer_ref<LayerIds, ComboCounts>... combo_layers) {
    constexpr uint8_t  n_layers = impl::constexpr_max<LayerIds...>() + 1;
    constexpr uint16_t n_combos = impl::constexpr_sum<ComboCounts...>();

    combo_storage_data<n_layers, n_combos> storage_data;

    size_t combos_offset = 0;
    impl::sink{(fill_in_combo_layer(combo_layers, storage_data, combos_offset), 0)...};

    return storage_data;
}

template <size_t UniversalComboCount, uint8_t... LayerIds, size_t... ComboCounts>
constexpr auto make_combos_data(combo_layer_ref<ALL_LAYER_COMBOS, UniversalComboCount> universal_combos, combo_layer_ref<LayerIds, ComboCounts>... combo_layers) {
    constexpr uint8_t  n_layers = impl::constexpr_max<LayerIds...>() + 1;
    constexpr uint16_t n_combos = impl::constexpr_sum<ComboCounts...>() + n_layers * UniversalComboCount;

    combo_storage_data<n_layers, n_combos> storage_data;

    size_t combos_offset = 0;
    impl::sink{(fill_in_combo_layer(combo_layers, storage_data, combos_offset, universal_combos), 0)...};

    return storage_data;
}

template <size_t LayerCount, size_t TotalComboCount>
constexpr combo_storage make_combos(const layout_combo_key (&keys_layout)[MATRIX_ROWS][MATRIX_COLS], const combo_storage_data<LayerCount, TotalComboCount>& storage_data) {
    combo_storage storage{};

    for (int16_t row = 0; row < MATRIX_ROWS; ++row) {
        for (int16_t col = 0; col < MATRIX_COLS; ++col) {
            storage.keys[row][col] = keys_layout[row][col].value;
        }
    }

    storage.layer_count = LayerCount;
    storage.layers      = &storage_data.layers[0];
    storage.combos      = &storage_data.combos[0];

    return storage;
}

#endif  // MAKE_COMBO_HPP
