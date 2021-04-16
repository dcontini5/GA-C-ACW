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



class GameObject : public std::enable_shared_from_this<GameObject>, public Subject {

	//Structors
public:
	GameObject();
	GameObject(const GameObject&);
	GameObject(GameObject&&); //exchange members here;
	~GameObject() = default;

	//Accessors
public:

	ComponentMap GetComponents();
	ComponentPtr GetComponent(ComponentType& pComponentName);
	glm::vec3 GetPos() const { return mPosition; };
	glm::vec3 GetOldPos() const { return mOldPosition; };
	glm::vec3 GetScale() const { return mScale; };
	glm::vec3 GetRot() const { return mRotation; }
	int GetId() const { return mID; }
	
	//Mutators
public:
	void InitPos(const glm::vec3 pNewPos) { mPosition = pNewPos; mOldPosition = pNewPos; }
	void SetPos(const glm::vec3& pNewPos) { mPosition = pNewPos; }
	void SetOldPos(const glm::vec3& pPos) { mOldPosition = pPos; }
	void setScale(const glm::vec3& pNewScale) { mScale = pNewScale; }
	void setRot(const glm::vec3& pNewRot) { mRotation = pNewRot; }
	// Public Functions
public:

	void AddComponent(ComponentPtr& pComponent);
	void AddComponent(GameObjectComponent* pComponent);
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

	glm::vec3 mPosition{0.f};
	glm::vec3 mOldPosition{0.f};
	glm::vec3 mScale{1.f};
	glm::vec3 mRotation{0.f};

	const int mID;
	bool mAlive{true};
	ComponentMap mComponents;
	
};
