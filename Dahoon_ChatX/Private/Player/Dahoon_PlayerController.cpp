#include "Player/Dahoon_PlayerController.h"

#include "UI/Dahoon_ChatInput.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Dahoon_ChatX/Dahoon_ChatX.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Game/Dahoon_GameModeBase.h"
#include "Player/Dahoon_PlayerState.h"
#include "Net/UnrealNetwork.h"

ADahoon_PlayerController::ADahoon_PlayerController()
{
	bReplicates = true;
}

void ADahoon_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController() == false)
	{
		return;
	}
	if (GetNetMode() == NM_DedicatedServer) return;
	if (!IsLocalPlayerController()) return;


	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);

	if (IsValid(Dahoon_ChatInputWidgetClass) == true)
	{
		Dahoon_ChatInputWidgetInstance = CreateWidget<UDahoon_ChatInput>(this, Dahoon_ChatInputWidgetClass);
		if (IsValid(Dahoon_ChatInputWidgetInstance) == true)
		{
			Dahoon_ChatInputWidgetInstance->AddToViewport();
		}
	}
	if (IsValid(NotificationTextWidgetClass) == true)
	{
		NotificationTextWidgetInstance = CreateWidget<UUserWidget>(this, NotificationTextWidgetClass);
		if (IsValid(NotificationTextWidgetInstance) == true)
		{
			NotificationTextWidgetInstance->AddToViewport();
		}
	}
}

void ADahoon_PlayerController::SetChatMessageString(const FString& InChatMessageString)
{
	ChatMessageString = InChatMessageString;

	if (IsLocalPlayerController() == true)
	{
		ADahoon_PlayerState* Dahoon_PS = GetPlayerState<ADahoon_PlayerState>();
		if (IsValid(Dahoon_PS) == true)
		{
			FString CombinedMessageString = Dahoon_PS->GetPlayerInfoString() + TEXT(": ") + InChatMessageString;

			ServerRPCPrintChatMessageString(CombinedMessageString);
		}
	}
}

void ADahoon_PlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
	Dahoon_ChatXFunctionLibrary::MyPrintString(this, InChatMessageString, 10.f);
}

void ADahoon_PlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, NotificationText);
}

void ADahoon_PlayerController::ClientRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	PrintChatMessageString(InChatMessageString);
}

void ADahoon_PlayerController::ServerRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
	if (IsValid(GM) == true)
	{
		ADahoon_GameModeBase* Dahoon_GM = Cast<ADahoon_GameModeBase>(GM);
		if (IsValid(Dahoon_GM) == true)
		{
			Dahoon_GM->PrintChatMessageString(this, InChatMessageString);
		}
	}
}


