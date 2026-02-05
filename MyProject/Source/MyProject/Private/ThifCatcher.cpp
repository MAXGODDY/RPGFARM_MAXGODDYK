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
}

void AThifCatcher::StopJump()
{
	bPressedJump = false;
}
