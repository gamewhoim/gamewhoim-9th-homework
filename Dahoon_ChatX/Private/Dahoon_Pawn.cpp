#include "Dahoon_Pawn.h"
#include "Dahoon_ChatX/Dahoon_ChatX.h"


void ADahoon_Pawn::BeginPlay()
{
	Super::BeginPlay();

	FString NetRoleString = Dahoon_ChatXFunctionLibrary::GetRoleString(this);
	FString CombinedString = FString::Printf(TEXT("Dahoon_Pawn::BeginPlay() %s [%s]"), *Dahoon_ChatXFunctionLibrary::GetNetModeString(this), *NetRoleString);
	Dahoon_ChatXFunctionLibrary::MyPrintString(this, CombinedString, 10.f);
}

void ADahoon_Pawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	FString NetRoleString = Dahoon_ChatXFunctionLibrary::GetRoleString(this);
	FString CombinedString = FString::Printf(TEXT("Dahoon_Pawn::PossessedBy() %s [%s]"), *Dahoon_ChatXFunctionLibrary::GetNetModeString(this), *NetRoleString);
	Dahoon_ChatXFunctionLibrary::MyPrintString(this, CombinedString, 10.f);
}