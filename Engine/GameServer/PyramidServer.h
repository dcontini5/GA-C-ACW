#pragma once
#include "Server.h"

class PyramidServer :public Server{

	//Structors
public:
	PyramidServer();
	~PyramidServer() = default;

	void CreateMessage(std::string& pMessage) override;
	void ParseMessage(std::string& pMessage) override;
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
