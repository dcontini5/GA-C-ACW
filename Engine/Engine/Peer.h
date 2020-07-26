#pragma once
#include <string>
#include <winsock2.h>


class Peer {

	//Structors
public:
	Peer();
	Peer(const std::string& pIP );
	Peer(const Peer&);
	Peer(Peer&&); //exchange members here;
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
