#pragma once
#include "TransferSocket.h"

class Client {

	//Structors
public:
	Client() : mPeer("127.0.0.1"){}
	Client(const Client&);
	Client(Client&&); //exchange members here;
	~Client() = default;

	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:
	void Init();
	void Start();
	void Echo(const std::string& pMessage);
	// Private Functions
private:

	//Operators
public:
	Client& operator=(const Client& pOther){ return *this = Client(pOther); }

	Client& operator=(const Client&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:

	TransferSocket	mTransferSocket;
	Peer			mPeer;
	
};
