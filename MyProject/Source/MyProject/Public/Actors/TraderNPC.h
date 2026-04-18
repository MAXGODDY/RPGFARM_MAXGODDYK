#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TraderNPC.generated.h"

UCLASS()
class MYPROJECT_API ATraderNPC : public AActor
{
	GENERATED_BODY()

public:
	ATraderNPC();

	UFUNCTION(BlueprintPure, Category = "Trader")
	FText GetTraderName() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trader")
	TObjectPtr<class USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trader")
	TObjectPtr<class UStaticMeshComponent> TraderMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trader")
	TObjectPtr<class USphereComponent> InteractionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Trader")
	FText TraderName;

private:
	UFUNCTION()
	void HandleInteractionSphereBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void HandleInteractionSphereEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
};
