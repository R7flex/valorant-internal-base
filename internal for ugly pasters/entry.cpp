#include <Windows.h>
#include <cstdio>
#include "sdk.h"
#include "decryption.h"
#include "hook.h"
using PostRenderHook = void(*)(uintptr_t _this, UCanvas* canvas);
PostRenderHook pRender = 0;
void PostRender(uintptr_t _this, UCanvas* canvas)
{
	if (!canvas)
		return PostRender(_this, canvas);
	UWorld* World = Memory::ReadStub<UWorld*>(_this + 0x80);
	APlayerController* MyController = ShooterGameBlueprints::GetFirstLocalPlayerController(World);
	AShooterCharacter* MyShooter = MyController->GetShooterCharacter();
	TArray<AShooterCharacter*> Actors = ShooterGameBlueprints::FindAllShooterCharactersWithAlliance(World, MyShooter, EAresAlliance::Alliance_Any, false, true);
	for (int Index = 0; Index < Actors.Num(); Index++)
	{
		if (!Actors.IsValidIndex(Index))
			continue;

		AShooterCharacter* Actor = Actors[Index];

		if (Actor == MyShooter)
			continue;

		if (BaseTeamComponent::IsAlly(Actor, MyShooter))
			continue;

		USkeletalMeshComponent* Mesh = Actor->GetPawnMesh();
		bool IsAlive = Actor->IsAlive();

		if (Mesh && IsAlive)
		{

			Mesh->SetAresOutlineMode(EAresOutlineMode::AlwaysOutline, true);
			AresOutlineRendering::SetOutlineColorsForRender(World, { 0,7,7,11 }, { 1, 1, 1, 1 });

		}
	}

	return pRender(_this, canvas);
}

void Init()
{
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	VALORANT::Module = (uintptr_t)GetModuleHandleA(0);
	uintptr_t WorldKey = *(uintptr_t*)(VALORANT::Module + Offsets::Key);
	State StateKey = *(State*)(VALORANT::Module + Offsets::State);
	uintptr_t UWorldXOR = Decryption::Decrypt_UWorld(WorldKey, (uintptr_t*)&StateKey);
	UWorld* UWorldClass = Memory::ReadStub<UWorld*>(UWorldXOR);
	UGameInstance* GameInstance = Memory::ReadStub<UGameInstance*>((uintptr_t)UWorldClass + 0x1A0);
	ULocalPlayer* LocalPlayers = Memory::ReadStub<ULocalPlayer*>((uintptr_t)GameInstance + 0x40); //this is tarray but im paster lol
	ULocalPlayer* LocalPlayer = Memory::ReadStub<ULocalPlayer*>((uintptr_t)LocalPlayers); //
	APlayerController* LocalController = Memory::ReadStub<APlayerController*>((uintptr_t)LocalPlayer + 0x38);
	uintptr_t ViewportClient = Memory::ReadStub<uintptr_t>((uintptr_t)LocalPlayer + 0x78);
	Hook::VMT((void*)ViewportClient, PostRender, 0x68, (void**)&pRender);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		Init();
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}