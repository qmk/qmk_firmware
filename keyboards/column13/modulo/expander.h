//
// Created by 樋田一幸 on 2020/06/27.
//

#pragma once

enum {
    CMD_INPUT = 0,
    CMD_OUTPUT,
    CMD_INVERSION,
    CMD_CONFIG,
};

typedef struct {
    uint8_t address;
    uint8_t num_port;
    uint16_t mask;
} expander;

#define PCA9555(offset) { 0x20 | offset, 2, 0xFFFF }
#define TCA9555(offset) { 0x20 | offset, 2, 0xFFFF }
#define PCA9554(offset) { 0x20 | offset, 1, 0x00FF }
#define TCA9554(offset) { 0x20 | offset, 1, 0x00FF }
#define PCA9536() { 0x41, 1, 0x000F }

void expander_init(const expander *slaves, uint8_t count);
uint16_t expander_readPins(const expander *slave);
