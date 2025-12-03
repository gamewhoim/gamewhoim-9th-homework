#include "Game/Dahoon_GameStateBase.h"

#include "Kismet/GameplayStatics.h"
#include "Player/Dahoon_PlayerController.h"

void ADahoon_GameStateBase::MulticastRPCBroadcastLoginMessage_Implementation(const FString& InNameString)
{
	if (HasAuthority() == false)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (IsValid(PC) == true)
		{
			ADahoon_PlayerController* Dahoon_PC = Cast<ADahoon_PlayerController>(PC);
			if (IsValid(Dahoon_PC) == true)
			{
				FString NotificationString = InNameString + TEXT(" has joined the game.");
				Dahoon_PC->PrintChatMessageString(NotificationString);
			}
		}
	}
}