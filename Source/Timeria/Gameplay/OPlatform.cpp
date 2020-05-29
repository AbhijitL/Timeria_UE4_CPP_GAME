// Copyright to Leihaorambam Abhijit Singh abhijitl.github.io or milkandegg.studios


#include "OPlatform.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOPlatform::UOPlatform()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	StartPoint = FVector(0.f);
	EndPoint = FVector(600.0f,0.0f,0.0f);
	bInterping = false;
	InterpSpeed = 4.0f;
	InterpTime = 0.1f;
	// ...
}


// Called when the game starts
void UOPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartPoint = GetOwner()->GetActorLocation();
	EndPoint += StartPoint;
	bInterping = false;
	GetWorld()->GetTimerManager().SetTimer(InterpTimer, this, &UOPlatform::StartInterping, InterpTime);
	Distance = (EndPoint - StartPoint).Size();
}


// Called every frame
void UOPlatform::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bInterping) {
		FVector CurrentLocation = GetOwner()->GetActorLocation();
		FVector Interp = FMath::VInterpTo(CurrentLocation, EndPoint, DeltaTime, InterpSpeed);
		GetOwner()->SetActorLocation(Interp);
		float DistanceTravelled = (GetOwner()->GetActorLocation() - StartPoint).Size();
		if (Distance - DistanceTravelled <= 1.f) {
			StartInterping();
			GetWorld()->GetTimerManager().SetTimer(InterpTimer, this, &UOPlatform::StartInterping, InterpTime);
			SwapVectors(StartPoint, EndPoint);
		}
	}
}

void UOPlatform::StartInterping() {
	bInterping = !bInterping;
}

void UOPlatform::SwapVectors(FVector& VecOne, FVector& VecTwo) {
	FVector Temp = VecOne;
	VecOne = VecTwo;
	VecTwo = Temp;
}