#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Dahoon_ChatInput.generated.h"

class UEditableTextBox;

/**
 * 
 */
UCLASS()
class DAHOON_CHATX_API UDahoon_ChatInput : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

protected:
	UFUNCTION()
	void OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);
	
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> EditableTextBox_Dahoon_ChatInput;

};
