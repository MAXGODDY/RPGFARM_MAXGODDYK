#include "GameplayCharacterBase.h"

#include "Actors/OreStoneBase.h"
#include "Animation/AnimSequenceBase.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Save/MyProjectJsonSaveUtils.h"
#include "ThiefPlayerController.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "UI/ResourceCounterWidget.h"
#include "UI/StaminaBarWidget.h"

AGameplayCharacterBase::AGameplayCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	WalkSpeed = 450.0f;
	SprintSpeed = 700.0f;
	bIsSprint = false;
	MaxStamina = 100.0f;
	Stamina = MaxStamina;
	CurrentStamina = Stamina;
	MinusStamina = 1.0f;
	PlusStamina = 1.0f;
	OreDamage = 1.0f;
	AttackRange = 350.0f;
	AttackCooldown = 0.45f;
	AttackStateDuration = 5.2f;
	AttackHitNormalizedTime = 0.55f;
	BaseExperienceToNextLevel = 100;
	MaxStaminaUpgradeAmount = 20.0f;
	OreDamageUpgradeAmount = 1.0f;
	MoveSpeedUpgradeAmount = 30.0f;
	bCanAttack = true;
	bIsAttacking = false;
	CollectedOreResources = 0;
	CollectedGold = 0;
	PlayerLevel = 1;
	CurrentExperience = 0;
	ExperienceToNextLevel = BaseExperienceToNextLevel;
	ResourceCounterWidget = nullptr;
	StaminaBarWidget = nullptr;

	if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
	{
		MovementComponent->MaxWalkSpeed = WalkSpeed;
	}

	static ConstructorHelpers::FObjectFinder<UAnimSequenceBase> DefaultAttackAnimationFinder(
		TEXT("/Game/MainPlayer/Animations/AM_Pickaxe_Attack.AM_Pickaxe_Attack"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DefaultAttackMontageFinder(
		TEXT("/Game/MainPlayer/Animations/AM_Pickaxe_Attack_Montage.AM_Pickaxe_Attack_Montage"));
	if (DefaultAttackMontageFinder.Succeeded())
	{
		AttackMontage = DefaultAttackMontageFinder.Object;
		AttackStateDuration = FMath::Max(AttackMontage->GetPlayLength(), 0.0f);
	}
	else
	{
		AttackMontage = nullptr;
	}

	if (DefaultAttackAnimationFinder.Succeeded())
	{
		AttackTimingAnimation = DefaultAttackAnimationFinder.Object;
		if (!AttackMontage)
		{
			AttackStateDuration = FMath::Max(AttackTimingAnimation->GetPlayLength(), 0.0f);
		}
	}
	else
	{
		AttackTimingAnimation = nullptr;
	}
}

void AGameplayCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(true);

	LoadCharacterDataFromJson();
	UpdateResourceCounter();
	UpdateStaminaBar();
}

void AGameplayCharacterBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	SaveCharacterDataToJson();
	Super::EndPlay(EndPlayReason);
}

void AGameplayCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (!PlayerInputComponent)
	{
		return;
	}

	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &AGameplayCharacterBase::Attack);
}

void AGameplayCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsSprint && !FMath::IsNearlyZero(Stamina))
	{
		DecreaseStamina();
	}
	else if (!bIsSprint && !FMath::IsNearlyEqual(Stamina, MaxStamina))
	{
		IncreaseStamina();
	}

	if (FMath::IsNearlyZero(Stamina))
	{
		SetSprintActive(false);
	}
}

