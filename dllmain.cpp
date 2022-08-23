#pragma once

//#define VERSION_3_5
//#define VERSION_4_1
//#define VERSION_4_5
//#define VERSION_5_21
#define VERSION_7_3

bool bRespawn = true;

#ifdef VERSION_3_5
#include "FortniteGame/SDKS/3_5/SDK.hpp"
#endif

#ifdef VERSION_4_1
#include "FortniteGame/SDKS/4_1/SDK.hpp"
#endif

#ifdef VERSION_4_5
#include "FortniteGame/SDKS/4_5/SDK.hpp"
#endif

#ifdef VERSION_5_21
#include "FortniteGame/SDKS/5_21/SDK.hpp"
#endif

#ifdef VERSION_7_3
#include "FortniteGame/SDKS/7_3/SDK.hpp"
#endif



#include "hooks.h"



#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include <d3d9.h>

#pragma comment(lib, "d3d9.lib")

static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp;

extern LRESULT ImGui_ImplDX9_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplDX9_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            ImGui_ImplDX9_InvalidateDeviceObjects();
            g_d3dpp.BackBufferWidth = LOWORD(lParam);
            g_d3dpp.BackBufferHeight = HIWORD(lParam);
            HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
            if (hr == D3DERR_INVALIDCALL)
                IM_ASSERT(0);
            ImGui_ImplDX9_CreateDeviceObjects();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}



void Main()
{
    AllocConsole();
    FILE* pFile;
    freopen_s(&pFile, "CONOUT$", "w", stdout);

    Functions::Initialize();

    printf("[+] Initializing android's 7.3\n");

    Abilities::Initialize();
    
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(void*&)Functions::NetDriver::TickFlush, Hooks::TickFlush);
    DetourAttach(&(void*&)Functions::LocalPlayer::SpawnPlayActor, Hooks::LocalPlayerSpawnPlayActor);
    DetourAttach(&(void*&)Functions::Engine::NetDebug, Hooks::NetDebug);
    DetourAttach(&(void*&)oProcessEvent, Hooks::ProcessEventHook);
    DetourTransactionCommit();

    printf("[+] Hooked Functions\n");

    
#ifdef VERSION_4_5
    std::vector<BYTE> patch = { 0xE9, 0x39, 0x02, 0x00, 0x00 };

    for (int i = 0; i < patch.size(); i++)
        *(BYTE*)(uintptr_t(GetModuleHandle(0)) + 0xAEC475 + i) = patch[i];
