/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PIO_DISASSEMBLER_H
#define _PIO_DISASSEMBLER_H

#ifdef __cplusplus

#include <string>

typedef unsigned int uint;

std::string disassemble(uint16_t inst, uint sideset_bits, bool sideset_opt);
extern "C" void disassemble(char *buf, int buf_len, uint16_t inst, uint sideset_bits, bool sideset_opt);
#else
void disassemble(char *buf, int buf_len, uint inst, uint sideset_bits, bool sideset_opt);
#endif

#endif