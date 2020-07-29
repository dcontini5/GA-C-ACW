#pragma once
#include "RenderComponent.h"
#include "System.h"


//typedef std::vector<std::shared_ptr<RenderComponent>> Components;

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
	void Start() override;
	// Private Functions
private:

	//Operators
private:
	RenderSystem& operator=(const RenderSystem& pOther){ return *this = RenderSystem(pOther); }
	RenderSystem& operator=(const RenderSystem&& pOther){

		/*Swap Members Here*/
		return *this;
	}

public:
	//Data:
private:

	//Components mComponents;
	static RenderSystem* mInstance;
	std::shared_ptr<Renderer> mRenderer;
	
};
