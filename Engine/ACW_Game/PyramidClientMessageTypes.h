#pragma once
#include "MessageTypes.h"

struct PyramidClientMessageTypes : MessageTypes{

	static MessageType UPDATE_FREQUENCY = 20;
	static MessageType UPDATE_PYRAMID_HEIGHT = 21;
};
