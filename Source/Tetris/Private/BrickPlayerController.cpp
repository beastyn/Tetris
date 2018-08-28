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

void ABrickPlayerController::Tick(float DeltaTime)
{

		UE_LOG(LogTemp, Warning, TEXT("Camera View Target: %s"), *(GetPawn()->GetName()))
	
}
void ABrickPlayerController::BeginPlay()
{
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABrickPlayerController::InstantMoveDown, 1.f, true);//TODO Clear Timer
	

}

void ABrickPlayerController::InstantMoveDown()
{
	Brick = Cast<ABrick>(GetPawn());
	
	if (Brick)
		
	{
		//find clamp values for bottom border
		auto RelativeCubesCoordinates = Brick->GetCubesCoordinates();
		auto MinYCoordinate = Brick->GetMinYCoordinate(RelativeCubesCoordinates);
	//	UE_LOG(LogTemp, Warning, TEXT("Min Y coordinate is: %f"), MinYCoordinate)
		bool AlmostZero = FMath::IsNearlyEqual(MinYCoordinate, -900, 0.01f);
		//UE_LOG(LogTemp, Warning, TEXT("Min Y coordinate is: %s"), AlmostZero ? TEXT("true") : TEXT("false"))
		if (!AlmostZero)
		{
		
			Brick->AddActorLocalOffset(FVector(0, -100, 0));
			
		}
		else
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
	
		}
			
	}
	 
}