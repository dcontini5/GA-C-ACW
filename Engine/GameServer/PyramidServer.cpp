#include "PyramidServer.h"
#include "ThreadManager.h"
#include "gtx/string_cast.hpp"
#include "NetworkMessageTypes.h"
#include "Game.h"
#include "UpdateFrequencyMessage.h"

PyramidServer::PyramidServer():Server(){}

void PyramidServer::CreateMessage(std::string& pMessage, const std::shared_ptr<TransferSocket>& pTransferSocket){


	pMessage += std::to_string(NetworkMessageTypes::SERVER_FREQUENCY) + ':';
		
	pMessage += std::to_string(pTransferSocket->GetAverageSend());

	pMessage += '#';
	
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

	const auto pos = std::to_string(player->GetPos().x) + '>' + std::to_string(player->GetPos().y) + '>' + std::to_string(player->GetPos().z) + ')';
	const auto rotation = std::to_string(player->GetRot().x) + '>' + std::to_string(player->GetRot().y) + '>' + std::to_string(player->GetRot().z) + ')';


	pMessage += 'P(';
	pMessage += pos;
	pMessage += 'R(';
	pMessage += rotation;
	pMessage += '~';

	pMessage += '#';
}

void PyramidServer::ParseMessage(std::string& pMessage, const std::shared_ptr<TransferSocket>& pTransferSocket){

	

	std::string data;

	size_t messageLenght = 0;

	while ((messageLenght = pMessage.find('#')) != std::string::npos) {

		size_t msgTypeDelimeter = pMessage.find(':');

		const NetworkMessageType msgType = std::stoi(pMessage.substr(0, msgTypeDelimeter));

		auto coords = pMessage.substr(0, messageLenght);

		switch (msgType) {

		case NetworkMessageTypes::PLAYER_UPDATE:
		{

			UpdatePlayer(coords, pTransferSocket);
			break;
		}

		case NetworkMessageTypes::SERVER_FREQUENCY:
		{

			coords.erase(0, msgTypeDelimeter + 1);

			const auto freq = std::stof(coords.substr(0, messageLenght));
			std::shared_ptr<Message> msg = std::make_shared<UpdateFrequencyMessage>(SystemTypes::NETWORKING, freq);
			Game::Instance()->BroadcastMessage(msg);
		}


		default:;
		}
		
		pMessage.erase(0, messageLenght + 1);
	}


	//UpdateScene(pTransferSocket);
	////process data
	//mGameObjectsUpdated.clear();



	
}


void PyramidServer::UpdatePlayer(std::string& pUpdate, const std::shared_ptr<TransferSocket>& pTransferSocket) {


	auto player = pTransferSocket->GetPlayer();

	pUpdate.erase(0, pUpdate.find('(') + 1);

	auto xPos = pUpdate.substr(0, pUpdate.find('>'));
	pUpdate.erase(0, xPos.length() + 1);

	auto yPos = pUpdate.substr(0, pUpdate.find('>'));
	pUpdate.erase(0, yPos.length() + 1);

	auto zPos = pUpdate.substr(0, pUpdate.find(')'));


	pUpdate.erase(0, pUpdate.find('(') + 1);

	auto xRot = pUpdate.substr(0, pUpdate.find('>'));
	pUpdate.erase(0, xRot.length() + 1);

	auto yRot = pUpdate.substr(0, pUpdate.find('>'));
	pUpdate.erase(0, yRot.length() + 1);

	auto zRot = pUpdate.substr(0, pUpdate.find(')'));

	pUpdate.erase(0, pUpdate.find('~') + 1);

	{
		std::unique_lock<std::shared_mutex> lk(ThreadManager::Instance()->GetSharedMutex());
		player->SetPos({ std::stof(xPos),std::stof(yPos),std::stof(zPos) });
		player->setRot({ std::stof(xRot),std::stof(xRot),std::stof(xRot) });
	}
}