// Fill out your copyright notice in the Description page of Project Settings.


#include "ThifCatcher.h"
#include "Actors/OreStoneBase.h"
#include "Animation/AnimSequenceBase.h"
#include "Components/InputComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "ThiefPlayerController.h"
#include "UI/ResourceCounterWidget.h"
#include "UI/StaminaBarWidget.h"

AThifCatcher::AThifCatcher() : Super()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 420.0f;
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 70.0f));
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 12.0f;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraRotationLagSpeed = 14.0f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bDoCollisionTest = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = false;


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;
	Camera->SetRelativeRotation(FRotator(-10.0f, 0.0f, 0.0f));

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 650.0f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1800.0f;
	GetCharacterMovement()->MaxAcceleration = 2048.0f;

	WalkSpeed = 450.0f;
	SprintSpeed = 700.0f;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	bIsSprint = false;
	MaxStamina = 100.0f;
	Stamina = MaxStamina;
	CurrentStamina = Stamina;
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

	static ConstructorHelpers::FObjectFinder<UAnimSequenceBase> DefaultAttackAnimationFinder(
		TEXT("/Game/MainPlayer/Animations/AM_Pickaxe_Attack.AM_Pickaxe_Attack"));
	if (DefaultAttackAnimationFinder.Succeeded())
	{
		AttackTimingAnimation = DefaultAttackAnimationFinder.Object;
		AttackStateDuration = FMath::Max(AttackTimingAnimation->GetPlayLength(), 0.0f);
	}
	else
	{
		AttackTimingAnimation = nullptr;
	}
}

void AThifCatcher::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(true);

	if (ResourceCounterWidget)
	{
		ResourceCounterWidget->RemoveFromParent();
		ResourceCounterWidget = nullptr;
	}

	if (StaminaBarWidget)
	{
		StaminaBarWidget->RemoveFromParent();
		StaminaBarWidget = nullptr;
	}
}

void AThifCatcher::SetupPlayerInputComponent(UInputComponent* MyPlayerInput)
{
	Super::SetupPlayerInputComponent(MyPlayerInput);


	MyPlayerInput->BindAxis("MoveForwardBackward", this, &AThifCatcher::MoveForwardBackward);
	MyPlayerInput->BindAxis("MoveRightLeft", this, &AThifCatcher::MoveRightLeft);


	MyPlayerInput->BindAxis("Turn", this, &AThifCatcher::AddControllerYawInput);
	MyPlayerInput->BindAxis("lookUpDown", this, &AThifCatcher::AddControllerPitchInput);


	MyPlayerInput->BindAction("Jump", IE_Pressed, this, &AThifCatcher::Jump);
	MyPlayerInput->BindAction("Jump", IE_Released, this, &AThifCatcher::StopJump);

	MyPlayerInput->BindAction("Sprint", IE_Pressed, this, &AThifCatcher::Sprint);
	MyPlayerInput->BindAction("Sprint", IE_Released, this, &AThifCatcher::StopSprint);
	MyPlayerInput->BindAction("Attack", IE_Pressed, this, &AThifCatcher::Attack);
}

void AThifCatcher::MoveForwardBackward(float Value)
{
	if (bIsAttacking || !Controller || FMath::IsNearlyZero(Value))
	{
		return;
	}

	const FRotator ControlRotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.0f, ControlRotation.Yaw, 0.0f);
	FVector Direction = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AThifCatcher::MoveRightLeft(float Value)
{
	if (bIsAttacking || !Controller || FMath::IsNearlyZero(Value))
	{
		return;
	}

	const FRotator ControlRotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.0f, ControlRotation.Yaw, 0.0f);
	FVector Direction = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AThifCatcher::Jump()
{
	if (bIsAttacking)
	{
		return;
	}

	bPressedJump = true;

	if (JumpAnimation)
	{
		PlayAnimMontage(JumpAnimation, 1.0, NAME_None);
	}
}

void AThifCatcher::StopJump()
{
	bPressedJump = false;
}

							//====================================Sprint=======================
void AThifCatcher::Sprint()
{
	if (bIsAttacking)
	{
		return;
	}

	if (FMath::IsNearlyZero(Stamina))
	{
		return;
	}

	bIsSprint = true;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}


