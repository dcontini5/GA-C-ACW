#pragma once

#include "Peer.h"

#include <iostream>



class Socket {

	//Structors
public:

	~Socket(){

		closesocket(mSocket);
		//WSACleanup();

	}

protected:
	Socket() {}
	Socket(const SOCKET& pSocket) : mSocket(pSocket) {}
	Socket(const Socket& pOther) : mSocket(pOther.mSocket) {}
	Socket(Socket&& pOther) noexcept : mSocket(std::exchange(pOther.mSocket, -1)) {} //exchange members here;

	
	//Accessors
public:

	SOCKET GetSocket() const { return mSocket; }
	
	//Mutators
public:

	virtual void SetSocket(SOCKET& pSocket) { mSocket = pSocket; }
	virtual void Disconnect() { closesocket(mSocket); mSocket = INVALID_SOCKET; }
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

	SOCKET mSocket{ INVALID_SOCKET };
	
};
