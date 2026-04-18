#include "ThiefCatcerGameMode.h"

#include "Misc/PackageName.h"
#include "ThiefPlayerController.h"
#include "UI/PlayerGameHUD.h"
#include "UObject/ConstructorHelpers.h"

AThiefCatcerGameMode::AThiefCatcerGameMode() : Super()
{
	ConstructorHelpers::FClassFinder<APawn> SandboxCharacterThiefCatcher(TEXT("/Game/Blueprints/BP_MyThifCatcher_Sandbox"));
	if (SandboxCharacterThiefCatcher.Succeeded())
	{
		DefaultPawnClass = SandboxCharacterThiefCatcher.Class;
	}
	else
	{
		ConstructorHelpers::FClassFinder<APawn> MainCharacterThiefCatcher(TEXT("/Game/Blueprints/Bp_MyThifCatcher"));
		if (MainCharacterThiefCatcher.Succeeded())
		{
			DefaultPawnClass = MainCharacterThiefCatcher.Class;
		}
	}

	PlayerControllerClass = AThiefPlayerController::StaticClass();
	HUDClass = APlayerGameHUD::StaticClass();
}

APawn* AThiefCatcerGameMode::SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot)
{
	if (GetWorld())
	{
		FString MapName = GetWorld()->GetMapName();
		MapName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
		if (FPackageName::GetShortName(MapName).Equals(TEXT("NewMap"), ESearchCase::IgnoreCase))
		{
			return nullptr;
		}
	}

	return Super::SpawnDefaultPawnFor_Implementation(NewPlayer, StartSpot);
}
