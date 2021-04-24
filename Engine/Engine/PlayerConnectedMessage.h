#pragma once
#include <string>

#include "Message.h"
#include "TransferSocket.h"

typedef std::shared_ptr<TransferSocket> TransferSocketPtr;

class PlayerConnectedMessage :public Message{

	//Structors
public:
	PlayerConnectedMessage(const TransferSocketPtr& pTransferSocket);
	PlayerConnectedMessage(const PlayerConnectedMessage&);
	PlayerConnectedMessage(PlayerConnectedMessage&&); //exchange members here;
	~PlayerConnectedMessage() = default;

	//Accessors
public:

	TransferSocketPtr GetTransferSocket() const { return mTransferSocket; }
	
	//Mutators
public:

	// Public Functions
public:

	// Private Functions
private:

	//Operators
public:
	PlayerConnectedMessage& operator=(const PlayerConnectedMessage& pOther){ return *this = PlayerConnectedMessage(pOther); }

	PlayerConnectedMessage& operator=(const PlayerConnectedMessage&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:

	TransferSocketPtr mTransferSocket;
	
};
