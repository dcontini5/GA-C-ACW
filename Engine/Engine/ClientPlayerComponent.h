#pragma once
#include "GameObjectComponent.h"
#include "TransferSocket.h"

typedef std::shared_ptr<TransferSocket> TransferSocketPtr;

class ClientPlayerComponent : public GameObjectComponent{

	//Structors
public:
	ClientPlayerComponent(GameObjectPtr& pParent, TransferSocketPtr& pSocket);
	ClientPlayerComponent(GameObjectPtr& pParent);
	ClientPlayerComponent(const ClientPlayerComponent&);
	ClientPlayerComponent(ClientPlayerComponent&&); //exchange members here;
	~ClientPlayerComponent();

	//Accessors
public:

	TransferSocketPtr GetTransferSocket() const { return mTransferSocket; }
	
	//Mutators
public:

	void SetTransferSocket(const TransferSocketPtr& pSocket) { mTransferSocket = pSocket; }
	
	// Public Functions
public:

	// Private Functions
private:

	//Operators
public:
	ClientPlayerComponent& operator=(const ClientPlayerComponent& pOther){ return *this = ClientPlayerComponent(pOther); }

	ClientPlayerComponent& operator=(const ClientPlayerComponent&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:

	TransferSocketPtr mTransferSocket;
	
};
