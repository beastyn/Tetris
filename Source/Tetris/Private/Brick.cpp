// Fill out your copyright notice in the Description page of Project Settings.

#include "Brick.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Classes/Engine/World.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "BrickPlayerController.h"


// Sets default values
ABrick::ABrick()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	


	
}

// Called when the game starts or when spawned
void ABrick::BeginPlay()
{
	
	Super::BeginPlay();
	
	CubesForFigure = GetStaticMeshesforCubes();
	
	BrickType = FMath::RandRange(1, 4);
	SetCubesForBrick(CubesForFigure, BrickType);
		
	auto BrickPlayerController = Cast<ABrickPlayerController>(GetWorld()->GetFirstPlayerController());
	
	BrickPlayerController->OnBrickStop.AddDynamic(this, &ABrick::DeleteEmptyBrick);
	
	
			
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

//Making Bricks and getters for coords and meshes

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

void ABrick::SetCubesForBrick(TArray<UStaticMeshComponent*>CubesForFigure, int32 BrickType)
{
	if (BrickType == 1)
	{
		CubesForFigure[0]->SetRelativeLocation(FVector(0, 100, 0));
		CubesForFigure[1]->SetRelativeLocation(FVector(0, 0, 0));
		CubesForFigure[2]->SetRelativeLocation(FVector(0, -100, 0));
		CubesForFigure[3]->SetRelativeLocation(FVector(0, -200, 0));
	}
	if (BrickType == 2)
	{
		CubesForFigure[0]->SetRelativeLocation(FVector(100, 0, 0));
		CubesForFigure[1]->SetRelativeLocation(FVector(0, 0, 0));
		CubesForFigure[2]->SetRelativeLocation(FVector(100, 100, 0));
		CubesForFigure[3]->SetRelativeLocation(FVector(0, 100, 0));
	}
	if (BrickType == 3)
	{
		CubesForFigure[0]->SetRelativeLocation(FVector(0, 100, 0));
		CubesForFigure[1]->SetRelativeLocation(FVector(0, 0, 0));
		CubesForFigure[2]->SetRelativeLocation(FVector(100, 100, 0));
		CubesForFigure[3]->SetRelativeLocation(FVector(0, -100, 0));
	}
	if (BrickType == 4)
	{
		CubesForFigure[0]->SetRelativeLocation(FVector(0, 100, 0));
		CubesForFigure[1]->SetRelativeLocation(FVector(0, 0, 0));
		CubesForFigure[2]->SetRelativeLocation(FVector(100, 100, 0));
		CubesForFigure[3]->SetRelativeLocation(FVector(-100, 0 , 0));
	}
}
int32 ABrick::GetBrickType()
{
	return BrickType;
	
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

TArray<int32> ABrick::GetCubeIndex(FVector CubeCoordinate)
{
	CubeIndex[0] = (int32)(CubeCoordinate.Y*(-1) / 100 + 10);
	CubeIndex[1] = (int32)(CubeCoordinate.X*(-1) / 100 + 5);

	return CubeIndex;
}

void ABrick::DeleteEmptyBrick()
{
	if (GetStaticMeshesforCubes().Num() == 0)
	{
		this->Destroy();
	}
	
}


