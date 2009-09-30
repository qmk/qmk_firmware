import javax.sound.midi.*;
import javax.sound.midi.MidiMessage.*;
import java.io.RandomAccessFile;

class BIN2BOOT
{
	private static final int MIDI_CONTROL_CHANNEL          = 9;
	private static final int MIDI_DATA_CHANNEL             = 0;

	private static final int CONTROL_DEVICE_READY          = 0xD1;
	private static final int CONTROL_ENTER_PROG_MODE       = 0xDC;
	private static final int CONTROL_LEAVE_PROG_MODE       = 0xDF;
	private static final int CONTROL_GET_PAGE_SIZE         = 0x01;

	public static void main(String[] args)
	{
		if (args.length != 1)
		{
			System.out.println("BIN2BOOT - USB-MIDI bootloader");
			System.out.println("  Usage: java BIN2BOOT {input}.bin");
		}	
	
		RandomAccessFile inFile = null;
		
		try
		{
			inFile = new RandomAccessFile(args[0], "r");
		}
		catch (Exception e)
		{
			System.out.println("Could not open input file!");
			return;
		}

		MidiDevice  currDevice = null;
		Receiver    midiOut    = null;
		Transmitter midiIn     = null;
		MIDIMessageReceiver midiInMessages = new MIDIMessageReceiver();
		
		try
		{
			MidiDevice.Info[] infos = MidiSystem.getMidiDeviceInfo();
			
			for (MidiDevice.Info info : infos)
			{
				currDevice = MidiSystem.getMidiDevice(info);
			
				if (!(currDevice instanceof Sequencer) && !(currDevice instanceof Synthesizer))
				{
					if (info.getName().indexOf("LUFA") == -1)
					  continue;
					  
					System.out.println(" MIDI Device: " + info.getName());
				
					currDevice.open();
				
					if (currDevice.getMaxReceivers() != 0)
					{
						midiOut = currDevice.getReceiver();
						break;
					}

					if (currDevice.getMaxTransmitters() != 0)
					{
						midiIn  = currDevice.getTransmitter();
						midiIn.setReceiver(midiInMessages);
					}
				}
			}
			
			if ((midiOut == null) || (midiIn == null))
			{
				System.out.println("Could not find suitable MIDI device!");
				return;
			}			
		}
		catch (Exception e)
		{
			System.out.println("Could not enumerate MIDI devices!");
			return;
		}
		
		System.out.println("PROGRAMMING FILE...");

		ProgramFirmware(inFile, midiOut, midiInMessages);

		System.out.println("DONE.");

		try
		{
			midiOut.close();
			midiIn.close();
			currDevice.close();
			inFile.close();
		}
		catch (Exception e)
		{
			System.out.println("ERROR: Could not close open resources.");		
		}
	}
	
	private static void ProgramFirmware(RandomAccessFile inFile, Receiver midiOut, MIDIMessageReceiver midiInMessages)
	{
		try
		{
			System.out.println("Entering Programming Mode...");
			sendByteViaMIDI(midiOut, MIDI_CONTROL_CHANNEL, CONTROL_ENTER_PROG_MODE);
			
			int[] messageData;
			do
			{
				messageData = receiveByteViaMIDI(midiInMessages);
			}
			while ((messageData[0] != MIDI_CONTROL_CHANNEL) && (messageData[1] != CONTROL_DEVICE_READY));
			
			System.out.println("Getting Page Size...");
			sendByteViaMIDI(midiOut, MIDI_CONTROL_CHANNEL, CONTROL_GET_PAGE_SIZE);

			int nextByte = inFile.read();
			while (nextByte != -1)
			{
				sendByteViaMIDI(midiOut, 9, nextByte);

				if ((inFile.getFilePointer() % (inFile.length() / 100)) == 0)
					System.out.println("  LOADING: " + (int)(inFile.getFilePointer() / (inFile.length() / 100.0)) + "%...");

				nextByte = inFile.read();
			}

			sendByteViaMIDI(midiOut, MIDI_CONTROL_CHANNEL, CONTROL_LEAVE_PROG_MODE);
		}
		catch (Exception e)
		{
			System.out.println("ERROR: Could not send data to device.");		
		}
	}

	private static void sendByteViaMIDI(Receiver midiOut, int channel, int data)
	{
		ShortMessage sendMessage = new ShortMessage();
		
		try
		{
			sendMessage.setMessage(ShortMessage.NOTE_ON, channel, (data & 0x7F), (((data & 0x80) == 0x80) ? 64 : 32));
			midiOut.send(sendMessage, -1);

//			try {Thread.sleep(1);} catch (Exception e) {}

			sendMessage.setMessage(ShortMessage.NOTE_OFF, channel, (data & 0x7F), (((data & 0x80) == 0x80) ? 64 : 32));
			midiOut.send(sendMessage, -1);
		}
		catch (Exception e)
		{
			System.out.println("ERROR: Could not send MIDI note press.");
		}
	}

	private static int[] receiveByteViaMIDI(MIDIMessageReceiver midiInReceiver)
	{
		byte[] messageData;
		
		do
		{
			while (!(midiInReceiver.hasReceived()));
			messageData = midiInReceiver.receive().getMessage();
		}
		while ((messageData[0] & 0xF0) != ShortMessage.NOTE_ON);
	
		int channel = (messageData[0] & 0x0F);
		int data    = (messageData[1] | ((messageData[2] == 64) ? 0x80 : 0x00));
		
		int[] formattedMessageData = new int[2];
		formattedMessageData[0] = channel;
		formattedMessageData[1] = data;
	
		return formattedMessageData;
	}
}