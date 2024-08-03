// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeBase_ToonTanks.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AGameModeBase_ToonTanks : public AGameModeBase
{
	GENERATED_BODY()


public:
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();
	
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

private:
	class ATank* Tank;
	class ATankPlayerController* ToonTanksPlayerController;

	float StartDelay = 3.f;

	void HandleGameStart();

	UPROPERTY(EditAnywhere)
	int32 TargetTowers = 0.f;

	int32 GetTargetTower();


	
};


