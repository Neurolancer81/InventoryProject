// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/INV_PlayerController.h"
#include "Inventory.h"

void AINV_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogInventory, Log, TEXT("AINV_PlayerController::BeginPlay"));	
}
