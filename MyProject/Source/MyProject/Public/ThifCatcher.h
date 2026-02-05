
#pragma once

#include "CoreMinimal.h"
#include "MainCheracter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "ThifCatcher.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AThifCatcher : public AMainCheracter
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


	virtual void SetupPlayerInputComponent(class UInputComponent* MyPlayerInput) override; //Подключаем базовую логику движка для инпута

	void MoveForwardBackward(float Value);

	void MoveRightLeft(float Value);

	void Jump();
	void StopJump();
		
};
