#include "Actors/TraderNPC.h"

#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ThiefPlayerController.h"
#include "GameplayCharacterBase.h"
#include "UObject/ConstructorHelpers.h"

ATraderNPC::ATraderNPC()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	TraderMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TraderMesh"));
	TraderMesh->SetupAttachment(SceneRoot);
	TraderMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TraderMesh->SetRelativeScale3D(FVector(0.9f, 0.9f, 2.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMeshFinder(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (DefaultMeshFinder.Succeeded())
	{
		TraderMesh->SetStaticMesh(DefaultMeshFinder.Object);
	}

	InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
	InteractionSphere->SetupAttachment(SceneRoot);
	InteractionSphere->SetSphereRadius(220.0f);
	InteractionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	TraderName = FText::FromString(TEXT("Trader"));
}

void ATraderNPC::BeginPlay()
{
	Super::BeginPlay();

	InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &ATraderNPC::HandleInteractionSphereBeginOverlap);
	InteractionSphere->OnComponentEndOverlap.AddDynamic(this, &ATraderNPC::HandleInteractionSphereEndOverlap);
}

FText ATraderNPC::GetTraderName() const
{
	return TraderName;
}

void ATraderNPC::HandleInteractionSphereBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (AGameplayCharacterBase* PlayerCharacter = Cast<AGameplayCharacterBase>(OtherActor))
	{
		if (AThiefPlayerController* ThiefController = Cast<AThiefPlayerController>(PlayerCharacter->GetController()))
		{
			ThiefController->SetNearbyTrader(this);
		}
	}
}

void ATraderNPC::HandleInteractionSphereEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (AGameplayCharacterBase* PlayerCharacter = Cast<AGameplayCharacterBase>(OtherActor))
	{
		if (AThiefPlayerController* ThiefController = Cast<AThiefPlayerController>(PlayerCharacter->GetController()))
		{
			ThiefController->ClearNearbyTrader(this);
		}
	}
}
