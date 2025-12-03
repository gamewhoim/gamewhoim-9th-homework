#include "Game/Dahoon_GameModeBase.h"
#include "Game/Dahoon_GameStateBase.h"

#include "Player/Dahoon_PlayerController.h"
#include "EngineUtils.h"
#include "Player/Dahoon_PlayerState.h"

void ADahoon_GameModeBase::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	ADahoon_PlayerController* Dahoon_PlayerController = Cast<ADahoon_PlayerController>(NewPlayer);
	if (IsValid(Dahoon_PlayerController) == true)
	{
		Dahoon_PlayerController->NotificationText = FText::FromString(TEXT("Connected to the game server."));
		
		AllPlayerControllers.Add(Dahoon_PlayerController);

		ADahoon_PlayerState* Dahoon_PS = Dahoon_PlayerController->GetPlayerState<ADahoon_PlayerState>();
		if (IsValid(Dahoon_PS) == true)
		{
			Dahoon_PS->PlayerNameString = TEXT("Player") + FString::FromInt(AllPlayerControllers.Num());
		}

		ADahoon_GameStateBase* Dahoon_GameStateBase = GetGameState<ADahoon_GameStateBase>();
		if (IsValid(Dahoon_GameStateBase) == true)
		{
			Dahoon_GameStateBase->MulticastRPCBroadcastLoginMessage(Dahoon_PS->PlayerNameString);
		}
	}
}

FString ADahoon_GameModeBase::GenerateSecretNumber()
{
	TArray<int32> Numbers;
	for (int32 i = 1; i <= 9; ++i)
	{
		Numbers.Add(i);
	}

	FMath::RandInit(FDateTime::Now().GetTicks());
	Numbers = Numbers.FilterByPredicate([](int32 Num) { return Num > 0; });

	FString Result;
	for (int32 i = 0; i < 3; ++i)
	{
		int32 Index = FMath::RandRange(0, Numbers.Num() - 1);
		Result.Append(FString::FromInt(Numbers[Index]));
		Numbers.RemoveAt(Index);
	}

	return Result;
}

bool ADahoon_GameModeBase::IsGuessNumberString(const FString& InNumberString)
{
	bool bCanPlay = false;

	do {

		if (InNumberString.Len() != 3)
		{
			break;
		}

		bool bIsUnique = true;
		TSet<TCHAR> UniqueDigits;
		for (TCHAR C : InNumberString)
		{
			if (FChar::IsDigit(C) == false || C == '0')
			{
				bIsUnique = false;
				break;
			}

			UniqueDigits.Add(C);
		}

		if (bIsUnique == false)
		{
			break;
		}

		bCanPlay = true;

	} while (false);

	return bCanPlay;
}

FString ADahoon_GameModeBase::JudgeResult(const FString& InSecretNumberString, const FString& InGuessNumberString)
{
	int32 StrikeCount = 0, BallCount = 0;

	for (int32 i = 0; i < 3; ++i)
	{
		if (InSecretNumberString[i] == InGuessNumberString[i])
		{
			StrikeCount++;
		}
		else
		{
			FString PlayerGuessChar = FString::Printf(TEXT("%c"), InGuessNumberString[i]);
			if (InSecretNumberString.Contains(PlayerGuessChar))
			{
				BallCount++;
			}
		}
	}

	if (StrikeCount == 0 && BallCount == 0)
	{
		return TEXT("OUT");
	}

	return FString::Printf(TEXT("%dS%dB"), StrikeCount, BallCount);
}

void ADahoon_GameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SecretNumberString = GenerateSecretNumber();
	UE_LOG(LogTemp, Error, TEXT("%s"), *SecretNumberString);
}

void ADahoon_GameModeBase::PrintChatMessageString(ADahoon_PlayerController* InChattingPlayerController, const FString& InChatMessageString)
{
	int Index = InChatMessageString.Len() - 3;
	FString GuessNumberString = InChatMessageString.RightChop(Index);
	if (IsGuessNumberString(GuessNumberString) == true)
	{
		FString JudgeResultString = JudgeResult(SecretNumberString, GuessNumberString);

		IncreaseGuessCount(InChattingPlayerController);

		for (TActorIterator<ADahoon_PlayerController> It(GetWorld()); It; ++It)
		{
			ADahoon_PlayerController* Dahoon_PlayerController = *It;
			if (IsValid(Dahoon_PlayerController) == true)
			{
				FString CombinedMessageString = InChatMessageString + TEXT(" -> ") + JudgeResultString;
				Dahoon_PlayerController->ClientRPCPrintChatMessageString(CombinedMessageString);

				int32 StrikeCount = FCString::Atoi(*JudgeResultString.Left(1));
				JudgeGame(InChattingPlayerController, StrikeCount);
			}
		}
	}
	else
	{
		for (TActorIterator<ADahoon_PlayerController> It(GetWorld()); It; ++It)
		{
			ADahoon_PlayerController* Dahoon_PlayerController = *It;
			if (IsValid(Dahoon_PlayerController) == true)
			{
				Dahoon_PlayerController->ClientRPCPrintChatMessageString(InChatMessageString);
			}
		}
	}
}

void ADahoon_GameModeBase::IncreaseGuessCount(ADahoon_PlayerController* InChattingPlayerController)
{
	ADahoon_PlayerState* Dahoon_PS = InChattingPlayerController->GetPlayerState<ADahoon_PlayerState>();
	if (IsValid(Dahoon_PS) == true)
	{
		Dahoon_PS->CurrentGuessCount++;
	}
}

void ADahoon_GameModeBase::ResetGame()
{
	SecretNumberString = GenerateSecretNumber();

	for (const auto& Dahoon_PlayerController : AllPlayerControllers)
	{
		ADahoon_PlayerState* Dahoon_PS = Dahoon_PlayerController->GetPlayerState<ADahoon_PlayerState>();
		if (IsValid(Dahoon_PS) == true)
		{
			Dahoon_PS->CurrentGuessCount = 0;
		}
	}
}

void ADahoon_GameModeBase::JudgeGame(ADahoon_PlayerController* InChattingPlayerController, int InStrikeCount)
{
	if (3 == InStrikeCount)
	{
		ADahoon_PlayerState* Dahoon_PS = InChattingPlayerController->GetPlayerState<ADahoon_PlayerState>();
		for (const auto& Dahoon_PlayerController : AllPlayerControllers)
		{
			if (IsValid(Dahoon_PS) == true)
			{
				FString CombinedMessageString = Dahoon_PS->PlayerNameString + TEXT(" has won the game.");
				Dahoon_PlayerController->NotificationText = FText::FromString(CombinedMessageString);

				ResetGame();
			}
		}
	}
	else
	{
		bool bIsDraw = true;
		for (const auto& Dahoon_PlayerController : AllPlayerControllers)
		{
			ADahoon_PlayerState* Dahoon_PS = Dahoon_PlayerController->GetPlayerState<ADahoon_PlayerState>();
			if (IsValid(Dahoon_PS) == true)
			{
				if (Dahoon_PS->CurrentGuessCount < Dahoon_PS->MaxGuessCount)
				{
					bIsDraw = false;
					break;
				}
			}
		}

		if (true == bIsDraw)
		{
			for (const auto& Dahoon_PlayerController : AllPlayerControllers)
			{
				Dahoon_PlayerController->NotificationText = FText::FromString(TEXT("Draw..."));

				ResetGame();
			}
		}
	}
}
