#pragma once
#include "GameObjectComponent.h"
#include "Mesh.h"

class RenderComponent : public GameObjectComponent {

	//Structors
public:
	RenderComponent(GameObjectPtr& pParent);
	~RenderComponent();

private:
	RenderComponent(const RenderComponent&);
	RenderComponent(RenderComponent&&) noexcept; //exchange members here;
	
	//Accessors
public:
	bool IsDrawable() const { return mDrawable; }
	std::shared_ptr<Mesh> GetMesh() const { return mMesh; }
	
	//Mutators
public:
	void SetMesh(std::shared_ptr<Mesh>& pMesh) { mMesh = pMesh; }
	void StartDrawing() { if (mMesh) mDrawable = true; }
	void StopDrawing() { mDrawable = false; }
	
	// Public Functions
public:

	void OnMessage(std::shared_ptr<Message>& pMessage) override {};
	
	// Private Functions
private:

	//Operators
public:
	RenderComponent& operator=(const RenderComponent& pOther){ return *this = RenderComponent(pOther); }

	RenderComponent& operator=(const RenderComponent&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:
	bool mDrawable = false;
	std::shared_ptr<Mesh> mMesh = nullptr;
};
