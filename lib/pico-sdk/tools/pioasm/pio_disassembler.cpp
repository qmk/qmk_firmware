/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <array>
#include <sstream>
#include <iomanip>
#include "pio_disassembler.h"

extern "C" void disassemble(char *buf, int buf_len, uint16_t inst, uint sideset_bits, bool sideset_opt) {
    if (buf_len) buf[disassemble(inst, sideset_bits, sideset_opt).copy(buf, buf_len - 1)] = 0;
}

std::string disassemble(uint16_t inst, uint sideset_bits_including_opt, bool sideset_opt) {
    std::stringstream ss;
    uint major = inst >> 13u;
    uint arg1 = ((uint) inst >> 5u) & 0x7u;
    uint arg2 = inst & 0x1fu;
    auto op = [&](const std::string &s) {
        ss << std::left << std::setw(7) << s;
    };
    auto op_guts = [&](const std::string &s) {
        ss << std::left << std::setw(16) << s;
    };

    bool invalid = false;
    switch (major) {
        case 0b000: {
            static std::array<std::string, 8> conditions{"", "!x, ", "x--, ", "!y, ", "y--, ", "x != y, ", "pin, ",
                                                         "!osre, "};
            op("jmp");
            op_guts(conditions[arg1] + std::to_string(arg2));
            break;
        }
        case 0b001: {
            uint source = arg1 & 3u;
            std::string guts;
            switch (source) {
                case 0b00:
                    guts = "gpio, " + std::to_string(arg2);
                    break;
                case 0b01:
                    guts = "pin, " + std::to_string(arg2);
                    break;
                case 0b10:
                    if (arg2 & 0x8u) {
                        invalid = true;
                    } else {
                        guts = "irq, " + std::to_string(arg2 & 7u);
                        if (arg2 & 0x10u) {
                            guts += " rel";
                        }
                    }
                    break;
            }
            if (!invalid) {
                guts = ((arg1 & 4u) ? "1 " : "0 ") + guts;
                op("wait");
                op_guts(guts);
            }
            break;
        }
        case 0b010: {
            static std::array<std::string, 8> sources { "pins", "x", "y", "null", "", "status", "isr", "osr"};
            std::string source = sources[arg1];
            if (source.empty()) {
                invalid = true;
            } else {
                op("in");
                op_guts(source + ", " + std::to_string(arg2 ? arg2 : 32));
            }
            break;
        }
        case 0b011: {
            static std::array<std::string, 8> dests { "pins", "x", "y", "null", "pindirs", "pc", "isr", "exec"};
            op("out");
            op_guts(dests[arg1] + ", " + std::to_string(arg2 ? arg2 : 32));
            break;
        }
        case 0b100: {
            if (arg2) {
                invalid = true;
            } else {
                std::string guts = "";
                if (arg1 & 4u) {
                    op("pull");
                    if (arg1 & 2u) guts = "ifempty ";
                } else {
                    op("push");
                    if (arg1 & 2u) guts = "iffull ";
                }
                guts += (arg1 & 0x1u) ? "block" : "noblock";
                op_guts(guts);
            }
            break;
        }
        case 0b101: {
            static std::array<std::string, 8> dests { "pins", "x", "y", "", "exec", "pc", "isr", "osr"};
            static std::array<std::string, 8> sources { "pins", "x", "y", "null", "", "status", "isr", "osr"};
            std::string dest = dests[arg1];
            std::string source = sources[arg2 & 7u];
            uint operation = arg2 >> 3u;
            if (source.empty() || dest.empty() || operation == 3) {
                invalid = true;
            }
            if (dest == source && !operation && (arg1 == 1 || arg2 == 2)) {
                op("nop");
                op_guts("");
            } else {
                op("mov");
                std::string guts = dest + ", ";
                if (operation == 1) {
                    guts += "!";
                } else if (operation == 2) {
                    guts += "::";
                }
                guts += source;
                op_guts(guts);
            }
            break;
        }
        case 0b110: {
            if ((arg1 & 0x4u) || (arg2 & 0x8u)) {
                invalid = true;
            } else {
                op("irq");
                std::string guts;
                if (arg1 & 0x2u) {
                    guts += "clear ";
                } else if (arg1 & 0x1u) {
                    guts += "wait ";
                } else {
                    guts += "nowait ";
                }
                guts += std::to_string(arg2 & 7u);
                if (arg2 & 0x10u) {
                    guts += " rel";
                }
                op_guts(guts);
            }
            break;
        }
        case 0b111: {
            static std::array<std::string, 8> dests{"pins", "x", "y", "", "pindirs", "", "", ""};
            std::string dest = dests[arg1];
            if (dest.empty()) {
                invalid = true;
            } else {
                op("set");
                op_guts(dests[arg1] + ", " + std::to_string(arg2));
            }
            break;
        }
    }
    if (invalid) {
        return "reserved";
    }
    uint delay = ((uint) inst >> 8u) & 0x1f;
    ss << std::left << std::setw(7);
    if (sideset_bits_including_opt && (!sideset_opt || (delay & 0x10u))) {
        ss << ("side "+ std::to_string((delay & (sideset_opt ? 0xfu : 0x1fu)) >> (5u - sideset_bits_including_opt)));
    } else {
        ss << "";
    }
    delay &= ((1u << (5 - sideset_bits_including_opt)) - 1u);
    ss << std::left << std::setw(4) << (delay ? ("[" + std::to_string(delay) + "]") : "");
    return ss.str();
}

