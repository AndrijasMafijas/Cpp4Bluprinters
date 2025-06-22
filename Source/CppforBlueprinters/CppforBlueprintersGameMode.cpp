// Copyright Epic Games, Inc. All Rights Reserved.

#include "CppforBlueprintersGameMode.h"
#include "CppforBlueprintersCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACppforBlueprintersGameMode::ACppforBlueprintersGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
