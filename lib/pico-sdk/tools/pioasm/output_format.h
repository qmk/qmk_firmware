/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _OUTPUT_FORMAT_H
#define _OUTPUT_FORMAT_H

#include <vector>
#include <map>
#include <string>
#include <memory>

typedef unsigned int uint;

// can't use optional because we want to support older compilers
template<typename T>
struct simple_optional {
    T value;
    T default_value;
    bool specified;

    simple_optional() : default_value(), specified(false) {}

    simple_optional(const T &value) : value(value), specified(true) {}

    simple_optional<T> &operator=(const T &v) {
        value = v;
        specified = true;
        return *this;
    }

    operator bool() = delete; // confusing
    const T &get() const { return specified ? value : default_value; }

    bool is_specified() const { return specified; }

    static simple_optional<T> with_default(const T &default_value) {
        simple_optional<T> rc;
        rc.default_value = default_value;
        return rc;
    }
};

typedef simple_optional<int> optional_int;
typedef simple_optional<bool> optional_bool;

struct compiled_source {
    struct symbol {
        std::string name;
        int value;
        bool is_label;

        symbol(std::string name, int value, bool is_label) : name(std::move(name)), value(value), is_label(is_label) {}
    };

    struct program {
        std::string name;
        optional_int origin = optional_int::with_default(-1);
        optional_int sideset_bits_including_opt;
        bool sideset_opt = false;
        bool sideset_pindirs = false;
        int wrap;
        int wrap_target;
        std::vector<uint> instructions;
        std::vector<symbol> symbols; // public only
        std::map<std::string, std::vector<std::string>> code_blocks;
        std::map<std::string, std::vector<std::pair<std::string,std::string>>> lang_opts;

        // todo can't have wrap at -1
        program(std::string name) : name(std::move(name)) {}
    };

    std::vector<symbol> global_symbols; // public only
    std::vector<program> programs;
};

struct output_format {
    static std::string default_name;

    std::string name;

    static void add(output_format *lang) {
        all().push_back(std::shared_ptr<output_format>(lang));
    }

    virtual int output(std::string destination, std::vector<std::string> output_options,
                       const compiled_source &source) = 0;

    virtual std::string get_description() = 0;

    FILE *open_single_output(std::string destination);
    virtual ~output_format() = default;

    static std::vector<std::shared_ptr<output_format>>& all() {
        static std::vector<std::shared_ptr<output_format>> output_formats;
        return output_formats;
    }
protected:
    output_format(std::string name) : name(std::move(name)) {}
};

#endif