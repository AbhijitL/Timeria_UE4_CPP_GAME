// Copyright to Leihaorambam Abhijit Singh abhijitl.github.io or milkandegg.studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UENUM(BlueprintType)
enum class EMovementStatus : uint8 {
	EMS_Normal UMETA(DisplayName = "Normal"),
	EMS_Sprinting UMETA(DisplayName = "Sprinting"),
	EMS_MAX UMETA(DisplayName = "Default")
};

UENUM(BlueprintType)
enum class EStaminaStatus : uint8 {
	ESS_Normal UMETA(DisplayName = "Normal"),
	ESS_BelowMinimum UMETA(DisplayName = "BelowMinimum"),
	ESS_Exhausted UMETA(DisplayName = "Exhausted"),
	ESS_ExhautedRecovering UMETA(DisplayName = "ExhautedRecovering"),

	ESS_MAX UMETA(DisplayName = "DefaultMax"),
};



UCLASS()
class TIMERIA_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	//It will store Player location and rotation so when player health goes 0 it will
	//Spawn at this location
	FVector PlayerInitialLocation;
	FRotator PlayerInitialRotation;

	UPROPERTY(VisibleAnyWhere,BlueprintReadWrite,Category="Enum")
	EStaminaStatus StaminaStatus;

	FORCEINLINE void SetStaminaStatus(EStaminaStatus Status) { StaminaStatus = Status; }

	UPROPERTY(VisibleAnyWhere,BlueprintReadWrite,Category="Enum")
	EMovementStatus MovementStatus;

	void SetMovementStatus(EMovementStatus Status);

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Movement")
	float StamindDrainRate;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Movement")
	float MinSprintStamina;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Running")
	float RunningSpeed;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Running")
	float SprintingSpeed;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Controller")
	class AMainPlayerController* MainPlayerController;

	bool bShiftKeyDown;

	void ShiftKeyDown();

	void ShiftKeyUp();

	bool bESCDown;
	void ESCDown();
	void ESCUp();

	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly,Category = "Movement")
	bool bSpaceKeyDown;

	virtual void Jump() override;

	virtual void StopJumping() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
	float MaxStamina;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Player Stats")
	float Stamina;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Player Stats")
	int32 MaxHeart;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Player Stats")
	int32 Heart;

	void IncrementHeart(int32 Amount);

	void DecrementHeart(int32 Amount);

	void Die();

	void SwitchLevel(FName LevelName);

	UPROPERTY(VisibleAnyWhere,BlueprintReadWrite,Category="Camera",meta = (AllowPrivateAccess = true))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnyWhere,BlueprintReadOnly,Category = "Camera", meta = (AllowPrivateAccess = true))
	class UCameraComponent* Camera;

	FORCEINLINE UCameraComponent* GetCameraComponent() const { return Camera; }
	FORCEINLINE USpringArmComponent* GetSpringArmComponent() const { return SpringArm; }

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Camera")
	float TurnRate;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Camera")
	float LookUpRate;

	bool bSlowMode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SlowMo")
	float GSlowMoSpeed;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SlowMo")
	float SelfSlowMoSpeed;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Anims")
	bool bAttacking;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anims")
	class UAnimMontage* CharMontage;

	
	FTimerHandle MaggicTimeHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Magic")
	float MaggicTimeEffect;

	UPROPERTY(EditAnyWhere,BlueprintReadWrite,Category="Magic")
	class UParticleSystem* TimeWrapParticle;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Magic")
	class USoundCue* MagicSoundStartCue;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Magic")
	class USoundCue* MagicSoundStopCue;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float move);
	void MoveRight(float move);

	void LookUp(float Rate);
	void Turn(float Rate);

	UFUNCTION(BlueprintCallable)
	void SlowDown();

	void UnSlowDown();

	void Magic();

	UFUNCTION(BlueprintCallable)
	void MagicEnd();

	void PPEffect(bool bOn);

	void PlaySound(bool bStartStop);

	UFUNCTION(BlueprintCallable)
	void SaveGame();
	

	UFUNCTION(BlueprintCallable)
	void LoadGame(bool SetPosition);
};
