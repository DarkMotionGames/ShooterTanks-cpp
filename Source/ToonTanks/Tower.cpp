// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ATower::ATower()
{

}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Find The Distance
	if (InFireRange())
	{

		RotateTurret(Tank->GetActorLocation());

	}
	

}

void ATower::HandleDestruction()
{

	Super::HandleDestruction();
	Destroy();

}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);


	

}

void ATower::CheckFireCondition()
{
	if (Tank == nullptr)
	{
		return;
	}
	if (InFireRange() && Tank->bAlive)
	{

		Fire();

	}
}


bool ATower::InFireRange()
{
	if (Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

		//Check to see if tower can focus to player Tank
		if (FireRange >= Distance)
		{

			return true;

		}

	}

	return false;
}

