import java.util.PriorityQueue;
import javax.sound.midi.*;
import javax.sound.midi.MidiMessage.*;

class MIDIMessageReceiver implements Receiver
{
	private PriorityQueue<MidiMessage> messages;
	
	MIDIMessageReceiver()
	{
		messages = new PriorityQueue<MidiMessage>();
	}
	
	public void send(MidiMessage message, long timeStamp)
	{
		messages.add(message);
	}
	
	public boolean hasReceived()
	{
		return (messages.size() != 0);
	}

	public MidiMessage receive()
	{
		return messages.poll();
	}
	
	public void close()
	{
	
	}
}
