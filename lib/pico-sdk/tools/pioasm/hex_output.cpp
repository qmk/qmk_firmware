/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "output_format.h"
#include <iostream>

struct hex_output : public output_format {
    struct factory {
        factory() {
            output_format::add(new hex_output());
        }
    };

    hex_output() : output_format("hex") {}

    std::string get_description() {
        return "Raw hex output (only valid for single program inputs)";
    }

    virtual int output(std::string destination, std::vector<std::string> output_options,
                       const compiled_source &source) {
        FILE *out = open_single_output(destination);
        if (!out) return 1;

        if (source.programs.size() > 1) {
            // todo don't have locations any more!
            std::cerr << "error: hex output only supports a single program input\n";
            return 1;
        }
        for (const auto &i : source.programs[0].instructions) {
            fprintf(out, "%04x\n", i);
        }
        if (out != stdout) { fclose(out); }
        return 0;
    }
};

static hex_output::factory creator;
