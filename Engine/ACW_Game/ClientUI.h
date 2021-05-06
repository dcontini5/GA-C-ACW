#pragma once
#include "UI.h"
#include "PyramidGame.h"

class ClientUI :public UI{

	//Structors
public:
	ClientUI():UI(), mGameState(PyramidGame::GetGameState()){}
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

	std::shared_ptr<GameState> mGameState;
	
};