void AGameplayCharacterBase::Attack()
{
	if (bIsAttacking || !bCanAttack)
	{
		return;
	}

	if (const AThiefPlayerController* ThiefController = Cast<AThiefPlayerController>(GetController()))
	{
		if (ThiefController->IsAnyModalOpen())
		{
			return;
		}
	}

	if (const UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
	{
		if (MovementComponent->IsFalling())
		{
			return;
		}
	}

	bCanAttack = false;
	bIsAttacking = true;
	SetSprintActive(false);
	StopJumping();

	const float EffectiveAttackDuration = AttackMontage
		? FMath::Max(AttackMontage->GetPlayLength(), 0.0f)
		: AttackTimingAnimation
		? FMath::Max(AttackTimingAnimation->GetPlayLength(), 0.0f)
		: AttackStateDuration;
	const float EffectiveAttackCooldown = FMath::Max(AttackCooldown, EffectiveAttackDuration);

	if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
	{
		MovementComponent->StopMovementImmediately();
		MovementComponent->DisableMovement();
	}

	if (AttackMontage)
	{
		PlayAnimMontage(AttackMontage, 1.0f, NAME_None);
	}

	GetWorldTimerManager().ClearTimer(AttackStateTimerHandle);
	GetWorldTimerManager().ClearTimer(AttackHitTimerHandle);

	if (EffectiveAttackDuration <= 0.0f)
	{
		TriggerAttackHit();
		FinishAttackState();
	}
	else
	{
		const float EffectiveHitDelay = FMath::Clamp(AttackHitNormalizedTime, 0.0f, 1.0f) * EffectiveAttackDuration;
		if (EffectiveHitDelay <= 0.0f)
		{
			TriggerAttackHit();
		}
		else
		{
			GetWorldTimerManager().SetTimer(
				AttackHitTimerHandle,
				this,
				&AGameplayCharacterBase::TriggerAttackHit,
				FMath::Min(EffectiveHitDelay, EffectiveAttackDuration),
				false);
		}

		GetWorldTimerManager().SetTimer(
			AttackStateTimerHandle,
			this,
			&AGameplayCharacterBase::FinishAttackState,
			EffectiveAttackDuration,
			false);
	}

	GetWorldTimerManager().ClearTimer(AttackCooldownHandle);
	if (EffectiveAttackCooldown <= 0.0f)
	{
		bCanAttack = true;
		return;
	}

	GetWorldTimerManager().SetTimer(
		AttackCooldownHandle,
		[this]()
		{
			bCanAttack = true;
		},
		EffectiveAttackCooldown,
		false);
}

void AGameplayCharacterBase::SetSprintActive(const bool bShouldSprint)
{
	if (bShouldSprint && FMath::IsNearlyZero(Stamina))
	{
		bIsSprint = false;
	}
	else
	{
		bIsSprint = bShouldSprint;
	}

	if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
	{
		MovementComponent->MaxWalkSpeed = bIsSprint ? SprintSpeed : WalkSpeed;
	}
}

void AGameplayCharacterBase::AddExperience(const int32 ExperienceAmount)
{
	if (ExperienceAmount <= 0)
	{
		return;
	}

	CurrentExperience += ExperienceAmount;
	while (CurrentExperience >= ExperienceToNextLevel)
	{
		CurrentExperience -= ExperienceToNextLevel;
		PlayerLevel += 1;
		AvailableUpgradePoints += 1;
		ExperienceToNextLevel = FMath::Max(BaseExperienceToNextLevel, ExperienceToNextLevel + 50);
	}

	SaveCharacterDataToJson();
}

bool AGameplayCharacterBase::SellOre(const int32 OreAmount, const int32 GoldPerOre)
{
	if (OreAmount <= 0 || GoldPerOre <= 0 || CollectedOreResources < OreAmount)
	{
		return false;
	}

	CollectedOreResources -= OreAmount;
	CollectedGold += OreAmount * GoldPerOre;
	UpdateResourceCounter();
	SaveCharacterDataToJson();
	return true;
}

bool AGameplayCharacterBase::BuyStaminaPotion(const int32 GoldCost, const float RestoreAmount)
{
	if (GoldCost <= 0 || RestoreAmount <= 0.0f || CollectedGold < GoldCost)
	{
		return false;
	}

	CollectedGold -= GoldCost;
	Stamina = FMath::Clamp(Stamina + RestoreAmount, 0.0f, MaxStamina);
	CurrentStamina = Stamina;
	UpdateStaminaBar();
	SaveCharacterDataToJson();
	return true;
}

bool AGameplayCharacterBase::SpendUpgradePoint(const EPlayerUpgradeType UpgradeType)
{
	if (AvailableUpgradePoints <= 0)
	{
		return false;
	}

	switch (UpgradeType)
	{
	case EPlayerUpgradeType::MaxStamina:
		MaxStamina += MaxStaminaUpgradeAmount;
		Stamina = MaxStamina;
		CurrentStamina = Stamina;
		UpdateStaminaBar();
		break;
	case EPlayerUpgradeType::OreDamage:
		OreDamage += OreDamageUpgradeAmount;
		break;
	case EPlayerUpgradeType::MoveSpeed:
		WalkSpeed += MoveSpeedUpgradeAmount;
		SprintSpeed += MoveSpeedUpgradeAmount;
		if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
		{
			MovementComponent->MaxWalkSpeed = bIsSprint ? SprintSpeed : WalkSpeed;
		}
		break;
	default:
		return false;
	}

	AvailableUpgradePoints -= 1;
	SaveCharacterDataToJson();
	return true;
}

int32 AGameplayCharacterBase::GetCollectedGold() const
{
	return CollectedGold;
}

int32 AGameplayCharacterBase::GetPlayerLevel() const
{
	return PlayerLevel;
}

int32 AGameplayCharacterBase::GetCurrentExperienceAmount() const
{
	return CurrentExperience;
}

int32 AGameplayCharacterBase::GetExperienceToNextLevelAmount() const
{
	return ExperienceToNextLevel;
}

int32 AGameplayCharacterBase::GetAvailableUpgradePoints() const
{
	return AvailableUpgradePoints;
}

float AGameplayCharacterBase::GetOreDamageAmount() const
{
	return OreDamage;
}

void AGameplayCharacterBase::DecreaseStamina()
{
	CurrentStamina = FMath::Clamp(Stamina - MinusStamina, 0.0f, MaxStamina);
	Stamina = CurrentStamina;
	UpdateStaminaBar();
}

void AGameplayCharacterBase::IncreaseStamina()
{
	if (!bIsSprint)
	{
		CurrentStamina = FMath::Clamp(Stamina + PlusStamina, 0.0f, MaxStamina);
		Stamina = CurrentStamina;
		UpdateStaminaBar();
	}
}

void AGameplayCharacterBase::AddOreResources(const int32 ResourceAmount)
{
	if (ResourceAmount <= 0)
	{
		return;
	}

	CollectedOreResources += ResourceAmount;
	UpdateResourceCounter();
	SaveCharacterDataToJson();
}

void AGameplayCharacterBase::TriggerAttackHit()
{
	GetWorldTimerManager().ClearTimer(AttackHitTimerHandle);
	TryDamageOre();
}

void AGameplayCharacterBase::FinishAttackState()
{
	GetWorldTimerManager().ClearTimer(AttackHitTimerHandle);
	bIsAttacking = false;

	if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
	{
		MovementComponent->SetMovementMode(MOVE_Walking);
		MovementComponent->MaxWalkSpeed = bIsSprint ? SprintSpeed : WalkSpeed;
	}
}

void AGameplayCharacterBase::UpdateResourceCounter() const
{
	if (!ResourceCounterWidget)
	{
		return;
	}

	ResourceCounterWidget->SetResourceAmount(CollectedOreResources);
}

void AGameplayCharacterBase::UpdateStaminaBar() const
{
	if (!StaminaBarWidget)
	{
		return;
	}

	StaminaBarWidget->SetStaminaValues(Stamina, MaxStamina);
}

void AGameplayCharacterBase::TryDamageOre()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController)
	{
		return;
	}

	FVector TraceStart;
	FRotator TraceRotation;
	PlayerController->GetPlayerViewPoint(TraceStart, TraceRotation);

	const FVector TraceEnd = TraceStart + (TraceRotation.Vector() * AttackRange);
	FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(OreAttackTrace), false, this);
	QueryParams.AddIgnoredActor(this);
	const FCollisionShape AttackShape = FCollisionShape::MakeSphere(65.0f);

	FHitResult HitResult;
	if (!GetWorld()->SweepSingleByChannel(HitResult, TraceStart, TraceEnd, FQuat::Identity, ECC_Visibility, AttackShape, QueryParams))
	{
		return;
	}

	if (AOreStoneBase* OreStone = Cast<AOreStoneBase>(HitResult.GetActor()))
	{
		const bool bWillBreak = OreStone->IsOreAvailable() && OreStone->GetCurrentHealth() <= OreDamage;
		OreStone->ApplyDamageToOre(OreDamage);
		if (bWillBreak && !OreStone->IsOreAvailable())
		{
			AddOreResources(OreStone->GetOreResourceReward());
			AddExperience(OreStone->GetOreExperienceReward());
		}
		return;
	}

	if (UPrimitiveComponent* HitComponent = HitResult.GetComponent())
	{
		if (AOreStoneBase* OreStoneOwner = Cast<AOreStoneBase>(HitComponent->GetOwner()))
		{
			const bool bWillBreak = OreStoneOwner->IsOreAvailable() && OreStoneOwner->GetCurrentHealth() <= OreDamage;
			OreStoneOwner->ApplyDamageToOre(OreDamage);
			if (bWillBreak && !OreStoneOwner->IsOreAvailable())
			{
				AddOreResources(OreStoneOwner->GetOreResourceReward());
				AddExperience(OreStoneOwner->GetOreExperienceReward());
			}
		}
	}
}

