#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Dahoon_GameModeBase.generated.h"

class ADahoon_PlayerController;

/**
 * 
 */
UCLASS()
class DAHOON_CHATX_API ADahoon_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void OnPostLogin(AController* NewPlayer) override;

	FString GenerateSecretNumber();

	bool IsGuessNumberString(const FString& InNumberString);

	FString JudgeResult(const FString& InSecretNumberString, const FString& InGuessNumberString);

	virtual void BeginPlay() override;

	void PrintChatMessageString(ADahoon_PlayerController* InChattingPlayerController, const FString& InChatMessageString);

	void IncreaseGuessCount(ADahoon_PlayerController* InChattingPlayerController);

	void ResetGame();

	void JudgeGame(ADahoon_PlayerController* InChattingPlayerController, int InStrikeCount);

protected:
	FString SecretNumberString;

	TArray<TObjectPtr<ADahoon_PlayerController>> AllPlayerControllers;

};