#endif
    






    Functions::GetEngine()->GameViewport->ViewportConsole = (UConsole*)GetGameplayStatics()->STATIC_SpawnObject(UConsole::StaticClass(), Functions::GetEngine()->GameViewport);


    for (int i = 0; i < ItemDefinitions::WeaponItemDefinitionArray.size(); i++)
        ItemDefinitions::WeaponItemDefinitionAddresses.push_back(FindObjectFast<UFortItemDefinition>(ItemDefinitions::WeaponItemDefinitionArray[i]));
    
    for (int i = 0; i < ItemDefinitions::ConsumableItemDefinitionArray.size(); i++)
        ItemDefinitions::ConsumableItemDefinitionAddresses.push_back(FindObjectFast<UFortItemDefinition>(ItemDefinitions::ConsumableItemDefinitionArray[i]));

    for (int i = 0; i < ItemDefinitions::AmmoItemDefinitionArray.size(); i++)
        ItemDefinitions::AmmoItemDefinitionAddresses.push_back(FindObjectFast<UFortItemDefinition>(ItemDefinitions::AmmoItemDefinitionArray[i]));

    for (int i = 0; i < ItemDefinitions::MaterialItemDefinitionArray.size(); i++)
        ItemDefinitions::MaterialItemDefinitionAddresses.push_back(FindObjectFast<UFortItemDefinition>(ItemDefinitions::MaterialItemDefinitionArray[i]));

    for (int i = 0; i < ItemDefinitions::TrapItemDefinitionArray.size(); i++)
        ItemDefinitions::TrapItemDefinitionAddresses.push_back(FindObjectFast<UFortItemDefinition>(ItemDefinitions::TrapItemDefinitionArray[i]));
    
    ItemDefinitions::Pickaxe = FindObjectFast<UFortItemDefinition>("/Game/Athena/Items/Weapons/WID_Harvest_Pickaxe_Celestial.WID_Harvest_Pickaxe_Celestial");

    printf("[+] Initialized Weapons\n");

    Sleep(2000);

    /*
    ((UKismetSystemLibrary*)UKismetSystemLibrary::StaticClass())->STATIC_ExecuteConsoleCommand(GetWorld(), L"open 1.1.1.1", nullptr);
    Sleep(1000);
    ((UKismetSystemLibrary*)UKismetSystemLibrary::StaticClass())->STATIC_ExecuteConsoleCommand(GetWorld(), L"open Athena_Terrain", nullptr);
    Sleep(15000);
    ((UKismetSystemLibrary*)UKismetSystemLibrary::StaticClass())->STATIC_ExecuteConsoleCommand(GetWorld(), L"open Frontend", nullptr);
    Sleep(10000);
    */
    Game::Start();

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    //DetourAttach(&(void*&)Functions::World::WelcomePlayer, Hooks::WelcomePlayer);
    DetourAttach(&(void*&)Functions::Actor::GetNetMode, Hooks::GetNetMode);
    DetourAttach(&(void*&)Functions::World::NotifyControlMessage, Hooks::World_NotifyControlMessage);
    DetourAttach(&(void*&)Functions::World::SpawnPlayActor, Hooks::SpawnPlayActor);
    DetourAttach(&(void*&)Functions::OnlineSession::KickPlayer, Hooks::KickPlayer);
    DetourAttach(&(void*&)Functions::GC::CollectGarbage, Hooks::CollectGarbage);
    DetourAttach(&(void*&)Functions::FortWeapon::OnReload, Hooks::OnReload);
    DetourTransactionCommit();



    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, LoadCursor(NULL, IDC_ARROW), NULL, NULL, L"MoonGS_Controller", NULL };
    RegisterClassEx(&wc);
    HWND hwnd = CreateWindowA("MoonGS_Controller", "MoonGS | Controller", WS_POPUP | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, 10, 10, 600, 400, NULL, NULL, wc.hInstance, NULL);

    // Initialize Direct3D
    LPDIRECT3D9 pD3D;
    if ((pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
    {
        UnregisterClassA("MoonGS_Controller", wc.hInstance);
        return;
    }
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

    // Create the D3DDevice
    if (pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
    {
        pD3D->Release();
        UnregisterClassA("MoonGS_Controller", wc.hInstance);
        return;
    }

    // Setup ImGui binding
    ImGui_ImplDX9_Init(hwnd, g_pd3dDevice);

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontDefault();

    // Main loop
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);

    ShowWindow(FindWindowA("UnrealWindow", "Fortnite  "), SW_HIDE);

    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }
        ImGui_ImplDX9_NewFrame();
        //Colors();

        static bool menu_opened = true;

        if (GetAsyncKeyState(VK_INSERT) & 1)
            menu_opened = !menu_opened;

        if (menu_opened && bListening/* && HostBeacon*/)
        {
            ImGui::Begin("Main", nullptr, ImVec2(600, 400), 1.0f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
            {
                auto GameState = (AFortGameStateAthena*)(GetWorld()->GameState);

                auto ClientConnections = GetWorld()->NetDriver->ClientConnections;//HostBeacon->NetDriver->ClientConnections;

                if (GameState->GamePhase < EAthenaGamePhase::Aircraft)
                {
                    if (ImGui::Button("Start Aircraft"))
                    {
                        GameState->bGameModeWillSkipAircraft = false;
                        GameState->AircraftStartTime = 0;
                        GameState->WarmupCountdownEndTime = 0;

                        GetKismetSystem()->STATIC_ExecuteConsoleCommand(GetWorld(), L"startaircraft", nullptr);
                    }
                }

                if (ImGui::Button("Spawn FloorLoot (nowork 4.1)"))
                {
                    CreateThread(0, 0, SummonFloorLoot, 0, 0, 0);
                    printf("Spawning Floor Loot!\n");
                }

                if (ImGui::Button("Spawn Random Weapon to players"))
                {
                    for (int i = 0; i < ClientConnections.Num(); i++)
                    {
                        auto Controller = (AFortPlayerControllerAthena*)ClientConnections[i]->PlayerController;

                        if (!Controller || Controller->PlayerState->bIsSpectator)
                            continue;

                        auto Location = Controller->Pawn->K2_GetActorLocation();
                        SummonPickupFromChest(ItemDefinitions::GetWeapon(true), 1, FVector(Location.X, Location.Y, Location.Z + 100));
                    }
                }

                if (ImGui::Button("Teleport everyone in the sky"))
                {
                    for (int i = 0; i < ClientConnections.Num(); i++)
                    {
                        auto Controller = (AFortPlayerControllerAthena*)ClientConnections[i]->PlayerController;

                        if (!Controller || Controller->PlayerState->bIsSpectator)
                            continue;

                        auto Location = Controller->Pawn->K2_GetActorLocation();

                        //Pawn->LaunchCharacter(FVector(PawnLocation.X, PawnLocation.Y, 50000), false, false);
                        FHitResult tmp;
                        Controller->Pawn->K2_SetActorLocation(FVector(Location.X, Location.Y, 50000), true, true, &tmp);
                    }
                }

                if (ImGui::Button("Kick Everyone"))
                {
                    for (int i = 0; i < ClientConnections.Num(); i++)
                    {
                        auto Controller = (AFortPlayerControllerAthena*)ClientConnections[i]->PlayerController;
                        if (!Controller) continue;

                        KickController(Controller, L"A fanculo bozo");
                    }
                }


                ImGui::End();
            }
        }

        // Rendering
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, false);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);

        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            g_pd3dDevice->EndScene();
        }
        g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
    }

    ImGui_ImplDX9_Shutdown();
    if (g_pd3dDevice) g_pd3dDevice->Release();
    if (pD3D) pD3D->Release();
    UnregisterClassA("MoonGS_Controller", wc.hInstance);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
        std::thread(Main).detach();

    return true;
}
