
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
		
};
