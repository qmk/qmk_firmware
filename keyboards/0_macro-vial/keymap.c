void midi_rx_user(uint8_t port, midi_packet_t packet) {
    if (packet.status == MIDI_NOTE_ON) {
        uint8_t note = packet.data[0];
        rgblight_setrgb(255, 0, 0); // Beispiel: Rot bei Note-On
    }
}