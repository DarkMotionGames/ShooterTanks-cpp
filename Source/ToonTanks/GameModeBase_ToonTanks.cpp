// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeBase_ToonTanks.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "TankPlayerController.h"
#include "Tower.h"

void AGameModeBase_ToonTanks::ActorDied(AActor* DeadActor)

{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();

		if (ToonTanksPlayerController)
		{
			ToonTanksPlayerController->PlayerEnabledState(false);
			GameOver(false);
		}
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		--TargetTowers;

		if (TargetTowers == 0)
		{
			GameOver(true);
		}
	
	}
}

void AGameModeBase_ToonTanks::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}


void AGameModeBase_ToonTanks::HandleGameStart()
{
	TargetTowers = GetTargetTower();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast <ATankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	

	if (ToonTanksPlayerController)
	{
		ToonTanksPlayerController->PlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			ToonTanksPlayerController,
			&ATankPlayerController::PlayerEnabledState,
			true
		);


		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle,
			PlayerEnableTimerDelegate,
			StartDelay,
			false
		);
	}


}

int32 AGameModeBase_ToonTanks::GetTargetTower()
{
	TArray<AActor*> Towers;

	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
	return Towers.Num();
		
}

