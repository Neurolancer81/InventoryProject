
#include "InventoryManagement/FastArray/INV_FastArray.h"

#include "ToolMenusEditor.h"
#include "InventoryManagement/Components/INV_InventoryComponent.h"
#include "Items/INV_InventoryItem.h"


TArray<UINV_InventoryItem*> FINV_InventoryFastArray::GetAllItems()
{
	TArray<UINV_InventoryItem*> AllItems;
	AllItems.Reserve(Entries.Num());
	for (const auto& Entry: Entries)
	{
		if (!IsValid(Entry.Item)) continue;
		AllItems.Add(Entry.Item);
			
	}
	return AllItems;
	
}

void FINV_InventoryFastArray::PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize)
{
	UINV_InventoryComponent* InventoryComponent = Cast<UINV_InventoryComponent>(OwnerComponent);
	if (!IsValid(InventoryComponent)) return;
	for (int32 Index: RemovedIndices)
	{
		InventoryComponent->OnItemRemoved.Broadcast(Entries[Index].Item);
	}
}

void FINV_InventoryFastArray::PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize)
{
	UINV_InventoryComponent* InventoryComponent = Cast<UINV_InventoryComponent>(OwnerComponent);
	if (!IsValid(InventoryComponent)) return;
	for (int32 Index: AddedIndices)
	{
		InventoryComponent->OnItemRemoved.Broadcast(Entries[Index].Item);
	}
}

UINV_InventoryItem* FINV_InventoryFastArray::AddEntry(UINV_ItemComponent* ItemComponent)
{
	//TODO: Implement when ItemComponent is more fleshed out.
	return nullptr;
}

UINV_InventoryItem* FINV_InventoryFastArray::AddEntry(UINV_InventoryItem* Item)
{
	check(OwnerComponent);
	AActor* OwningActor = OwnerComponent->GetOwner();
	check(OwningActor->HasAuthority());

	FINV_InventoryEntry& NewEntry = Entries.AddDefaulted_GetRef();
	NewEntry.Item = Item;

	MarkItemDirty(NewEntry);

	return Item;
	
}

void FINV_InventoryFastArray::RemoveEntry(UINV_InventoryItem* Item)
{
	for (auto EntryIt = Entries.CreateIterator(); EntryIt; ++EntryIt)
	{
		FINV_InventoryEntry& Entry = *EntryIt;
		if (Entry.Item == Item)
		{
			EntryIt.RemoveCurrent();
			MarkArrayDirty();
		}
	}	
	
}
