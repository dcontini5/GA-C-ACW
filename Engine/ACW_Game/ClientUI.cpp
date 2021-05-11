#include "ClientUI.h"
void ClientUI::PrepareFrame(){


	{
		
		static int dummy = 0;

		ImGui::Begin("Head up Display");                          // Create a window called "Hello, world!" and append into it.
		
		ImGui::Text("Size of the pyramid = %d", mGameState->pyramidSize);
		ImGui::Text("Target Graphics Frequency = %d Hz", mGameState->graphicsTargetFrequency);
		ImGui::Text("Actual Graphics Frequency = %.2f Hz", mGameState->graphicsActualFrequency);
		ImGui::Text("Target Network Frequency = %d Hz", mGameState->networkTargetFrequency);
		ImGui::Text("Actual Network Frequency = %.2f Hz", mGameState->clientActualFrequency);
		//ImGui::Text("Actual Server Frequency = %.2f Hz", mGameState->clientActualFrequency);
		ImGui::Text("Time from the start of the simulation = %d s", dummy);
		ImGui::Text("Time from the start of the playback = %d s", dummy);

		//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		
		ImGui::End();
	}

	
}
