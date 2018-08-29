// Fill out your copyright notice in the Description page of Project Settings.

#include "Brick.h"
#include "GridCounter.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Classes/Engine/World.h"
#include "GameFramework/Pawn.h"


// Sets default values
ABrick::ABrick()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
	Grid = CreateDefaultSubobject<UGridCounter>(FName("Grid Counter"));


	
}

// Called when the game starts or when spawned
void ABrick::BeginPlay()
{
	
	Super::BeginPlay();

	CubesForFigure = GetStaticMeshesforCubes();
	//TODO make random figure generation
	CubesForFigure[0]->SetRelativeLocation(FVector(0));
	CubesForFigure[1]->SetRelativeLocation(FVector(0, -100, 0));
	CubesForFigure[2]->SetRelativeLocation(FVector(0, -200, 0));
	CubesForFigure[3]->SetRelativeLocation(FVector(0, -300, 0));


			
}

// Called every frame
void ABrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABrick::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//Making Bricks and getters for coords

TArray<UStaticMeshComponent*> ABrick::GetStaticMeshesforCubes()
{
	TArray<UActorComponent*> StaticMeshComps;
	TArray<UStaticMeshComponent*> MeshComp;
	StaticMeshComps = GetComponentsByClass(UStaticMeshComponent::StaticClass());

	for (int32 i = 0; i < StaticMeshComps.Num(); i++)
	{
		if (StaticMeshComps[i])
		{
			MeshComp.Add(Cast<UStaticMeshComponent>(StaticMeshComps[i]));
		}
	}
	return MeshComp;
}

TArray<FVector> ABrick::GetCubesCoordinates()
{
	TArray<FVector> CubeCoordinate = { FVector(0), FVector(0), FVector(0), FVector(0) };
	
	for (int32 i = 0; i < CubesForFigure.Num(); i++)
	{
		CubeCoordinate[i] = CubesForFigure[i]->GetComponentLocation();
	}
	return CubeCoordinate;
}


float ABrick::GetMinYCoordinate(TArray<FVector> CubesRelativeLocation)
{
	float MinValueY = CubesRelativeLocation[0].Y;
	for (int32 i = 0; i < CubesRelativeLocation.Num(); i++)
	{
		
		if (CubesRelativeLocation[i].Y <= MinValueY) { MinValueY = CubesRelativeLocation[i].Y; } // recording for MIN Y
	}

	return MinValueY;
}

float ABrick::GetMaxXCoordinate(TArray<FVector> CubesRelativeLocation)
{
	float MaxValueX = CubesRelativeLocation[0].X;
	for (int32 i = 0; i < CubesRelativeLocation.Num(); i++)
	{
		if (CubesRelativeLocation[i].X > MaxValueX) { MaxValueX = CubesRelativeLocation[i].X; } // recording for MIN Y
	}

	return MaxValueX;
}

float ABrick::GetMinXCoordinate(TArray<FVector> CubesRelativeLocation)
{
	float MinValueX = CubesRelativeLocation[0].X;
	for (int32 i = 0; i < CubesRelativeLocation.Num(); i++)
	{
		
		if (CubesRelativeLocation[i].X <= MinValueX) { MinValueX = CubesRelativeLocation[i].X; } // recording for MIN Y
	}

	return MinValueX;
}

// Collect information about Grid
FVector2D ABrick::GetGridMaxXY()
{
	return Grid->GetGridMaxXY();
}


FVector2D ABrick::GetGridMinXY()
{
	return Grid->GetGridMinXY();
	
}

float ABrick::GetUnitLength()
{
	return Grid->GetUnitLength();
}



