#include "Player/Dahoon_PlayerState.h"

#include "Net/UnrealNetwork.h"

ADahoon_PlayerState::ADahoon_PlayerState()
	: PlayerNameString(TEXT("None"))
	, CurrentGuessCount(0)
	, MaxGuessCount(3)
{
	bReplicates = true;
}

void ADahoon_PlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	{
		Super::GetLifetimeReplicatedProps(OutLifetimeProps);

		DOREPLIFETIME(ThisClass, PlayerNameString);
		DOREPLIFETIME(ThisClass, CurrentGuessCount);
		DOREPLIFETIME(ThisClass, MaxGuessCount); 
	}
}

FString ADahoon_PlayerState::GetPlayerInfoString()
{
	FString PlayerInfoString = PlayerNameString + TEXT("(") + FString::FromInt(CurrentGuessCount) + TEXT("/") + FString::FromInt(MaxGuessCount) + TEXT(")");
	return PlayerInfoString;
}
