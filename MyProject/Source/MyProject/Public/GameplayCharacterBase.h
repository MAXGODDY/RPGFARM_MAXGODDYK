#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimSequenceBase.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/Character.h"
#include "GameplayCharacterBase.generated.h"

UENUM(BlueprintType)
enum class EPlayerUpgradeType : uint8
{
	MaxStamina,
	OreDamage,
	MoveSpeed
};

UCLASS()
class MYPROJECT_API AGameplayCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AGameplayCharacterBase();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Attack")
	virtual void Attack();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void SetSprintActive(bool bShouldSprint);

	UFUNCTION(BlueprintCallable, Category = "Progression")
	void AddExperience(int32 ExperienceAmount);

	UFUNCTION(BlueprintCallable, Category = "Trading")
	bool SellOre(int32 OreAmount, int32 GoldPerOre);

	UFUNCTION(BlueprintCallable, Category = "Trading")
	bool BuyStaminaPotion(int32 GoldCost, float RestoreAmount);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool UseStaminaPotion();

	UFUNCTION(BlueprintCallable, Category = "Progression")
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

	UFUNCTION(BlueprintPure, Category = "Inventory")
	int32 GetStaminaPotionCount() const;

	UPROPERTY(BlueprintReadOnly, Category = "Attack")
	bool bIsAttacking;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resources")
	int32 CollectedOreResources;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resources")
	int32 CollectedGold;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	int32 StaminaPotionCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Progression")
	int32 PlayerLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Progression")
	int32 CurrentExperience;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Progression")
	int32 ExperienceToNextLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Progression")
	int32 AvailableUpgradePoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float WalkSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float SprintSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool bIsSprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stamina")
	float CurrentStamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stamina")
	float MinusStamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stamina")
	float PlusStamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stamina", meta = (ClampMin = "0.0"))
	float MovingStaminaRegen;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stamina", meta = (ClampMin = "0.0"))
	float StaminaRegenDelay;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stamina", meta = (ClampMin = "0"))
	float Stamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stamina", meta = (ClampMin = "1.0"))
	float MaxStamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory", meta = (ClampMin = "1.0"))
	float StaminaPotionRestoreAmount;

	void DecreaseStamina();
	void IncreaseStamina();

protected:
	virtual bool HasMovementInputIntent() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack")
	TObjectPtr<UAnimSequenceBase> AttackTimingAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
	TObjectPtr<class UStaticMesh> EquippedPickaxeMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
	FName PickaxeAttachSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
	FVector PickaxeRelativeLocation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
	FRotator PickaxeRelativeRotation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
	FVector PickaxeRelativeScale;

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
	void HandleUseStaminaPotionInput();
	void LoadCharacterDataFromJson();
	void SaveCharacterDataToJson() const;
	void UpdateResourceCounter() const;
	void UpdateStaminaBar() const;
	void TryDamageOre();
	void SyncAttachedVisualInputState();
	bool TriggerAttachedVisualAttack();
	void AttachPickaxeToAttachedVisual();

	bool bCanAttack;
	float TimeSinceLastStaminaUse;
	FTimerHandle AttackCooldownHandle;
	FTimerHandle AttackHitTimerHandle;
	FTimerHandle AttackStateTimerHandle;
	FTimerHandle AttachedVisualInputSyncTimerHandle;

	UPROPERTY(Transient)
	TObjectPtr<class UResourceCounterWidget> ResourceCounterWidget;

	UPROPERTY(Transient)
	TObjectPtr<class UStaminaBarWidget> StaminaBarWidget;
};
