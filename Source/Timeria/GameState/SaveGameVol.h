// Copyright to Leihaorambam Abhijit Singh abhijitl.github.io or milkandegg.studios

// THis is a level Transition Volume Not Save Game i dont want to delete and 
//Compile again it will waste time

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SaveGameVol.generated.h"

UCLASS()
class TIMERIA_API ASaveGameVol : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASaveGameVol();

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Transition")
	class UBoxComponent* TransitionVolume;

	class UBillboardComponent* BillBoard;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Transition")
	FName TransitionLevelName;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

};
