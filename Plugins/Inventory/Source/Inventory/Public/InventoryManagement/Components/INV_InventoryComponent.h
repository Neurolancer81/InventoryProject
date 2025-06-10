// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "INV_InventoryComponent.generated.h"


class UINV_ItemComponent;
class UINV_InventoryBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryItemChange, UINV_InventoryItem*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNoRoomInInventory);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class INVENTORY_API UINV_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UINV_InventoryComponent();

	UFUNCTION(BlueprintCallable, Category = "Inventory", BlueprintAuthorityOnly)
	void TryAddItem(UINV_ItemComponent* ItemComponent);

	void ToggleInventoryMenu();

	FInventoryItemChange OnItemAdded;
	FInventoryItemChange OnItemRemoved;
	FNoRoomInInventory NoRoomInInventory;

protected:
	
	virtual void BeginPlay() override;

private:
	void ConstructInventory();

	TWeakObjectPtr<APlayerController> OwningPlayerController;

	UPROPERTY()
	TObjectPtr<UINV_InventoryBase> InventoryMenu;
	
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TSubclassOf<UINV_InventoryBase> InventoryMenuClass;

	bool bInventoryMenuOpen = false;
	void InventoryMenuOpen();
	void InventoryMenuClose();
	
};
