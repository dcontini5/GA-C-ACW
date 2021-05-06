#include "ClientUI.h"
void ClientUI::PrepareFrame(){


	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Head up Display");                          // Create a window called "Hello, world!" and append into it.

		//ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		//ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		//ImGui::Checkbox("Another Window", &show_another_window);

		//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		//if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		//	counter++;
		//ImGui::SameLine();
		
		ImGui::Text("Size of the pyramid = %d", mGameState->pyramidSize);
		ImGui::Text("Target Graphics Frequency = %d Hz", mGameState->graphicsTargetFrequency);
		ImGui::Text("Actual Graphics Frequency = %.2f Hz", mGameState->graphicsActualFrequency);
		ImGui::Text("Target Network Frequency = %d Hz", counter);
		ImGui::Text("Actual Network Frequency = %f Hz", counter);
		ImGui::Text("Time from the start of the simulation = %d s", counter);
		ImGui::Text("Time from the start of the playback = %d s", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		
		ImGui::End();
	}

	
}
