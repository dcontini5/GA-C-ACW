#pragma once
#include "GameObjectComponent.h"
#include "map"
#include "InputKeys.h"

struct KeyState {

	bool isActive{ false };
	short value{ 0 };
	
};

typedef std::map<InputKeys, KeyState> KeyStates;

class InputStateComponent : public GameObjectComponent {

	//Structors
public:
	InputStateComponent(GameObjectPtr& pParent): GameObjectComponent(pParent, ComponentTypes::INPUT_STATE){}
	InputStateComponent(const InputStateComponent&);
	InputStateComponent(InputStateComponent&&); //exchange members here;
	~InputStateComponent() = default;

	//Accessors
public:

	//Mutators
public:
	void UpdateState(const KeyState& pKeyState);
	// Public Functions
public:

	void ResetStates();
	// Private Functions
private:

	//Operators
public:
	InputStateComponent& operator=(const InputStateComponent& pOther) = default;

	InputStateComponent& operator=(const InputStateComponent&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:

	KeyStates mKeyStates;
	
	
};
