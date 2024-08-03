// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "GameFramework/Pawn.h"

void ATankPlayerController::PlayerEnabledState(bool bPlayeEnabled)
{
	if (bPlayeEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}

	bShowMouseCursor = bPlayeEnabled;
}

