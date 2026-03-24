#include "ThiefPlayerController.h"

#include "Engine/World.h"
#include "GameFramework/HUD.h"
#include "InputCoreTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Misc/PackageName.h"
#include "ThifCatcher.h"
#include "UI/PlayerGameHUD.h"

namespace
{
	FString GetShortMapName(const UWorld* World)
	{
		if (!World)
		{
			return FString();
		}

		FString MapName = World->GetMapName();
		MapName.RemoveFromStart(World->StreamingLevelsPrefix);
		return FPackageName::GetShortName(MapName);
	}
}

AThiefPlayerController::AThiefPlayerController()
{
	bTradeMenuOpen = false;
	bProgressionMenuOpen = false;
	MenuMapName = TEXT("NewMap");
	GameplayMapName = TEXT("/Game/Namaqualand/Levels/Showcase");
	GoldPerOre = 10;
	StaminaPotionCost = 25;
	StaminaPotionRestoreAmount = 40.0f;
}

void AThiefPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!GetHUD() || !GetHUD()->IsA(APlayerGameHUD::StaticClass()))
	{
		ClientSetHUD(APlayerGameHUD::StaticClass());
	}

	ApplyMenuInputState();
}

void AThiefPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (!InputComponent)
	{
		return;
	}

	InputComponent->BindKey(EKeys::Enter, IE_Pressed, this, &AThiefPlayerController::HandlePrimaryConfirm);
	InputComponent->BindKey(EKeys::Escape, IE_Pressed, this, &AThiefPlayerController::HandleBackAction);
	InputComponent->BindKey(EKeys::B, IE_Pressed, this, &AThiefPlayerController::ToggleTradeMenu);
	InputComponent->BindKey(EKeys::P, IE_Pressed, this, &AThiefPlayerController::ToggleProgressionMenu);
	InputComponent->BindKey(EKeys::One, IE_Pressed, this, &AThiefPlayerController::HandleOptionOne);
	InputComponent->BindKey(EKeys::Two, IE_Pressed, this, &AThiefPlayerController::HandleOptionTwo);
	InputComponent->BindKey(EKeys::Three, IE_Pressed, this, &AThiefPlayerController::HandleOptionThree);
}

bool AThiefPlayerController::IsInMenuMap() const
{
	return GetShortMapName(GetWorld()).Equals(MenuMapName.ToString(), ESearchCase::IgnoreCase);
}

bool AThiefPlayerController::IsTradeMenuOpen() const
{
	return bTradeMenuOpen;
}

bool AThiefPlayerController::IsProgressionMenuOpen() const
{
	return bProgressionMenuOpen;
}

bool AThiefPlayerController::IsAnyModalOpen() const
{
	return bTradeMenuOpen || bProgressionMenuOpen || IsInMenuMap();
}

void AThiefPlayerController::CloseAllMenus()
{
	bTradeMenuOpen = false;
	bProgressionMenuOpen = false;
	ApplyMenuInputState();
}

void AThiefPlayerController::ApplyMenuInputState()
{
	const bool bMenuLocked = IsAnyModalOpen();
	SetIgnoreMoveInput(bMenuLocked);
	SetIgnoreLookInput(bMenuLocked);
	SetShowMouseCursor(false);
}

void AThiefPlayerController::HandlePrimaryConfirm()
{
	if (!IsInMenuMap())
	{
		return;
	}

	UGameplayStatics::OpenLevel(this, GameplayMapName);
}

void AThiefPlayerController::HandleBackAction()
{
	if (IsInMenuMap())
	{
		UKismetSystemLibrary::QuitGame(this, this, EQuitPreference::Quit, false);
		return;
	}

	CloseAllMenus();
}

void AThiefPlayerController::ToggleTradeMenu()
{
	if (IsInMenuMap())
	{
		return;
	}

	if (const AThifCatcher* PlayerCharacter = GetPlayerCharacter())
	{
		if (PlayerCharacter->bIsAttacking)
		{
			return;
		}
	}

	bTradeMenuOpen = !bTradeMenuOpen;
	if (bTradeMenuOpen)
	{
		bProgressionMenuOpen = false;
	}

	ApplyMenuInputState();
}

void AThiefPlayerController::ToggleProgressionMenu()
{
	if (IsInMenuMap())
	{
		return;
	}

	if (const AThifCatcher* PlayerCharacter = GetPlayerCharacter())
	{
		if (PlayerCharacter->bIsAttacking)
		{
			return;
		}
	}

	bProgressionMenuOpen = !bProgressionMenuOpen;
	if (bProgressionMenuOpen)
	{
		bTradeMenuOpen = false;
	}

	ApplyMenuInputState();
}

void AThiefPlayerController::HandleOptionOne()
{
	if (AThifCatcher* PlayerCharacter = GetPlayerCharacter())
	{
		if (bTradeMenuOpen)
		{
			PlayerCharacter->SellOre(1, GoldPerOre);
			return;
		}

		if (bProgressionMenuOpen)
		{
			PlayerCharacter->SpendUpgradePoint(EPlayerUpgradeType::MaxStamina);
		}
	}
}

void AThiefPlayerController::HandleOptionTwo()
{
	if (AThifCatcher* PlayerCharacter = GetPlayerCharacter())
	{
		if (bTradeMenuOpen)
		{
			PlayerCharacter->SellOre(5, GoldPerOre);
			return;
		}

		if (bProgressionMenuOpen)
		{
			PlayerCharacter->SpendUpgradePoint(EPlayerUpgradeType::OreDamage);
		}
	}
}

void AThiefPlayerController::HandleOptionThree()
{
	if (AThifCatcher* PlayerCharacter = GetPlayerCharacter())
	{
		if (bTradeMenuOpen)
		{
			PlayerCharacter->BuyStaminaPotion(StaminaPotionCost, StaminaPotionRestoreAmount);
			return;
		}

		if (bProgressionMenuOpen)
		{
			PlayerCharacter->SpendUpgradePoint(EPlayerUpgradeType::MoveSpeed);
		}
	}
}

AThifCatcher* AThiefPlayerController::GetPlayerCharacter() const
{
	return Cast<AThifCatcher>(GetPawn());
}
