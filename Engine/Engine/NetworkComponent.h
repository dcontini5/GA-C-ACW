#pragma once
#include "GameObjectComponent.h"

class NetworkComponent : public GameObjectComponent{

	//Structors
public:
	NetworkComponent(GameObjectPtr& pParent): GameObjectComponent(pParent, ComponentTypes::NETWORKING) {}
	NetworkComponent(const NetworkComponent&);
	NetworkComponent(NetworkComponent&&); //exchange members here;
	~NetworkComponent();

	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:
	void OnMessage(std::shared_ptr<Message>& pMessage) override;
	// Private Functions
private:

	//Operators
public:
	NetworkComponent& operator=(const NetworkComponent& pOther){ return *this = NetworkComponent(pOther); }

	NetworkComponent& operator=(const NetworkComponent&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
	private:
	
};
