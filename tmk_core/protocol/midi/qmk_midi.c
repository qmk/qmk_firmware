#include <LUFA/Drivers/USB/USB.h>
#include "qmk_midi.h"
#include "sysex_tools.h"
#include "midi.h"
#include "usb_descriptor.h"
#include "process_midi.h"
#if API_SYSEX_ENABLE
#    include "api.h"
#endif

/*******************************************************************************
 * MIDI
 ******************************************************************************/

MidiDevice midi_device;

#define SYSEX_START_OR_CONT 0x40
#define SYSEX_ENDS_IN_1 0x50
#define SYSEX_ENDS_IN_2 0x60
#define SYSEX_ENDS_IN_3 0x70

#define SYS_COMMON_1 0x50
#define SYS_COMMON_2 0x20
#define SYS_COMMON_3 0x30

static void usb_send_func(MidiDevice* device, uint16_t cnt, uint8_t byte0, uint8_t byte1, uint8_t byte2) {
    MIDI_EventPacket_t event;
    event.Data1 = byte0;
    event.Data2 = byte1;
    event.Data3 = byte2;

    uint8_t cable = 0;

    // if the length is undefined we assume it is a SYSEX message
    if (midi_packet_length(byte0) == UNDEFINED) {
        switch (cnt) {
            case 3:
                if (byte2 == SYSEX_END)
                    event.Event = MIDI_EVENT(cable, SYSEX_ENDS_IN_3);
                else
                    event.Event = MIDI_EVENT(cable, SYSEX_START_OR_CONT);
                break;
            case 2:
                if (byte1 == SYSEX_END)
                    event.Event = MIDI_EVENT(cable, SYSEX_ENDS_IN_2);
                else
                    event.Event = MIDI_EVENT(cable, SYSEX_START_OR_CONT);
                break;
            case 1:
                if (byte0 == SYSEX_END)
                    event.Event = MIDI_EVENT(cable, SYSEX_ENDS_IN_1);
                else
                    event.Event = MIDI_EVENT(cable, SYSEX_START_OR_CONT);
                break;
            default:
                return;  // invalid cnt
        }
    } else {
        // deal with 'system common' messages
        // TODO are there any more?
        switch (byte0 & 0xF0) {
            case MIDI_SONGPOSITION:
                event.Event = MIDI_EVENT(cable, SYS_COMMON_3);
                break;
            case MIDI_SONGSELECT:
            case MIDI_TC_QUARTERFRAME:
                event.Event = MIDI_EVENT(cable, SYS_COMMON_2);
                break;
            default:
                event.Event = MIDI_EVENT(cable, byte0);
                break;
        }
    }

    send_midi_packet(&event);
}

static void usb_get_midi(MidiDevice* device) {
    MIDI_EventPacket_t event;
    while (recv_midi_packet(&event)) {
        midi_packet_length_t length = midi_packet_length(event.Data1);
        uint8_t              input[3];
        input[0] = event.Data1;
        input[1] = event.Data2;
        input[2] = event.Data3;
        if (length == UNDEFINED) {
            // sysex
            if (event.Event == MIDI_EVENT(0, SYSEX_START_OR_CONT) || event.Event == MIDI_EVENT(0, SYSEX_ENDS_IN_3)) {
                length = 3;
            } else if (event.Event == MIDI_EVENT(0, SYSEX_ENDS_IN_2)) {
                length = 2;
            } else if (event.Event == MIDI_EVENT(0, SYSEX_ENDS_IN_1)) {
                length = 1;
            } else {
                // XXX what to do?
            }
        }

        // pass the data to the device input function
        if (length != UNDEFINED) midi_device_input(device, length, input);
    }
}

static void fallthrough_callback(MidiDevice* device, uint16_t cnt, uint8_t byte0, uint8_t byte1, uint8_t byte2) {
#ifdef AUDIO_ENABLE
    if (cnt == 3) {
        switch (byte0 & 0xF0) {
            case MIDI_NOTEON:
                play_note(((double)261.6) * pow(2.0, -4.0) * pow(2.0, (byte1 & 0x7F) / 12.0), (byte2 & 0x7F) / 8);
                break;
            case MIDI_NOTEOFF:
                stop_note(((double)261.6) * pow(2.0, -4.0) * pow(2.0, (byte1 & 0x7F) / 12.0));
                break;
        }
    }
    if (byte0 == MIDI_STOP) {
        stop_all_notes();
    }
#endif
}

static void cc_callback(MidiDevice* device, uint8_t chan, uint8_t num, uint8_t val) {
    // sending it back on the next channel
    // midi_send_cc(device, (chan + 1) % 16, num, val);
}

#ifdef API_SYSEX_ENABLE
uint8_t midi_buffer[MIDI_SYSEX_BUFFER] = {0};

static void sysex_callback(MidiDevice* device, uint16_t start, uint8_t length, uint8_t* data) {
    // SEND_STRING("\n");
    // send_word(start);
    // SEND_STRING(": ");
    // Don't store the header
    int16_t pos = start - 4;
    for (uint8_t place = 0; place < length; place++) {
        // send_byte(*data);
        if (pos >= 0) {
            if (*data == 0xF7) {
                // SEND_STRING("\nRD: ");
                // for (uint8_t i = 0; i < start + place + 1; i++){
                //     send_byte(midi_buffer[i]);
                // SEND_STRING(" ");
                // }
                const unsigned decoded_length = sysex_decoded_length(pos);
                uint8_t        decoded[API_SYSEX_MAX_SIZE];
                sysex_decode(decoded, midi_buffer, pos);
                process_api(decoded_length, decoded);
                return;
            } else if (pos >= MIDI_SYSEX_BUFFER) {
                return;
            }
            midi_buffer[pos] = *data;
        }
        // SEND_STRING(" ");
        data++;
        pos++;
    }
}
#endif

void midi_init(void);

void setup_midi(void) {
#ifdef MIDI_ADVANCED
    midi_init();
#endif
    midi_device_init(&midi_device);
    midi_device_set_send_func(&midi_device, usb_send_func);
    midi_device_set_pre_input_process_func(&midi_device, usb_get_midi);
    midi_register_fallthrough_callback(&midi_device, fallthrough_callback);
    midi_register_cc_callback(&midi_device, cc_callback);
#ifdef API_SYSEX_ENABLE
    midi_register_sysex_callback(&midi_device, sysex_callback);
#endif
}
