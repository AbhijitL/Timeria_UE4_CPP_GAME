// Copyright to Leihaorambam Abhijit Singh abhijitl.github.io or milkandegg.studios

// THis is a level Transition Volume Not Save Game i dont want to delete and 
//Compile again it will waste time

#include "SaveGameVol.h"
#include "Components/BoxComponent.h"
#include "Components/BillboardComponent.h"
#include "Character/MainCharacter.h"

// Sets default values
ASaveGameVol::ASaveGameVol()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TransitionVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TransitionVolume"));
	RootComponent = TransitionVolume;
	BillBoard = CreateDefaultSubobject<UBillboardComponent>(TEXT("BillBoard"));
	BillBoard->SetupAttachment(GetRootComponent());
	TransitionLevelName = "Prototype";
}


// Called when the game starts or when spawned
void ASaveGameVol::BeginPlay()
{
	Super::BeginPlay();
	TransitionVolume->OnComponentBeginOverlap.AddDynamic(this, &ASaveGameVol::OnOverlapBegin);
}

// Called every frame
void ASaveGameVol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASaveGameVol::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
	if (OtherActor) {
		AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);
		if (Main) {
			Main->SwitchLevel(TransitionLevelName);
		}
	}
}
