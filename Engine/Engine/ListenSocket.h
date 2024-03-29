﻿#pragma once
#include "Socket.h"

class ListenSocket : public Socket {

	//Structors
public:
	ListenSocket() : Socket() {};
	ListenSocket(const ListenSocket&);
	ListenSocket(ListenSocket&&); //exchange members here;
	~ListenSocket() = default;
	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:
	
	SOCKET Listen();
	void Listen(SOCKET& pSocket, sockaddr_in& pAddress, int& pAddressSize);
	
	// Private Functions
private:

	//Operators
public:
	ListenSocket& operator=(const ListenSocket& pOther) = delete;

	ListenSocket& operator=(const ListenSocket&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	
	//Data:
private:
	
};


