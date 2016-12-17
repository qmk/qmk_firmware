#include "api_sysex.h"

void send_bytes_sysex(uint8_t message_type, uint8_t data_type, uint8_t * bytes, uint16_t length) {
    // SEND_STRING("\nTX: ");
    // for (uint8_t i = 0; i < length; i++) {
    //     send_byte(bytes[i]);
    //     SEND_STRING(" ");
    // }
    uint8_t * precode = malloc(sizeof(uint8_t) * (length + 2));
    precode[0] = message_type;
    precode[1] = data_type;
    memcpy(precode + 2, bytes, length);
    uint8_t * encoded = malloc(sizeof(uint8_t) * (sysex_encoded_length(length + 2)));
    uint16_t encoded_length = sysex_encode(encoded, precode, length + 2);
    uint8_t * array = malloc(sizeof(uint8_t) * (encoded_length + 5));
    array[0] = 0xF0;
    array[1] = 0x00;
    array[2] = 0x00;
    array[3] = 0x00;
    array[encoded_length + 4] = 0xF7;
    memcpy(array + 4, encoded, encoded_length);
    midi_send_array(&midi_device, encoded_length + 5, array);

    // SEND_STRING("\nTD: ");
    // for (uint8_t i = 0; i < encoded_length + 5; i++) {
    //     send_byte(array[i]);
    //     SEND_STRING(" ");
    // }
}