void AGameplayCharacterBase::LoadCharacterDataFromJson()
{
	FMyProjectCharacterSaveData SaveData;
	if (!FMyProjectJsonSaveUtils::LoadCharacterData(SaveData))
	{
		SaveCharacterDataToJson();
		return;
	}

	MaxStamina = FMath::Max(1.0f, SaveData.MaxStamina);
	Stamina = FMath::Clamp(SaveData.CurrentStamina, 0.0f, MaxStamina);
	CurrentStamina = Stamina;
	CollectedOreResources = FMath::Max(0, SaveData.CollectedOreResources);
	CollectedGold = FMath::Max(0, SaveData.CollectedGold);
	PlayerLevel = FMath::Max(1, SaveData.PlayerLevel);
	CurrentExperience = FMath::Max(0, SaveData.CurrentExperience);
	ExperienceToNextLevel = FMath::Max(BaseExperienceToNextLevel, SaveData.ExperienceToNextLevel);
	AvailableUpgradePoints = FMath::Max(0, SaveData.AvailableUpgradePoints);
	OreDamage = FMath::Max(0.0f, SaveData.OreDamage);
	WalkSpeed = FMath::Max(1.0f, SaveData.WalkSpeed);
	SprintSpeed = FMath::Max(WalkSpeed, SaveData.SprintSpeed);

	if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
	{
		MovementComponent->MaxWalkSpeed = bIsSprint ? SprintSpeed : WalkSpeed;
	}
}

void AGameplayCharacterBase::SaveCharacterDataToJson() const
{
	FMyProjectCharacterSaveData SaveData;
	SaveData.MaxStamina = MaxStamina;
	SaveData.CurrentStamina = FMath::Clamp(Stamina, 0.0f, MaxStamina);
	SaveData.CollectedOreResources = CollectedOreResources;
	SaveData.CollectedGold = CollectedGold;
	SaveData.PlayerLevel = PlayerLevel;
	SaveData.CurrentExperience = CurrentExperience;
	SaveData.ExperienceToNextLevel = ExperienceToNextLevel;
	SaveData.AvailableUpgradePoints = AvailableUpgradePoints;
	SaveData.OreDamage = OreDamage;
	SaveData.WalkSpeed = WalkSpeed;
	SaveData.SprintSpeed = SprintSpeed;
	FMyProjectJsonSaveUtils::SaveCharacterData(SaveData);
}
