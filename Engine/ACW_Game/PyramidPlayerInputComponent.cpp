#include "PyramidPlayerInputComponent.h"


#include "Game.h"
#include "UpdateFrequencyMessage.h"
#include "CameraUpdateMessage.h"

void PyramidPlayerInputComponent::Update(const InputState& pKeyState){

	mKeyStates[pKeyState.key] = pKeyState.keyState;

	
	for (const auto& key : mKeyStates) {

		if (!key.second) continue;
		
		switch (key.first) {


		case ESCAPE:
		{
			Game::Instance()->Quit();
			continue;
		}

		case R:
		{

			mGameState->sceneReset = true;
			//mGameState->hasUpdated = true;
			continue;
		}
		case T:
		{

			mGameState->pyramidSize = glm::clamp(++mGameState->pyramidSize, static_cast<uint8_t>(3), static_cast<uint8_t>(50));
			mGameState->hasUpdated = true;
			continue;
		}
		case G:
		{

			mGameState->pyramidSize = glm::clamp(--mGameState->pyramidSize, static_cast<uint8_t>(3), static_cast<uint8_t>(50));
			mGameState->hasUpdated = true;
			continue;
		}
		case U:
		{
			mGameState->graphicsTargetFrequency = glm::clamp(++mGameState->graphicsTargetFrequency, static_cast<short>(1), static_cast<short>(1000));
			std::shared_ptr<Message>  msg = std::make_shared<UpdateFrequencyMessage>(SystemTypes::RENDER, mGameState->graphicsTargetFrequency);
			Game::Instance()->BroadcastMessage(msg);
			continue;
		}
		case J:
		{
			mGameState->graphicsTargetFrequency = glm::clamp(--mGameState->graphicsTargetFrequency, static_cast<short>(1), static_cast<short>(1000));
			std::shared_ptr<Message>  msg = std::make_shared<UpdateFrequencyMessage>(SystemTypes::RENDER, mGameState->graphicsTargetFrequency);
			Game::Instance()->BroadcastMessage(msg);
			continue;
		}
		case Y:
		{

			mGameState->networkTargetFrequency = glm::clamp(++mGameState->networkTargetFrequency, static_cast<short>(1), static_cast<short>(1000));
			//std::shared_ptr<Message>  msg = std::make_shared<UpdateFrequencyMessage>(SystemTypes::NETWORKING, mGameState->networkTargetFrequency);
			//Game::Instance()->BroadcastMessage(msg);
			mGameState->hasUpdated = true;
			continue;
		}
		case H:
		{
			mGameState->networkTargetFrequency = glm::clamp(--mGameState->networkTargetFrequency, static_cast<short>(1), static_cast<short>(1000));
			//std::shared_ptr<Message>  msg = std::make_shared<UpdateFrequencyMessage>(SystemTypes::NETWORKING, mGameState->networkTargetFrequency);
			//Game::Instance()->BroadcastMessage(msg);
			mGameState->hasUpdated = true;
			continue;
		}
		case NUM1:
		{
			
			//mGameState->projectileFired = 1;
			//mGameState->hasUpdated = true;
			//continue;
		}
		case NUM2:
		{
			//fire big proj
		}
		case NUM3:
		{
			//fire grenade
		}
		case LEFT:
		{
			//move playback backward
		}
		case RIGHT:
		{
			//move playback forward
		}
		case UP:
		{
			//pause playback
		}
		case DOWN:
		{
			//unpause playback
		}

		case MOUSEL:
		{
			if (ImGui::IsAnyItemActive()) continue;
			std::shared_ptr<Message> msg = std::make_shared<CameraUpdateMessage>(pKeyState.mouseMov, false, 0);

			Game::Instance()->BroadcastMessage(msg);
			mGameState->hasUpdated = true;
			continue;
				
		}
		case MOUSER:
		{
			if (ImGui::IsAnyItemActive()) continue;
			std::shared_ptr<Message> msg = std::make_shared<CameraUpdateMessage>(pKeyState.mouseMov, true, 0);

			Game::Instance()->BroadcastMessage(msg);
			mGameState->hasUpdated = true;
			continue;

		}
		case MOUSEWHEEL:
		{
				
			std::shared_ptr<Message> msg = std::make_shared<CameraUpdateMessage>(pKeyState.mouseMov, true, pKeyState.wheelRot);
			Game::Instance()->BroadcastMessage(msg);
			mKeyStates[MOUSEWHEEL] = false;
			mGameState->hasUpdated = true;
			continue;	
		}

			
		default: continue;
		}

	}
	
}
