#pragma once
#include "Peer.h"
#include "System.h"
#include "TransferSocket.h"
#include <queue>
#include <utility>

typedef std::queue<std::string> MessageQueue;
typedef std::shared_ptr<TransferSocket> TransferSocketPtr;

class NetworkingSystem : public System {

	//Structors
public:
	NetworkingSystem(Peer pPeer) : System(SystemTypes::NETWORKING), mPeer(std::move(pPeer)){}
	~NetworkingSystem() = default;

	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:
	virtual void Init() = 0;
	void Send(const TransferSocketPtr& pTransferSocket);
	void Receive(const TransferSocketPtr& pTransferSocket);

	virtual void CreateMessage(std::string& pMessage, const TransferSocketPtr& pTransferSocket) = 0;	//must implement on game
	virtual void ParseMessage(std::string& pMessage, const TransferSocketPtr& pTransferSocket) = 0;	//must implement on game
	// Private Functions
private:

	void Process() override{}; // not going to be used
	
	//Operators
public:
	

	//Data:
protected:
	
	Peer			mPeer;
	//int				mSendThreadID;
	//int				mReceiveThreadID;
	MessageQueue    mSendQueue;
};
