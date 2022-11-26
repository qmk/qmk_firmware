#pragma once

#ifndef __ASSEMBLER__
#include <stdint.h>
/*
================   TYPES   ================
*/
typedef enum pcal_gpio_state{LOW, HIGH} pcal_gpio_state;
typedef enum pcal_gpio_dir{OUTPUT, INPUT, INPUT_PULLUP, INPUT_PULLDOWN} pcal_gpio_dir;
typedef uint8_t pcal_gpio_pin;

/*
================ FUNCTIONS ================
*/
pcal_gpio_state pcal_read_pin(pcal_gpio_pin pin);
void pcal_write_pin(pcal_gpio_pin pin, pcal_gpio_state state);
void pcal_set_pin_direction(pcal_gpio_pin pin, pcal_gpio_dir dir);

/*
================ REGISTERS ================
*/
//                                            | RW? | Reset State | Register Name                                |
//                                            |-----|-------------|----------------------------------------------|
#define INPUT_PORT0                   0x00 // |  R  |  ???? ????  | Input port 0 register                        |
#define INPUT_PORT1                   0x01 // |  R  |  ???? ????  | Input port 1 register                        |

#define OUTPUT_PORT0                  0x02 // | R/W |  1111 1111  | Output port 0 register                       |
#define OUTPUT_PORT1                  0x03 // | R/W |  1111 1111  | Output port 1 register                       |

#define POLARITY_INVERSION_PORT0      0x04 // | R/W |  0000 0000  | Polarity inversion port 0 register           |
#define POLARITY_INVERSION_PORT1      0x05 // | R/W |  0000 0000  | Polarity inversion port 1 register           |

#define CONFIGURATION_PORT0           0x06 // | R/W |  1111 1111  | Configuration port 0 register                |
#define CONFIGURATION_PORT1           0x07 // | R/W |  1111 1111  | Configuration port 1 register                |

#define OUTPUT_DRIVE_STRENGTH_A_PORT0 0x40 // | R/W |  1111 1111  | Output drive strength port 0 register A      |
#define OUTPUT_DRIVE_STRENGTH_B_PORT0 0x41 // | R/W |  1111 1111  | Output drive strength port 0 register B      |
#define OUTPUT_DRIVE_STRENGTH_A_PORT1 0x42 // | R/W |  1111 1111  | Output drive strength port 1 register A      |
#define OUTPUT_DRIVE_STRENGTH_B_PORT1 0x43 // | R/W |  1111 1111  | Output drive strength port 1 register B      |

#define INPUT_LATCH_PORT0             0x44 // | R/W |  0000 0000  | Input latch port 0 register                  |
#define INPUT_LATCH_PORT1             0x45 // | R/W |  0000 0000  | Input latch port 1 register                  |

#define PULLUP_PULLDOWN_ENABLE_PORT0  0x46 // | R/W |  0000 0000  | Pull-up/Pull-down selection port 0 register  |
#define PULLUP_PULLDOWN_ENABLE_PORT1  0x47 // | R/W |  0000 0000  | Pull-up/Pull-down selection port 1 register  |
#define PULLUP_PULLDOWN_SELECT_PORT0  0x48 // | R/W |  1111 1111  | Pull-up/Pull-down selection port 0 register  |
#define PULLUP_PULLDOWN_SELECT_PORT1  0x49 // | R/W |  1111 1111  | Pull-up/Pull-down selection port 1 register  |

#define INTERRUPT_MASK_PORT0          0x4A // | R/W |  1111 1111  | Interrupt mask port 0 register               |
#define INTERRUPT_MASK_PORT1          0x4B // | R/W |  1111 1111  | Interrupt mask port 1 register               |
#define INTERRUPT_STATUS_PORT0        0x4C // |  R  |  0000 0000  | Interrupt status port 0 register             |
#define INTERRUPT_STATUS_PORT1        0x4D // |  R  |  0000 0000  | Interrupt status port 1 register             |

#define OUTPUT_PORT_CONFIGURATION     0x4F // | R/W |  0000 0000  | Output port configuration register           |

/*
================    GPIO   ================
*/

#define PORT_0 0
#define PORT_1 1
#define GET_PORT(pin) (pin >> 7)
#define GET_PIN_NUMBER(pin) (pin & 0b0111111)
#define REGISTER_FOR_PIN(pin, register) (GET_PORT(pin) == PORT_0 ? register##_PORT0 : register##_PORT1)

#define PCAL_0_0 (PORT_0 << 7) | 0
#define PCAL_0_1 (PORT_0 << 7) | 1
#define PCAL_0_2 (PORT_0 << 7) | 2
#define PCAL_0_3 (PORT_0 << 7) | 3
#define PCAL_0_4 (PORT_0 << 7) | 4
#define PCAL_0_5 (PORT_0 << 7) | 5
#define PCAL_0_6 (PORT_0 << 7) | 6
#define PCAL_0_7 (PORT_0 << 7) | 7

#define PCAL_1_0 (PORT_1 << 7) | 0
#define PCAL_1_1 (PORT_1 << 7) | 1
#define PCAL_1_2 (PORT_1 << 7) | 2
#define PCAL_1_3 (PORT_1 << 7) | 3
#define PCAL_1_4 (PORT_1 << 7) | 4
#define PCAL_1_5 (PORT_1 << 7) | 5
#define PCAL_1_6 (PORT_1 << 7) | 6
#define PCAL_1_7 (PORT_1 << 7) | 7

#endif
