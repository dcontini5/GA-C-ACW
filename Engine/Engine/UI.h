#pragma once
#include "ImGui/imgui.h"

class UI {

	//Structors
public:
	UI() {};
	//UI(const UI&);
	//UI(UI&&); //exchange members here;
	~UI();

	//Accessors
public:

	//Mutators
public:

	// Public Functions
public:
	void Init();
	void DrawFrame();
	void CleanUI() { ImGui::DestroyContext(); }
	// Private Functions
private:

	virtual void PrepareFrame() {} // create your ui here;
	
	//Operators
public:
	UI& operator=(const UI& pOther) = delete;

	UI& operator=(const UI&& pOther){

		/*Swap Members Here*/
		return *this;
	}

	//Data:
private:

	
};
