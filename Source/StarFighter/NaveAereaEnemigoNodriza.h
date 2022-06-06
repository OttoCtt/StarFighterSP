// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NaveAerea.h"
#include "NaveAereaEnemigoNodriza.generated.h"

/**
 * 
 */
UCLASS()
class STARFIGHTER_API ANaveAereaEnemigoNodriza : public ANaveAerea
{
	GENERATED_BODY()

public:
	ANaveAereaEnemigoNodriza();
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	float randX = 0.f;
	float randY = 0.f;
	FVector GunOffset;
	void timer();
	virtual void FireShot(FVector FireDirection);
	void Fire();
	float FireForwardValue;
	float FireRightValue;

	FTimerHandle MemberTimerStt;
	FTimerHandle MemberTimerSttf1;
private:
	uint32 bCanFire : 1;
};
