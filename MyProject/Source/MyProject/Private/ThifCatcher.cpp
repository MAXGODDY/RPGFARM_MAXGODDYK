// Fill out your copyright notice in the Description page of Project Settings.


#include "ThifCatcher.h"


AThifCatcher::AThifCatcher() : Super()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 500.f;


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	Camera->SetupAttachment(SpringArm);


	SpringArm->bUsePawnControlRotation = true;
	Camera->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
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

}

void AThifCatcher::MoveForwardBackward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AThifCatcher::MoveRightLeft(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AThifCatcher::Jump()
{
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

	bIsSprint = true;
	GetCharacterMovement()->MaxWalkSpeed = 800.0f;

	DecreaseStamina();
}


void AThifCatcher::StopSprint()
{
	bIsSpatiallyLoaded = false;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	IncreaseStamina();
}

void AThifCatcher::DecreaseStamina()
{
	CurrentStamina = Stamina - MinusStamina;
	Stamina = CurrentStamina;

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Stamina: %f"), Stamina));
}

void AThifCatcher::IncreaseStamina()
{
	if (bIsSprint == false)
	{
		CurrentStamina = Stamina + PlusStamina;
		Stamina = CurrentStamina;

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Stamina: %f"), Stamina));
	}

}


void AThifCatcher::Tick(float DeltaTime)
{
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