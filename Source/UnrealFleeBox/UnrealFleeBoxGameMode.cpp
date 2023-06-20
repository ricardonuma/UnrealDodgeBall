// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealFleeBoxGameMode.h"
#include "UnrealFleeBoxCharacter.h"

AUnrealFleeBoxGameMode::AUnrealFleeBoxGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = AUnrealFleeBoxCharacter::StaticClass();	
}
