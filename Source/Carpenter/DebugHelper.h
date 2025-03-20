#pragma once

namespace Debug
{
	static void Print(const FString& Message, const FColor& Color = FColor::MakeRandomColor(), int32 InKey = -1)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(InKey, 7.0f, Color, Message);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
		}
	}
}