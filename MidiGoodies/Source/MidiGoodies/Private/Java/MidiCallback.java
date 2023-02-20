package com.ninevastudios.midilib;

import com.ninevastudios.midilib.IMidiCallback;

public class MidiCallback implements IMidiCallback {
	@Override
	public void RawMidi(byte command, byte data1, byte data2) {
		Bridge.RawMidi(command, data1, data2);
	}

	@Override
	public void NoteOn(int note, int velocity) {
		Bridge.NoteOn(note, velocity);
	}

	@Override
	public void NoteOff(int note) {
		Bridge.NoteOff(note);
	}

	@Override
	public void DeviceAttached(String name) {
		Bridge.DeviceAttached(name);
	}

	@Override
	public void DeviceDetached(String name) {
		Bridge.DeviceDetached(name);
	}
}