#pragma once
#include "MessageTypes.h"

struct PyramidMessageTypes : MessageTypes {

	static MessageType UPDATE_FREQUENCY = 20;
	static MessageType UPDATE_PYRAMID_HEIGHT = 21;
	static MessageType FIRE_PROJECTILE = 22;
};
