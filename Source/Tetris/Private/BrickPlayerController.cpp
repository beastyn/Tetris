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
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABrickPlayerController::InstantMoveDown, 1.f, true);//TODO Clear Timer
	

}

void ABrickPlayerController::InstantMoveDown() //TODO need refactoring
{
	
	if (Brick) //TODO use Grid data
		
	{
	   	
		auto MinYCoordinate = GetMinYCoordinate(GetCubesCoordinates());
		bool AlmostZero = FMath::IsNearlyEqual(MinYCoordinate, -900, 0.01f);
		//UE_LOG(LogTemp, Warning, TEXT("Min Y coordinate is: %f"), MinYCoordinate)
		//UE_LOG(LogTemp, Warning, TEXT("Min Y coordinate is: %s"), AlmostZero ? TEXT("true") : TEXT("false"))
		if (!AlmostZero)
		{
		
			Brick->AddActorLocalOffset(FVector(0, -100, 0));
			
		}
		else //TODO maybe make spawner component instead
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			ABrick* NewBrick = GetWorld()->SpawnActor<ABrick>(
				BrickSome,
				FVector(0.f, 0.f, 140.2),
				FRotator::ZeroRotator,
				SpawnParams
				);
			Brick = Cast<ABrick>(GetPawn());
	
		}
			
	}
	 
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