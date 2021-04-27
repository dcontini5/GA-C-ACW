#include "PyramidClient.h"
#include "NetworkMessageTypes.h"
#include "ResetSceneMessage.h"
#include "ThreadManager.h"


void PyramidClient::CreateMessage(std::string& pMessage, const std::shared_ptr<TransferSocket>& pTransferSocket){

	pMessage = "culoculo\n";

	
	
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
				pMessage.erase(0, messageLenght + 1);
				break;
			}
			
		
		default: ;
		}
		
	}


	UpdateScene(pTransferSocket);
	//process data
	mGameObjectsUpdated.clear();
	//pMessage.erase(0, ++messageLenght);


	
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
