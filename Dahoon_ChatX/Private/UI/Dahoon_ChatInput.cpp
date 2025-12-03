#include "UI/Dahoon_ChatInput.h"
#include "Components/EditableTextBox.h"
#include "Player/Dahoon_PlayerController.h"

void UDahoon_ChatInput::NativeConstruct()
{
	Super::NativeConstruct();

	if (EditableTextBox_Dahoon_ChatInput->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnChatInputTextCommitted) == false)
	{
		EditableTextBox_Dahoon_ChatInput->OnTextCommitted.AddDynamic(this, &ThisClass::OnChatInputTextCommitted);
	}
}

void UDahoon_ChatInput::NativeDestruct()
{
	Super::NativeDestruct();

	if (EditableTextBox_Dahoon_ChatInput->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnChatInputTextCommitted) == true)
	{
		EditableTextBox_Dahoon_ChatInput->OnTextCommitted.RemoveDynamic(this, &ThisClass::OnChatInputTextCommitted);
	}
}

void UDahoon_ChatInput::OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		APlayerController* OwningPlayerController = GetOwningPlayer();
		if (IsValid(OwningPlayerController) == true)
		{
			ADahoon_PlayerController* OwningDahoon_PlayerController = Cast<ADahoon_PlayerController>(OwningPlayerController);
			if (IsValid(OwningDahoon_PlayerController) == true)
			{
				OwningDahoon_PlayerController->SetChatMessageString(Text.ToString());

				EditableTextBox_Dahoon_ChatInput->SetText(FText());
			}
		}
	}
}
