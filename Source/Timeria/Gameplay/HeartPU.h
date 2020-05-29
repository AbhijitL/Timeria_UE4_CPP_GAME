// Copyright to Leihaorambam Abhijit Singh abhijitl.github.io or milkandegg.studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HeartPU.generated.h"

UCLASS()
class TIMERIA_API AHeartPU : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHeartPU();

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Heart")
	class USphereComponent* Collision;

	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly,Category="Heart")
	class UStaticMeshComponent* HeartMesh;

	UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category="Heart")
	class USoundCue* OverlapSound;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Heart")
	class UParticleSystem* OverlapParticle;

	int32 Heart;

	UPROPERTY(EditAnyWhere, Category = "Heart")
	bool Rotate;

	UPROPERTY(EditAnyWhere, Category = "Heart")
	float Speed;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);


};
