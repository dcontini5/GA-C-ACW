#pragma once
#include "InputStateComponent.h"
#include "ResourceManager.h"
#include "PyramidGame.h"




class PyramidPlayerInputComponent : public InputStateComponent{

	//Structors
public:
	PyramidPlayerInputComponent(GameObjectPtr& pParent) : InputStateComponent(pParent), mGameState(PyramidGame::GetGameState()) {}
	PyramidPlayerInputComponent(const PyramidPlayerInputComponent&);
	PyramidPlayerInputComponent(PyramidPlayerInputComponent&&); //exchange members here;
	~PyramidPlayerInputComponent() = default;

	//Accessors
public:

	//Mutators
public:

	void Update(const InputState& pKeyState) override;
	
	// Public Functions
public:

	// Private Functions
private:

	//Operators
public:
	PyramidPlayerInputComponent& operator=(const PyramidPlayerInputComponent& pOther){ return *this = PyramidPlayerInputComponent(pOther); }

	PyramidPlayerInputComponent& operator=(const PyramidPlayerInputComponent&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:

	std::shared_ptr<GameState> mGameState;

	
};
