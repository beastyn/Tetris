// Fill out your copyright notice in the Description page of Project Settings.

#include "BrickPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Classes/Engine/World.h"
#include "TimerManager.h"
#include "Brick.h"
#include "ConstructorHelpers.h"
#include "Camera/PlayerCameraManager.h"
#include "GameFramework/PlayerController.h"
#include "Components/StaticMeshComponent.h"
#include "GridCounter.h"
#include "TetrisResolve.h"



ABrickPlayerController::ABrickPlayerController()
{

	static ConstructorHelpers::FObjectFinder<UClass> BrickFinder(TEXT("Class '/Game/Tetris/Brick/Brick_BP.Brick_BP_C'"));
	BrickSome = BrickFinder.Object;
	EmptyCellMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("DefaultEmptyMesh"));
	bAutoManageActiveCameraTarget = false;
	Grid = CreateDefaultSubobject<UGridCounter>(FName("Grid Counter"));
	TetrisResolve = CreateDefaultSubobject<UTetrisResolve>(FName("Tetris Resolving"));
}

void ABrickPlayerController::Tick(float DeltaTime) //TODO Do I need this?
{

}
void ABrickPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//Set Default Data
	Brick = Cast<ABrick>(GetPawn());
	CubesMeshesForBrick = Brick->GetStaticMeshesforCubes();
	GridData = Grid->GetGridData();
	SetEmptyStaticMeshesinGrid();
	//Grid Data for movement
	UnitLength = Grid->GetUnitLength();
	GridMaxXY = Grid->GetGridMaxXY();
	GridMinXY = Grid->GetGridMinXY();
	
	//istant move down
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABrickPlayerController::InstantMoveDown, 1.f, true);//TODO Clear Timer
	

}

void ABrickPlayerController::TestTimer()
{
	UE_LOG(LogTemp, Warning, TEXT("Is timer tick"))
}

void ABrickPlayerController::InstantMoveDown() 
{	
	if (Brick)
	{
		/*for (int32 i = 0; i < GridData.Num(); i++)
		{
		UE_LOG(LogTemp, Warning, TEXT("%d: %s"), i, GridData[i].isFilled ? "1" : "0")
		}*/
		auto CubesCoordinates = GetCubesCoordinates();
		auto MinYCoordinate = GetMinYCoordinate(CubesCoordinates);
		bool AlmostZero = FMath::IsNearlyEqual(MinYCoordinate, -900, 0.01f);
		
		CheckForDownSide(CubesCoordinates);
		
		if (!AlmostZero && IsAbleMoveDown)
		{		
			Brick->AddActorLocalOffset(FVector(0, -100, 0));
		}
		else 
		{
			SetGridFilledCell(CubesCoordinates, CubesMeshesForBrick);
			
			TetrisResolve->CheckSolving(GridData, EmptyCellMesh);
						
		//	TetrisResolve->CorrectBrickPositions(GridData, EmptyCellMesh);
			
			OnBrickStop.Broadcast();

			//Brick->DeleteEmptyBrick(Brick->GetStaticMeshesforCubes());

			SpawnNewBrick();
		}
			
	}
	 
}

void ABrickPlayerController::SetEmptyStaticMeshesinGrid()
{
	for (int32 i = 0; i < GridData.Num(); i++)
	{
		GridData[i].CubeFromBrick = EmptyCellMesh;
	}
}

int32 ABrickPlayerController::GetBrickType()
{
	return Brick->GetBrickType();
}

void ABrickPlayerController::CheckForDownSide(TArray<FVector> CubesCoordinates)
{
	for (int32 i = 0; i < CubesCoordinates.Num(); i++)
	{
		int32 IndexI = GetCubeIndex(CubesCoordinates[i])[0];
		int32 IndexJ = GetCubeIndex(CubesCoordinates[i])[1];
		if (IndexI < 19)
		{
			if (GridData[IndexI * 10 + IndexJ + 10].isFilled)
			{
				IsAbleMoveDown = false;
			}
		}
	}
	
}

void ABrickPlayerController::CheckForLeftSide(TArray<FVector> CubesCoordinates)
{
	for (int32 i = 0; i < CubesCoordinates.Num(); i++)
	{
		int32 IndexI = GetCubeIndex(CubesCoordinates[i])[0];
		int32 IndexJ = GetCubeIndex(CubesCoordinates[i])[1];
		if (IndexI <= 19)
		{
			if (GridData[IndexI * 10 + IndexJ - 1].isFilled)
			{
				IsAbleMoveLeft = false;
			}
		}
	}
}

void ABrickPlayerController::CheckForRightSide(TArray<FVector> CubesCoordinates)
{
	for (int32 i = 0; i < CubesCoordinates.Num(); i++)
	{
		int32 IndexI = GetCubeIndex(CubesCoordinates[i])[0];
		int32 IndexJ = GetCubeIndex(CubesCoordinates[i])[1];
		if (IndexI <= 19)
		{
			if (GridData[IndexI * 10 + IndexJ + 1].isFilled)
			{
				IsAbleMoveRight = false;
			}
		}
	}

}

TArray<int32> ABrickPlayerController::GetCubeIndex(FVector CubeCoordinate)
{
	return Brick->GetCubeIndex(CubeCoordinate);
}

void ABrickPlayerController::SetGridFilledCell(TArray<FVector> CubesCoordinates, TArray<UStaticMeshComponent*> CubesMeshesForBrick)
{
	for (int32 i = 0; i < CubesCoordinates.Num(); i++)
	{
		int32 IndexI = Brick->GetCubeIndex(CubesCoordinates[i])[0];
		int32 IndexJ = Brick->GetCubeIndex(CubesCoordinates[i])[1];
		GridData[IndexI * 10 + IndexJ].isFilled = true;
		GridData[IndexI * 10 + IndexJ].CubeFromBrick = CubesMeshesForBrick[i];
	}
}

void ABrickPlayerController::SpawnNewBrick()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = Instigator;
	ABrick* NewBrick = GetWorld()->SpawnActor<ABrick>(
		BrickSome,
		FVector(0.f, 900.f, 140.2),
		FRotator::ZeroRotator,
		SpawnParams
		);
	Brick = Cast<ABrick>(GetPawn());
	IsAbleMoveDown = true;
	IsAbleMoveLeft = true;
	IsAbleMoveRight = true;
	CubesMeshesForBrick = Brick->GetStaticMeshesforCubes();
}

//For Brick Controller in BP

TArray<FVector> ABrickPlayerController::GetCubesCoordinates()
{
	return Brick->GetCubesCoordinates();
}

float ABrickPlayerController::GetMinYCoordinate(TArray<FVector> CubesRelativeLocation)
{
	return Brick->GetMinYCoordinate(CubesRelativeLocation);
}

float ABrickPlayerController::GetMaxXCoordinate(TArray<FVector> CubesRelativeLocation)
{
	return Brick->GetMaxXCoordinate(CubesRelativeLocation);
}

float ABrickPlayerController::GetMinXCoordinate(TArray<FVector> CubesRelativeLocation)
{
	return Brick->GetMinXCoordinate(CubesRelativeLocation);
}




