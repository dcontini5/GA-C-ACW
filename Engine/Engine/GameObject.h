#pragma once
#include <glm.hpp>
#include <map>
#include <memory>

class GameObjectComponent;
enum ComponentTypes;

typedef std::map <ComponentTypes, std::shared_ptr<GameObjectComponent>> ComponentMap;
typedef std::map <ComponentTypes, std::shared_ptr<GameObjectComponent>>::iterator ComponentMapIterator;
typedef std::shared_ptr<GameObjectComponent> ComponentPtr;


class GameObject{

	//Structors
public:
	GameObject();
	GameObject(const GameObject&);
	GameObject(GameObject&&); //exchange members here;
	~GameObject();

	//Accessors
public:

	ComponentMap GetComponents();
	ComponentPtr GetComponent(const ComponentTypes& pComponentName);
	glm::vec3 GetPos() const { return mPos; };
	glm::vec3 GetScale() const { return mScale; };
	
	//Mutators
public:
	void SetPos(const glm::vec3& pNewPos) { mPos = pNewPos; }
	// Public Functions
public:

	void AddComponent(ComponentPtr& pComponent);
	void RemoveComponent(const ComponentTypes& pType);
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

	glm::vec3 mPos;
	glm::vec3 mScale;

	ComponentMap mComponents;
	
};
