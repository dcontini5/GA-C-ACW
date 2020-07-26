#pragma once

#include "Socket.h"

class TransferSocket : public Socket {

	//Structors
public:
	TransferSocket() : Socket() {}
	TransferSocket(SOCKET& pSocket) : Socket(pSocket) {}
	TransferSocket(const TransferSocket&);
	TransferSocket(TransferSocket&&); //exchange members here;
	~TransferSocket() = default;

	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:
	
	void Send(const std::string pMessage);
	void SetSocket(SOCKET& pSocket) { mSocket = pSocket; }
	void Connect(const Peer& pPeer) const;
	void Receive();
	//void Receive(std::string& pMessage);
	
	// Private Functions
private:

	//Operators
public:
	TransferSocket& operator=(const TransferSocket& pOther){ return *this = TransferSocket(pOther); }

	TransferSocket& operator=(const TransferSocket&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:
	
	
};
