
#pragma once

#include "CoreMinimal.h"
#include "MainCheracter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/UnrealMathUtility.h"
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

	// ======================================== SPRINT=============================

	void Sprint();
	void StopSprint();

	bool bIsSprint;

	UPROPERTY(EditDefaultsOnly, Category = "Stamina")
	float CurrentStamina;

	UPROPERTY(EditDefaultsOnly, Category = "Stamina")
	float MinusStamina = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Stamina")
	float PlusStamina = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Stamina", meta = (ClampMin = "0", ClampMax = "100"))
	float Stamina = 100.0f;

	void DecreaseStamina();
	void IncreaseStamina();

	virtual void Tick(float DeltaTime) override;
		
};
