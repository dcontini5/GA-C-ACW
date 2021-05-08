#pragma once
#include "CameraComponent.h"

class PyramidCameraComponent : public CameraComponent{

	//Structors
public:
	PyramidCameraComponent(GameObjectPtr& pParent) : CameraComponent(pParent){}
	PyramidCameraComponent(const PyramidCameraComponent&);
	PyramidCameraComponent(PyramidCameraComponent&&); //exchange members here;
	~PyramidCameraComponent() = default;

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
	PyramidCameraComponent& operator=(const PyramidCameraComponent& pOther) = delete;

	PyramidCameraComponent& operator=(const PyramidCameraComponent&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
	private:
	
};
