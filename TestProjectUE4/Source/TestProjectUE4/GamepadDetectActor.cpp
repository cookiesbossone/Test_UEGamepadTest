// Fill out your copyright notice in the Description page of Project Settings.

#include "GamepadDetectActor.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Windows/WindowsApplication.h"

#include "RawInput.h"
#include "RawInputFunctionLibrary.h"
#include "IInputDeviceModule.h"
#include "IInputDevice.h"
#include "GenericPlatform/GenericApplicationMessageHandler.h"

// Sets default values
AGamepadDetectActor::AGamepadDetectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FCoreDelegates::OnControllerConnectionChange.AddUObject(this, &AGamepadDetectActor::ListenForGamepadChange);
}

// Called when the game starts or when spawned
void AGamepadDetectActor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("AGamepadDetectActor::BeginPlay()"));

	IRawInput* RawInput = static_cast<IRawInput*>(static_cast<FRawInputPlugin*>(&FRawInputPlugin::Get())->GetRawInputDevice().Get());

	if (RawInput != nullptr) {
		RawInput->QueryConnectedDevices();
		OnGamepadConnection();
	}
}

// Called every frame
void AGamepadDetectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AGamepadDetectActor::IsGamepadConnected() 
{
	//bool isGamepadConneted = FWindowsApplication::GetWindowsApplication()->IsGamepadAttached();
	bool isGamepadConneted = false;
	FString str = isGamepadConneted ? "YES" : "No";

	UE_LOG(LogTemp, Log, TEXT("AGamepadDetectActor::IsGamepadConnected() : %s"), *str);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("IsGamepadConnected() : %s"), *str));

	return true;
}

void AGamepadDetectActor::ListenForGamepadChange(bool isConnected, int32 useless, int32 uselessIndex) 
{
	UE_LOG(LogTemp, Log, TEXT("AGamepadDetectActor::ListenForGamepadChange() : isConnected=%d, useless=%d, uselessIndex=%d"), isConnected?1:0, useless, uselessIndex);

	IRawInput* RawInput = static_cast<IRawInput*>(static_cast<FRawInputPlugin*>(&FRawInputPlugin::Get())->GetRawInputDevice().Get());

	RawInput->QueryConnectedDevices();
	OnGamepadConnection();
}

//void AGamepadDetectActor::OnGamepadConnection() 
//{
//
//}

