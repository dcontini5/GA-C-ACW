#pragma once

#include <vector>
#include <memory>
#include "RenderComponent.h"
#include "System.h"


//typedef std::vector<std::shared_ptr<RenderComponent>> Components;
typedef std::vector<std::shared_ptr<GameObject>> RenderableObjects;

class RenderSystem : public System {

	//Structors
public:
	~RenderSystem();

private:
	RenderSystem() = default;
	RenderSystem(const RenderSystem&);
	RenderSystem(RenderSystem&&); //exchange members here;

	
	//Accessors
public:
	static RenderSystem* Instance(){

		if (!mInstance) mInstance = new RenderSystem();

		return mInstance;
		
	}
	//Mutators
public:

	void SetRenderer(std::shared_ptr<Renderer>& pRenderer) { mRenderer = pRenderer; }
	
	// Public Functions
public:
	void Process() override;
	void AddObject(GameObjectPtr& pGameObject) override;
	void RemoveObject(GameObjectPtr& pGameObject) override;
	// Private Functions
private:

	//Operators
private:
	RenderSystem& operator=(const RenderSystem& pOther){ return *this = RenderSystem(pOther); }
	RenderSystem& operator=(const RenderSystem&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:

	//Components mComponents;
	static RenderSystem* mInstance;
	RenderableObjects mRenderableObjects;
	std::shared_ptr<Renderer> mRenderer;
	
};
