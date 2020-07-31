#pragma once
#include <memory>
#include <vector>
#include "Message.h"

class GameObject;
class CollisionSystem;
class PhysicsSystem;
class RenderSystem;
class Renderer;

typedef std::shared_ptr<GameObject> GameObjectPtr;
typedef std::vector<std::shared_ptr<GameObject>> GameObjects;


class Scene {

	//Structors
public:
	Scene();
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
	void Start(std::shared_ptr<Renderer>& pRenderer);
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
private:

	GameObjects mGameObjectList;
	std::shared_ptr<CollisionSystem> mCollisionSystem	= nullptr;
	std::shared_ptr<PhysicsSystem> mPhysicsSystem		= nullptr;
	std::shared_ptr<RenderSystem> mRenderSystem			= nullptr;

	int mCollisionSystemThreadID = -1;
	int mPhysicsSystemThreadID = -1;
	int mRenderSystemThreadID = -1;
	
};
