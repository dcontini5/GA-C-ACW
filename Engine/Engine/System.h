#pragma once
#include <chrono>
#include <vector>
#include <memory>
#include "GameObject.h"
#include "GameObjectComponent.h"
#include "Scene.h"
#include "SystemTypes.h"

class System {

	//Structors
public:
	System(SystemType& pType): mType(pType){}
	System(const System&);
	System(System&&); //exchange members here;
	virtual ~System() = default;

	//Accessors
public:

	SystemType GetType() const { return mType; }
	int GetSysFrequency() const { return mSystemFrequency; }
	//Mutators
public:

	void SetSysFrequency(const int& pNewFrequency) { mSystemFrequency = pNewFrequency; mTimeStep = std::chrono::duration<double>(1.f / static_cast<float>(mSystemFrequency)); }
	// Public Functions
public:

	virtual void Process() = 0;
	virtual void Start() = 0;
	void AddObject(GameObjectPtr& pGameObject);
	void RemoveObject(GameObjectPtr& pGameObject);
	void RemoveObjectByID(const int& pID);
	
	// Private Functions
private:

	//Operators
public:
	System& operator=(const System& pOther) = delete;

	System& operator=(const System&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
protected:

	GameObjects mGameObjects;
	SystemType mType;
	int mSystemFrequency{ 60 };
	std::chrono::time_point<std::chrono::high_resolution_clock> mLastTime;
	std::chrono::duration<double> mTimeStep{ 1.f /60.f };
};
