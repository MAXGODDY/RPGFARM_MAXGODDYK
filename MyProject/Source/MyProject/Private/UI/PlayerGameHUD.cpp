#include "UI/PlayerGameHUD.h"

#include "Engine/Canvas.h"
#include "Engine/Engine.h"
#include "Engine/Font.h"
#include "GameFramework/PlayerController.h"
#include "Math/UnrealMathUtility.h"
#include "ThiefPlayerController.h"
#include "ThifCatcher.h"

namespace
{
	const FLinearColor PanelBackgroundColor(0.02f, 0.02f, 0.02f, 0.82f);
	const FLinearColor PanelBorderColor(0.55f, 0.55f, 0.55f, 1.0f);
	const FLinearColor StaminaFillColor(0.12f, 0.80f, 0.18f, 1.0f);
	const FLinearColor AccentColor(0.90f, 0.75f, 0.18f, 1.0f);
	const FLinearColor PositiveColor(0.18f, 0.86f, 0.32f, 1.0f);

	void DrawPanel(UCanvas* Canvas, const FVector2D& Position, const FVector2D& Size)
	{
		FCanvasTileItem BackgroundTile(Position, Size, PanelBackgroundColor);
		BackgroundTile.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(BackgroundTile);

		FCanvasBoxItem BorderBox(Position, Size);
		BorderBox.SetColor(PanelBorderColor);
		Canvas->DrawItem(BorderBox);
	}

	void DrawTextLine(UCanvas* Canvas, UFont* Font, const FString& Text, const FVector2D& Position, const FLinearColor& Color)
	{
		FCanvasTextItem TextItem(Position, FText::FromString(Text), Font, Color);
		TextItem.EnableShadow(FLinearColor::Black);
		Canvas->DrawItem(TextItem);
	}
}

void APlayerGameHUD::DrawHUD()
{
	Super::DrawHUD();

	if (!Canvas || !PlayerOwner)
	{
		return;
	}

	const float ViewportWidth = Canvas->SizeX;
	const float ViewportHeight = Canvas->SizeY;
	if (ViewportWidth <= 0.0f || ViewportHeight <= 0.0f)
	{
		return;
	}

	if (const AThiefPlayerController* ThiefController = GetThiefPlayerController())
	{
		if (ThiefController->IsInMenuMap())
		{
			DrawMainMenu(ViewportWidth, ViewportHeight);
			return;
		}
	}

	DrawResourcePanel(ViewportWidth);
	DrawLevelPanel();
	DrawStaminaPanel(ViewportHeight);

	if (const AThiefPlayerController* ThiefController = GetThiefPlayerController())
	{
		if (ThiefController->IsTradeMenuOpen())
		{
			DrawTradePanel(ViewportWidth, ViewportHeight);
		}

		if (ThiefController->IsProgressionMenuOpen())
		{
			DrawProgressionPanel(ViewportWidth, ViewportHeight);
		}
	}
}

void APlayerGameHUD::DrawMainMenu(float ViewportWidth, float ViewportHeight) const
{
	UFont* LargeFont = GEngine ? GEngine->GetLargeFont() : nullptr;
	UFont* MediumFont = GEngine ? GEngine->GetMediumFont() : nullptr;
	if (!LargeFont || !MediumFont)
	{
		return;
	}

	const FVector2D PanelSize(640.0f, 280.0f);
	const FVector2D PanelPosition((ViewportWidth - PanelSize.X) * 0.5f, (ViewportHeight - PanelSize.Y) * 0.5f);
	DrawPanel(Canvas, PanelPosition, PanelSize);

	DrawTextLine(Canvas, LargeFont, TEXT("RPG FARM"), PanelPosition + FVector2D(210.0f, 40.0f), AccentColor);
	DrawTextLine(Canvas, MediumFont, TEXT("Start Menu"), PanelPosition + FVector2D(240.0f, 96.0f), FLinearColor::White);
	DrawTextLine(Canvas, MediumFont, TEXT("[Enter] Start Game"), PanelPosition + FVector2D(185.0f, 150.0f), FLinearColor::White);
	DrawTextLine(Canvas, MediumFont, TEXT("[Esc] Quit"), PanelPosition + FVector2D(225.0f, 192.0f), FLinearColor::White);
}

