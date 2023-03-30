/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <iostream>
#include "pio_assembler.h"

#define DEFAULT_OUTPUT_FORMAT "c-sdk"

void usage() {
    std::cerr << "usage: pioasm <options> <input> (<output>)\n\n";
    std::cerr << "Assemble file of PIO program(s) for use in applications.\n";
    std::cerr << "   <input>             the input filename\n";
    std::cerr << "   <output>            the output filename (or filename prefix if the output format produces multiple outputs).\n";
    std::cerr << "                       if not specified, a single output will be written to stdout\n";
    std::cerr << "\n";
    std::cerr << "options:\n";
    std::cerr << "  -o <output_format>   select output_format (default '" << DEFAULT_OUTPUT_FORMAT << "'); available options are:\n";
    for(const auto& f : output_format::all()) {
        std::cerr << "                           " << f->name << std::endl;
        std::cerr << "                               " << f->get_description() << std::endl;
    }
    std::cerr << "  -p <output_param>    add a parameter to be passed to the output format generator" << std::endl;
    std::cerr << "  -?, --help           print this help and exit\n";
}

int main(int argc, char *argv[]) {
    int res = 0;
    pio_assembler pioasm;
    std::string format(DEFAULT_OUTPUT_FORMAT);
    const char *input = nullptr;
    const char *output = nullptr;
    std::vector<std::string> options;
    int i = 1;
    for (; !res && i < argc; i++) {
        if (argv[i][0] != '-') break;
        if (argv[i] == std::string("-o")) {
            if (++i < argc) {
                format = argv[i];
            } else {
                std::cerr << "error: -o requires format value" << std::endl;
                res = 1;
            }
        } else if (argv[i] == std::string("-p")) {
            if (++i < argc) {
                options.emplace_back(argv[i]);
            } else {
                std::cerr << "error: -p requires parameter value" << std::endl;
                res = 1;
            }
        } else if (argv[i] == std::string("-?") || argv[i] == std::string("--help")) {
            usage();
            return 1;
        } else {
            std::cerr << "error: unknown option " << argv[i] << std::endl;
            res = 1;
        }
    }
    if (!res) {
        if (i != argc) {
            input = argv[i++];
        } else {
            std::cerr << "error: expected input filename\n";
            res = 1;
        }
    }
    if (!res) {
        if (i != argc) {
            output = argv[i++];
        } else {
            output = "-";
        }
    }
    if (!res && i != argc) {
        std::cerr << "unexpected command line argument " << argv[i] << std::endl;
        res = 1;
    }
    std::shared_ptr<output_format> oformat;
    if (!res) {
        const auto& e = std::find_if(output_format::all().begin(), output_format::all().end(),
                                     [&](const std::shared_ptr<output_format> &f) {
                                         return f->name == format;
                                     });
        if (e == output_format::all().end()) {
            std::cerr << "error: unknown output format '" << format << "'" << std::endl;
            res = 1;
        } else {
            oformat = *e;
        }
    }
    if (res) {
        std::cerr << std::endl;
        usage();
    } else {
        res = pioasm.generate(oformat, input, output, options);
    }
    return res;
}