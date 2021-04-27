#include "PyramidServer.h"
#include "ThreadManager.h"
#include "gtx/string_cast.hpp"
#include "NetworkMessageTypes.h"


PyramidServer::PyramidServer():Server(){}

void PyramidServer::CreateMessage(std::string& pMessage, const std::shared_ptr<TransferSocket>& pTransferSocket){

	pMessage += std::to_string(NetworkMessageTypes::GAMEOBJECT_UPDATE) + ':';
	
	for(const auto& obj : mGameObjects){

		std::shared_lock<std::shared_mutex> lk(ThreadManager::Instance()->GetSharedMutex());

		const auto pos = std::to_string(obj->GetPos().x) + '>' + std::to_string(obj->GetPos().y) + '>' + std::to_string(obj->GetPos().z) + ')';
		const auto scale = std::to_string(obj->GetScale().x) + '>' + std::to_string(obj->GetScale().y) + '>' + std::to_string(obj->GetScale().z) + ')';
		
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
