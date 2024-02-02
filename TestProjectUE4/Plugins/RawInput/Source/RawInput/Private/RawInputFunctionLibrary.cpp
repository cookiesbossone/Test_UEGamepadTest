// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "RawInputFunctionLibrary.h"
#if PLATFORM_WINDOWS
	#include "Windows/RawInputWindows.h"
#endif
#include "Kismet/KismetSystemLibrary.h"

TArray<FRegisteredDeviceInfo> URawInputFunctionLibrary::GetRegisteredDevices()
{
	TArray<FRegisteredDeviceInfo> RegisteredDevices;
	UE_LOG(LogTemp, Log, TEXT("URawInputFunctionLibrary::GetRegisteredDevices() : Enter"));

#if PLATFORM_WINDOWS
	FRawInputWindows* RawInput = static_cast<FRawInputWindows*>(static_cast<FRawInputPlugin*>(&FRawInputPlugin::Get())->GetRawInputDevice().Get());

	UE_LOG(LogTemp, Log, TEXT("URawInputFunctionLibrary::GetRegisteredDevices() RawInput->RegisteredDeviceList.Num() = %d"), RawInput->RegisteredDeviceList.Num());
	RegisteredDevices.Reserve(RawInput->RegisteredDeviceList.Num());
	for (const TPair<int32, FRawWindowsDeviceEntry>& RegisteredDevice : RawInput->RegisteredDeviceList)
	{
		// UE_LOG(LogTemp, Log, TEXT("URawInputFunctionLibrary::GetRegisteredDevices() For loop device : Name=%s, VID=%d, PID=%d"), *RegisteredDevice.Value.DeviceData.DeviceName, RegisteredDevice.Value.DeviceData.VenderID, RegisteredDevice.Value.DeviceData.ProductID);
		const FRawWindowsDeviceEntry& DeviceEntry = RegisteredDevice.Value;
		if (DeviceEntry.bIsConnected)
		{
			RegisteredDevices.Add(RawInput->GetDeviceInfo(RegisteredDevice.Key));
			UE_LOG(LogTemp, Log, TEXT("URawInputFunctionLibrary::GetRegisteredDevices() Add device : %s"), *RegisteredDevice.Value.DeviceData.DeviceName);
		}
	}

#endif

	return RegisteredDevices;
}