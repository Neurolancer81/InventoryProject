// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/HUD/INV_InfoMessage.h"

#include "Components/TextBlock.h"

void UINV_InfoMessage::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InfoText->SetText(FText::GetEmpty());
	MessageHide();
}

void UINV_InfoMessage::SetMessageText(const FText& Message)
{
	InfoText->SetText(Message);

	if (!bIsMessageActive)
	{
		MessageShow();
	}
	bIsMessageActive = true;

	GetWorld()->GetTimerManager().SetTimer(MessageTimer,
		[this]()
		{
			MessageHide();
			bIsMessageActive = false;			
		},
		MessageLifeTime,
		false);
}
