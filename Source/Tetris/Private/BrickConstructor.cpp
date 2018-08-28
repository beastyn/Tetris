// Fill out your copyright notice in the Description page of Project Settings.

#include "BrickConstructor.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "ConstructorHelpers.h"

// Sets default values
ABrickConstructor::ABrickConstructor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
/*	RootComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("RootCube"));
	RootComponent->AddRelativeLocation(FVector(0, 0, 0));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>CubeVisualAsset(TEXT("/Game/Props/Shape_Cube.Shape_Cube"));

	// static mesh array initialization
	for (int32 i = 0; i < 4; i++)
	{
		CubesForFigure.Add(CreateDefaultSubobject<UStaticMeshComponent>(FName("Cube", i)));

	}

	// creating cube meshed on positions
	for (int32 i = 0; i<4; i++)
	{
		if (CubeVisualAsset.Succeeded() && CubesForFigure[i])
		{
			CubesForFigure[i]->SetupAttachment(RootComponent);
			CubesForFigure[i]->SetStaticMesh(CubeVisualAsset.Object);
			CubesForFigure[i]->SetRelativeLocation(GenerateFirstFigure()[i]);
			CubesForFigure[i]->SetWorldScale3D(FVector(1.f));
		}

	}
	*/
}

// Called when the game starts or when spawned
void ABrickConstructor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABrickConstructor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/*TArray<FVector> ABrickConstructor::GenerateFirstFigure()
{
	int32 i = 0;
	for (FVector Cube : CubesRelativeLocation)
	{
		Cube = FVector(0, i * 100, 0);
		CubesRelativeLocation[i] = Cube;
		i++;

	}

	return CubesRelativeLocation;
}

TArray<FVector> ABrickConstructor::GetCubesCoordinates()
{
	TArray<FVector> CubeCoordinate = { FVector(0), FVector(0), FVector(0), FVector(0) };

	for (int32 i = 0; i < 4; i++)
	{
		if (CubesForFigure[i])
		{
			CubeCoordinate[i] = CubesForFigure[i]->GetComponentLocation();


		}
	}
	return CubeCoordinate;
}*/