void APlayerGameHUD::DrawResourcePanel(float ViewportWidth) const
{
	AThifCatcher* PlayerCharacter = GetPlayerCharacter();
	if (!PlayerCharacter)
	{
		return;
	}

	UFont* Font = GEngine ? GEngine->GetLargeFont() : nullptr;
	if (!Font)
	{
		return;
	}

	float OreTextWidth = 0.0f;
	float OreTextHeight = 0.0f;
	float GoldTextWidth = 0.0f;
	float GoldTextHeight = 0.0f;
	const FString OreText = FString::Printf(TEXT("Ore: %d"), PlayerCharacter->CollectedOreResources);
	const FString GoldText = FString::Printf(TEXT("Gold: %d"), PlayerCharacter->GetCollectedGold());
	Canvas->StrLen(Font, OreText, OreTextWidth, OreTextHeight);
	Canvas->StrLen(Font, GoldText, GoldTextWidth, GoldTextHeight);

	const FVector2D PanelSize(FMath::Max(OreTextWidth, GoldTextWidth) + 40.0f, OreTextHeight + GoldTextHeight + 32.0f);
	const FVector2D PanelPosition(ViewportWidth - PanelSize.X - 40.0f, 26.0f);
	DrawPanel(Canvas, PanelPosition, PanelSize);
	DrawTextLine(Canvas, Font, OreText, PanelPosition + FVector2D(18.0f, 8.0f), FLinearColor::White);
	DrawTextLine(Canvas, Font, GoldText, PanelPosition + FVector2D(18.0f, 8.0f + OreTextHeight + 4.0f), AccentColor);
}

void APlayerGameHUD::DrawLevelPanel() const
{
	AThifCatcher* PlayerCharacter = GetPlayerCharacter();
	if (!PlayerCharacter)
	{
		return;
	}

	UFont* Font = GEngine ? GEngine->GetMediumFont() : nullptr;
	if (!Font)
	{
		return;
	}

	const FVector2D PanelPosition(34.0f, 26.0f);
	const FVector2D PanelSize(260.0f, 72.0f);
	DrawPanel(Canvas, PanelPosition, PanelSize);

	const FString LevelText = FString::Printf(TEXT("Level: %d"), PlayerCharacter->GetPlayerLevel());
	const FString ExperienceText = FString::Printf(
		TEXT("XP: %d / %d"),
		PlayerCharacter->GetCurrentExperienceAmount(),
		PlayerCharacter->GetExperienceToNextLevelAmount());

	DrawTextLine(Canvas, Font, LevelText, PanelPosition + FVector2D(16.0f, 10.0f), AccentColor);
	DrawTextLine(Canvas, Font, ExperienceText, PanelPosition + FVector2D(16.0f, 36.0f), FLinearColor::White);
}

void APlayerGameHUD::DrawStaminaPanel(float ViewportHeight) const
{
	AThifCatcher* PlayerCharacter = GetPlayerCharacter();
	if (!PlayerCharacter)
	{
		return;
	}

	UFont* Font = GEngine ? GEngine->GetMediumFont() : nullptr;
	if (!Font)
	{
		return;
	}

	const FVector2D PanelPosition(34.0f, ViewportHeight - 90.0f);
	const FVector2D PanelSize(320.0f, 54.0f);
	const FVector2D InnerPosition = PanelPosition + FVector2D(10.0f, 8.0f);
	const FVector2D InnerSize(PanelSize.X - 20.0f, PanelSize.Y - 16.0f);

	const float SafeMaxStamina = FMath::Max(PlayerCharacter->MaxStamina, 1.0f);
	const float StaminaPercent = FMath::Clamp(PlayerCharacter->Stamina / SafeMaxStamina, 0.0f, 1.0f);

	DrawPanel(Canvas, PanelPosition, PanelSize);

	FCanvasTileItem BarBackground(InnerPosition, InnerSize, FLinearColor(0.08f, 0.08f, 0.08f, 1.0f));
	BarBackground.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(BarBackground);

	FCanvasTileItem BarFill(InnerPosition, FVector2D(InnerSize.X * StaminaPercent, InnerSize.Y), StaminaFillColor);
	BarFill.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(BarFill);

	const FString StaminaText = FString::Printf(
		TEXT("Stamina: %d / %d"),
		FMath::RoundToInt(PlayerCharacter->Stamina),
		FMath::RoundToInt(SafeMaxStamina));

	float TextWidth = 0.0f;
	float TextHeight = 0.0f;
	Canvas->StrLen(Font, StaminaText, TextWidth, TextHeight);

	FCanvasTextItem StaminaTextItem(
		PanelPosition + FVector2D((PanelSize.X - TextWidth) * 0.5f, (PanelSize.Y - TextHeight) * 0.5f),
		FText::FromString(StaminaText),
		Font,
		FLinearColor::White);
	StaminaTextItem.EnableShadow(FLinearColor::Black);
	Canvas->DrawItem(StaminaTextItem);
}

AThiefPlayerController* APlayerGameHUD::GetThiefPlayerController() const
{
	return Cast<AThiefPlayerController>(PlayerOwner);
}

AThifCatcher* APlayerGameHUD::GetPlayerCharacter() const
{
	if (!PlayerOwner)
	{
		return nullptr;
	}

	return Cast<AThifCatcher>(PlayerOwner->GetPawn());
}

