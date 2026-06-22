#include "ThiefCharacterMovementComponent.h"

#include "GameplayCharacterBase.h"

float UThiefCharacterMovementComponent::GetMaxSpeed() const
{
	const float BaseMaxSpeed = Super::GetMaxSpeed();

	// When stamina is exhausted the character may not exceed its walk speed, no
	// matter what value the Blueprint pushed into MaxWalkSpeed for sprinting.
	if (const AGameplayCharacterBase* OwningCharacter = Cast<AGameplayCharacterBase>(GetCharacterOwner()))
	{
		if (OwningCharacter->IsStaminaExhausted())
		{
			return FMath::Min(BaseMaxSpeed, OwningCharacter->WalkSpeed);
		}
	}

	return BaseMaxSpeed;
}

void UThiefCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// Blueprints (Enhanced Input sprint) push MaxWalkSpeed up to the sprint value and
	// the Game Animation Sample anim graph derives the Walk/Run/Sprint gait from it.
	// Clamp the property down while exhausted so the animation matches the real,
	// capped locomotion instead of looping the sprint pose in place.
	if (const AGameplayCharacterBase* OwningCharacter = Cast<AGameplayCharacterBase>(GetCharacterOwner()))
	{
		if (OwningCharacter->IsStaminaExhausted() && MaxWalkSpeed > OwningCharacter->WalkSpeed)
		{
			MaxWalkSpeed = OwningCharacter->WalkSpeed;
		}
	}

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
