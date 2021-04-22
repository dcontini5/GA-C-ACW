#pragma once
#include <string>

#include "Message.h"
#include "TransferSocket.h"

typedef std::shared_ptr<TransferSocket> TransferSocketPtr;

class NewPlayerConnectedMessage :public Message{

	//Structors
public:
	NewPlayerConnectedMessage(const TransferSocketPtr& pTransferSocket);
	NewPlayerConnectedMessage(const NewPlayerConnectedMessage&);
	NewPlayerConnectedMessage(NewPlayerConnectedMessage&&); //exchange members here;
	~NewPlayerConnectedMessage() = default;

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
	NewPlayerConnectedMessage& operator=(const NewPlayerConnectedMessage& pOther){ return *this = NewPlayerConnectedMessage(pOther); }

	NewPlayerConnectedMessage& operator=(const NewPlayerConnectedMessage&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:

	TransferSocketPtr mTransferSocket;
	
};
