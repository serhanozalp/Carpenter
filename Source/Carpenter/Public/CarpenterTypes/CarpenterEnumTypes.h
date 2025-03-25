#pragma once

UENUM()
enum class ECarpenterItemState : uint8
{
	Initial,
	AttachedToWorkbench,
	PickedUp,
	Dropped
};