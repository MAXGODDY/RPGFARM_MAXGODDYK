#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ThiefPlayerController.generated.h"

UCLASS()
class MYPROJECT_API AThiefPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AThiefPlayerController();

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintPure, Category = "UI")
	bool IsInMenuMap() const;

	UFUNCTION(BlueprintPure, Category = "UI")
	bool IsTradeMenuOpen() const;

	UFUNCTION(BlueprintPure, Category = "UI")
	bool IsProgressionMenuOpen() const;

	UFUNCTION(BlueprintPure, Category = "UI")
	bool IsAnyModalOpen() const;

	void CloseAllMenus();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Menu")
	FName MenuMapName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Menu")
	FName GameplayMapName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Trading", meta = (ClampMin = "1"))
	int32 GoldPerOre;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Trading", meta = (ClampMin = "1"))
	int32 StaminaPotionCost;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Trading", meta = (ClampMin = "1.0"))
	float StaminaPotionRestoreAmount;

private:
	void ApplyMenuInputState();
	void HandlePrimaryConfirm();
	void HandleBackAction();
	void ToggleTradeMenu();
	void ToggleProgressionMenu();
	void HandleOptionOne();
	void HandleOptionTwo();
	void HandleOptionThree();
	class AThifCatcher* GetPlayerCharacter() const;

	bool bTradeMenuOpen;
	bool bProgressionMenuOpen;
};
