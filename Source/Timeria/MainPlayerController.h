// Copyright to Leihaorambam Abhijit Singh abhijitl.github.io or milkandegg.studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TIMERIA_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> HUDOverlayAsset;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widgets")
	class UUserWidget* HUDOverlay;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> WPauseMenu;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widgets")
	class UUserWidget* PauseMenu;

	bool bPauseMenuVisible;

	UFUNCTION(BlueprintCallable)
	void DisplayPauseMenu();

	UFUNCTION(BlueprintCallable)
	void RemovePauseMenu();
	
	void TooglePauseMenu();

protected:
	virtual void BeginPlay() override;

};
