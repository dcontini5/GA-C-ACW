#pragma once
#include "GameObject.h"
#include <memory>

enum ComponentType {

	RENDERER,
	PHYSICS,
	COLLISION,
	NETWORK,
	RIGIDBODY,
	INPUT
};

class Component : public std::enable_shared_from_this<Component> {

	//Structors
public:
	Component(std::shared_ptr<GameObject>& pParent, const ComponentType& pType);
	virtual ~Component();
	
	//Accessors
public:
	ComponentType GetComponentType() const { return mType; }
	std::shared_ptr<GameObject> GetParent() const { return mParent; }

	
	//Mutators
public:
	
	// Public Functions
public:
	virtual void Start() = 0;
	virtual void Update(float pDeltaTime) = 0;
	virtual void End() = 0;

	
	// Private Functions
private:

	//Data:
private:
	std::shared_ptr<GameObject> mParent;
	ComponentType mType;
};
