#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Dahoon_PlayerController.generated.h"

class UDahoon_ChatInput;
class UUserWidget;

/**
 * 
 */
UCLASS()
class DAHOON_CHATX_API ADahoon_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ADahoon_PlayerController();

	virtual void BeginPlay() override;

	void SetChatMessageString(const FString& InChatMessageString);

	void PrintChatMessageString(const FString& InChatMessageString);

	UFUNCTION(Client, Reliable)
	void ClientRPCPrintChatMessageString(const FString& InChatMessageString);

	UFUNCTION(Server, Reliable)
	void ServerRPCPrintChatMessageString(const FString& InChatMessageString);

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDahoon_ChatInput> Dahoon_ChatInputWidgetClass;

	UPROPERTY()
	TObjectPtr<UDahoon_ChatInput> Dahoon_ChatInputWidgetInstance;

	FString ChatMessageString;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> NotificationTextWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> NotificationTextWidgetInstance;

public:
	UPROPERTY(Replicated, BlueprintReadOnly)
	FText NotificationText;

};
