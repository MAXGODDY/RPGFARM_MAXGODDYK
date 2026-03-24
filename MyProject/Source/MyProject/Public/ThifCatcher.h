#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimSequenceBase.h"
#include "Animation/AnimMontage.h"
#include "MainCheracter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/UnrealMathUtility.h"
#include "ThifCatcher.generated.h"

UENUM(BlueprintType)
enum class EPlayerUpgradeType : uint8
{
	MaxStamina,
	OreDamage,
	MoveSpeed
};

UCLASS()
class MYPROJECT_API AThifCatcher : public AMainCheracter
{
	GENERATED_BODY()

public:
	AThifCatcher();

	// Пружинный держатель камеры, который отвечает за дистанцию и плавность камеры.
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	// Основная игровая камера персонажа.
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JampAnimation")
	UAnimMontage* JumpAnimation;

	UPROPERTY(BlueprintReadOnly, Category = "Attack")
	bool bIsAttacking;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resources")
	int32 CollectedOreResources;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resources")
	int32 CollectedGold;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Progression")
	int32 PlayerLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Progression")
	int32 CurrentExperience;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Progression")
	int32 ExperienceToNextLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Progression")
	int32 AvailableUpgradePoints;

	// Базовая скорость передвижения персонажа.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float WalkSpeed;

	// Скорость передвижения персонажа во время спринта.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float SprintSpeed;

	virtual void SetupPlayerInputComponent(class UInputComponent* MyPlayerInput) override; // Подключаем базовую логику движка для инпута.

	virtual void BeginPlay() override;

	void MoveForwardBackward(float Value);
	void MoveRightLeft(float Value);

	void Jump();
	void StopJump();

	void Sprint();
	void StopSprint();
	void Attack();

	void AddExperience(int32 ExperienceAmount);
	bool SellOre(int32 OreAmount, int32 GoldPerOre);
	bool BuyStaminaPotion(int32 GoldCost, float RestoreAmount);
	bool SpendUpgradePoint(EPlayerUpgradeType UpgradeType);

	UFUNCTION(BlueprintPure, Category = "Resources")
	int32 GetCollectedGold() const;

	UFUNCTION(BlueprintPure, Category = "Progression")
	int32 GetPlayerLevel() const;

	UFUNCTION(BlueprintPure, Category = "Progression")
	int32 GetCurrentExperienceAmount() const;

	UFUNCTION(BlueprintPure, Category = "Progression")
	int32 GetExperienceToNextLevelAmount() const;

	UFUNCTION(BlueprintPure, Category = "Progression")
	int32 GetAvailableUpgradePoints() const;

	UFUNCTION(BlueprintPure, Category = "Progression")
	float GetOreDamageAmount() const;

	bool bIsSprint;

	UPROPERTY(EditDefaultsOnly, Category = "Stamina")
	float CurrentStamina;

	UPROPERTY(EditDefaultsOnly, Category = "Stamina")
	float MinusStamina = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Stamina")
	float PlusStamina = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Stamina", meta = (ClampMin = "0", ClampMax = "100"))
	float Stamina = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stamina", meta = (ClampMin = "1.0"))
	float MaxStamina;

	void DecreaseStamina();
	void IncreaseStamina();

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	TObjectPtr<UAnimSequenceBase> AttackTimingAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack", meta = (ClampMin = "0.0"))
	float OreDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack", meta = (ClampMin = "0.0"))
	float AttackRange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack", meta = (ClampMin = "0.0"))
	float AttackCooldown;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack", meta = (ClampMin = "0.0"))
	float AttackStateDuration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float AttackHitNormalizedTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Progression", meta = (ClampMin = "1"))
	int32 BaseExperienceToNextLevel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Progression", meta = (ClampMin = "1.0"))
	float MaxStaminaUpgradeAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Progression", meta = (ClampMin = "0.1"))
	float OreDamageUpgradeAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Progression", meta = (ClampMin = "1.0"))
	float MoveSpeedUpgradeAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resources")
	TSubclassOf<class UResourceCounterWidget> ResourceCounterWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stamina")
	TSubclassOf<class UStaminaBarWidget> StaminaBarWidgetClass;

private:
	void AddOreResources(int32 ResourceAmount);
	void TriggerAttackHit();
	void FinishAttackState();
	void InitializeResourceCounter();
	void InitializeStaminaBar();
	void UpdateHudLayout() const;
	void UpdateResourceCounter() const;
	void UpdateStaminaBar() const;
	void TryDamageOre();

	bool bCanAttack;
	FTimerHandle AttackCooldownHandle;
	FTimerHandle AttackHitTimerHandle;
	FTimerHandle AttackStateTimerHandle;

	UPROPERTY(Transient)
	TObjectPtr<class UResourceCounterWidget> ResourceCounterWidget;

	UPROPERTY(Transient)
	TObjectPtr<class UStaminaBarWidget> StaminaBarWidget;

};
