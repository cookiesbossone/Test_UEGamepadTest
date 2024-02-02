// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GamepadDetectActor.generated.h"

UCLASS()
class TESTPROJECTUE4_API AGamepadDetectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGamepadDetectActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Gamepad Events")
	bool IsGamepadConnected();

	void ListenForGamepadChange(bool isConnected, int32 useless, int32 uselessIndex);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Gamepad Events") 
	void OnGamepadConnection();



};
