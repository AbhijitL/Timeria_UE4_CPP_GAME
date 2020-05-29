// Copyright to Leihaorambam Abhijit Singh abhijitl.github.io or milkandegg.studios

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TIMERIA_API UCharAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:

	virtual void NativeInitializeAnimation() override;

	UFUNCTION(BlueprintCallable,Category=AnimationProperties)
	void UpdateAnimationProperties();

	UPROPERTY(EditAnyWhere,BlueprintReadOnly,Category="Movement")
	float MovementSpeed;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Movement")
	bool bIsInAir;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Movement")
	class APawn* Pawn;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Movement")
	class AMainCharacter* Main;
};