void AThifCatcher::StopSprint()
{
	bIsSprint = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AThifCatcher::Attack()
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
	StopSprint();
	StopJump();

	const float EffectiveAttackDuration = AttackTimingAnimation
		? FMath::Max(AttackTimingAnimation->GetPlayLength(), 0.0f)
		: AttackStateDuration;
	const float EffectiveAttackCooldown = FMath::Max(AttackCooldown, EffectiveAttackDuration);

	if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
	{
		MovementComponent->StopMovementImmediately();
		MovementComponent->DisableMovement();
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
				&AThifCatcher::TriggerAttackHit,
				FMath::Min(EffectiveHitDelay, EffectiveAttackDuration),
				false);
		}

		GetWorldTimerManager().SetTimer(
			AttackStateTimerHandle,
			this,
			&AThifCatcher::FinishAttackState,
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

void AThifCatcher::DecreaseStamina()
{
	CurrentStamina = FMath::Clamp(Stamina - MinusStamina, 0.0f, MaxStamina);
	Stamina = CurrentStamina;
	UpdateStaminaBar();
}

void AThifCatcher::IncreaseStamina()
{
	if (bIsSprint == false)
	{
		CurrentStamina = FMath::Clamp(Stamina + PlusStamina, 0.0f, MaxStamina);
		Stamina = CurrentStamina;
		UpdateStaminaBar();
	}

}


void AThifCatcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsSprint == true && Stamina != 0.f)
	{
		DecreaseStamina();
	}
	else
	{
		if (bIsSprint == false && Stamina != 100.f)
		{
			IncreaseStamina();
		}
	}

	if(FMath::IsNearlyZero(Stamina))
	{
		StopSprint();
	}
}

void AThifCatcher::AddOreResources(int32 ResourceAmount)
{
	if (ResourceAmount <= 0)
	{
		return;
	}

	CollectedOreResources += ResourceAmount;
	UpdateResourceCounter();
}

void AThifCatcher::AddExperience(int32 ExperienceAmount)
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
}

bool AThifCatcher::SellOre(int32 OreAmount, int32 GoldPerOre)
{
	if (OreAmount <= 0 || GoldPerOre <= 0 || CollectedOreResources < OreAmount)
	{
		return false;
	}

	CollectedOreResources -= OreAmount;
	CollectedGold += OreAmount * GoldPerOre;
	UpdateResourceCounter();
	return true;
}

bool AThifCatcher::BuyStaminaPotion(int32 GoldCost, float RestoreAmount)
{
	if (GoldCost <= 0 || RestoreAmount <= 0.0f || CollectedGold < GoldCost)
	{
		return false;
	}

	CollectedGold -= GoldCost;
	Stamina = FMath::Clamp(Stamina + RestoreAmount, 0.0f, MaxStamina);
	CurrentStamina = Stamina;
	UpdateStaminaBar();
	return true;
}

bool AThifCatcher::SpendUpgradePoint(EPlayerUpgradeType UpgradeType)
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
	return true;
}

int32 AThifCatcher::GetCollectedGold() const
{
	return CollectedGold;
}

int32 AThifCatcher::GetPlayerLevel() const
{
	return PlayerLevel;
}

int32 AThifCatcher::GetCurrentExperienceAmount() const
{
	return CurrentExperience;
}

int32 AThifCatcher::GetExperienceToNextLevelAmount() const
{
	return ExperienceToNextLevel;
}

int32 AThifCatcher::GetAvailableUpgradePoints() const
{
	return AvailableUpgradePoints;
}

float AThifCatcher::GetOreDamageAmount() const
{
	return OreDamage;
}

void AThifCatcher::FinishAttackState()
{
	GetWorldTimerManager().ClearTimer(AttackHitTimerHandle);
	bIsAttacking = false;

	if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
	{
		MovementComponent->SetMovementMode(MOVE_Walking);
		MovementComponent->MaxWalkSpeed = bIsSprint ? SprintSpeed : WalkSpeed;
	}
}

void AThifCatcher::TriggerAttackHit()
{
	GetWorldTimerManager().ClearTimer(AttackHitTimerHandle);
	TryDamageOre();
}

void AThifCatcher::InitializeResourceCounter()
{
	// HUD now renders resources directly through APlayerGameHUD.
}

void AThifCatcher::InitializeStaminaBar()
{
	// HUD now renders stamina directly through APlayerGameHUD.
}

void AThifCatcher::UpdateHudLayout() const
{
	// HUD layout is handled by APlayerGameHUD.
}

void AThifCatcher::UpdateResourceCounter() const
{
	if (!ResourceCounterWidget)
	{
		return;
	}

	ResourceCounterWidget->SetResourceAmount(CollectedOreResources);
}

void AThifCatcher::UpdateStaminaBar() const
{
	if (!StaminaBarWidget)
	{
		return;
	}

	StaminaBarWidget->SetStaminaValues(Stamina, MaxStamina);
}

void AThifCatcher::TryDamageOre()
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

