// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "MidiGoodiesBPLibrary.generated.h"

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/


DECLARE_DYNAMIC_DELEGATE_OneParam(FMidiStringDelegate, FString, Name);
DECLARE_DYNAMIC_DELEGATE_OneParam(FMidiIntDelegate, int, Note);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FMidiDeviceNoteOnDelegate, int, Note, int, Velocity);
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FMidiRawDelegate, uint8, Command, uint8, Data1, uint8, Data2);



UCLASS()
class UMidiGoodiesBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

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
