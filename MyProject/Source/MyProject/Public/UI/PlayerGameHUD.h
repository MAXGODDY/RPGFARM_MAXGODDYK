#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerGameHUD.generated.h"

UCLASS()
class MYPROJECT_API APlayerGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

private:
	void DrawMainMenu(float ViewportWidth, float ViewportHeight) const;
	void DrawResourcePanel(float ViewportWidth) const;
	void DrawLevelPanel() const;
	void DrawStaminaPanel(float ViewportHeight) const;
	void DrawTradePanel(float ViewportWidth, float ViewportHeight) const;
	void DrawProgressionPanel(float ViewportWidth, float ViewportHeight) const;
	class AThifCatcher* GetPlayerCharacter() const;
	class AThiefPlayerController* GetThiefPlayerController() const;
};
