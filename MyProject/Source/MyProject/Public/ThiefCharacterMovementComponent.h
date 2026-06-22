#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ThiefCharacterMovementComponent.generated.h"

/**
 * Movement component that keeps the C++ stamina system authoritative over sprint
 * speed. Even if a Blueprint sets MaxWalkSpeed directly (for example through an
 * Enhanced Input sprint action), GetMaxSpeed() hard-caps the speed to the walk
 * value while the owning character has its stamina exhausted.
 */
UCLASS()
class MYPROJECT_API UThiefCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	virtual float GetMaxSpeed() const override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
