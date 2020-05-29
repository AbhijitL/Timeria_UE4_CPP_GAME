// Copyright to Leihaorambam Abhijit Singh abhijitl.github.io or milkandegg.studios


#include "MainCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "TimerManager.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/PostProcessVolume.h"
#include "Sound/SoundCue.h"
#include "GameState/GameSave.h"
#include "MainPlayerController.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 600.f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	TurnRate = 65.f;
	LookUpRate = 65.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 450;
	GetCharacterMovement()->AirControl = 0.0;
	bSpaceKeyDown = false;
	
	//Player Stats
	MaxStamina = 150.f;
	Stamina = 120.f;
	Heart = 3;
	MaxHeart = 5;
	StamindDrainRate = 25.f;
	MinSprintStamina = 50.0f;
	RunningSpeed = 650.f;
	SprintingSpeed = 950.f;
	bShiftKeyDown = false;
	MovementStatus = EMovementStatus::EMS_Normal;
	StaminaStatus = EStaminaStatus::ESS_Normal;
	bESCDown = false;

	bSlowMode = false;
	GSlowMoSpeed = 0.3;
	SelfSlowMoSpeed = GSlowMoSpeed * 10;
	bAttacking = false;

	MaggicTimeEffect = 5.0f;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	MainPlayerController = Cast<AMainPlayerController>(GetController());

	PlayerInitialLocation = GetActorLocation();
	PlayerInitialRotation = GetActorRotation();
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float DeltaStamina = StamindDrainRate * DeltaTime;
	FVector Speed = GetVelocity();
	FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.0f);
	float MovementSpeed = LateralSpeed.Size();
	switch (StaminaStatus)
	{
	case EStaminaStatus::ESS_Normal:
		if (bShiftKeyDown) {
			if (Stamina - DeltaStamina <= MinSprintStamina) {
				SetStaminaStatus(EStaminaStatus::ESS_BelowMinimum);
				if (MovementSpeed == 0.0f) {
					if (Stamina + DeltaStamina >= MaxStamina) {
						Stamina = MaxStamina;
					}
					else if (Stamina + DeltaStamina <= MaxStamina) {
						Stamina += DeltaStamina;
					}
				}
				else {
					Stamina -= DeltaStamina;
				}
			}
			else {
				if (MovementSpeed == 0.0f) {
					if (Stamina + DeltaStamina >= MaxStamina) {
						Stamina = MaxStamina;
					}
					else if (Stamina + DeltaStamina <= MaxStamina) {
						Stamina += DeltaStamina;
					}
				}
				else {
					Stamina -= DeltaStamina;
				}
			}
			if (MovementSpeed == 0.0f) {
				SetMovementStatus(EMovementStatus::EMS_Normal);
			}
			else {
				SetMovementStatus(EMovementStatus::EMS_Sprinting);
			}
		}
		else {//if shifkey is up
			if (Stamina + DeltaStamina >= MaxStamina) {
				Stamina = MaxStamina;
			}
			else {
				Stamina += DeltaStamina;
			}
			SetMovementStatus(EMovementStatus::EMS_Normal);
		}
		break;
	case EStaminaStatus::ESS_BelowMinimum:
		if (bShiftKeyDown) {
			if (Stamina - DeltaStamina <= 0) {
				SetStaminaStatus(EStaminaStatus::ESS_Exhausted);
				Stamina = 0;
				SetMovementStatus(EMovementStatus::EMS_Normal);
			}
			else {
				if (MovementSpeed == 0.0f) {
					if (Stamina + DeltaStamina >= MaxStamina) {
						Stamina = MaxStamina;
					}
					else if (Stamina + DeltaStamina <= MaxStamina) {
						Stamina += DeltaStamina;
					}
				}
				else {
					Stamina -= DeltaStamina;
				}
				if (MovementSpeed == 0.0f) {
					SetMovementStatus(EMovementStatus::EMS_Normal);
				}
				else {
					SetMovementStatus(EMovementStatus::EMS_Sprinting);
				}
			}
		}
		else {//if shift key is up
			if (Stamina + DeltaStamina >= MinSprintStamina) {
				SetStaminaStatus(EStaminaStatus::ESS_Normal);
				Stamina += DeltaStamina;
			}
			else {
				Stamina += DeltaStamina;
			}
			SetMovementStatus(EMovementStatus::EMS_Normal);
		}
		break;
	case EStaminaStatus::ESS_Exhausted:
		if (bShiftKeyDown) {
			Stamina = 0.f;
		}
		else {// is shift key is up
			SetStaminaStatus(EStaminaStatus::ESS_ExhautedRecovering);
			Stamina += DeltaStamina;
		}
		SetMovementStatus(EMovementStatus::EMS_Normal);
		break;
	case EStaminaStatus::ESS_ExhautedRecovering:
		if (Stamina + DeltaStamina >= MinSprintStamina) {
			SetStaminaStatus(EStaminaStatus::ESS_Normal);
			Stamina += DeltaStamina;
		}
		else {
			Stamina += DeltaStamina;
		}
		SetMovementStatus(EMovementStatus::EMS_Normal);
		break;
	default:
		;
	}
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMainCharacter::StopJumping);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Sprint",IE_Pressed,this, &AMainCharacter::ShiftKeyDown);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMainCharacter::ShiftKeyUp);

	PlayerInputComponent->BindAction("LMB", IE_Pressed, this, &AMainCharacter::Magic);

	PlayerInputComponent->BindAction("ESC", IE_Pressed, this, &AMainCharacter::ESCDown);
	PlayerInputComponent->BindAction("ESC", IE_Released, this, &AMainCharacter::ESCUp);
}

