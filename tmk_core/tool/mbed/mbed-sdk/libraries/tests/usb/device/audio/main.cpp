// Playback example with the USBAUDIO library

#include "mbed.h"
#include "USBAudio.h"

// frequency: 48 kHz
#define FREQ_SPK 48000
#define FREQ_MIC 48000

// 2channels: stereo
#define NB_CHA_SPK 2
#define NB_CHA_MIC 2

// length computed: each ms, we receive 48 * 16bits ->48 * 2 bytes. as there are two channels, the length will be 48 * 2 * 2
#define LENGTH_AUDIO_PACKET_SPK (FREQ_SPK / 500) * NB_CHA_SPK
#define LENGTH_AUDIO_PACKET_MIC (FREQ_MIC / 500) * NB_CHA_MIC

// USBAudio object
USBAudio audio(FREQ_SPK, NB_CHA_SPK, FREQ_MIC, NB_CHA_MIC, 0xab45, 0x0378);

int main() {
    // buffer of int
    int buf_in[LENGTH_AUDIO_PACKET_SPK/sizeof(int)];
    int buf_out[LENGTH_AUDIO_PACKET_MIC/sizeof(int)];
    int * stream_out = buf_in;
    int * stream_in = buf_out;
    int * tmp = NULL;

    while (1) {
        // read and write one audio packet each frame
        audio.readWrite((uint8_t *)stream_in, (uint8_t *)stream_out);

        // swap the buffers
        tmp = stream_in;
        stream_in = stream_out;
        stream_out = tmp;
    }
}


