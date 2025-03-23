#pragma once

UENUM()
enum class ECarpenterItemState : uint8
{
	None,
	Initial,
	PickedUp,
	Dropped
};