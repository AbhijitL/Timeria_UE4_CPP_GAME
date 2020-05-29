// Copyright to Leihaorambam Abhijit Singh abhijitl.github.io or milkandegg.studios


#include "DeathTrigger.h"
#include "Components/BoxComponent.h"
#include "Components/BillboardComponent.h"
#include "Character/MainCharacter.h"

// Sets default values
ADeathTrigger::ADeathTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;
	BillBoard = CreateDefaultSubobject<UBillboardComponent>(TEXT("BillBoard"));
	BillBoard->SetupAttachment(GetRootComponent());
	Damage = 1;
}

// Called when the game starts or when spawned
void ADeathTrigger::BeginPlay()
{
	Super::BeginPlay();
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ADeathTrigger::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ADeathTrigger::OnOverlapEnd);
}

// Called every frame
void ADeathTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADeathTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {

	if (OtherActor) {
		AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);
		if (Main) {
			Main->DecrementHeart(Damage);
			//Main->SaveGameHeart();
		}
	}
}

void ADeathTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	if (OtherActor) {
		AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);
		if (Main) {
			Main->LoadGame(true);
		}
	}
}