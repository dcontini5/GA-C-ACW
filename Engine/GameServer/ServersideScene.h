#pragma once
#include "Scene.h"

class ServersideScene : public Scene {

	//Structors
public:
	ServersideScene() = default;
	ServersideScene(const ServersideScene&);
	ServersideScene(ServersideScene&&); //exchange members here;
	~ServersideScene() = default;

	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:
	void Start() override;
	void OnMessage(std::shared_ptr<Message>& pMessage) override;
	void ResetScene();
	void CreatePyramid();
	// Private Functions
private:

	//Operators
public:
	ServersideScene& operator=(const ServersideScene& pOther){ return *this = ServersideScene(pOther); }

	ServersideScene& operator=(const ServersideScene&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:

	uint8_t mHeight{ 5 };
	
};
