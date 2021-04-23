#pragma once
#include <string>

#include "NetworkingSystem.h"


class Client : public NetworkingSystem{

	//Structors
public:
	Client() :NetworkingSystem({"127.0.0.1"}){}
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
	void Start();
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
private:

	TransferSocket mTransferSocket;
	
};
