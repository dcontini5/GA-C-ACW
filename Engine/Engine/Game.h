#pragma once
#include "AddedComponentMessage.h"
#include "Window.h"
#include "InputState.h"
#include "ResourceManager.h"

class Message;
class Scene;

class Game {

	//Private Structors
protected:
	Game(){
		mInstance = this;
		ResourceManager::Instance()->LoadSettings();
	}

	//Public Structors
public:
	~Game() = default;


	static Game* Instance(){

		return mInstance;
	}

	//Accessors
public:
	bool GetQuitFlag() const { return !mQuitFlag; }
	std::shared_ptr<Window> GetWindow() const { return mWindow; }
	//Mutators
public:

	void Quit() { mQuitFlag = true; }
	void SetWindow(std::shared_ptr<Window>& pWindow) { mWindow = pWindow; }
	void BroadcastMessage(std::shared_ptr<Message>& pMessage);
	void OnKeyboard(const InputState& pState);
	void SetActiveCamera(const std::shared_ptr<GameObject>& pCamera);
	//void StartRenderer();
	
	// Public Functions
public:

	virtual void Initialize(std::shared_ptr<Window>& pWindow);
	virtual void Initialize() {};
	
	// Private Functions
private:

	//Data:
protected:
	
	static Game* mInstance;
	bool mQuitFlag = false;
	std::shared_ptr<Window> mWindow = nullptr;
	std::shared_ptr<Scene> mScene = nullptr;
	
};
