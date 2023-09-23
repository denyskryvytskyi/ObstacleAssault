// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
//UE_DISABLE_OPTIMIZATION_SHIP
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	FString str = "test";

	UE_LOG(LogTemp, Warning, TEXT("Configured moved distances: %f"), MaxMoveDistance);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
    RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
    const FVector CurrentLocation = GetActorLocation();
        const FVector NewLocation = CurrentLocation + MoveVelocity * DeltaTime;
    SetActorLocation(NewLocation);

    if (ShouldPlatformReturn(NewLocation)) {
        const FVector CurrentMoveDirection = MoveVelocity.GetSafeNormal();
        StartLocation = StartLocation + CurrentMoveDirection * MaxMoveDistance;
        MoveVelocity = -MoveVelocity;
    }
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
    AddActorLocalRotation(RotationVelocity * DeltaTime);
}

bool AMovingPlatform::ShouldPlatformReturn(const FVector& NewLocation) const
{
    const float MovedDistance = FVector::Dist(NewLocation, StartLocation);
    return MovedDistance > MaxMoveDistance;
}

