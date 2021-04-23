#pragma once
#include "Client.h"

class PyramidClient : public Client {

	//Structors
public:
	PyramidClient() = default;
	PyramidClient(const PyramidClient&);
	PyramidClient(PyramidClient&&); //exchange members here;
	~PyramidClient() = default;

	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:

	void CreateMessage(std::string& pMessage) override;
	void ParseMessage(std::string& pMessage) override;
	
	// Private Functions
private:

	//Operators
public:
	PyramidClient& operator=(const PyramidClient& pOther) = default;

	PyramidClient& operator=(const PyramidClient&& pOther){

		/*Swap Members Here*/
		return *this;
	}


	//Data:
private:

};
