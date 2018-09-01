// Fill out your copyright notice in the Description page of Project Settings.

#include "BrickPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Classes/Engine/World.h"
#include "TimerManager.h"
#include "Brick.h"
#include "ConstructorHelpers.h"
#include "Camera/PlayerCameraManager.h"
#include "GameFramework/PlayerController.h"


ABrickPlayerController::ABrickPlayerController()
{

	static ConstructorHelpers::FObjectFinder<UClass> BrickFinder(TEXT("Class'/Game/Props/Brick_BP.Brick_BP_C'"));
	BrickSome = BrickFinder.Object;
	bAutoManageActiveCameraTarget = false;
	
}

void ABrickPlayerController::Tick(float DeltaTime) //TODO Do I need this?
{

	
}
void ABrickPlayerController::BeginPlay()
{
	Brick = Cast<ABrick>(GetPawn());
	UpdatedGridData = Brick->GetGridData();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABrickPlayerController::InstantMoveDown,1.f, true);//TODO Clear Timer

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
			SetGridFilledCell(CubesCoordinates);
			SpawnNewBrick();
		}
			
	}
	 
}

void ABrickPlayerController::GetOnceGridData()
{
	if (UpdatedGridData.Num() == 0)
	{
		UpdatedGridData = Brick->GetGridData();

	}
}

void ABrickPlayerController::CheckForDownSide(TArray<FVector> &CubesCoordinates)
{
	for (int32 i = 0; i < CubesCoordinates.Num(); i++)
	{
		int32 IndexI = Brick->GetCubeIndex(CubesCoordinates[i])[0];
		int32 IndexJ = Brick->GetCubeIndex(CubesCoordinates[i])[1];
		if (IndexI < 19)
		{
			if (UpdatedGridData[IndexI * 10 + IndexJ + 10].isFilled)
			{
				IsAbleMoveDown = false;
				UE_LOG(LogTemp, Warning, TEXT("Not able move down"))
			}
		}
	}
}

void ABrickPlayerController::SetGridFilledCell(TArray<FVector> &CubesCoordinates)
{
	for (int32 i = 0; i < CubesCoordinates.Num(); i++)
	{
		int32 IndexI = Brick->GetCubeIndex(CubesCoordinates[i])[0];
		int32 IndexJ = Brick->GetCubeIndex(CubesCoordinates[i])[1];
		UpdatedGridData[IndexI * 10 + IndexJ].isFilled = true;
	}
}

void ABrickPlayerController::SpawnNewBrick()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = Instigator;
	ABrick* NewBrick = GetWorld()->SpawnActor<ABrick>(
		BrickSome,
		FVector(0.f, 1000.f, 140.2),
		FRotator::ZeroRotator,
		SpawnParams
		);
	Brick = Cast<ABrick>(GetPawn());
	IsAbleMoveDown = true;
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

float ABrickPlayerController::GetUnitLength()
{
	return Brick->GetUnitLength();
}

FVector2D ABrickPlayerController::GetGridMaxXY()
{
	return Brick->GetGridMaxXY();
}

FVector2D ABrickPlayerController::GetGridMinXY()
{
	return Brick->GetGridMinXY();
}



