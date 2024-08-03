// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"


UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* Movement;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", ExposeFunctionCategories = "Components"))
	UStaticMeshComponent* BaseMesh;
	
	UPROPERTY(VisibleAnywhere, Category = "Combat")
	class UParticleSystemComponent* TrailParticles;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* LaunchSound;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<UCameraShakeBase> HitShakeClass;



	UFUNCTION()
	void OnHit
	(
		UPrimitiveComponent* HitComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		FVector NormalImpulse,
		const FHitResult& Hit
	);

	UPROPERTY(EditAnywhere)
	float Damage = 25.f;


	UPROPERTY(EditAnywhere)
	class UParticleSystem* HitParticle;
};
