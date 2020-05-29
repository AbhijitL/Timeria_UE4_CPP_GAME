// Copyright to Leihaorambam Abhijit Singh abhijitl.github.io or milkandegg.studios


#include "HeartPU.h"
#include "Components/StaticMeshComponent.h"
#include "Character\MainCharacter.h"
#include "Components\SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Sound/SoundCue.h"

// Sets default values
AHeartPU::AHeartPU()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = Collision;
	HeartMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HeartMesh"));
	HeartMesh->SetupAttachment(GetRootComponent());
	Rotate = true;
	Heart = 1;
	Speed = 60;
}

// Called when the game starts or when spawned
void AHeartPU::BeginPlay()
{
	Super::BeginPlay();
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AHeartPU::OnOverlapBegin);
}

// Called every frame
void AHeartPU::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (HeartMesh) {
		if (Rotate) {
			FRotator Rotation = GetActorRotation();
			Rotation.Yaw += DeltaTime * Speed;
			SetActorRotation(Rotation);
		}
	}
}

void AHeartPU::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) {
	if (OtherActor) {
		AMainCharacter* Main = Cast<AMainCharacter>(OtherActor);
		if (Main) {
			Main->IncrementHeart(Heart);
			if (OverlapParticle) {
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OverlapParticle, GetActorLocation(),FRotator(0.f),true);				
			}
			if (OverlapSound) {
				UGameplayStatics::PlaySound2D(GetWorld(), OverlapSound);
			}
		}
		Destroy();
	}
}




