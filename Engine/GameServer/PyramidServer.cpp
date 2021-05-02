#include "PyramidServer.h"
#include "ThreadManager.h"
#include "gtx/string_cast.hpp"
#include "NetworkMessageTypes.h"


PyramidServer::PyramidServer():Server(){}

void PyramidServer::CreateMessage(std::string& pMessage, const std::shared_ptr<TransferSocket>& pTransferSocket){

	pMessage += std::to_string(NetworkMessageTypes::GAMEOBJECT_UPDATE) + ':';
	
	for(const auto& obj : mGameObjects){

		glm::vec3 objPos;
		glm::vec3 objScale;

		{
			std::shared_lock<std::shared_mutex> lk(ThreadManager::Instance()->GetSharedMutex());
			objPos = obj->GetPos();
			objScale = obj->GetScale();
		}
			
		const auto pos = std::to_string(objPos.x) + '>' + std::to_string(objPos.y) + '>' + std::to_string(objPos.z) + ')';
		const auto scale = std::to_string(objScale.x) + '>' + std::to_string(objScale.y) + '>' + std::to_string(objScale.z) + ')';

		
		pMessage += "P(";
		pMessage += pos;
		pMessage += "S(";
		pMessage += scale;
		pMessage += '~';
		
		
	}
	pMessage += '#';
	
	pMessage += std::to_string(NetworkMessageTypes::PLAYER_UPDATE) + ':';

	const auto player = pTransferSocket->GetPlayer();

	const auto pos = std::to_string(player->GetPos().x) + '>' + std::to_string(player->GetPos().y) + '>' + std::to_string(player->GetPos().z) + '-';
	const auto rotation = std::to_string(player->GetRot().x) + '>' + std::to_string(player->GetRot().y) + '>' + std::to_string(player->GetRot().z) + '-';


	pMessage += 'P';
	pMessage += pos;
	pMessage += 'R';
	pMessage += rotation;
}

void PyramidServer::ParseMessage(std::string& pMessage, const std::shared_ptr<TransferSocket>& pTransferSocket){

	
	std::cout << pMessage << std::endl;

	
}
