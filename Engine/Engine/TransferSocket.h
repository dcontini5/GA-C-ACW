#pragma once

#include "Socket.h"
#include "GameObject.h"

typedef std::shared_ptr<GameObject> GameObjectPtr;

class TransferSocket : public Socket {

	//Structors
public:
	TransferSocket() : Socket() {}
	explicit TransferSocket(SOCKET& pSocket) : Socket(pSocket) {}
	explicit TransferSocket(SOCKET& pSocket, std::string pClientAddress) : Socket(pSocket), mClientAddress(pClientAddress) {}
	TransferSocket(const TransferSocket& pOther) = default;
	TransferSocket(TransferSocket&& pOther) noexcept = default; //exchange members here;
	~TransferSocket() = default;

	//Accessors
public:

	GameObjectPtr GetPlayerGameObject() const { return mPlayerGameObject; }
	std::string GetClientAddress() const { return mClientAddress; }
	bool IsConnected() const { return mConnected; }
	int GetSendThreadID() const { return mSendThreadID; }
	int GetReceiveThreadID() const { return mReceiveThreadID; }
	
	
	//Mutators
public:


	void SetPlayerGameObject(const GameObjectPtr& pGameObjectPtr ) {  mPlayerGameObject = pGameObjectPtr; }
	void SetClientAddress(const std::string& pClientAddress ) {  mClientAddress = pClientAddress; }
	void SetSocket(SOCKET& pSocket) override { mConnected = true; Socket::SetSocket(pSocket); }
	void Disconnect() override { mConnected = false; Socket::Disconnect(); }
	void GetSendThreadID(const int& pID) {mSendThreadID = pID; }
	void GetReceiveThreadID(const int& pID) {mReceiveThreadID = pID; }
	// Public Functions
public:
		
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

	GameObjectPtr mPlayerGameObject{nullptr};
	std::string mClientAddress;
	bool mConnected{ false };
	int mSendThreadID{-1};
	int mReceiveThreadID{-1};
	
};
