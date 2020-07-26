#pragma once
#include <iostream>
#include <winsock2.h>

#include "Peer.h"

class Socket {

	//Structors
public:
	Socket(const Socket&);
	Socket(Socket&&); //exchange members here;
	~Socket(){

		closesocket(mSocket);
		WSACleanup();

	};
	
protected:
	Socket() : mSocket(INVALID_SOCKET) {}
	Socket(SOCKET& const pSocket) : mSocket(pSocket) {}

	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:

	void Init(const int& pMinVersion, const int& pMaxVersion);
	void Create();
	// Private Functions
private:

	//Operators
public:
	Socket& operator=(const Socket& pOther) = delete;

	Socket& operator=(const Socket&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
protected:

	SOCKET mSocket;
	
};
