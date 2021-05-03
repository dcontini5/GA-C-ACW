#pragma once
#include "GameObjectComponent.h"

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

	// Public Functions
public:

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
	
};
