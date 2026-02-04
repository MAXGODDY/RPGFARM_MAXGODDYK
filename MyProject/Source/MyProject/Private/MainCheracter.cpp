

#include "MainCheracter.h" // Include the header file for the AMainCheracter class
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"


AMainCheracter::AMainCheracter()
{

	PrimaryActorTick.bCanEverTick = false;


	ChacterStamina = 100.f; // Initialize character stamina to 100

	pIsTired = false; // Initialize tired state to false

}

float AMainCheracter::GetStaminaPercent()
{
	return ChacterStamina;
}

float AMainCheracter::AddStamina()
{
	return 0.0f;
}

float AMainCheracter::DecreaseStamina()
{
	return 0.0f;
}

bool AMainCheracter::StaminaIsZero()
{
	if(ChacterStamina <= 0)
	{
		pIsTired = true;

		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision); // Disable collision for the character's capsule component when stamina is zero, effectively making the character unable to interact with the environment
		
	}

	UGameplayStatics::SpawnSoundAtLocation(this, TiredSound, GetActorLocation()); // Play the tired sound at the character's location


	return pIsTired;
}



