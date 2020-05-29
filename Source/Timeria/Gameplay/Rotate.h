// Copyright to Leihaorambam Abhijit Singh abhijitl.github.io or milkandegg.studios

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Rotate.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TIMERIA_API URotate : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URotate();

	UPROPERTY(EditAnyWhere,Category="Speed")
	float SpeedYaw;

	UPROPERTY(EditAnyWhere, Category = "Speed")
	float SpeedPitch;

	UPROPERTY(EditAnyWhere, Category = "Speed")
	float SpeedRoll;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
