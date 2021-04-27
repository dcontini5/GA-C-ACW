#pragma once

typedef const int MessageType;

struct MessageTypes {

	static MessageType COLLISION = 1;

	static MessageType PLAYER_CONNECTED = 4;
	
	static MessageType ADDED_COMPONENT = 8;
	static MessageType REMOVED_COMPONENT = 9;
	static MessageType RESET_SCENE = 10;
	
};