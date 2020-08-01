#pragma once
#include <glm.hpp>
#include <map>
#include <memory>

#include "ComponentTypes.h"
#include "Subject.h"

class GameObjectComponent;

typedef std::map <int, std::shared_ptr<GameObjectComponent>> ComponentMap;
typedef std::map <int, std::shared_ptr<GameObjectComponent>>::iterator ComponentMapIterator;
typedef std::shared_ptr<GameObjectComponent> ComponentPtr;


class GameObject :std::enable_shared_from_this<GameObject>, public Subject {

	//Structors
public:
	GameObject() = default;
	GameObject(const GameObject&);
	GameObject(GameObject&&); //exchange members here;
	~GameObject() = default;

	//Accessors
public:

	ComponentMap GetComponents();
	ComponentPtr GetComponent(ComponentType& pComponentName);
	glm::vec3 GetPos() const { return mPosition; };
	glm::vec3 GetScale() const { return mScale; };
	glm::vec3 GetRot() const { return mRotation; }
	
	//Mutators
public:
	void SetPos(const glm::vec3& pNewPos) { mPosition = pNewPos; }
	void setScale(const glm::vec3& pNewScale) { mScale = pNewScale; }
	void setRot(const glm::vec3& pNewRot) { mRotation = pNewRot; }
	// Public Functions
public:

	void AddComponent(ComponentPtr& pComponent);
	void RemoveComponent(ComponentType& pType);
	void RemoveComponent(ComponentPtr& pComponent);
	

	// Private Functions
private:

	//Operators
public:
	GameObject& operator=(const GameObject& pOther){ return *this = GameObject(pOther); }

	GameObject& operator=(const GameObject&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:

	glm::vec3 mPosition;
	glm::vec3 mScale;
	glm::vec3 mRotation;

	bool mAlive = true;
	ComponentMap mComponents;
	
};
