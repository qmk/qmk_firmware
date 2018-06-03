#include "vortex.h"

uint16_t from_leu16(const uint8_t *bytes) {
    return (bytes[0] | (bytes[1] << 8));
}

uint32_t from_leu32(const uint8_t *bytes) {
    return (bytes[0] | (bytes[1] << 8) | (bytes[2] << 16) | (bytes[3] << 24));
}

void to_leu16(uint8_t *bytes, uint16_t num) {
    bytes[0] = num & 0xFF;
    bytes[1] = (num >> 8) & 0xFF;
}

void to_leu32(uint8_t *bytes, uint32_t num) {
    bytes[0] = num & 0xFF;
    bytes[1] = (num >> 8) & 0xFF;
    bytes[2] = (num >> 16) & 0xFF;
    bytes[3] = (num >> 24) & 0xFF;
}

// From http://mdfs.net/Info/Comp/Comms/CRC16.htm
// CRC-CCITT
#define CCITT_POLY 0x1021
uint16_t crc16(const uint8_t *ptr, uint32_t size, uint32_t crc) {
    for(uint32_t i = 0; i < size; ++i){
        crc ^= (uint16_t)(ptr[i] << 8);
        for(int j = 0; j < 8; j++){
            crc = crc << 1;
            if(crc & 0x10000)
                crc = (crc ^ CCITT_POLY) & 0xFFFF;
        }
    }
    return (uint16_t)(crc & 0xFFFF);
}
