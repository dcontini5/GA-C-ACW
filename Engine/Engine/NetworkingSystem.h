#pragma once
#include "Peer.h"
#include "System.h"
#include "TransferSocket.h"
#include <queue>
#include <utility>

typedef std::queue<std::string> MessageQueue;

class NetworkingSystem : public System {

	//Structors
public:
	NetworkingSystem(Peer pPeer) : System(SystemTypes::NETWORKING), mPeer(std::move(pPeer)), mSendThreadID(-1), mReceiveThreadID(-1){}
	~NetworkingSystem() = default;

	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:
	virtual void Init(){};
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
	

	//Data:
protected:
	TransferSocket	mTransferSocket;
	Peer			mPeer;
	int				mSendThreadID;
	int				mReceiveThreadID;
	MessageQueue    mSendQueue;
};
