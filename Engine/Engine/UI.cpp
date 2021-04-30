#include "UI.h"
UI::~UI(){


	
}

void UI::Init(){

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	
}

void UI::DrawFrame(){

	ImGui::NewFrame();

	PrepareFrame();

	ImGui::Render();
	
}
