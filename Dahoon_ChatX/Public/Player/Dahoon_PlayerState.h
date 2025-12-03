// Dahoon_PlayerState.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Dahoon_PlayerState.generated.h"

/**
 *
 */
UCLASS()
class DAHOON_CHATX_API ADahoon_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ADahoon_PlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	FString GetPlayerInfoString();

public:
	UPROPERTY(Replicated)
	FString PlayerNameString;

	UPROPERTY(Replicated)
	int32 CurrentGuessCount;

	UPROPERTY(Replicated)
	int32 MaxGuessCount;

};