#pragma once
#include "Server.h"

class PyramidServer :public Server{

	//Structors
public:
	PyramidServer();
	~PyramidServer() = default;

	void CreateMessage(std::string& pMessage, const std::shared_ptr<TransferSocket>& pTransferSocket) override;
	void ParseMessage(std::string& pMessage, const std::shared_ptr<TransferSocket>& pTransferSocket) override;
	//Accessors

	//Mutators
public:

	// Public Functions
public:

	// Private Functions
private:

	//Operators
public:
	
	//Data:
private:
	
};
