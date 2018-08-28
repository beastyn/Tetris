// Fill out your copyright notice in the Description page of Project Settings.

#include "Brick.h"
#include "Components/SceneComponent.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "ConstructorHelpers.h"
#include "GridCounter.h"
#include "Classes/Engine/World.h"
#include "BrickConstructor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraActor.h"

// Sets default values
ABrick::ABrick()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
	Grid = CreateDefaultSubobject<UGridCounter>(FName("Grid Counter"));


	//RootComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("RootCube"));
	//RootComponent->AddRelativeLocation(FVector(0, 0, 0));
	//static ConstructorHelpers::FObjectFinder<UStaticMesh>CubeVisualAsset(TEXT("/Game/Props/Shape_Cube.Shape_Cube"));
	
	// static mesh array initialization
	/*for (int32 i = 0; i < 4; i++)
	{
		CubesForFigure.Add(CreateDefaultSubobject<UStaticMeshComponent>(FName("Cube", i)));

	}*/

	// creating cube meshed on positions
/*	for (int32 i = 0; i<4; i++)
	{
		CubesForFigure.Add(CreateDefaultSubobject<UStaticMeshComponent>(FName("Cube", i)));
		if (CubeVisualAsset.Succeeded() && CubesForFigure[i])
		{
			CubesForFigure[i]->SetupAttachment(RootComponent);
			CubesForFigure[i]->SetStaticMesh(CubeVisualAsset.Object);
			CubesForFigure[i]->SetRelativeLocation(GenerateFirstFigure()[i]);
			CubesForFigure[i]->SetWorldScale3D(FVector(1.f));
			UE_LOG(LogTemp, Warning, TEXT("Cube %d: %s"), i, *GenerateFirstFigure()[i].ToString())
		}

	}
	*/
}

// Called when the game starts or when spawned
void ABrick::BeginPlay()
{
	
	Super::BeginPlay();

	CubesForFigure = GetStaticMeshesforCubes();

	CubesForFigure[0]->SetRelativeLocation(FVector(0));
	CubesForFigure[1]->SetRelativeLocation(FVector(0));
	CubesForFigure[2]->SetRelativeLocation(FVector(0));
	CubesForFigure[3]->SetRelativeLocation(FVector(0));
	//FVector Location = CubeForBrick2->GetComponentLocation();
	
	//SpawnBrick();
	
		
}

/*void ABrick::SpawnBrick()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = Instigator;

	auto NewBrick = GetWorld()->SpawnActor<ABrickConstructor>(
		FVector(0.f, 700.f, 140.2),
		FRotator::ZeroRotator,
		SpawnParams
		);
	auto CubeCoordinates = NewBrick->GetCubesCoordinates();
	
	for (int32 i = 0; i < CubeCoordinates.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cube %d: %s"), i, *CubeCoordinates[i].ToString())
	}

}*/

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
TArray<FVector> ABrick::GenerateFirstFigure()
{
	/*int32 i = 0;
	for (FVector Cube: CubesRelativeLocation)
	{
		Cube = FVector(0, i*100, 0);
		CubesRelativeLocation[i] = Cube;
		i++;
		
	}*/
	CubesRelativeLocation = { FVector(0,0,0), FVector(0,-100,0), FVector(0,-300,0), FVector(0,0,0) };
	
	return CubesRelativeLocation;
}
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










