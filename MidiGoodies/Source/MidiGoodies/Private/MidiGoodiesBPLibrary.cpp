// Copyright (c) 2023 Nineva Studios

#include "MidiGoodiesBPLibrary.h"
#include "MidiGoodies.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJavaEnv.h"
#include "Android/AndroidPlatform.h"
//#include "Android/Utils/MGMethodCallUtils.h"
#endif

#include "Async/Async.h"

FMidiRawDelegate UMidiGoodiesBPLibrary::MidiRawDelegate;
FMidiDeviceNoteOnDelegate UMidiGoodiesBPLibrary::MidiDeviceNoteOnDelegate;
FMidiIntDelegate UMidiGoodiesBPLibrary::MidiNoteOffDelegate;
FMidiStringDelegate UMidiGoodiesBPLibrary::MidiDeviceAttachedDelegate;
FMidiStringDelegate UMidiGoodiesBPLibrary::MidiDeviceDetachedDelegate;

void UMidiGoodiesBPLibrary::Init()
{
#if PLATFORM_ANDROID
	MGMethodCallUtils::CallStaticVoidMethod("com/ninevastudios/midilib/Bridge", "init", "(Landroid/app/Activity;)V", FJavaWrapper::GameActivityThis);
#endif
}

void UMidiGoodiesBPLibrary::BindEventRawMidi(const FMidiRawDelegate& Delegate)
{
	UMidiGoodiesBPLibrary::MidiRawDelegate = Delegate;
}

void UMidiGoodiesBPLibrary::BindEventNoteOn(const FMidiDeviceNoteOnDelegate& Delegate)
{
	UMidiGoodiesBPLibrary::MidiDeviceNoteOnDelegate = Delegate;
}

void UMidiGoodiesBPLibrary::BindEventNoteOff(const FMidiIntDelegate& Delegate)
{
	UMidiGoodiesBPLibrary::MidiNoteOffDelegate = Delegate;
}

void UMidiGoodiesBPLibrary::BindEventDeviceAttached(const FMidiStringDelegate& Delegate)
{
	UMidiGoodiesBPLibrary::MidiDeviceAttachedDelegate = Delegate;
}

void UMidiGoodiesBPLibrary::BindEventDeviceDetached(const FMidiStringDelegate& Delegate)
{
	UMidiGoodiesBPLibrary::MidiDeviceDetachedDelegate = Delegate;
}

#if PLATFORM_ANDROID
JNI_METHOD void Java_com_ninevastudios_midilib_Bridge_RawMidi(JNIEnv* env, jclass clazz, jbyte command, jbyte data1, jbyte data2)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UMidiGoodiesBPLibrary::MidiRawDelegate.ExecuteIfBound(command, data1, data2);
	});
}

JNI_METHOD void Java_com_ninevastudios_midilib_Bridge_NoteOn(JNIEnv* env, jclass clazz, jint note, jint velocity)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UMidiGoodiesBPLibrary::MidiDeviceNoteOnDelegate.ExecuteIfBound(note, velocity);
	});
}

JNI_METHOD void Java_com_ninevastudios_midilib_Bridge_NoteOff(JNIEnv* env, jclass clazz, jint note)
{
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UMidiGoodiesBPLibrary::MidiNoteOffDelegate.ExecuteIfBound(note);
	});
}

JNI_METHOD void Java_com_ninevastudios_midilib_Bridge_DeviceAttached(JNIEnv* env, jclass clazz, jstring name)
{
	FString Name = FJavaHelper::FStringFromParam(env, name);
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UMidiGoodiesBPLibrary::MidiDeviceAttachedDelegate.ExecuteIfBound(Name);
	});
}

JNI_METHOD void Java_com_ninevastudios_midilib_Bridge_DeviceDetached(JNIEnv* env, jclass clazz, jstring name)
{
	FString Name = FJavaHelper::FStringFromParam(env, name);
	AsyncTask(ENamedThreads::GameThread, [=]()
	{
		UMidiGoodiesBPLibrary::MidiDeviceDetachedDelegate.ExecuteIfBound(Name);
	});
}
#endif