﻿#pragma once
#include <memory>
#include "Core/HAL/PlatformType.h"
#include "Core/Container/Name.h"
#include "Object/Class/Class.h"
#include "Cast.h"

// TODO: RTTI 구현하면 enable_shared_from_this 제거
class UObject : public std::enable_shared_from_this<UObject>
{
	friend class FObjectFactory;

	uint32 UUID = 0;
	uint32 InternalIndex; // Index of GUObjectArray

public:
	UObject();
	virtual ~UObject();
	FName Name;

public:
	uint32 GetUUID() const { return UUID; }
	uint32 GetInternalIndex() const { return InternalIndex; }

public:
	FORCEINLINE virtual UClass* GetClass() const
	{
		return StaticClass();
	}

	static UClass* StaticClass(); // 각 클래스마다 하나씩
	FORCEINLINE bool IsA(UClass* TargetClass) const
	{
		UClass* CurrentClass = GetClass();
		while (CurrentClass) {
			if (CurrentClass == TargetClass)
				return true;
			CurrentClass = CurrentClass->SuperClass;
		}
		return false;
	}
	FORCEINLINE virtual const char* GetTypeName() { return "UObject"; }
};