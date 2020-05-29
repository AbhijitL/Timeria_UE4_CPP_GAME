// Copyright to Leihaorambam Abhijit Singh abhijitl.github.io or milkandegg.studios


#include "MainPlayerController.h"
#include "Blueprint/UserWidget.h"

void AMainPlayerController::BeginPlay() {
	Super::BeginPlay();
	if (HUDOverlayAsset) {
		HUDOverlay = CreateWidget<UUserWidget>(this, HUDOverlayAsset);
	}
	HUDOverlay->AddToViewport();
	HUDOverlay->SetVisibility(ESlateVisibility::Visible);

	if (WPauseMenu) {
		PauseMenu = CreateWidget<UUserWidget>(this, WPauseMenu);
		if (PauseMenu) {
			PauseMenu->AddToViewport();
			PauseMenu->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
void AMainPlayerController::DisplayPauseMenu() {
	if (PauseMenu) {
		bPauseMenuVisible = true;
		PauseMenu->SetVisibility(ESlateVisibility::Visible);

		FInputModeGameAndUI InputModeGameAndUI;
		SetInputMode(InputModeGameAndUI);
		bShowMouseCursor = true;
		SetPause(true);
	}
}
void AMainPlayerController::RemovePauseMenu() {
	if (PauseMenu) {
		bPauseMenuVisible = false;
		PauseMenu->SetVisibility(ESlateVisibility::Hidden);

		FInputModeGameOnly InputModeGameOnly;
		SetInputMode(InputModeGameOnly);
		bShowMouseCursor = false;
		SetPause(false);
	}
}

void AMainPlayerController::TooglePauseMenu() {

	if (bPauseMenuVisible) {
		RemovePauseMenu();
	}
	else {
		DisplayPauseMenu();
	}

}




