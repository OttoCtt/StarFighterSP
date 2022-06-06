// Copyright Epic Games, Inc. All Rights Reserved.


#include "StarFighterGameModeBase.h"
#include "NaveTerrestreEnemiga01.h"
#include "NaveAereaEnemigoNodriza.h"

ANaveAereaEnemigoNodriza* AStarFighterGameModeBase::instancia = nullptr;
void AStarFighterGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//auto ne = SpawnNave<ANaveTerrestreEnemiga01>();
	//UE_LOG(LogTemp, Warning, TEXT("Dentro de BeginPlay en GameModeBase"));
	//GetWorld()->SpawnActor<ANaveTerrestreEnemiga01>(FVector::ZeroVector, FRotator::ZeroRotator);
	
	ANaveAereaEnemigoNodriza* nve1 = AStarFighterGameModeBase::GetInstancia();
	nve1->MoveSpeed = 320.f;
	nve1->Energy = 200.f;
	nve1->GetShipMeshComponent()->SetWorldScale3D(nve1->GetShipMeshComponent()->GetComponentScale() * 3);
	//Para comprobar que no spawnea otro objeto
	GetWorldTimerManager().SetTimer(MemberTimerSpawner, this, &AStarFighterGameModeBase::spawner, 5.0f, true, 10.f);
}

AStarFighterGameModeBase::AStarFighterGameModeBase()
{
	/*UE_LOG(LogTemp, Warning, TEXT("Dentro de constructor en GameModeBase"));
	GetWorld()->SpawnActor<ANaveTerrestreEnemiga01>(FVector::ZeroVector, FRotator::ZeroRotator);*/

	//SpawnNave<ANaveTerrestreEnemiga01>();

}

ANaveAereaEnemigoNodriza* AStarFighterGameModeBase::GetInstancia()
{
	if (instancia == nullptr) {
		//instancia = NewObject<ANaveAereaEnemigoNodriza>();
		instancia = GetWorld()->SpawnActor<ANaveAereaEnemigoNodriza>(FVector(500.f, -500.f, 310.f), FRotator::ZeroRotator);
	}
	return instancia;
}

void AStarFighterGameModeBase::spawner()
{
	ANaveAereaEnemigoNodriza* nve2 = AStarFighterGameModeBase::GetInstancia();
}
