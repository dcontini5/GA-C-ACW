#pragma once

typedef const int NetworkMessageType;

struct NetworkMessageTypes {

	static NetworkMessageType DISCONNECT = 0;
	
	static NetworkMessageType GAMEOBJECT_UPDATE = 1;
	
	static NetworkMessageType PLAYER_UPDATE = 2;
	
	static NetworkMessageType SCENE_RESET = 3;

	static NetworkMessageType SERVER_FREQUENCY = 4;

	static NetworkMessageType PYRAMID_HEIGHT = 5;

	static NetworkMessageType PROJECTILE_FIRED = 6;
	
	static NetworkMessageType SPAWN_OBJECT = 7;
	
};
