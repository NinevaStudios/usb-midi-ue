package com.ninevastudios.midilib.bridge;

import android.app.Activity;

import com.ninevastudios.midilib.source.UsbMidiController;

public class Bridge {
	public static native void RawMidi(byte command, byte data1, byte data2);
	public static native void NoteOn(int note, int velocity);
	public static native void NoteOff(int note);
	public static native void DeviceAttached(String name);
	public static native void DeviceDetached(String name);

	private static MidiCallback _midiCallback;

	public static void init(Activity activity) {
		_midiCallback = new MidiCallback();
		UsbMidiController.getInstance().ctor(_midiCallback, activity);
	}
}
