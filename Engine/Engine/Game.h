#pragma once
#include "Window.h"

class Game {

	//Private Structors
private:
	Game(){  };

	//Public Structors
public:
	~Game() = default;

	static Game* Instance(){

		if (!mInstance){ mInstance = new Game(); }

		return mInstance;
	}

	//Accessors
public:
	bool GetQuitFlag() const { mQuitFlag; }
	
	//Mutators
public:

	void SetQuitFlag(const bool& pQuitFlag) { mQuitFlag = pQuitFlag; }
	void SetWindow(std::shared_ptr<Window>& pWindow) { mWindow = pWindow; }

	//void StartRenderer();
	
	// Public Functions
public:

	// Private Functions
private:

	//Data:
private:
	static Game* mInstance;

	bool mQuitFlag = false;

	std::shared_ptr<Window> mWindow = nullptr;
	
};