void APlayerGameHUD::DrawTradePanel(float ViewportWidth, float ViewportHeight) const
{
	AThifCatcher* PlayerCharacter = GetPlayerCharacter();
	if (!PlayerCharacter)
	{
		return;
	}

	UFont* LargeFont = GEngine ? GEngine->GetLargeFont() : nullptr;
	UFont* MediumFont = GEngine ? GEngine->GetMediumFont() : nullptr;
	if (!LargeFont || !MediumFont)
	{
		return;
	}

	const FVector2D PanelSize(680.0f, 320.0f);
	const FVector2D PanelPosition((ViewportWidth - PanelSize.X) * 0.5f, (ViewportHeight - PanelSize.Y) * 0.5f);
	DrawPanel(Canvas, PanelPosition, PanelSize);

	DrawTextLine(Canvas, LargeFont, TEXT("Trading"), PanelPosition + FVector2D(250.0f, 24.0f), AccentColor);
	DrawTextLine(Canvas, MediumFont, FString::Printf(TEXT("Ore: %d"), PlayerCharacter->CollectedOreResources), PanelPosition + FVector2D(32.0f, 84.0f), FLinearColor::White);
	DrawTextLine(Canvas, MediumFont, FString::Printf(TEXT("Gold: %d"), PlayerCharacter->GetCollectedGold()), PanelPosition + FVector2D(220.0f, 84.0f), AccentColor);
	DrawTextLine(Canvas, MediumFont, TEXT("[1] Sell 1 Ore (+10 Gold)"), PanelPosition + FVector2D(32.0f, 138.0f), FLinearColor::White);
	DrawTextLine(Canvas, MediumFont, TEXT("[2] Sell 5 Ore (+50 Gold)"), PanelPosition + FVector2D(32.0f, 178.0f), FLinearColor::White);
	DrawTextLine(Canvas, MediumFont, TEXT("[3] Buy Stamina Potion (-25 Gold, +40 Stamina)"), PanelPosition + FVector2D(32.0f, 218.0f), PositiveColor);
	DrawTextLine(Canvas, MediumFont, TEXT("[Esc] Close"), PanelPosition + FVector2D(32.0f, 266.0f), FLinearColor::White);
}

void APlayerGameHUD::DrawProgressionPanel(float ViewportWidth, float ViewportHeight) const
{
	AThifCatcher* PlayerCharacter = GetPlayerCharacter();
	if (!PlayerCharacter)
	{
		return;
	}

	UFont* LargeFont = GEngine ? GEngine->GetLargeFont() : nullptr;
	UFont* MediumFont = GEngine ? GEngine->GetMediumFont() : nullptr;
	if (!LargeFont || !MediumFont)
	{
		return;
	}

	const FVector2D PanelSize(720.0f, 360.0f);
	const FVector2D PanelPosition((ViewportWidth - PanelSize.X) * 0.5f, (ViewportHeight - PanelSize.Y) * 0.5f);
	DrawPanel(Canvas, PanelPosition, PanelSize);

	DrawTextLine(Canvas, LargeFont, TEXT("Character Progression"), PanelPosition + FVector2D(158.0f, 24.0f), AccentColor);
	DrawTextLine(Canvas, MediumFont, FString::Printf(TEXT("Level: %d"), PlayerCharacter->GetPlayerLevel()), PanelPosition + FVector2D(32.0f, 84.0f), FLinearColor::White);
	DrawTextLine(
		Canvas,
		MediumFont,
		FString::Printf(TEXT("XP: %d / %d"), PlayerCharacter->GetCurrentExperienceAmount(), PlayerCharacter->GetExperienceToNextLevelAmount()),
		PanelPosition + FVector2D(220.0f, 84.0f),
		FLinearColor::White);
	DrawTextLine(
		Canvas,
		MediumFont,
		FString::Printf(TEXT("Upgrade Points: %d"), PlayerCharacter->GetAvailableUpgradePoints()),
		PanelPosition + FVector2D(440.0f, 84.0f),
		PositiveColor);
	DrawTextLine(
		Canvas,
		MediumFont,
		FString::Printf(TEXT("Max Stamina: %d"), FMath::RoundToInt(PlayerCharacter->MaxStamina)),
		PanelPosition + FVector2D(32.0f, 138.0f),
		FLinearColor::White);
	DrawTextLine(
		Canvas,
		MediumFont,
		FString::Printf(TEXT("Ore Damage: %.0f"), PlayerCharacter->GetOreDamageAmount()),
		PanelPosition + FVector2D(32.0f, 178.0f),
		FLinearColor::White);
	DrawTextLine(
		Canvas,
		MediumFont,
		FString::Printf(TEXT("Walk Speed: %.0f"), PlayerCharacter->WalkSpeed),
		PanelPosition + FVector2D(32.0f, 218.0f),
		FLinearColor::White);
	DrawTextLine(Canvas, MediumFont, TEXT("[1] +20 Max Stamina"), PanelPosition + FVector2D(380.0f, 138.0f), PositiveColor);
	DrawTextLine(Canvas, MediumFont, TEXT("[2] +1 Ore Damage"), PanelPosition + FVector2D(380.0f, 178.0f), PositiveColor);
	DrawTextLine(Canvas, MediumFont, TEXT("[3] +30 Move Speed"), PanelPosition + FVector2D(380.0f, 218.0f), PositiveColor);
	DrawTextLine(Canvas, MediumFont, TEXT("[Esc] Close"), PanelPosition + FVector2D(32.0f, 296.0f), FLinearColor::White);
}
