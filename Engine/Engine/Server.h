#pragma once
#include "ListenSocket.h"
#include "TransferSocket.h"

#include <vector>


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
	void Listen();
	void Send();
	//void Receive();
	void Receive(TransferSocket& pClient);
	
	
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

	typedef std::vector<TransferSocket> ClientList;
	ClientList                  mClients;
	ListenSocket				mListenSocket;
	TransferSocket				mTransferSocket;
	Peer						mPeer;
	
};