void AMainCharacter::Jump() {
	bShiftKeyDown = true;
	Super::Jump();

}

void AMainCharacter::StopJumping() {
	bShiftKeyDown = false;
	Super::StopJumping();
}

void AMainCharacter::ShiftKeyDown() {
	bShiftKeyDown = true;
}

void AMainCharacter::ShiftKeyUp() {
	bShiftKeyDown = false;
}

void AMainCharacter::ESCDown() {
	bESCDown = true;
	if (MainPlayerController) {
		MainPlayerController->TooglePauseMenu();
	}
}
void AMainCharacter::ESCUp() {
	bESCDown = false;
}

void AMainCharacter::SetMovementStatus(EMovementStatus Status) {
	MovementStatus = Status;
	if (MovementStatus == EMovementStatus::EMS_Sprinting) {
		GetCharacterMovement()->MaxWalkSpeed = SprintingSpeed;
	}
	else {
		GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
	}
}

void AMainCharacter::MoveForward(float move) {
	if ((Controller != nullptr) && (move != 0.0f) && !bAttacking) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator RotationYaw(0.f, Rotation.Yaw, 0.f);
		const FVector Direction = FRotationMatrix(RotationYaw).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, move);
	}
}

void AMainCharacter::MoveRight(float move) {
	if ((Controller != nullptr) && (move != 0.0f) && !bAttacking) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator RotationYaw(0.f, Rotation.Yaw, 0.f);
		const FVector Direction = FRotationMatrix(RotationYaw).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, move);
	}
}
void AMainCharacter::LookUp(float Rate) {
	AddControllerPitchInput(Rate*LookUpRate*GetWorld()->GetDeltaSeconds());
}
void AMainCharacter::Turn(float Rate) {
	AddControllerYawInput(Rate*TurnRate*GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::Magic() {
	if ((bAttacking == false) && !bSlowMode && !(GetCharacterMovement()->IsFalling())) {
		bAttacking = true;
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance && CharMontage) {
			AnimInstance->Montage_Play(CharMontage, 1.0f);
			AnimInstance->Montage_JumpToSection(FName("Magic1"), CharMontage);
		}

	}
}
void AMainCharacter::MagicEnd() {
	bAttacking = false;
}


void AMainCharacter::SlowDown() {

	if (bSlowMode == false) {
		bSlowMode = true;
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), GSlowMoSpeed);
		CustomTimeDilation = SelfSlowMoSpeed;
		UE_LOG(LogTemp, Warning, TEXT("Slowed Down"));
		PPEffect(true);
		PlaySound(true);
		const USkeletalMeshSocket* MagicSocket = GetMesh()->GetSocketByName("MagicSocket");
		if (MagicSocket) {
			FVector SocketLocation = MagicSocket->GetSocketLocation(GetMesh());
			if (TimeWrapParticle) {
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TimeWrapParticle, SocketLocation, FRotator(0.f), true);
			}
		}
		if (Heart != 0) { 
			GetWorldTimerManager().SetTimer(MaggicTimeHandle, this, &AMainCharacter::UnSlowDown, MaggicTimeEffect);
		}

	}
	

}

