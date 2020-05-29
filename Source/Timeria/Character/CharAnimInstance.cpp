// Copyright to Leihaorambam Abhijit Singh abhijitl.github.io or milkandegg.studios


#include "CharAnimInstance.h"
#include "MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


void UCharAnimInstance::NativeInitializeAnimation() {
	if (Pawn == nullptr) {
		Pawn = TryGetPawnOwner();
		if (Pawn) {
			Main = Cast<AMainCharacter>(Pawn);
		}
	}
}

void UCharAnimInstance::UpdateAnimationProperties() {
	if (Pawn == nullptr) {
		Pawn = TryGetPawnOwner();
	}
		if (Pawn) {
			FVector Speed = Pawn->GetVelocity();
			FVector LSpeed = FVector(Speed.X, Speed.Y, 0.0f);
			MovementSpeed = LSpeed.Size();
			bIsInAir = Pawn->GetMovementComponent()->IsFalling();
			if (Main == nullptr) {
				Main = Cast<AMainCharacter>(Pawn);
			}
		}
	
}