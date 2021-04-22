#pragma once
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib") 

class Peer {

	//Structors
public:
	Peer();
	Peer(const std::string& pIP );
	Peer(const Peer& pOther);
	Peer(Peer&& pOther) noexcept; //exchange members here;
	~Peer() = default;

	//Accessors
public:

	sockaddr_in Get() const { return mPeer; }
	
	//Mutators
public:

	// Public Functions
public:

	// Private Functions
private:

	//Operators
public:
	Peer& operator=(const Peer& pOther){ return *this = Peer(pOther); }

	Peer& operator=(const Peer&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:

	sockaddr_in mPeer;
	
};
