#pragma once
#include <string>

#include "NetworkingSystem.h"
#include "ResourceManager.h"

class Client : public NetworkingSystem{

	//Structors
public:
	Client() :NetworkingSystem({ResourceManager::Instance()->GetServerAddress(), ResourceManager::Instance()->GetPort()}), mTransferSocket(std::make_shared<TransferSocket>()){}
	Client(const Client&);
	Client(Client&&); //exchange members here;
	~Client() = default;

	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:
	
	void Init() override;
	void Connect();
	void Start() override;
	void Echo(const std::string& pMessage);

	
	// Private Functions
private:

	//Operators
public:
	Client& operator=(const Client& pOther) = delete;

	Client& operator=(const Client&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	
	//Data:
protected:


	typedef std::shared_ptr<TransferSocket> TransferSocketPtr;
	TransferSocketPtr mTransferSocket;
	
};