void AMainCharacter::UnSlowDown() {
	bSlowMode = false;
	UE_LOG(LogTemp, Warning, TEXT("Un Slowed Down"));
	PPEffect(false);
	PlaySound(false);
	if (!bSlowMode) {
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
		CustomTimeDilation = 1.0f;
	}
}

//Posible of crashes when there is no post processing volumes in the world and also
//enable the chromatic aberration intensity(5.0) and offset(1.0).
void AMainCharacter::PPEffect(bool bOn) {
	
	int32 count = GetWorld()->PostProcessVolumes.Num();
	FPostProcessVolumeProperties volume;
	FPostProcessSettings* settings;
	if (bOn) {
		for (int32 x = 0; x < count; ++x) {
			volume = GetWorld()->PostProcessVolumes[x]->GetProperties();
			if (volume.bIsUnbound) {
				settings = (FPostProcessSettings*)volume.Settings;
				settings->ChromaticAberrationStartOffset = 0.0f;
			}
		}
	}
	else {
		for (int32 x = 0; x < count; ++x) {
			volume = GetWorld()->PostProcessVolumes[x]->GetProperties();
			if (volume.bIsUnbound) {
				settings = (FPostProcessSettings*)volume.Settings;
				settings->ChromaticAberrationStartOffset = 1.0f;
			}
		}
	}
}

//Play sound when the slowdown fucton is called and also Unslowdown fucntion is called
void AMainCharacter::PlaySound(bool bStartStop) {
	if (MagicSoundStartCue && MagicSoundStopCue) {
		if (bStartStop) {
			UGameplayStatics::PlaySound2D(this, MagicSoundStartCue);
		}
		else {
			UGameplayStatics::PlaySound2D(this, MagicSoundStopCue);
		}
	}
}

void AMainCharacter::DecrementHeart(int32 Amount){
	if (Heart > 0) {
		Heart -= Amount;
	}
}

void AMainCharacter::Die() {
	if (Heart <= 0) {
		SetActorLocation(PlayerInitialLocation);
		SetActorRotation(PlayerInitialRotation);
		Heart += 3;
	}
}

void AMainCharacter::SwitchLevel(FName LevelName) {
	UWorld* World = GetWorld();
	if (World) {
		FString CurrentLevel = World->GetMapName();
		FName CurrentLevelName(*CurrentLevel);
		if (CurrentLevelName != LevelName) {
			UGameplayStatics::OpenLevel(World, LevelName);
		}
	}
}

void AMainCharacter::SaveGame() {
	UGameSave* SaveGameInstance = Cast<UGameSave>(UGameplayStatics::CreateSaveGameObject(UGameSave::StaticClass()));

	SaveGameInstance->CharacterStats.Location = GetActorLocation();
	SaveGameInstance->CharacterStats.Rotation = GetActorRotation();

	UGameplayStatics::SaveGameToSlot(SaveGameInstance,SaveGameInstance->PlayerName , SaveGameInstance->UserIndex);
}

void AMainCharacter::LoadGame(bool SetPosition) {
	
	if (Heart > 0) {
		UGameSave* LoadGameInstance = Cast<UGameSave>(UGameplayStatics::CreateSaveGameObject(UGameSave::StaticClass()));
		LoadGameInstance = Cast<UGameSave>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->PlayerName, LoadGameInstance->UserIndex));
		if (bSlowMode == true) {
			UnSlowDown();
		}
		if (SetPosition) {
			SetActorLocation(LoadGameInstance->CharacterStats.Location);
			SetActorRotation(LoadGameInstance->CharacterStats.Rotation);
		}
	}
	else {
		SetActorLocation(PlayerInitialLocation);
		SetActorRotation(PlayerInitialRotation);
		Heart += 3;
		if (bSlowMode == true) {
			UnSlowDown();
		}
	}
}

void AMainCharacter::IncrementHeart(int32 Amount) {
	if (Heart >= MaxHeart) {
		Heart = MaxHeart;
	}
	else {
		Heart += Amount;
	}
}


