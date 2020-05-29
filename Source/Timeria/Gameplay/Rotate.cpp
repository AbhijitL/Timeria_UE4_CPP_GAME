// Copyright to Leihaorambam Abhijit Singh abhijitl.github.io or milkandegg.studios


#include "Rotate.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
URotate::URotate()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SpeedYaw = 60.0f;
	SpeedPitch = 0.0f;
	SpeedRoll = 0.0f;
	// ...
}


// Called when the game starts
void URotate::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}


// Called every frame
void URotate::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FRotator Rotation = GetOwner()->GetActorRotation();
	Rotation.Yaw += DeltaTime * SpeedYaw;
	Rotation.Pitch += DeltaTime * SpeedPitch;
	Rotation.Roll += DeltaTime * SpeedRoll;
	GetOwner()->SetActorRotation(Rotation);
	// ...
}

