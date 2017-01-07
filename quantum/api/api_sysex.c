#include "api_sysex.h"
#include "sysex_tools.h"
#include "print.h"

void send_bytes_sysex(uint8_t message_type, uint8_t data_type, uint8_t * bytes, uint16_t length) {
    // SEND_STRING("\nTX: ");
    // for (uint8_t i = 0; i < length; i++) {
    //     send_byte(bytes[i]);
    //     SEND_STRING(" ");
    // }
    if (length > API_SYSEX_MAX_SIZE) {
        xprintf("Sysex msg too big %d %d %d", message_type, data_type, length);
        return;
    }


    // The buffer size required is calculated as the following
    // API_SYSEX_MAX_SIZE is the maximum length
    // In addition to that we have a two byte message header consisting of the message_type and data_type
    // This has to be encoded with an additional overhead of one byte for every starting 7 bytes
    // We just add one extra byte in case it's not divisible by 7
    // Then we have an unencoded header consisting of 4 bytes
    // Plus a one byte terminator
    const unsigned message_header = 2;
    const unsigned unencoded_message = API_SYSEX_MAX_SIZE + message_header;
    const unsigned encoding_overhead = unencoded_message / 7 + 1;
    const unsigned encoded_size = unencoded_message + encoding_overhead;
    const unsigned unencoded_header = 4;
    const unsigned terminator = 1;
    const unsigned buffer_size = encoded_size + unencoded_header + terminator;
    uint8_t buffer[encoded_size + unencoded_header + terminator];
    // The unencoded header
    buffer[0] = 0xF0;
    buffer[1] = 0x00;
    buffer[2] = 0x00;
    buffer[3] = 0x00;

    // We copy the message to the end of the array, this way we can do an inplace encoding, using the same
    // buffer for both input and output
    const unsigned message_size = length + message_header;
    uint8_t* unencoded_start = buffer + buffer_size - message_size;
    uint8_t* ptr = unencoded_start;
    *(ptr++) = message_type;
    *(ptr++) = data_type;
    memcpy(ptr, bytes, length);

    unsigned encoded_length = sysex_encode(buffer + unencoded_header, unencoded_start, message_size);
    unsigned final_size = unencoded_header + encoded_length + terminator;
    buffer[final_size - 1] = 0xF7;
    midi_send_array(&midi_device, final_size, buffer);

    // SEND_STRING("\nTD: ");
    // for (uint8_t i = 0; i < encoded_length + 5; i++) {
    //     send_byte(buffer[i]);
    //     SEND_STRING(" ");
    // }
}
