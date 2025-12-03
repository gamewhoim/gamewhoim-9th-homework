#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Dahoon_GameStateBase.generated.h"

/**
 *
 */
UCLASS()
class DAHOON_CHATX_API ADahoon_GameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCBroadcastLoginMessage(const FString& InNameString = FString(TEXT("XXXXXXX")));

};
