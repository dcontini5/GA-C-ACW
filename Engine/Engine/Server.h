#pragma once
#include "ListenSocket.h"
#include "TransferSocket.h"

class Server {

	//Structors
public:
	Server() {}
	Server(const Server&);
	Server(Server&&); //exchange members here;
	~Server() = default;

	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:
	void Init();
	void Start();
	void Echo(std::string& pMessage);
	// Private Functions
private:

	//Operators
public:
	Server& operator=(const Server& pOther){ return *this = Server(pOther); }

	Server& operator=(const Server&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:

	ListenSocket	mListenSocket;
	TransferSocket	mTransferSocket;
	Peer			mPeer;
	
};
