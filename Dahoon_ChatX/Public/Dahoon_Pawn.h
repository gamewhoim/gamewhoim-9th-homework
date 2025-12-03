#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Dahoon_Pawn.generated.h"

UCLASS()
class DAHOON_CHATX_API ADahoon_Pawn : public APawn
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

};