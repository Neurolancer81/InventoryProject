// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "INV_InfoMessage.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORY_API UINV_InfoMessage : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent, Category="Inventory")
	void MessageShow();

	UFUNCTION(BlueprintImplementableEvent, Category="Inventory")
	void MessageHide();

	void SetMessageText(const FText& Message);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> InfoText;

	UPROPERTY(EditAnywhere, Category="Inventory")
	float MessageLifeTime{3.f};

	FTimerHandle MessageTimer;
	bool bIsMessageActive{false};
};
