// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveAereaEnemigoNodriza.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Proyectil.h"

ANaveAereaEnemigoNodriza::ANaveAereaEnemigoNodriza()
{
	MoveSpeed = 210.f;
	Energy = 100.f;
	GunOffset = FVector(90, 0.f, 0.f);
	bCanFire = false;
	const FVector MoveDirection = FVector(FireForwardValue, FireRightValue, 0.f).GetClampedToMaxSize(1.0f);

	const FRotator FireRotation = MoveDirection.Rotation();
	// Spawn projectile at an offset from this pawn
	const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);
}

void ANaveAereaEnemigoNodriza::Tick(float DeltaSeconds)
{
	// Find movement direction
	const int ForwardValue = randX;
	const int RightValue = randY;

	if (ForwardValue != 0.0f || RightValue != 0.0f) {

		if (ForwardValue != FireForwardValue) {
			FireForwardValue = ForwardValue;
		}

		if (RightValue != FireRightValue) {
			FireRightValue = RightValue;
		}
	}

	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);

	// Calculate  movement
	const FVector Movement = MoveDirection * MoveSpeed * DeltaSeconds;

	// If non-zero size, move this actor
	if (Movement.SizeSquared() > 0.0f)
	{
		const FRotator NewRotation = Movement.Rotation();
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);

		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, NewRotation, true);
		}
	}
}

void ANaveAereaEnemigoNodriza::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(MemberTimerStt, this, &ANaveAereaEnemigoNodriza::timer, 2.0f, true);
	GetWorldTimerManager().SetTimer(MemberTimerSttf1, this, &ANaveAereaEnemigoNodriza::Fire, 3.0f, true, 4.0f);
}

void ANaveAereaEnemigoNodriza::timer()
{
	randX = FMath::RandRange(-1, 1);
	randY = FMath::RandRange(-1, 1);
}

void ANaveAereaEnemigoNodriza::FireShot(FVector FireDirection)
{
	if (bCanFire == true) {
		//Si estamos presionando fuego en una direccion
		const FRotator FireRotation = FireDirection.Rotation();
		const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);
		UWorld* const World = GetWorld();
		if (World != nullptr) {
			//spawn the projectile
			World->SpawnActor<AProyectil>(SpawnLocation, FireRotation);
		}
		bCanFire = false;
	}
}

void ANaveAereaEnemigoNodriza::Fire()
{
	bCanFire = true;
	const FVector FireDirection = FVector(FireForwardValue, FireRightValue, 0.f).GetClampedToMaxSize(1.0f);
	FireShot(FireDirection);
}
