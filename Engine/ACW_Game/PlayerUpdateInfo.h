#pragma once
#include <ext/scalar_uint_sized.hpp>

struct PlayerUpdateInfo {

	bool hasUpdated{ false };
	bool sceneReset{ false };
	uint8_t hasShot{ 0 };
	
};
