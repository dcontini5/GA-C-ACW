#pragma once
#include "UI.h"

class ClientUI :public UI{

	//Structors
public:
	ClientUI(){};
	ClientUI(const ClientUI&);
	ClientUI(ClientUI&&); //exchange members here;
	~ClientUI() = default;

	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:

	// Private Functions
private:
	void PrepareFrame() override;
	//Operators
public:
	ClientUI& operator=(const ClientUI& pOther) = delete;
	ClientUI& operator=(const ClientUI&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:
	
};
