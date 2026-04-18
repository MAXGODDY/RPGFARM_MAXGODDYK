#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimMontage.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameplayCharacterBase.h"
#include "ThifCatcher.generated.h"

UCLASS()
class MYPROJECT_API AThifCatcher : public AGameplayCharacterBase
{
	GENERATED_BODY()

public:
	AThifCatcher();

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JampAnimation")
	UAnimMontage* JumpAnimation;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForwardBackward(float Value);
	void MoveRightLeft(float Value);

	void Jump();
	void StopJump();

	void Sprint();
	void StopSprint();
};
