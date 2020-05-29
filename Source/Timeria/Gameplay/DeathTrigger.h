// Copyright to Leihaorambam Abhijit Singh abhijitl.github.io or milkandegg.studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DeathTrigger.generated.h"

UCLASS()
class TIMERIA_API ADeathTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADeathTrigger();

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "TriggerBox", Meta = (MakeEditWidget = "true"))
	class UBoxComponent* TriggerBox;

	class UBillboardComponent* BillBoard;

	int32 Damage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
