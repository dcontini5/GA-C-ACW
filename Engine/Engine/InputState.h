#pragma once
#include <vec2.hpp>

struct InputState {

	short key{ -1 };
	int8_t wheelRot{0};
	bool keyState{ false };
	glm::vec2 mouseMov{ 0.f, 0.f };
	

};
