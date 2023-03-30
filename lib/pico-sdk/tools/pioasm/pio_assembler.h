/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PIO_ASSEMBLER_H
#define _PIO_ASSEMBLER_H

#include <algorithm>
#include "parser.hpp"
#include "output_format.h"

// Give Flex the prototype of yylex we want ...
# define YY_DECL \
  yy::parser::symbol_type yylex (pio_assembler& pioasm)
// ... and declare it for the parser's sake.
YY_DECL;


struct pio_assembler {
public:
    using syntax_error = yy::parser::syntax_error;
    using location_type = yy::parser::location_type;

    std::shared_ptr<program> dummy_global_program;
    std::vector<program> programs;
    int error_count = 0;

    pio_assembler();

    std::shared_ptr<output_format> format;
    // The name of the file being parsed.
    std::string source;
    // name of the output file or "-" for stdout
    std::string dest;
    std::vector<std::string> options;

    int write_output();

    bool add_program(const yy::location &l, const std::string &name) {
        if (std::find_if(programs.begin(), programs.end(), [&](const program &p) { return p.name == name; }) ==
            programs.end()) {
            programs.emplace_back(this, l, name);
            return true;
        } else {
            return false;
        }
    }

    program &get_dummy_global_program() {
        if (!dummy_global_program) {
            dummy_global_program = std::shared_ptr<program>(new program(this, yy::location(&source), ""));
        }
        return *dummy_global_program;
    }

    program &get_current_program(const location_type &l, const std::string &requiring_program,
                                 bool before_any_instructions = false, bool disallow_global = true) {
        if (programs.empty()) {
            if (disallow_global) {
                std::stringstream msg;
                msg << requiring_program << " is invalid outside of a program";
                throw syntax_error(l, msg.str());
            }
            return get_dummy_global_program();
        }
        auto &p = programs[programs.size() - 1];
        if (before_any_instructions && !p.instructions.empty()) {
            std::stringstream msg;
            msg << requiring_program << " must preceed any program instructions";
            throw syntax_error(l, msg.str());
        }
        return p;
    }

    // note p may be null for global symbols only
    std::shared_ptr<symbol> get_symbol(const std::string &name, const program *p) {
        const auto &i = get_dummy_global_program().symbols.find(name);
        if (i != get_dummy_global_program().symbols.end())
            return i->second;

        if (p) {
            const auto &i2 = p->symbols.find(name);
            if (i2 != p->symbols.end())
                return i2->second;
        }
        return nullptr;
    }

    std::vector<compiled_source::symbol> public_symbols(program &program);
    int generate(std::shared_ptr<output_format> _format, const std::string &_source, const std::string &_dest,
                 const std::vector<std::string> &_options = std::vector<std::string>());

    // Handling the scanner.
    void scan_begin();
    void scan_end();

    // The token's location used by the scanner.
    yy::location location;
};

#endif