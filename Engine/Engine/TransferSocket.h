#pragma once

#include "Socket.h"

class TransferSocket : public Socket {

	//Structors
public:
	TransferSocket() : Socket() {}
	explicit TransferSocket(SOCKET& pSocket) : Socket(pSocket) {}
	TransferSocket(const TransferSocket& pOther) = default;
	TransferSocket(TransferSocket&& pOther) noexcept = default; //exchange members here;
	~TransferSocket() = default;

	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:
		
	void SetSocket(SOCKET& pSocket) { mSocket = pSocket; }
	void Connect(const Peer& pPeer) const;
	void Send();
	void Receive();
	//void Send(const std::string pMessage);
	//void Receive(std::string& pMessage);
	
	// Private Functions
private:

	//Operators
public:
	TransferSocket& operator=(const TransferSocket& pOther) = delete;

	TransferSocket& operator=(const TransferSocket&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:
	
	
};
