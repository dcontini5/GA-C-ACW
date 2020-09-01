#pragma once
#include "Peer.h"
#include "System.h"
#include "TransferSocket.h"
#include <queue>

typedef std::queue<std::string> MessageQueue;

class NetworkingSystem : public System {

	//Structors
public:
	NetworkingSystem(const Peer& pPeer) : System(SystemTypes::NETWORKING), mPeer(pPeer), mSendThreadID(-1), mReceiveThreadID(-1){}
	NetworkingSystem(const NetworkingSystem&);
	NetworkingSystem(NetworkingSystem&&); //exchange members here;
	~NetworkingSystem() = default;

	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:
	virtual void Init();
	void Send();
	void Receive();
	
	void Start() override;

	virtual void CreateMessage(std::string& pMessage) {};	//implement on game
	virtual void ParseMessage(std::string& pMessage) {};	//implement on game
	// Private Functions
private:

	void Process() override { return; }; // not going to be used
	
	//Operators
public:
	NetworkingSystem& operator=(const NetworkingSystem& pOther) = delete;

	NetworkingSystem& operator=(const NetworkingSystem&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
protected:
	TransferSocket	mTransferSocket;
	Peer			mPeer;
	int				mSendThreadID;
	int				mReceiveThreadID;
	MessageQueue    mSendQueue;
};
