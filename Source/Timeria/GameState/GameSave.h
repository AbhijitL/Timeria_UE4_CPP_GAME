// Copyright to Leihaorambam Abhijit Singh abhijitl.github.io or milkandegg.studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameSave.generated.h"

USTRUCT(BlueprintType)
struct FCharacterStats {
	GENERATED_BODY()

	UPROPERTY(VisibleAnyWhere,Category="SaveGameData")
	float Heart;

	UPROPERTY(VisibleAnyWhere, Category = "SaveGameData")
	float MaxHeart;

	UPROPERTY(VisibleAnyWhere, Category = "SaveGameData")
	FVector Location;

	UPROPERTY(VisibleAnyWhere, Category = "SaveGameData")
	FRotator Rotation;
};

/**
 * 
 */
UCLASS()
class TIMERIA_API UGameSave : public USaveGame
{
	GENERATED_BODY()
	
public:
	UGameSave();

	UPROPERTY(VisibleAnyWhere,Category=Basic)
	FString PlayerName;

	UPROPERTY(VisibleAnyWhere, Category = Basic)
	uint32 UserIndex;

	UPROPERTY(VisibleAnyWhere, Category = Basic)
	FCharacterStats CharacterStats;
};
