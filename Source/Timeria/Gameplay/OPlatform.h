// Copyright to Leihaorambam Abhijit Singh abhijitl.github.io or milkandegg.studios

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OPlatform.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TIMERIA_API UOPlatform : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOPlatform();

	UPROPERTY(EditAnyWhere)
	FVector StartPoint;

	UPROPERTY(EditAnyWhere , Meta = (MakeEditWidget = "true"))
	FVector EndPoint;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly , Category="Platform")
	float InterpSpeed;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Platform")
	float InterpTime;

	FTimerHandle InterpTimer;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Platform")
	bool bInterping;

	float Distance;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void StartInterping();

	void SwapVectors(FVector& VecOne, FVector& VecTwo);
};
