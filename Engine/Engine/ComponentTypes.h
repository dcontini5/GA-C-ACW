#pragma once

typedef const int ComponentType;

struct ComponentTypes {
	
	static ComponentType PHYSICS = 1;
	static ComponentType RENDER = 2;
	static ComponentType COLLISION = 3;
	static ComponentType NETWORKING = 4;
	static ComponentType PLAYER_CLIENT = 5;
	static ComponentType INPUT_STATE = 6;
	
};
