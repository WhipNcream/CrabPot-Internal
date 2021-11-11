#include "includes.h"
namespace settings {
    bool MoonGravity;
    bool InfiniteJump;
    bool FastPunch;
    bool NoCameraShake;
    bool AlwaysSprint;
};
void FirstInit(bool _) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(console, 7); // white

    Console::Log("Crabpot Version 1.0");
    Console::Log("----------------------------");
    if (_) {
        SetConsoleTextAttribute(console, 12);
        Console::Log("[F1] Moon Gravity");
        Console::Log("[F2] Always Sprint");
        Console::Log("[F3] Fast Punch");
        Console::Log("[F4] No Cam Shake");
        Console::Log("[F5] Infinite Jump");
        Console::Log("[F9] Exit Cheat");
        SetConsoleTextAttribute(console, 7);
    }
}
void PrintStatus(bool a1, bool a2, bool a3, bool a4, bool a5) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    FirstInit(false);
    if (a1) {
        SetConsoleTextAttribute(console, 10);
        Console::Log("[F1] Moon Gravity -> On");
    }
    else {
        SetConsoleTextAttribute(console, 12);
        Console::Log("[F1] Moon Gravity -> Off");

    }

    if (a2) {
        SetConsoleTextAttribute(console, 10);
        Console::Log("[F2] Always Sprint -> On");
    }
    else {
        SetConsoleTextAttribute(console, 12);
        Console::Log("[F2] Always Sprint -> Off");


    }

    if (a3) {
        SetConsoleTextAttribute(console, 10);
        Console::Log("[F3] Fast Punch -> On");

    }
    else {
        SetConsoleTextAttribute(console, 12);
        Console::Log("[F3] Fast Punch -> Off");


    }

    if (a4) {
        SetConsoleTextAttribute(console, 10);
        Console::Log("[F4] No Cam Shake -> On");

    }
    else {
        SetConsoleTextAttribute(console, 12);
        Console::Log("[F4] No Cam Shake -> Off");


    }

    if (a5) {
        SetConsoleTextAttribute(console, 10);
        Console::Log("[F5] Infinite Jump -> On");

    }
    else {
        SetConsoleTextAttribute(console, 12);
        Console::Log("[F5] Infinite Jump -> Off");


    }
    Console::Log("[F9] Exit Cheat");

}


void CheatMain() {
    settings::AlwaysSprint = false;
    settings::MoonGravity = false;
    settings::FastPunch = false;
    settings::NoCameraShake = false;
    settings::InfiniteJump = false;
    FirstInit(true);
}

void CheatMainLoop() {

    if (GetAsyncKeyState(VK_F1) & 1) {
        settings::MoonGravity = !settings::MoonGravity;
        Game::MoonGravity(settings::MoonGravity);
        Console::Clear();
        PrintStatus(settings::MoonGravity, settings::AlwaysSprint, settings::FastPunch, settings::NoCameraShake, settings::InfiniteJump);
    }
    if (GetAsyncKeyState(VK_F2) & 1) {
        settings::AlwaysSprint = !settings::AlwaysSprint;
        Game::AlwaysSprint(settings::AlwaysSprint);
        Console::Clear();
        PrintStatus(settings::MoonGravity, settings::AlwaysSprint, settings::FastPunch, settings::NoCameraShake, settings::InfiniteJump);
    }
    if (GetAsyncKeyState(VK_F3) & 1) {
        settings::FastPunch = !settings::FastPunch;
        Game::FastPunch(settings::FastPunch);
        Console::Clear();
        PrintStatus(settings::MoonGravity, settings::AlwaysSprint, settings::FastPunch, settings::NoCameraShake, settings::InfiniteJump);
    }
    if (GetAsyncKeyState(VK_F4) & 1) {
        settings::NoCameraShake = !settings::NoCameraShake;
        Game::NoCameraShake(settings::NoCameraShake);
        Console::Clear();
        PrintStatus(settings::MoonGravity, settings::AlwaysSprint, settings::FastPunch, settings::NoCameraShake, settings::InfiniteJump);
    }
    if (GetAsyncKeyState(VK_F5) & 1) {
        settings::InfiniteJump = !settings::InfiniteJump;
        Game::InfiniteJump(settings::InfiniteJump);
        Console::Clear();
        PrintStatus(settings::MoonGravity, settings::AlwaysSprint, settings::FastPunch, settings::NoCameraShake, settings::InfiniteJump);
    }
}