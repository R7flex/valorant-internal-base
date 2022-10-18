#pragma once
#include "memory.h"
#include "unrealengine.h"
class UObject
{
public:
	static UObject* StaticFindObject(UObject* Class, UObject* InOuter, const wchar_t* Name, bool ExactClass)
	{
		static uintptr_t StaticFindObjectAddress = VALORANT::Module + Offsets::StaticFindObject;

		auto StaticFindObjectFN = reinterpret_cast<UObject * (__fastcall*)(UObject*, UObject*, const wchar_t*, bool)>(StaticFindObjectAddress);

		return StaticFindObjectFN(Class, InOuter, Name, ExactClass);
	}
	static void ProcessEvent(void* class_, UObject* function, void* params)
	{
		reinterpret_cast<void (*)(void*, UObject*, void*)>(VALORANT::Module + Offsets::ProcessEvent)(class_, function, params);
	}
};

struct UWorld
{

};

struct UCanvas
{

};

struct UGameInstance
{

};

struct ULocalPlayer
{

};

struct USkeletalMeshComponent
{
	void SetAresOutlineMode(EAresOutlineMode Mode, bool bPropagateToChildren)
	{
		UObject* Function = UObject::StaticFindObject(nullptr, nullptr, L"Engine.MeshComponent.SetAresOutlineMode", false);
		if (!Function)
		{
			return;
		}
		struct
		{
			EAresOutlineMode Mode;
			bool bPropagateToChildren;
		}Parameters;
		Parameters.Mode = Mode;
		Parameters.bPropagateToChildren = bPropagateToChildren;
		Function->ProcessEvent(this, Function, &Parameters);
	}
};

struct AShooterCharacter
{
	USkeletalMeshComponent* GetPawnMesh()
	{
		UObject* Function = UObject::StaticFindObject(nullptr, nullptr, L"ShooterGame.ShooterCharacter.GetPawnMesh", false);
		if (!Function)
		{
			return 0;
		}
		struct
		{
			USkeletalMeshComponent* Out;
		}Parameters;
		Function->ProcessEvent(this, Function, &Parameters);
		return Parameters.Out;
	}
	bool IsAlive()
	{
		UObject* Function = UObject::StaticFindObject(nullptr, nullptr, L"ShooterGame.ShooterCharacter.IsAlive", false);
		if (!Function)
		{
			return 0;
		}
		struct
		{
			bool Out;
		}Parameters;
		Function->ProcessEvent(this, Function, &Parameters);
		return Parameters.Out;
	}
};

struct APlayerController
{
	AShooterCharacter* GetShooterCharacter()
	{
		UObject* Function = UObject::StaticFindObject(nullptr, nullptr, L"ShooterGame.AresPlayerController.GetShooterCharacter", false);
		if (!Function)
		{
			return 0;
		}
		struct
		{
			AShooterCharacter* Out;
		}Parameters;
		Function->ProcessEvent(this, Function, &Parameters);
		return Parameters.Out;
	}
};

namespace ShooterGameBlueprints
{
	UObject* Static_Class()
	{
		return UObject::StaticFindObject(nullptr, nullptr, L"ShooterGame.Default__ShooterBlueprintLibrary", false);
	}

	APlayerController* GetFirstLocalPlayerController(UWorld* WorldContextObject)
	{
		UObject* Function = UObject::StaticFindObject(nullptr, nullptr, L"ShooterGame.ShooterBlueprintLibrary.GetFirstLocalPlayerController", false);
		if (!Function)
		{
			return 0;
		}
		struct
		{
			UWorld* WorldContextObject;
			APlayerController* Out;
		}Parameters;
		Parameters.WorldContextObject = WorldContextObject;
		Function->ProcessEvent(Static_Class(), Function, &Parameters);
		return Parameters.Out;
	}
	TArray<AShooterCharacter*> FindAllShooterCharactersWithAlliance(UWorld* WorldContextObject, AShooterCharacter* LocalViewer, EAresAlliance Alliance, bool OnlyPlayerControlled, bool OnlyAlivePlayers)
	{
		UObject* Function = UObject::StaticFindObject(nullptr, nullptr, L"ShooterGame.ShooterBlueprintLibrary.FindAllShooterCharactersWithAlliance", false);
		struct
		{
			UWorld* WorldContextObject;
			AShooterCharacter* LocalViewer;
			EAresAlliance Alliance;
			bool OnlyPlayerControlled;
			bool OnlyAlivePlayers;
			TArray<AShooterCharacter*> Out;
		}Parameters;
		Parameters.WorldContextObject = WorldContextObject;
		Parameters.LocalViewer = LocalViewer;
		Parameters.Alliance = Alliance;
		Parameters.OnlyPlayerControlled = OnlyPlayerControlled;
		Parameters.OnlyAlivePlayers = OnlyAlivePlayers;
		Function->ProcessEvent(Static_Class(), Function, &Parameters);
		return Parameters.Out;
	}
}

namespace AresOutlineRendering
{
	UObject* Static_Class()
	{
		return UObject::StaticFindObject(nullptr, nullptr, L"Renderer.Default__AresOutlineRendering", false);
	}

	void SetOutlineColorsForRender(UWorld* WorldContextObject, FLinearColor AllyColor, FLinearColor EnemyColor)
	{
		UObject* Function = UObject::StaticFindObject(nullptr, nullptr, L"Renderer.AresOutlineRendering.SetOutlineColorsForRender", false);
		if (!Function)
		{
			return;
		}
		struct {
			UWorld* WorldContextObject;
			FLinearColor AllyColor;
			FLinearColor EnemyColor;
		}Parameters;
		Parameters.WorldContextObject = WorldContextObject;
		Parameters.AllyColor = AllyColor;
		Parameters.EnemyColor = EnemyColor;
		Function->ProcessEvent(Static_Class(), Function, &Parameters);
	}
}

namespace BaseTeamComponent
{
	UObject* Static_Class()
	{
		return UObject::StaticFindObject(nullptr, nullptr, L"ShooterGame.Default__BaseTeamComponent", false);
	}

	bool IsAlly(AShooterCharacter* Enemy, AShooterCharacter* Self)
	{
		UObject* Function = UObject::StaticFindObject(nullptr, nullptr, L"ShooterGame.BaseTeamComponent.IsAlly", false);
		struct {
			AShooterCharacter* Enemy;
			AShooterCharacter* Self;
			bool ReturnValue;
		}Parameters;
		Parameters.Enemy = Enemy;
		Parameters.Self = Self;
		Function->ProcessEvent(Static_Class(), Function, &Parameters);
		return Parameters.ReturnValue;
	}
}