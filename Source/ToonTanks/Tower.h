// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
	

public:
	ATower();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float FireRange;

	void HandleDestruction();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class ATank* Tank;

private:

	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.f;
	void CheckFireCondition();

	bool InFireRange();

};


