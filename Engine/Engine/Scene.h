#pragma once
#include <memory>
#include <vector>
#include "Message.h"
#include "map"

class GameObject;
class CollisionSystem;
class PhysicsSystem;
class RenderSystem;
class System;
class Renderer;

typedef std::shared_ptr<GameObject> GameObjectPtr;
typedef std::vector<std::shared_ptr<GameObject>> GameObjects;
typedef std::map<const int, std::shared_ptr<System>> SystemMap;
typedef std::map<const int, int> ThreadIDMap;

class Scene {

	//Structors
public:
	Scene() = default;
	Scene(const Scene&);
	Scene(Scene&&); //exchange members here;
	~Scene();

	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:
	void OnMessage(std::shared_ptr<Message>& pMessage);
	virtual void Start();
	void AddSystem(std::shared_ptr<System>& pSystem);
	// Private Functions
private:

	//Operators
public:
	Scene& operator=(const Scene& pOther){ return *this = Scene(pOther); }

	Scene& operator=(const Scene&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
protected:

	GameObjects mGameObjectList;
	SystemMap   mSystems;
	ThreadIDMap mSystemThreadIDs;

	
	//std::shared_ptr<CollisionSystem> mCollisionSystem	= nullptr;
	//std::shared_ptr<PhysicsSystem> mPhysicsSystem		= nullptr;
	//std::shared_ptr<RenderSystem> mRenderSystem			= nullptr;

};
