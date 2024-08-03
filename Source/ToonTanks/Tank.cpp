// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PawnMovementComponent.h"



ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera-> SetupAttachment(SpringArm);

	MovementComponent = CreateDefaultSubobject<UPawnMovementComponent>(TEXT("Pawn Movement"));
	


}



// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerContoller = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerContoller->GetLocalPlayer()))
		{
			SubSystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	TankPlayerController = Cast<APlayerController>(GetController());
	//PlayerControllerRef->SetShowMouseCursor(true);
	


}





// Called every frame
void ATank::Tick(float DeltaTime)
{	
	Super::Tick(DeltaTime);

	if (TankPlayerController)
	{
		FHitResult HitResult;
		TankPlayerController->GetHitResultUnderCursor
		(
			ECollisionChannel::ECC_Visibility,
			false,
			HitResult
		);

		/*DrawDebugSphere
		(
			GetWorld(),
			HitResult.ImpactPoint,
			32,
			5,
			FColor::Red,
			false,
			-1
		);*/
		RotateTurret(HitResult.ImpactPoint);

		//UE_LOG(LogTemp, Warning, TEXT("The boolean value is %s"), (IsSprinting ? TEXT("true") : TEXT("false")));
	}

}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	bAlive = false;
}





void ATank::Move(const FInputActionValue& Value)
{

		const FVector2D MovementVector = Value.Get<FVector2D>();

		/*const FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, MovementVector.Y);

		const FVector Right = GetActorRightVector();
		AddMovementInput(Right, MovementVector.X);*/



		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(ForwardDirection, MovementVector.Y);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(RightDirection, MovementVector.X);
	

}




void ATank::Dash(const FInputActionValue& Value)
{
	const bool DashValue = Value.Get<bool>();
	if (DashValue)
	{
		UE_LOG(LogTemp, Warning, TEXT("Dashing"));
	}
}




void ATank::Look(const FInputActionValue& Value)
{

	FVector2D LookAxisValue = Value.Get<FVector2D>();

	if (GetController())
	{
		AddControllerYawInput(LookAxisValue.X);
		AddControllerPitchInput(LookAxisValue.Y);
	}
}




void ATank::Sprint(const FInputActionValue& Value)
{
	const bool SprintValue = Value.Get<bool>();
	if (SprintValue)
	{
		IsSprinting = true;
		
	}
}




void ATank::SprintEnd(const FInputActionValue& Value)
{
	const bool SprintEndValue = Value.Get<bool>();
	if (!SprintEndValue)
	{
		IsSprinting = false;
	}
}





void ATank::Shoot(const FInputActionValue& Value)
{
	const bool CurrentValue = Value.Get<bool>();
	if (CurrentValue)
	{
		UE_LOG(LogTemp, Warning, TEXT("Shooting"));

		Fire();


	}
}




// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* AInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{

		AInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::Move);
		AInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATank::Look);
		AInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &ATank::Shoot);
		AInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ATank::Sprint);
		AInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ATank::SprintEnd);
		AInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &ATank::Dash);
	}

}