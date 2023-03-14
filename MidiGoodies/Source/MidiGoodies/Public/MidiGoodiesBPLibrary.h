// Copyright (c) 2023 Nineva Studios

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "MidiGoodiesBPLibrary.generated.h"


DECLARE_DYNAMIC_DELEGATE_OneParam(FMidiStringDelegate, FString, Name);
DECLARE_DYNAMIC_DELEGATE_OneParam(FMidiIntDelegate, int, Note);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FMidiDeviceNoteOnDelegate, int, Note, int, Velocity);
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FMidiRawDelegate, uint8, Command, uint8, Data1, uint8, Data2);


UCLASS()
class MIDIGOODIES_API UMidiGoodiesBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Midi Goodies", meta = (AutoCreateRefTerm = ""))
	static void Init();

	UFUNCTION(BlueprintCallable, Category = "Midi Goodies", meta = (AutoCreateRefTerm = ""))
	static void BindEventRawMidi(const FMidiRawDelegate& Delegate);
	
	UFUNCTION(BlueprintCallable, Category = "Midi Goodies", meta = (AutoCreateRefTerm = ""))
	static void BindEventNoteOn(const FMidiDeviceNoteOnDelegate& Delegate);

	
	UFUNCTION(BlueprintCallable, Category = "Midi Goodies", meta = (AutoCreateRefTerm = ""))
	static void BindEventNoteOff(const FMidiIntDelegate& Delegate);

	
	UFUNCTION(BlueprintCallable, Category = "Midi Goodies", meta = (AutoCreateRefTerm = ""))
	static void BindEventDeviceAttached(const FMidiStringDelegate& Delegate);

	
	UFUNCTION(BlueprintCallable, Category = "Midi Goodies", meta = (AutoCreateRefTerm = ""))
	static void BindEventDeviceDetached(const FMidiStringDelegate& Delegate);
	
	
	static FMidiRawDelegate MidiRawDelegate;
	static FMidiDeviceNoteOnDelegate MidiDeviceNoteOnDelegate;
	static FMidiIntDelegate MidiNoteOffDelegate;
	static FMidiStringDelegate MidiDeviceAttachedDelegate;
	static FMidiStringDelegate MidiDeviceDetachedDelegate;
	
};
