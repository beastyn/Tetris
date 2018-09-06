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


ABrickPlayerController::ABrickPlayerController()
{

	static ConstructorHelpers::FObjectFinder<UClass> BrickFinder(TEXT("Class'/Game/Props/Brick_BP.Brick_BP_C'"));
	BrickSome = BrickFinder.Object;
	EmptyCellMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("DefaultEmptyMesh"));
	bAutoManageActiveCameraTarget = false;
	
}

void ABrickPlayerController::Tick(float DeltaTime) //TODO Do I need this?
{

}
void ABrickPlayerController::BeginPlay()
{
	Brick = Cast<ABrick>(GetPawn());
	CubesMeshesForBrick = Brick->GetStaticMeshesforCubes();
	//Grid Data for movement
	UnitLength = Brick->GetUnitLength();
	GridMaxXY = Brick->GetGridMaxXY();
	GridMinXY = Brick->GetGridMinXY();
	UpdatedGridData = Brick->GetGridData();

	//istant move down
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABrickPlayerController::InstantMoveDown, 1.f, true);//TODO Clear Timer

}

ABrick* ABrickPlayerController::GetBrick()
{
	return Brick;
}


void ABrickPlayerController::InstantMoveDown() 
{	
	if (Brick)
	{
		GetOnceGridData(); 

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
			
			int32 CountFilledLine = 0;
			int32 MaxJ = 0;
			for (int32 j = 0; j < 20; j++)
			{
				for (int32 i = 0; i < 10; i++)
				{
					if (UpdatedGridData[j * 10 + i].isFilled)
					{
						CountFilledLine++;
					}
				}
				if (CountFilledLine == 10)
				{
					MaxJ = j;
					isSolved = true;
					for (int32 i = 0; i < 10; i++)
					{
						UpdatedGridData[j * 10 + i].CubeFromBrick->DestroyComponent();
						UpdatedGridData[j * 10 + i].CubeFromBrick= EmptyCellMesh;
						UpdatedGridData[j * 10 + i].isFilled = false;
						
					}
				}	
				CountFilledLine = 0;
								
			}
		
			if (isSolved)
			{
				for (int32 x = MaxJ - 1; x >= 0; x--)
				{
					for (int32 y = 0; y < 10; y++)
					{
						UE_LOG(LogTemp, Warning, TEXT("%d: %s"), x * 10 + 10 + y, UpdatedGridData[x * 10 + 10 + y].isFilled ? "1" : "0")
						if (UpdatedGridData[x * 10 + y].isFilled)
						{
							UpdatedGridData[x * 10 + y].CubeFromBrick->AddRelativeLocation(FVector(0, -100, 0));
							UpdatedGridData[x * 10 + y + 10].CubeFromBrick = UpdatedGridData[x * 10 + y].CubeFromBrick;
							UpdatedGridData[x * 10 + y].CubeFromBrick = EmptyCellMesh;
							UpdatedGridData[x * 10 + y].isFilled = false;
							UpdatedGridData[x * 10 + 10 + y].isFilled = true;

							UE_LOG(LogTemp, Warning, TEXT("%d: %s"), x * 10 + 10 + y, UpdatedGridData[x * 10 + 10 + y].isFilled ? "1" : "0")

						}
					}
				}

				MaxJ = 0;
				
			}
		
			SpawnNewBrick();
		}
			
	}
	 
}

void ABrickPlayerController::GetOnceGridData()
{
	if (UpdatedGridData.Num() == 0)
	{
		UpdatedGridData = Brick->GetGridData();
		SetEmptyStaticMeshesinGrid();
		UE_LOG(LogTemp, Warning, TEXT("%s"), *(UpdatedGridData[1].CubeFromBrick->GetName()))

	}
}

void ABrickPlayerController::CheckForDownSide(TArray<FVector> CubesCoordinates)
{
	for (int32 i = 0; i < CubesCoordinates.Num(); i++)
	{
		int32 IndexI = GetCubeIndex(CubesCoordinates[i])[0];
		int32 IndexJ = GetCubeIndex(CubesCoordinates[i])[1];
		if (IndexI < 19)
		{
			if (UpdatedGridData[IndexI * 10 + IndexJ + 10].isFilled)
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
		if (IndexI < 19)
		{
			if (UpdatedGridData[IndexI * 10 + IndexJ - 1].isFilled)
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
		if (IndexI < 19)
		{
			if (UpdatedGridData[IndexI * 10 + IndexJ + 1].isFilled)
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

void ABrickPlayerController::SetEmptyStaticMeshesinGrid()
{
	for (int32 i = 0; i < UpdatedGridData.Num(); i++)
	{
		UpdatedGridData[i].CubeFromBrick = EmptyCellMesh;
	}
}

void ABrickPlayerController::SetGridFilledCell(TArray<FVector> CubesCoordinates, TArray<UStaticMeshComponent*> CubesMeshesForBrick)
{
	for (int32 i = 0; i < CubesCoordinates.Num(); i++)
	{
		int32 IndexI = Brick->GetCubeIndex(CubesCoordinates[i])[0];
		int32 IndexJ = Brick->GetCubeIndex(CubesCoordinates[i])[1];
		UpdatedGridData[IndexI * 10 + IndexJ].isFilled = true;
		UpdatedGridData[IndexI * 10 + IndexJ].CubeFromBrick = CubesMeshesForBrick[i];
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




