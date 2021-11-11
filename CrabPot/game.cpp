#include "includes.h"

uintptr_t Game::GameAssembly() {
	return (uintptr_t)GetModuleHandleA("GameAssembly.dll");
}

void Game::FastPunch(bool toggle) {
	if (toggle)
		Internal::Patch((uintptr_t*)Game::FASTPUNCH_ADDR, (uintptr_t*)"\x80\x7B\x20\x44", 4);
	else
		Internal::Patch((uintptr_t*)Game::FASTPUNCH_ADDR, (uintptr_t*)"\x80\x7B\x20\x00", 4);
}
void Game::AlwaysSprint(bool toggle) {
	if (toggle)
		Internal::Patch((uintptr_t*)Game::ALWAYSSPRINT_ADDR, (uintptr_t*)"\x74\x11", 2);
	else
		Internal::Patch((uintptr_t*)Game::ALWAYSSPRINT_ADDR, (uintptr_t*)"\x75\x11", 2);
}
void Game::InfiniteJump(bool toggle) {
	if (toggle) 
		Internal::Patch((uintptr_t*)Game::INFJUMP_ADDR, (uintptr_t*)"\x90\x90", 2);
	else
		Internal::Patch((uintptr_t*)Game::INFJUMP_ADDR, (uintptr_t*)"\x74\x09", 2);

	Console::Log(std::to_string(Game::INFJUMP_ADDR));

}
void Game::MoonGravity(bool toggle) {
	if (toggle)
		Internal::Patch((uintptr_t*)Game::MOONGRAVITY_ADDR, (uintptr_t*)"\x90\x90\x90\x90\x90", 5);
	else
		Internal::Patch((uintptr_t*)Game::MOONGRAVITY_ADDR, (uintptr_t*)"\xE8\x83\x43\xCD\xFF", 5);
}
void Game::NoCameraShake(bool toggle) {
	if (toggle)
		Internal::Patch((uintptr_t*)Game::CAMERA_ADDR, (uintptr_t*)"\x90\x90\x90\x90\x90", 5);
	else
		Internal::Patch((uintptr_t*)Game::CAMERA_ADDR, (uintptr_t*)"\xE8\x7E\x07\x4E\x00", 5);
}