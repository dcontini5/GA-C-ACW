#include "PyramidClient.h"

#include "CurrentSystemFrequencyMessage.h"
#include "NetworkMessageTypes.h"
#include "PyramidGame.h"
#include "ResetSceneMessage.h"
#include "ThreadManager.h"

void PyramidClient::CreateMessage(std::string& pMessage, const std::shared_ptr<TransferSocket>& pTransferSocket){


	const auto timeout = std::chrono::high_resolution_clock::now() + std::chrono::seconds(30);
	
	while (!mPlayerUpdateInfo.hasUpdated && timeout >= std::chrono::high_resolution_clock::now()) {
		//wait
	}
	
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

	pMessage += std::to_string(NetworkMessageTypes::SCENE_RESET) + ':';
	
	pMessage += std::to_string(mPlayerUpdateInfo.sceneReset);
	pMessage += '~';

	pMessage += '#';

	pMessage += std::to_string(NetworkMessageTypes::SERVER_FREQUENCY) + ':';

	pMessage += std::to_string(mSystemFrequency);
	pMessage += '~';

	pMessage += '#';
}

void PyramidClient::ParseMessage(std::string& pMessage, const std::shared_ptr<TransferSocket>& pTransferSocket) {

	

	std::string data;

	size_t messageLenght = 0;
	
	while((messageLenght = pMessage.find('#')) != std::string::npos){

		size_t msgTypeDelimeter = pMessage.find(':');

		const NetworkMessageType msgType = std::stoi(pMessage.substr(0, msgTypeDelimeter));

		auto coords = pMessage.substr(0, messageLenght);
		
		switch (msgType){

		case NetworkMessageTypes::GAMEOBJECT_UPDATE:
			{


				UpdateGameObjects(coords);
				break;
			}

		case NetworkMessageTypes::PLAYER_UPDATE:
			{

				//UpdatePlayer(coords);
				break;
			}

		case NetworkMessageTypes::SERVER_FREQUENCY:
			{

				coords.erase(0, msgTypeDelimeter + 1);

				const auto freq = std::stof(coords.substr(0, messageLenght));

				
				
			
				std::shared_ptr<Message> msg = std::make_shared<CurrentSystemFrequencyMessage>(SystemTypes::NETWORKING, freq);
				Game::Instance()->BroadcastMessage(msg);
			}

			
		default: ;
		}
		
		pMessage.erase(0, messageLenght + 1);
	}


	UpdateScene(pTransferSocket);
	//process data
	mGameObjectsUpdated.clear();


	
}

void PyramidClient::UpdateGameObjects(std::string& pUpdate){

	std::string data;

	size_t messageLenght = 0;
	
	while ((messageLenght = pUpdate.find('~')) != std::string::npos) {

		GameObjectPtr go = std::make_shared<GameObject>();
		
		//const auto pos = pUpdate.find('(');
		pUpdate.erase(0, pUpdate.find('(') + 1);
		
		auto xPos = pUpdate.substr(0, pUpdate.find('>'));
		pUpdate.erase(0, xPos.length() + 1);

		auto yPos = pUpdate.substr(0, pUpdate.find('>'));
		pUpdate.erase(0,  yPos.length() + 1);

		auto zPos = pUpdate.substr(0, pUpdate.find(')'));
		//pUpdate.erase(0, zPos.length() + 1);

		pUpdate.erase(0, pUpdate.find('(') + 1);

		auto xScale = pUpdate.substr(0, pUpdate.find('>'));
		pUpdate.erase(0, xScale.length() + 1);

		auto yScale = pUpdate.substr(0, pUpdate.find('>'));
		pUpdate.erase(0, yScale.length() + 1);

		auto zScale = pUpdate.substr(0, pUpdate.find(')'));
		
		pUpdate.erase(0, pUpdate.find('~') + 1);

		go->InitPos({ std::stof(xPos),std::stof(yPos),std::stof(zPos) });
		go->setScale({ std::stof(xScale),std::stof(yScale),std::stof(zScale) });

		mGameObjectsUpdated.push_back(std::move(go));
		
	}

	
}

void PyramidClient::UpdateScene(const std::shared_ptr<TransferSocket>& pTransferSocket){

	if(pTransferSocket->IsResetted()){

		pTransferSocket->ResetDone();
		std::shared_ptr<Message> msg = std::make_shared<ResetSceneMessage>(mGameObjectsUpdated);
		Game::Instance()->BroadcastMessage(msg);
		return;
	}

	for(size_t i = 0; i<mGameObjects.size(); i++){

		std::unique_lock<std::shared_mutex> lk(ThreadManager::Instance()->GetSharedMutex());
		mGameObjects[i]->SetPos(mGameObjectsUpdated[i]->GetNewPos());
		
	}
	
	
}

void PyramidClient::UpdatePlayer(std::string& pUpdate) {


	auto player = mTransferSocket->GetPlayer();
	
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
