#pragma once
#include <glm/glm.hpp>
#include "Component.h"
#include <map>

typedef std::map<ComponentType ,std::shared_ptr<Component>> ComponentMap;
//typedef 

class GameObject : public std::enable_shared_from_this<GameObject> {

	//Structors
public:
	GameObject(const glm::vec3& pPosition, const glm::vec3& pRotation, const glm::vec3& pScale);
	~GameObject();
	
	//Accessors
public:
	glm::vec3 GetPosition() const { return  mPosition; }
	glm::vec3 GetRotation() const { return  mRotation; }
	glm::vec3 GetScale() const { return  mScale; }
	
	//Mutators
public:
	void SetPosition(const glm::vec3 pPosition) { mPosition = pPosition; }
	void SetRotation(const glm::vec3 pRotation) { mRotation = pRotation; }
	void SetScale(const glm::vec3 pScale) { mScale = pScale; }
 
	
	// Public Functions
public:
	void AddComponent(const std::shared_ptr<Component>& pComponent);
	void RemoveComponent(const ComponentType& pType);
	std::shared_ptr<Component> GetComponent(const ComponentType& pType);
	
	// Private Functions
private:

	//Data:
private:
	glm::vec3 mPosition;
	glm::vec3 mRotation;
	glm::vec3 mScale;
	ComponentMap mComponents;
};
