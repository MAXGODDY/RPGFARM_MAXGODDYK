#pragma once

#include "Animation/AnimMontage.h"
#include "CoreMinimal.h"
#include "GameplayCharacterBase.h"
#include "ThifCatcherSandboxBase.generated.h"

UCLASS()
class MYPROJECT_API AThifCatcherSandboxBase : public AGameplayCharacterBase
{
	GENERATED_BODY()

public:
	AThifCatcherSandboxBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JumpAnimation")
	TObjectPtr<UAnimMontage> JumpAnimation;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForwardBackward(float Value);
	void MoveRightLeft(float Value);

	void Jump();
	void StopJump();

	void Sprint();
	void StopSprint();
};
