// Copyright to Leihaorambam Abhijit Singh abhijitl.github.io or milkandegg.studios


#include "SavePointVol.h"
#include "Components/BoxComponent.h"
#include "Components/BillboardComponent.h"
#include "Character/MainCharacter.h"

// Sets default values
ASavePointVol::ASavePointVol()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SavePointVol = CreateDefaultSubobject<UBoxComponent>(TEXT("SavePoint"));
	RootComponent = SavePointVol;
	BillBoard = CreateDefaultSubobject<UBillboardComponent>(TEXT("BillBoard"));
	BillBoard->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ASavePointVol::BeginPlay()
{
	Super::BeginPlay();
	SavePointVol->OnComponentBeginOverlap.AddDynamic(this, &ASavePointVol::OnOverlapBegin);
}

// Called every frame
void ASavePointVol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASavePointVol::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
	
	if (OtherActor) {
		AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);
		if (Main) {
			Main->SaveGame();
		}
	}

}
