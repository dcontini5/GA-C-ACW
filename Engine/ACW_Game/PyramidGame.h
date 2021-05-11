#pragma once
#include "Game.h"


struct GameState {

	bool sceneReset{ false }; 
	bool hasUpdated{ false };
	uint8_t projectileFired{ 0 };
	uint8_t pyramidSize{ 5 }; //improve 
	short networkTargetFrequency{ 60 };
	short graphicsTargetFrequency{ 60 };
	float clientActualFrequency{ 0.f };
	float serverActualFrequency{ 0.f };
	float graphicsActualFrequency{ 0.f };
	
};

class PyramidGame : public Game {

	//Structors
public:
	PyramidGame() = default;
	PyramidGame(const PyramidGame&);
	PyramidGame(PyramidGame&&); //exchange members here;
	~PyramidGame() = default;

	//Accessors
public:
	static std::shared_ptr<GameState>& GetGameState(){ return mGameState; }
	//Mutators
public:

	// Public Functions
public:
	void Initialize(std::shared_ptr<Window>& pWindow) override;
	void Initialize() override { return; }
	// Private Functions
private:

	//Operators
public:
	PyramidGame& operator=(const PyramidGame& pOther){ return *this = PyramidGame(pOther); }

	PyramidGame& operator=(const PyramidGame&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:

	static std::shared_ptr<GameState> mGameState;
	
};
