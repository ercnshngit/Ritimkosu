// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "RitimTile.h"
#include "RitimkosuGameModeBase.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(FPSCameraComponent != nullptr);

	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));

	FPSCameraComponent->bUsePawnControlRotation = true;

	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	check(FPSMesh != nullptr);

	FPSMesh->SetOnlyOwnerSee(true);

	FPSMesh->SetupAttachment(FPSCameraComponent);

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	MovementPtr =  Cast<UCharacterMovementComponent>(GetCharacterMovement());
	check(MovementPtr != nullptr);

	MovementPtr->MaxWalkSpeed = DefaultSpeed;

	GameMode = Cast<ARitimkosuGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if(GameMode->bIsPlayerDeadRecently)
	{
		Bullet = 0;
	}
	else
	{
		Bullet = 2;
	}
	
	
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::StopJump);	
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::PullTrigger);	
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &APlayerCharacter::StartRun);	
	PlayerInputComponent->BindAction("Run", IE_Released, this, &APlayerCharacter::StopRun);	



}

void APlayerCharacter::MoveForward(float Value) 
{
	AddMovementInput(GetActorForwardVector() * Value);	
	
}

void APlayerCharacter::MoveRight(float Value) 
{
	AddMovementInput(GetActorRightVector() * Value);	

}

void APlayerCharacter::StartJump() 
{
	bPressedJump = true;
}

void APlayerCharacter::StopJump() 
{
	bPressedJump = false;	
}

void APlayerCharacter::StartRun() 
{
	MovementPtr->MaxWalkSpeed = RunSpeed;

}

void APlayerCharacter::StopRun() 
{
	MovementPtr->MaxWalkSpeed = DefaultSpeed;

}

void APlayerCharacter::PullTrigger() 
{


	if(Bullet >= 1)
	{
		
		FVector Location;
		FRotator Rotation;
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Location, Rotation);

		FVector End = Location + Rotation.Vector() * MaxRange;


		FHitResult Hit;
		FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("Trace")), true, this);
		ECollisionChannel Channel = ECC_WorldStatic;


		bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, Channel, TraceParams);
		if (bSuccess)
		{

			UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, FPSMesh, TEXT("Muzzle"));
			UGameplayStatics::PlaySound2D(GetWorld(), FireSound);


			FRotator ShotDirection = Rotation.GetInverse();
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection);

			AActor* ActorHit = Hit.GetActor();

			if(ActorHit->ActorHasTag(FName(TEXT("Ritim"))))
			{	
				Bullet -= 1;

				ARitimTile* RitimTile = Cast<ARitimTile>(ActorHit);

				RitimTile->ActivateTile();
			}

		}
	}else{

		UGameplayStatics::PlaySound2D(GetWorld(), BosSound);

	}
	
	PullTriggerBP();

	





	// if(ActorHit->ActorHasTag(FName(TEXT("Paper"))))
	// {
	// 			FName PropName = TEXT("bPenActive");
	// 			FBoolProperty* BoolProp = FindField<FBoolProperty>(ActorHit->GetClass(), PropName);
	// 			if (BoolProp != NULL)
	// 			{
	// 				BoolProp->SetPropertyValue_InContainer(ActorHit, false);

	// 			}
	// }

}