﻿#pragma once
#include "RenderComponent.h"
#include "System.h"


//typedef std::vector<std::shared_ptr<RenderComponent>> Components;

class RenderSystem : public System {

	//Structors
public:
	~RenderSystem() = default;
	RenderSystem() :System(SystemTypes::RENDER){}
	RenderSystem(const RenderSystem&);
	RenderSystem(RenderSystem&&); //exchange members here;

	
	//Accessors
public:

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
	
	std::shared_ptr<Renderer> mRenderer;
	
};
