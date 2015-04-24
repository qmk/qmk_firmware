#include "mbed.h"
#include "USBMIDI.h"

USBMIDI midi;
Serial pc(USBTX, USBRX);

// MIDI IN
void transmitMessage(MIDIMessage msg) {
 	switch (msg.type()) {
        case MIDIMessage::NoteOnType:
        	wait(0.1);
			midi.write(MIDIMessage::NoteOn(msg.key()));
            break;
        case MIDIMessage::NoteOffType:
        	wait(0.1);
			midi.write(MIDIMessage::NoteOff(msg.key()));
            break;
        case MIDIMessage::ProgramChangeType:
        	wait(0.1);
        	midi.write(MIDIMessage::ProgramChange(msg.program()));
            break;
        case MIDIMessage::SysExType:
        	wait(0.1);
        	unsigned char tmp[64];
            for(int i=0;i<msg.length-1;i++) {
	            tmp[i]=msg.data[i+1];
            }
            midi.write(MIDIMessage::SysEx(tmp,msg.length-1));
            break;
        default:
            break;
    }    
}

int main(void)
{
	wait(5);
	// MIDI OUT

	// set piano
	midi.write(MIDIMessage::ProgramChange(1));
	wait(0.1);

	// play A
	midi.write(MIDIMessage::NoteOn(21));
	wait(0.1);
	midi.write(MIDIMessage::NoteOff(21));
	wait(0.1);

	// GM reset
	unsigned char gm_reset[]={0xF0,0x7E,0x7F,0x09,0x01,0xF7};
	midi.write(MIDIMessage::SysEx(gm_reset,6));
	wait(0.1);

	// GM Master volume max
	unsigned char gm_master_vol_max[]={0xF0,0x7F,0x7F,0x04,0x01,0x7F,0x7F,0xF7};
	midi.write(MIDIMessage::SysEx(gm_master_vol_max,8));
	wait(0.1);

	// GS reset
	unsigned char gs_reset[]={0xF0,0x41,0x10,0x42,0x12,0x40,0x00,0x7F,0x00,0x41,0xF7};
	midi.write(MIDIMessage::SysEx(gs_reset,11));
	wait(0.1);

	// GS Master volume max
	unsigned char gs_master_vol_max[]={0xF0,0x41,0x10,0x42,0x12,0x40,0x00,0x04,0x7F,0x3D,0xF7};
	midi.write(MIDIMessage::SysEx(gs_master_vol_max,11));
	wait(0.1);

	midi.attach(transmitMessage);

    while(1);
}
