#include "includes.h"

namespace Game {
	uintptr_t GameAssembly();
	void FastPunch(bool toggle);
	void AlwaysSprint(bool toggle);
	void InfiniteJump(bool toggle);
	void MoonGravity(bool toggle);
	void NoCameraShake(bool toggle);
	const uintptr_t CAMERA_ADDR = GameAssembly() + 0xE4B48D;
	const uintptr_t FASTPUNCH_ADDR = GameAssembly() + 0xE4B451;
	const uintptr_t ALWAYSSPRINT_ADDR = GameAssembly() + 0xC09DC1;
	const uintptr_t INFJUMP_ADDR = GameAssembly() + 0xC052DC;
	const uintptr_t MOONGRAVITY_ADDR = GameAssembly() + 0xC0A068;
}